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
	
	std::set<int> all_possible_allergens;

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

		all_possible_allergens.insert(possibly_this_allergen.begin(), possibly_this_allergen.end());
	}

	int count = 0;
	for (const auto& food : all_foods)
		for (const int ingredient : food.ingredients())
			if (all_possible_allergens.find(ingredient) == all_possible_allergens.end())
				count++;

	std::cout << count;

	return 0;
}