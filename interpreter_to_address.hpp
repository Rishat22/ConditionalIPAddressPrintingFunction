#ifndef IPInterpreter_H
#define IPInterpreter_H
#include <iostream>
#include <algorithm>
#include <string>
#include <array>

class InterpreterToAddress
{
public:
	InterpreterToAddress() = default;

	template <typename T>
	void print(const T value);

private:
	template <typename T, size_t size>
	void printArrayAsIp(const std::array<T, size> bytes_array);

	template <typename T>
	std::array<uint8_t, sizeof(T)> reinterpretToBytes(const T value);

};

template <typename T>
void InterpreterToAddress::print(const T value)
{
	const auto bytes_array = reinterpretToBytes(value);
	printArrayAsIp(bytes_array);
}

template <typename T>
std::array<uint8_t, sizeof(T)> InterpreterToAddress::reinterpretToBytes(const T value)
{
	std::array<uint8_t, sizeof(T)> bytes_array;
	uint8_t byte_index = 0;
	std::generate(bytes_array.rbegin(), bytes_array.rend(),
				  [&value, &byte_index]()
	{
		return value >> (byte_index++ * 8);
	});

	return bytes_array;
}


template <typename T, size_t size>
void InterpreterToAddress::printArrayAsIp(const std::array<T, size> bytes_array)
{
	for(const auto byte_value : bytes_array)
	{
		std::cout << static_cast<size_t>(byte_value) << ".";
	}
	std::cout << std::endl;
}

#endif // IPInterpreter_H
