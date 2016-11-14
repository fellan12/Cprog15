#include <iostream>
#include "hello.h"

using namespace std;

void hello (const char * name, int count) {
	if (count != 0) {
		std::cout << "Hello,";
		for (int c = 0; c < count; c++) {
			std::cout << " " << name;
		}
		std::cout << "!\n";
	}
}


std::pair<const char *, int> parse_args (int argc, char * argv[]) {
	if (argc == 1)
		return std::make_pair ("world", 1);
	if (argc == 2)
		return std::make_pair (argv[1], 1);
	if (argc == 3) {
		int times;
		if (std::string(argv[2]).compare("0")) { //true if argv[2] != "0"
			times = std::atoi (argv[2]);
			if (times <= 0) {//if times is <= 0 here then it must either have been below 0 to start with or it was not an integer at all
				times = -1;
				std::cerr << "error: 2nd argument must be an integral greater than zero!\n";
			}
			return std::make_pair (argv[1], times);
		} else {
			times = 0;
		}
		return std::make_pair (argv[1], times);
	}
	std::cerr << "error: Too many arguments!\n";
	return std::make_pair ("", -1);
}