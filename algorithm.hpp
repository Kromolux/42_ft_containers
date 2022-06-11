/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:38:17 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/11 15:10:25 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterator.hpp"

namespace ft
{
	
template <class InputIterator1, class InputIterator2>
bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	#if DEBUG
		std::cout << COLOR_YELLOW << "[equal] function template called.\n" << COLOR_DEFAULT;
	#endif
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!(*first1 == *first2))
			return (false);
	}
	return (true);
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
	#if DEBUG
		std::cout << COLOR_YELLOW << "[equal] function template called.\n" << COLOR_DEFAULT;
	#endif
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!(pred(*first1 == *first2)))
			return (false);
	}
	return (true);
}

}