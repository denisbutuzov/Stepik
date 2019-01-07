#include <iostream>
#include <string>
#include <regex>
#include <cmath>

long long&& triangular_number(long long&& n)
{
	auto result = (sqrt(n*8+1)-1)/2;
	long long number = 0;

	if(result - static_cast<long long>(result) == 0)
	{
		number = static_cast<long long>(result);
	}

	return std::move(number);
}

int main(int argc, char* argv[])
{
	std::string in_str;
	std::cin >> in_str;

	std::regex true_input_regex("^\\+*\\d+$");
	if(std::regex_match(in_str, true_input_regex))
	{
		auto n = stoll(in_str);
		std::cout << triangular_number(std::move(n)) << std::endl;
	}
	else
	{
		std::cout << 0 << std::endl;
	}

	return 0;
}
