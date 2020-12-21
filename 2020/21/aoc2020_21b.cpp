#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>

int next_ingredient_id = 0;
std::vector<std::string> ingredient_names;
std::map<std::string, int> ingredient_id_map;

int next_allergen_id = 0;
std::vector<std::string> allergen_names;
std::map<std::string, int> allergen_id_map;

struct food_t
{
	std::set<int> m_ingredients;
	std::set<int> m_allergens;

	bool contains_allergen(int id) const
	{
		return m_allergens.find(id) != m_allergens.end();
	}

	bool contains_ingredient(int id) const
	{
		return m_ingredients.find(id) != m_ingredients.end();
	}
};

void intersect_with(std::set<int>& A, const std::set<int>& B)
{
	auto it = A.begin();
	while (it != A.end())
	{
		if (B.find(*it) == B.end())
			it = A.erase(it);
		else
			++it;
	}
}

int main(int argc, const char* argv[])
{
	std::vector<food_t> all_foods;

	std::string line;
	while (std::getline(std::cin, line))
	{
		food_t food;

		size_t offset = 0;
		while (line[offset] != '(')
		{
			const size_t next = line.find_first_of(' ', offset);

			const std::string ingredient = line.substr(offset, next - offset);

			int ingredient_id = next_ingredient_id;

			const auto pair = ingredient_id_map.emplace(ingredient, ingredient_id);

			if (pair.second)
			{
				// new ingredient
				ingredient_names.push_back(ingredient);
				next_ingredient_id++;
			}
			else
			{
				const auto& it = pair.first;
				ingredient_id = it->second;
			}

			food.m_ingredients.insert(ingredient_id);

			offset = next + 1;
		}

		offset += _countof("contains ");

		while (offset < (int)line.size())
		{
			const size_t next = line.find_first_of(",)", offset);

			const std::string allergen = line.substr(offset, next - offset);

			int allergen_id = next_allergen_id;

			const auto pair = allergen_id_map.emplace(allergen, allergen_id);
			
			if (pair.second)
			{
				// new ingredient
				allergen_names.push_back(allergen);
				next_allergen_id++;
			}
			else
			{
				const auto& it = pair.first;
				allergen_id = it->second;
			}

			food.m_allergens.insert(allergen_id);

			offset = next + 2;
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

			if (possibly_this_allergen.empty())
			{
				possibly_this_allergen.insert(food.m_ingredients.begin(), food.m_ingredients.end());
			}
			else
			{
				intersect_with(possibly_this_allergen, food.m_ingredients);
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

	for (const auto& pair : solution)
		printf("%s,", pair.second.c_str());

	printf("\b "); // yup

	return 0;
}