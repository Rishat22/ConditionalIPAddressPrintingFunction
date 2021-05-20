#include <iostream>
#include <algorithm>
#include <string>
#include <array>
#include <list>

template <typename T>
std::array<uint8_t, sizeof(T)> reinterpretToBytes(const T value)
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


template <typename T>
void printContainerAsIp(const T& bytes_array)
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

template <typename T>
void print(T value)
{
	const auto bytes_array = reinterpretToBytes(value);
	printContainerAsIp(bytes_array);
}

template<>
void print(const std::string value)
{
	std::cout << value << std::endl;
};

template<class TupType, size_t... I>
void print(const TupType& _tup, std::index_sequence<I...>)
{
	(..., (std::cout << (I == 0 ? "" : ".") << std::get<I>(_tup)));
	std::cout << std::endl;
}

template<class... T>
void print(const std::tuple<T...>& _tup)
{
	print(_tup, std::make_index_sequence<sizeof...(T)>());
}

template <typename T>
void print(const std::vector<T>& value_container)
{
	printContainerAsIp(value_container);
}

template <typename T>
void print(const std::list<T>& value_container)
{
	printContainerAsIp(value_container);
}

/* An attempt to combine a vector and a list into one case.
template <class T>
struct is_list: std::false_type {};

template <class T>
struct is_list<typename std::list<T>>: std::true_type { };

template <class T>
struct is_vector: std::false_type { };

template <class T>
struct is_vector<typename std::vector<T>>: std::true_type { };
template<typename T, class = std::enable_if_t<is_list<T>::value || is_vector<T>::value>>
void print(T value_container)
{
	std::cout << "is list" << std::endl;
	for(const auto byte_value : value_container)
	{
		std::cout << static_cast<size_t>(byte_value) << ".";
	}
	std::cout << std::endl;
};
*/

int main()
{
	print( char{-1} );
	print( short{0} );
	print( int{2130706433} );
	print( long{8875824491850138409} );

	print( std::string("Hello, World!") );

	print( std::vector<short>{100, 200, 300, 400} );
	print( std::list<short>{400, 300, 200, 100} );

	print( std::make_tuple(123, 456, 789, 0) );

	return 0;
}
