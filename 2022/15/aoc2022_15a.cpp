#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <vector> //std::vector
#include <set> //std::set
#include <utility> // std::pair, std::tuple
#include <cmath> // std::abs

int main(int argc, const char* argv[])
{
	std::vector<std::tuple<int, int, int>> sensors;
	std::set<std::pair<int, int>> beacons;

	int target_y = 2'000'000;

	if (argc >= 2)
		target_y = std::strtol(argv[1], nullptr, 10);

	std::string line;
	while (std::getline(std::cin, line))
	{
		int sensor_x, sensor_y;
		int beacon_x, beacon_y;
		sscanf_s(line.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &sensor_x, &sensor_y, &beacon_x, &beacon_y);

		const int sensor_distance = std::abs(beacon_x - sensor_x) + std::abs(beacon_y - sensor_y);

		sensors.emplace_back(sensor_x, sensor_y, sensor_distance);
		beacons.emplace(beacon_x, beacon_y);
	}

	int min_x, max_x;
	bool first = true;

	for (const auto& [x, y, distance] : sensors)
	{
		const int offset = distance - std::abs(target_y - y);
		if (offset >= 0)
		{
			const int min_x_on_row = x - offset;
			const int max_x_on_row = x + offset;

			if (first || min_x_on_row < min_x)
				min_x = min_x_on_row;

			if (first || max_x_on_row > max_x)
				max_x = max_x_on_row;

			first = false;
		}
	}

	if (first)
	{
		// we didn't find a min/max, so all are valid
		std::cout << 0;
		return 0;
	}

	int count = 0;

	for (int beacon_x = min_x; beacon_x <= max_x; beacon_x++)
	{
		if (beacons.contains({ beacon_x, target_y }))
			continue;

		bool could_contain_beacon = true;

		for (const auto& [sensor_x, sensor_y, sensor_distance] : sensors)
		{
			const int distance = std::abs(sensor_x - beacon_x) + std::abs(sensor_y - target_y);
			if (distance <= sensor_distance)
			{
				could_contain_beacon = false;
				break;
			}
		}

		if (!could_contain_beacon)
			count++;
	}

	std::cout << count;

	return 0;
}
