#include <iostream>
#include "interpreter_to_address.hpp"

int main()
{
	InterpreterToAddress ip_interpreter;

	std::cout << "char{-1}: ";
	ip_interpreter.print(char{-1});

	std::cout << "short{0}: ";
	ip_interpreter.print(short{0});

	std::cout << "int{2130706433}: ";
	ip_interpreter.print(int{2130706433});

	std::cout << "long{8875824491850138409}: ";
	ip_interpreter.print(long{8875824491850138409});

	return 0;
}
