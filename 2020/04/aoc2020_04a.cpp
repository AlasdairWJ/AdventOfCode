#include <cstdio>
#include <iostream>
#include <string>

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

int main(int argc, const char* argv[])
{
	int count = 0;
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
			if (field_id >= 0)
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