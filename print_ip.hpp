/**
 ******************************************************************************
* \file print_ip.hpp
*   Description: This file implements class print_ip.
*		 The class provides the ability to print
*		 any type by interpreting it to an imaginary address.
*
*   Rev 1.0 21 May 2021 Zakirov Rishat
*   Initial revision
*/

#include <iostream>
#include <algorithm>
#include <type_traits>
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

/**
 *******************************************************************************
 * * \brief Interprets the entered value as an imaginary ip-address
 *
 *   \par Name:
 *              void print_ip(T value) \n
 *
 *   \par Purpose:
 * 				Interprets the entered value as an imaginary ip-address.\n
 *
 *   \par Inputs:
 * 				T value - any numeric type.\n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				None \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
template <typename T>
auto print_ip(T value) -> decltype(
		std::declval<
		typename std::enable_if<std::is_convertible<T, uint8_t>::value, T>::type
		  >(), void() )
{
	const auto bytes_array = reinterpretToBytes(value);
	printContainerAsIp(bytes_array);
}

/**
 *******************************************************************************
 * * \brief Interprets the entered value as an imaginary ip-address
 *
 *   \par Name:
 *              void print_ip(const std::string value) \n
 *
 *   \par Purpose:
 * 				Interprets the entered value as an imaginary ip-address.\n
 *
 *   \par Inputs:
 * 				std::string value - string value.\n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				None \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
template < class T>
struct is_string : std::integral_constant <bool,
									 std::is_same<std::string, T>::value ||
									 std::is_same<const char*, T>::value >{};
template <typename T>
auto print_ip(const std::string value) -> decltype(
		std::declval<
		typename std::enable_if<is_string<T>::value, T>::type
		  >(), void() )
{
	std::cout << value << std::endl;
}

template <typename> struct is_tuple : std::false_type {};
template <typename... T> struct is_tuple<std::tuple<T...>> : std::true_type {};

template<class TupType, size_t... index>
void print_tuple(const TupType& tuple_value, std::index_sequence<index...>)
{
	(..., (std::cout << (index == 0 ? "" : ".") << std::get<index>(tuple_value)));
	std::cout << std::endl;
}

template<class... T>
void print_tuple(const std::tuple<T...>& tuple_value)
{
	print_tuple(tuple_value, std::make_index_sequence<sizeof...(T)>());
}

/**
 *******************************************************************************
 * * \brief Interprets the entered value as an imaginary ip-address
 *
 *   \par Name:
 *              void print_ip(const std::tuple<T...>& tuple_value) \n
 *
 *   \par Purpose:
 * 				Interprets the entered value as an imaginary ip-address.\n
 *
 *   \par Inputs:
 * 				std::tuple<T...>& tuple_value - std::tuple value.\n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				None \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
template<typename T>
auto print_ip(T value) -> decltype(
		std::declval<
		typename std::enable_if<is_tuple<T>::value, T>::type
		  >(), void() )
{
	print_tuple(value);
}

template<typename T, typename _ = void>
struct is_container : std::false_type {};

template<typename... Ts>
struct is_container_helper {};

template<typename T>
struct is_container<
		T,
		std::conditional_t<
			false,
			is_container_helper<
				typename T::value_type,
				typename T::size_type,
				typename T::allocator_type,
				typename T::iterator,
				typename T::const_iterator,
				decltype(std::declval<T>().size()),
				decltype(std::declval<T>().begin()),
				decltype(std::declval<T>().end()),
				decltype(std::declval<T>().cbegin()),
				decltype(std::declval<T>().cend())
				>,
			void
			>
		> : public std::true_type {};

template <typename T>
auto print_ip(T value) -> decltype(
		std::declval<
		typename std::enable_if<is_container<T>::value, T>::type
		  >(), void() )
{
	printContainerAsIp(value);
}
