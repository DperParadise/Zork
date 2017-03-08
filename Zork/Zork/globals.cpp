#include "globals.h"
#include <memory>

 
void ParseInput(const char *input, char *output)
{
	bool blank_read = true;
	int i = 0;
	int last_pos = 0;
	while (input[i] != '\0')
	{
		if (input[i] != ' ')
		{
			output[last_pos] = input[i];						
			blank_read = false;
			last_pos++;
		}
		else
		{
			if (!blank_read)
			{
				output[last_pos] = input[i];
				blank_read = true;
				last_pos++;
			}
		}
		i++;
	}
	if (output[last_pos - 1] == ' ')
		output[last_pos - 1] = '\0';
	else
		output[last_pos] = '\0';
}

std::string ToUpper(std::string s1)
{
	std::string copy = s1;
	std::transform(copy.begin(), copy.end(), copy.begin(), ::toupper);
	return copy;
}

