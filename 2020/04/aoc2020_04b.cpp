#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>

int field_to_id(const char* field)
{
	if (strcmp(field, "byr") == 0) return 0;
	if (strcmp(field, "iyr") == 0) return 1;
	if (strcmp(field, "eyr") == 0) return 2;
	if (strcmp(field, "hgt") == 0) return 3;
	if (strcmp(field, "hcl") == 0) return 4;
	if (strcmp(field, "ecl") == 0) return 5;
	if (strcmp(field, "pid") == 0) return 6;
	if (strcmp(field, "cid") == 0) return 7;
	return -1;
}

bool validate(const int field_id, const char* value)
{
	switch (field_id)
	{
	case 0: // byr
	{
		const int year = std::strtol(value, nullptr, 10);
		return year >= 1920 && year <= 2002;
	}
	case 1: // iyr
	{
		const int year = std::strtol(value, nullptr, 10);
		return year >= 2010 && year <= 2020;
	}
	case 2: // eyr
	{
		const int year = std::strtol(value, nullptr, 10);
		return year >= 2020 && year <= 2030;
	}
	case 3: // hgt
	{
		int x;
		char unit[10];
		if (sscanf_s(value, "%d%s", &x,
			unit, (unsigned)_countof(unit)) != 2)
			return false;

		if (strcmp(unit, "in") == 0)
			return 59 <= x && x <= 76;
		else if (strcmp(unit, "cm") == 0)
			return 150 <= x && x <= 193;
		return false;
	}
	case 4: // hcl
	{
		if (value[0] != '#')
			return false;

		if (strlen(value) != 7)
			return false;

		for (int i = 1; i < 7; i++)
			if (!isxdigit(value[i]))
				return false;

		return true;
	}
	case 5: // ecl
	{
		if (strcmp(value, "amb") == 0) return true;
		if (strcmp(value, "blu") == 0) return true;
		if (strcmp(value, "brn") == 0) return true;
		if (strcmp(value, "gry") == 0) return true;
		if (strcmp(value, "grn") == 0) return true;
		if (strcmp(value, "hzl") == 0) return true;
		if (strcmp(value, "oth") == 0) return true;
		return false;
	}
	case 6: // pid
	{
		if (strlen(value) != 9)
			return false;

		for (int i = 0; i < 9; i++)
			if (!isdigit(value[i]))
				return false;

		return true;
	}
	case 7:// cid
		return true;

	default:
		return false;
	}
}

int main(int argc, const char* argv[])
{
	int count = 0;
	int line_count = 0;

	unsigned field_mask = 0;

	char line[128];
	while (gets_s(line))
	{
		if (line[0] == '\0')
		{
			if ((field_mask & 0b1111111) == 0b1111111)
				count++;

			field_mask = 0;
			continue;
		}

		int offset = 0, n;
		char field[32], value[32];
		while (sscanf_s(&line[offset], "%[^:]:%[^ ]%n",
				field, (unsigned)_countof(field),
				value, (unsigned)_countof(value), &n) == 2)
		{
			const int field_id = field_to_id(field);
			if (field_id >= 0 && validate(field_id, value))
				field_mask |= 1 << field_id;

			offset += n;
			if (line[offset] == '\0')
				break;
			offset++;
		}
	}

	if ((field_mask & 0b1111111) == 0b1111111)
		count++;

	printf("%d", count);

	return 0;
}