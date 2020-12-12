#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>

using orbit_map_type = std::map<std::string, std::string>;

int main(int argc, const char* argv[])
{
	orbit_map_type orbit_map;

	char object[4], satellite[4];
	while (scanf_s("%3s)%3s\n", object, (unsigned)_countof(object), satellite, (unsigned)_countof(satellite)) == 2)
		orbit_map.emplace(satellite, object);

	std::vector<orbit_map_type::iterator> you_to_com_path;

	for (auto it = orbit_map.find("YOU"); it != orbit_map.end() && it->first != "COM"; it = orbit_map.find(it->second))
		you_to_com_path.push_back(it);

	int count = 0;
	for (auto it = orbit_map.find("SAN"); it != orbit_map.end() && it->first != "COM"; it = orbit_map.find(it->second), count++)
		for (int n = 0; n < you_to_com_path.size(); n++)
			if (you_to_com_path[n] == it)
			{
				printf("%d", n + count - 2);
				return 0;
			}

	return 1;
}