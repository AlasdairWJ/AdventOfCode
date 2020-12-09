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
	while (gets_s(line, (unsigned)_countof(line)))
	{
		const int line_length = strlen(line);

		if (line_length == 0)
		{
			if ((field_mask & 0b1111111) == 0b1111111)
				count++;

			field_mask = 0;
			continue;
		}

		int offset = 0;
		
		do
		{
			int n;
			char field[32], value[32];
			if (sscanf_s(&line[offset], "%[^:]:%[^ ]%n",
				field, (unsigned)_countof(field),
				value, (unsigned)_countof(value), &n) != 2)
				break;

			const int field_id = field_to_id(field);
			if (field_id >= 0)
				field_mask |= 1 << field_id;

			offset += n + 1;
		}
		while (offset < line_length);
	}

	if ((field_mask & 0b1111111) == 0b1111111)
		count++;

	printf("%d", count);

	return 0;
}