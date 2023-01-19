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

	int viable_area_size = 4'000'000;

	if (argc >= 2)
		viable_area_size = std::strtol(argv[1], nullptr, 10);

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

	for (int beacon_y = 0; beacon_y < viable_area_size; beacon_y++)
		for (int beacon_x = 0; beacon_x < viable_area_size; beacon_x++)
		{
			if (beacons.contains({ beacon_x, beacon_y }))
				continue;

			bool could_contain_beacon = true;

			for (const auto& [sensor_x, sensor_y, sensor_distance] : sensors)
			{
				const int y_distance = std::abs(sensor_y - beacon_y);
				const int distance = std::abs(sensor_x - beacon_x) + y_distance;
				if (distance <= sensor_distance)
				{
					could_contain_beacon = false;
					beacon_x = sensor_x + (sensor_distance - y_distance);
					break;
				}
			}

			if (could_contain_beacon)
			{
				std::cout << beacon_x * 4'000'000ll + beacon_y;
				return 0;
			}
	}

	return 1;
}
