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

	template<>
	void print(const std::string value);

	template<class... T>
	void print(const std::tuple<T...>& _tup);

	/*
	template<typename T>
	void print(T value_container)
	*/

private:
	template<class TupType, size_t... I>
	void print(const TupType& _tup, std::index_sequence<I...>);

	template <typename T, size_t size>
	void printContainerAsIp(const std::array<T, size> bytes_array);

	template <typename T>
	std::array<uint8_t, sizeof(T)> reinterpretToBytes(const T value);

};

template <typename T>
void InterpreterToAddress::print(const T value)
{
	const auto bytes_array = reinterpretToBytes(value);
	printContainerAsIp(bytes_array);
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
void InterpreterToAddress::printContainerAsIp(const std::array<T, size> bytes_array)
{
	size_t index = 0;
	for(const auto byte_value : bytes_array)
	{
		std::cout << static_cast<size_t>(byte_value);
		if(++index < bytes_array.size())
			std::cout << ".";
	}
	std::cout << std::endl;
}

template<>
void InterpreterToAddress::print(const std::string value)
{
	std::cout << value << std::endl;
};

template<class... T>
void InterpreterToAddress::print(const std::tuple<T...>& _tup)
{
	print(_tup, std::make_index_sequence<sizeof...(T)>());
}


template<class TupType, size_t... I>
void InterpreterToAddress::print(const TupType& _tup, std::index_sequence<I...>)
{
	(..., (std::cout << (I == 0 ? "" : ".") << std::get<I>(_tup)));
	std::cout << std::endl;
}

#endif // IPInterpreter_H
