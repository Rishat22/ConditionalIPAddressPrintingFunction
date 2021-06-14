#ifndef CUSTOM_TYPE_TRAITS_H
#define CUSTOM_TYPE_TRAITS_H
#include <type_traits>
#include <list>
#include <vector>

template < class T>
struct is_string : std::integral_constant <bool,
									 std::is_same<std::string, T>::value ||
									 std::is_same<const char*, T>::value >{};

template<typename T, typename _ = void>
struct is_container : std::false_type {};

template<typename... Ts>
struct is_container_helper {};

template<typename T>
struct is_container< T,
		std::conditional_t< false,
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

template <typename> struct is_list : std::false_type {};
template <typename T> struct is_list<std::list<T>> : std::true_type {};
template <typename> struct is_vector : std::false_type {};
template <typename T> struct is_vector<std::vector<T>> : std::true_type {};

template <typename> struct is_tuple : std::false_type {};
template <typename... T> struct is_tuple<std::tuple<T...>> : std::true_type {};

#endif // CUSTOM_TYPE_TRAITS_H
