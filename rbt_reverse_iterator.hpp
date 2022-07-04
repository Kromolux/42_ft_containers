/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_reverse_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 09:53:32 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/28 13:43:10 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "rbt_iterator.hpp"
#include "iterator_traits.hpp"

class rbt_iterator;

namespace ft
{
	template <class Iterator>
	class rbt_reverse_iterator
	{
		public:
		typedef Iterator												iterator_type;		//Iterator's type
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;	//Preserves Iterator's category
		typedef typename iterator_traits<Iterator>::value_type			value_type;			//Preserves Iterator's value type
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;	//Preserves Iterator's difference type
		typedef typename iterator_traits<Iterator>::pointer				pointer;			//Preserves Iterator's pointer type
		typedef typename iterator_traits<Iterator>::reference			reference;			//Preserves Iterator's reference type
		/*
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T *								pointer;
			typedef T &								reference;
			typedef random_access_iterator_tag		iterator_category;
		*/
		private:
		iterator_type	_base;

		public:
		rbt_reverse_iterator(void)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_reverse_iterator] default constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		explicit rbt_reverse_iterator (iterator_type it) : _base(it)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_reverse_iterator] constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		rbt_reverse_iterator (const reverse_iterator<Iterator>& rev_it) : _base(rev_it._base)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_reverse_iterator] copy constructor called.\n" << COLOR_DEFAULT;
			#endif
		}

		iterator_type base() const
		{
			return (this->_base);
		}
	}; //rbt_reverse_iterator

} // namespace ft
