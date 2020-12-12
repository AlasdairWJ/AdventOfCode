#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>

int main(int argc, char const *argv[])
{
	std::map<std::string, std::string> orbit_map;

	char object[4], satellite[4];
	while (scanf_s("%3s)%3s\n", object, (unsigned)_countof(object), satellite, (unsigned)_countof(satellite)) == 2)
		orbit_map.emplace(satellite, object);

	int count = 0;

	for (auto target_it = orbit_map.begin(); target_it != orbit_map.end(); ++target_it)
		for (auto it = target_it; it != orbit_map.end() && it->first != "COM"; it = orbit_map.find(it->second))
			count++;

	printf("%d", count);
	return 0;
}