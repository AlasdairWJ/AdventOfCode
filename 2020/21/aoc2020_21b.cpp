#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

int next_ingredient_id = 0;
std::vector<std::string> ingredient_names;
std::map<std::string, int> ingredient_id_map;

int next_allergen_id = 0;
std::vector<std::string> allergen_names;
std::map<std::string, int> allergen_id_map;

struct Food
{
	void add_ingredient(const int id)
	{
		m_ingredients.insert(id);
	}

	bool contains_ingredient(const int id) const
	{
		return m_ingredients.find(id) != m_ingredients.end();
	}

	void add_allergen(const int id)
	{
		m_allergens.insert(id);
	}

	bool contains_allergen(const int id) const
	{
		return m_allergens.find(id) != m_allergens.end();
	}

	auto ingredients() const { return m_ingredients; }

private:
	std::set<int> m_ingredients;
	std::set<int> m_allergens;
};

int main(int argc, const char* argv[])
{
	std::vector<Food> all_foods;

	std::string line;
	while (std::getline(std::cin, line))
	{
		Food food;

		std::stringstream ss(line);

		while (ss.peek() != '(')
		{
			std::string ingredient;
			ss >> ingredient;

			const auto [it, is_new_ingredient] = ingredient_id_map.emplace(ingredient, next_ingredient_id);

			if (is_new_ingredient)
			{
				ingredient_names.push_back(ingredient);
				next_ingredient_id++;
			}

			food.add_ingredient(it->second);

			ss.ignore(1); // ' '
		}

		std::string ignore;
		ss >> ignore; // "(contains"

		bool done_reading_allergens = false;
		while (!done_reading_allergens)
		{
			std::string allergen;
			ss >> allergen;

			if (allergen.back() == ')')
				done_reading_allergens = true;

			allergen.pop_back();

			const auto [it, is_new_allergen] = allergen_id_map.emplace(allergen, next_allergen_id);
			
			if (is_new_allergen)
			{
				// new ingredient
				allergen_names.push_back(allergen);
				next_allergen_id++;
			}

			food.add_allergen(it->second);
		}

		all_foods.push_back(food);
	}
	
	std::vector<std::set<int>> allergen_candidates;

	for (int id = 0; id < next_allergen_id; id++)
	{
		std::set<int> possibly_this_allergen;

		for (const auto& food : all_foods)
		{
			if (!food.contains_allergen(id))
				continue;

			const auto& ingredients = food.ingredients();
			if (possibly_this_allergen.empty())
			{
				possibly_this_allergen.insert(ingredients.begin(), ingredients.end());
			}
			else
			{
				for (auto it = possibly_this_allergen.begin(); it != possibly_this_allergen.end();)
				{
					if (ingredients.find(*it) == ingredients.end())
						it = possibly_this_allergen.erase(it);
					else
						++it;
				}
			}
		}

		allergen_candidates.push_back(possibly_this_allergen);
	}

	std::set<std::pair<std::string, std::string>> solution;

	for (int i = 0; i < next_allergen_id; i++)
	{
		int solved_allergen_id;
		int solved_ingredient_id;

		for (int id = 0; id < next_allergen_id; id++)
		{
			const auto& candidates = allergen_candidates[id];
			if (candidates.size() == 1)
			{
				solved_allergen_id = id;
				solved_ingredient_id = *candidates.begin();
				break;
			}
		}

		solution.emplace(allergen_names[solved_allergen_id], ingredient_names[solved_ingredient_id]);

		for (auto& candidates : allergen_candidates)
			candidates.erase(solved_ingredient_id);
	}

	auto it = solution.begin();
	std::cout << it->second;
	for (++it; it != solution.end(); ++it)
		std::cout << ',' << it->second;

	return 0;
}