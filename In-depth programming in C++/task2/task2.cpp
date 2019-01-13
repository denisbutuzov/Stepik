#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <exception>
#include <regex>

std::pair<int, std::vector<double>> parse_string(std::string &&string)
{
	std::string delimiter(" ");
	std::size_t pos;

	double number = -1;
	std::vector<double> parsed_sequence;
	try
	{
		while((pos = string.find(delimiter)) != std::string::npos)
		{
			if(number == -1)
			{
				number = std::stod(string.substr(0, pos));
				if(number - static_cast<int>(number) != 0)
				{
					number = 0;
				}
			}
			else
			{
				parsed_sequence.push_back(std::stod(string.substr(0, pos)));
			}
			string.erase(0, pos + delimiter.length());
		}
		parsed_sequence.push_back(std::stod(string));
	}
	catch(std::exception const &e)
	{
		number = 0;
	}

	return std::move(std::pair<int, std::vector<double>> {static_cast<int>(number), parsed_sequence});
}

std::pair<int, int> find_sequence(std::vector<double>::const_iterator begin,
                                  std::vector<double>::const_iterator end)
{
	int temp_count = 1;
	int max_count = 0;
	auto temp_pos = begin;
	decltype(temp_pos) max_pos;
	for(auto it = begin; it != (end - 1); it++)
	{
		if(*it <= *(it + 1))
		{
			++temp_count;
		}
		else
		{
			if(max_count < temp_count)
			{
				max_count = temp_count;
				max_pos = temp_pos;
			}
			temp_count = 1;
			temp_pos = std::find(max_pos, end, *it) + 1;
		}
	}
	if(max_count < temp_count)
	{
		max_count = temp_count;
		max_pos = temp_pos;
	}

	return std::move(std::pair<int, int> {max_count, max_pos - begin + 1});
}

int main(int argc, char *argv[])
{
	std::string str;
	std::getline(std::cin, str);

	auto parsed_string = parse_string(std::move(str));
	if(parsed_string.first < 2 || parsed_string.second.size() < parsed_string.first)
	{
		std::cout << "[error]" << std::endl;
	}
	else
	{
		auto sequence = find_sequence(parsed_string.second.cbegin(),
                                              parsed_string.second.cbegin() + parsed_string.first);

		if(sequence.first < 2)
		{
			std::cout << 0 << std::endl;
		}
		else
		{
			std::cout << sequence.first << " " << sequence.second << std::endl;
		}
	}

	return 0;
}
