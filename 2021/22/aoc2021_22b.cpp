#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Cuboid
{
	int left, right, front, back, bottom, top;

	__int64 area() const
	{
		return static_cast<__int64>(right - left) * 
			   static_cast<__int64>(back - front) * 
			   static_cast<__int64>(top - bottom);
	}
};

bool intersects(const Cuboid& a, const Cuboid& b)
{
	return a.right > b.left && a.left < b.right &&
		   a.back > b.front && a.front < b.back && 
		   a.top > b.bottom && a.bottom < b.top;
}

int main(int argc, const char* argv[])
{
	std::vector<Cuboid> cuboids;

	std::string line;
	while (std::getline(std::cin, line) && !line.empty())
	{
		Cuboid new_cuboid = {};

		char active_str[8];
		sscanf_s(line.c_str(), "%s x=%d..%d,y=%d..%d,z=%d..%d",
				 active_str, 8u,
				 &new_cuboid.left, &new_cuboid.right,
				 &new_cuboid.front, &new_cuboid.back,
				 &new_cuboid.bottom, &new_cuboid.top);

		new_cuboid.right++;
		new_cuboid.back++;
		new_cuboid.top++;

		const bool active = (std::string(active_str) == "on");

		for (auto it = cuboids.begin(); it != cuboids.end(); )
		{
			const auto cuboid = *it;

			if (!intersects(cuboid, new_cuboid))
			{
				++it;
				continue;
			}

			it = cuboids.erase(it);

			if (new_cuboid.top < cuboid.top)
			{
				Cuboid top_cuboid;
				top_cuboid.left   = cuboid.left;
				top_cuboid.right  = cuboid.right;
				top_cuboid.front  = cuboid.front;
				top_cuboid.back   = cuboid.back;
				top_cuboid.bottom = new_cuboid.top;
				top_cuboid.top    = cuboid.top;
				it = cuboids.insert(it, top_cuboid) + 1;
			}

			if (new_cuboid.bottom > cuboid.bottom)
			{
				Cuboid bottom_cuboid;
				bottom_cuboid.left   = cuboid.left;
				bottom_cuboid.right  = cuboid.right;
				bottom_cuboid.front  = cuboid.front;
				bottom_cuboid.back   = cuboid.back;
				bottom_cuboid.bottom = cuboid.bottom;
				bottom_cuboid.top    = new_cuboid.bottom;
				it = cuboids.insert(it, bottom_cuboid) + 1;
			}
			
			if (new_cuboid.back < cuboid.back)
			{
				Cuboid back_cuboid;
				back_cuboid.left   = cuboid.left;
				back_cuboid.right  = cuboid.right;
				back_cuboid.front  = new_cuboid.back;
				back_cuboid.back   = cuboid.back;
				back_cuboid.bottom = std::max(new_cuboid.bottom, cuboid.bottom);
				back_cuboid.top    = std::min(new_cuboid.top, cuboid.top);
				it = cuboids.insert(it, back_cuboid) + 1;
			}
			 
			if (new_cuboid.front > cuboid.front)
			{
				Cuboid front_cuboid;
				front_cuboid.left   = cuboid.left;
				front_cuboid.right  = cuboid.right;
				front_cuboid.front  = cuboid.front;
				front_cuboid.back   = new_cuboid.front;
				front_cuboid.bottom = std::max(new_cuboid.bottom, cuboid.bottom);
				front_cuboid.top    = std::min(new_cuboid.top, cuboid.top);
				it = cuboids.insert(it, front_cuboid) + 1;
			}
			
			if (new_cuboid.right < cuboid.right)
			{
				Cuboid right_cuboid;
				right_cuboid.left   = new_cuboid.right;
				right_cuboid.right  = cuboid.right;
				right_cuboid.front  = std::max(new_cuboid.front, cuboid.front);
				right_cuboid.back   = std::min(new_cuboid.back, cuboid.back);
				right_cuboid.bottom = std::max(new_cuboid.bottom, cuboid.bottom);
				right_cuboid.top    = std::min(new_cuboid.top, cuboid.top);
				it = cuboids.insert(it, right_cuboid) + 1;
			}
			
			if (new_cuboid.left > cuboid.left)
			{
				Cuboid left_cuboid;
				left_cuboid.left   = cuboid.left;
				left_cuboid.right  = new_cuboid.left;
				left_cuboid.front  = std::max(new_cuboid.front, cuboid.front);
				left_cuboid.back   = std::min(new_cuboid.back, cuboid.back);
				left_cuboid.bottom = std::max(new_cuboid.bottom, cuboid.bottom);
				left_cuboid.top    = std::min(new_cuboid.top, cuboid.top);
				it = cuboids.insert(it, left_cuboid) + 1;
			}
		}

		if (active)
			cuboids.push_back(new_cuboid);
	}

	__int64 count = 0;

	for (const auto& cuboid : cuboids)
		count += cuboid.area();

	std::cout << count;

	return 0;
}