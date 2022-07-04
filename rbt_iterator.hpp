/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 09:52:47 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/28 13:39:00 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iterator>
#include <cstddef>
#include "algorithm.hpp"
#include "rbt_reverse_iterator.hpp"

namespace ft
{
	template <class T, class nonconst_T>
	class rbt_iterator
	{
		public:
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T *								pointer;
		typedef T &								reference;
		typedef bidirectional_iterator_tag		iterator_category;
		
		private:
		T * ptr;

		public:
		rbt_iterator(void) : ptr(NULL)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_iterator] default constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		rbt_iterator(T * input) : ptr(input)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_iterator] constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		rbt_iterator(rbt_iterator const & copy) : ptr(copy.ptr)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_iterator] copy constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		template <class It>
		rbt_iterator(const rbt_iterator<It, nonconst_T>& i,
		typename ft::enable_if<ft::is_same<It, nonconst_T>::value>::type* = NULL) : ptr(i.address())
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_iterator] const constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		~rbt_iterator(void)
		{
			#if DEBUG
				std::cout << COLOR_RED << "[rbt_iterator] deconstructor called.\n" << COLOR_DEFAULT;
			#endif
		}
	}; //rbt_iterator

} // namespace ft
