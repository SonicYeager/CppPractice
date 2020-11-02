#pragma once
#include "InternalTypes.h"

namespace TOOLBOX
{
	//template<typename T>
	//concept iteratable = !std::is_empty_v<T> && requires(T t)
	//{
	//	std::begin(t) != std::end(t);
	//	{std::begin(t)} -> std::random_access_iterator<T>;
	//};

	// To allow ADL with custom begin/end

	template<typename Type>
	concept serializeable =
		!std::is_empty_v<Type> &&
		std::is_object_v<std::remove_reference_t<Type>>;

	using std::begin;
	using std::end;

	template <typename T>
	auto is_iterable_impl(int)
		-> decltype (
			begin(std::declval<T&>()) != end(std::declval<T&>()), // begin/end and operator !=
			void(), // Handle evil operator ,
			++std::declval<decltype(begin(std::declval<T&>()))&>(), // operator ++
			void(*begin(std::declval<T&>())), // operator*
			std::true_type{});

	template <typename T>
	std::false_type is_iterable_impl(...);
}