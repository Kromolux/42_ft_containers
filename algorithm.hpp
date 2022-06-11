/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:38:17 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/11 19:19:44 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterator.hpp"

namespace ft
{
	
template <class InputIterator1, class InputIterator2>
bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	#if DEBUG
		std::cout << COLOR_YELLOW << "[equal] function template 1 called.\n" << COLOR_DEFAULT;
	#endif
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!(*first1 == *first2))
			return (false);
	}
	return (true);
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
	#if DEBUG
		std::cout << COLOR_YELLOW << "[equal] function template 2 called.\n" << COLOR_DEFAULT;
	#endif
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!(pred(*first1 == *first2)))
			return (false);
	}
	return (true);
}

template <class T>
void	swap(T & a, T & b)
{
	#if DEBUG
		std::cout << COLOR_YELLOW << "[swap] function template called.\n" << COLOR_DEFAULT;
	#endif
	T	tmp(a);

	a = b;
	b = tmp;
}

//https://cplusplus.com/reference/algorithm/lexicographical_compare/?kw=lexicographical_compare
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
{
	#if DEBUG
		std::cout << COLOR_YELLOW << "[lexicographical_compare] function template 1 called.\n" << COLOR_DEFAULT;
	#endif
	for (; first1 != last1; ++first1, ++first2)
	{
		if (first2 == last2 || *first2 < *first1)
			return (false);
		else if (*first1 < *first2)
			return (true);
	}
	return (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
{
	#if DEBUG
		std::cout << COLOR_YELLOW << "[lexicographical_compare] function template 2 called.\n" << COLOR_DEFAULT;
	#endif
	for (; first1 != last1; ++first1, ++first2)
	{
		if (first2 == last2 || comp(*first2, *first1))
			return (false);
		else if (comp(*first1, *first2))
			return (true);
	}
	return (first2 != last2);
}

}