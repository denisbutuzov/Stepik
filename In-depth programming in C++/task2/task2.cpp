#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <utility>
#include <regex>

void replace_all_substrings_in_string(std::string &string, 
				      const std::string &old_substring,
				      const std::string &new_substring)
{
	std::size_t pos;

	while((pos = string.find(old_substring)) != std::string::npos)
	{
		string.replace(pos, old_substring.length(), new_substring);
	}
}

std::list<std::string> split_string(std::string &&string)
{
	std::string delimiter(" ");
	std::size_t pos;
	std::list<std::string> splitted_string;

	while((pos = string.find(delimiter)) != std::string::npos)
	{
		splitted_string.push_back(string.substr(0, pos));
		string.erase(0, pos + delimiter.length());
	}
	splitted_string.push_back(string);

	return std::move(splitted_string);
}

std::tuple<bool, int, std::vector<double>> parse_string(std::list<std::string> &&string_list)
{
	bool valid_string = true;
	int number_elements;
	std::vector<double> elements;
	
	if(std::regex_match(string_list.front(), std::regex("^\\+{0,1}\\d+$")))
	{
		number_elements = std::stoi(string_list.front());
		string_list.pop_front();

		while(string_list.size() > 0)
		{
			if(std::regex_match(string_list.front(),
					    std::regex("^[-+]?[0-9]*[.,]?[0-9]+(?:[eE][-+]?[0-9]+)?$")))
			{
				elements.push_back(std::stod(string_list.front()));
				string_list.pop_front();
			}
			else
			{
				valid_string = false;
				break;
			}
		}
	}
	else
	{
		valid_string = false;
	}

	return std::move(std::make_tuple(valid_string, number_elements, elements));
}

std::pair<int, int> find_sequence(std::vector<double>::const_iterator begin,
                                  std::vector<double>::const_iterator end)
{
	int temp_max_count = 1;
	int max_count = 0;
	int temp_max_pos = 0;
	int max_pos = 0;
	for(auto it = begin; it != (end - 1); it++)
	{
		if(*it <= *(it + 1))
		{
			++temp_max_count;
		}
		else
		{
			if(max_count < temp_max_count)
			{
				max_count = temp_max_count;
				max_pos = temp_max_pos;
			}
			temp_max_count = 1;
			temp_max_pos = std::distance(begin, it) + 1;
		}
	}
	if(max_count < temp_max_count)
	{
		max_count = temp_max_count;
		max_pos = temp_max_pos;
	}

	return std::move(std::make_pair(max_count, max_pos + 1));
}

int main(int argc, char *argv[])
{
	std::string str;
	std::getline(std::cin, str);

	replace_all_substrings_in_string(str, "\\n", " ");
	std::list<std::string> splitted_string = split_string(std::move(str));


	bool valid;
	int number;
	std::vector<double> elements;

	std::tie(valid, number, elements) = parse_string(std::move(splitted_string));
	if(!valid || number < 2 || number > elements.size())
	{
		std::cout << "[error]" << std::endl;
	}
	else
	{
		auto sequence = find_sequence(elements.cbegin(),
                                              elements.cbegin() + number);

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
