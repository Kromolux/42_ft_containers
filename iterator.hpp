/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:36:54 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/12 10:17:36 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iterator>
#include <cstddef>
#include "colors.h"

namespace ft
{
	
template <class T>
class iterator
{
	public:
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T *								pointer;
		typedef T &								reference;
		typedef std::random_access_iterator_tag	iterator_category;

		iterator(void) : ptr(NULL)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[iterator] default constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		iterator(T * input) : ptr(input)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[iterator] constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		iterator(iterator const & copy) : ptr(copy.ptr)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[iterator] copy constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		~iterator(void)
		{
			#if DEBUG
				std::cout << COLOR_RED << "[iterator] deconstructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		iterator const & operator=(iterator const & rhs)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator= called.\n" << COLOR_DEFAULT;
			#endif
			this->ptr = rhs.ptr;
			return (*this);
		}
		pointer	address(void) const
		{
			return (this->ptr);
		}
		iterator &	operator++()
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator++() called.\n" << COLOR_DEFAULT;
			#endif
			this->ptr++;
			return (*this);
		}
		iterator	operator++(int)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator++(int) called.\n" << COLOR_DEFAULT;
			#endif
			iterator tmp = *this;
			this->ptr++;
			return (tmp);
		}
		iterator &	operator--()
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator--() called.\n" << COLOR_DEFAULT;
			#endif
			this->ptr--;
			return (*this);
		}
		iterator	operator--(int)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator--(int) called.\n" << COLOR_DEFAULT;
			#endif
			iterator tmp = *this;
			this->ptr--;
			return (tmp);
		}
		reference	operator[](size_t index)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator[] called.\n" << COLOR_DEFAULT;
			#endif
			return (*(this->ptr + index));
		}
		pointer	operator->()
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator-> called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr);
		}
		reference	operator*()
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator* called.\n" << COLOR_DEFAULT;
			#endif
			return (*this->ptr);
		}
		bool	operator==(iterator const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator== called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr == rhs.ptr);
		}
		bool	operator!=(iterator const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator!= called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr != rhs.ptr);
		}
		// bool	operator!=(iterator & rhs)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_MAGENTA << "[iterator] operator!= called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (this->ptr != rhs.ptr);
		// }
		bool	operator<(iterator const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator< called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr < rhs.ptr);
		}
		bool	operator<=(iterator const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator<= called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr <= rhs.ptr);
		}
		bool	operator>(iterator const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator> called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr > rhs.ptr);
		}
		bool	operator>=(iterator const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator>= called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr >= rhs.ptr);
		}
		difference_type	operator-(iterator const & rhs)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] difference_type operator- called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr - rhs.ptr);
		}
		iterator	operator-(difference_type n)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] iterator operator- called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator (this->ptr - n));
		}
		// difference_type	operator+(iterator const & rhs)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_MAGENTA << "[iterator] difference_type operator+ called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (this->ptr + rhs.ptr);
		// }
		friend iterator	operator+(difference_type n, iterator const & rhs)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] difference_type operator+ called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator (rhs.ptr + n));
		}
		iterator	operator+(difference_type n)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] iterator operator+ called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator (this->ptr + n));
		}
		// difference_type	operator-=(iterator const & rhs)
		// {
		// 	return (this->ptr - rhs.prt);
		// }
		iterator &	operator-=(difference_type n)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] iterator operator-= called.\n" << COLOR_DEFAULT;
			#endif
			this->ptr -= n;
			return (*this);
		}
		// difference_type	operator+=(iterator const & rhs)
		// {
		// 	return (this->ptr + rhs.prt);
		// }
		iterator &	operator+=(difference_type n)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] iterator operator+= called.\n" << COLOR_DEFAULT;
			#endif
			this->ptr += n;
			return (*this);
		}
	protected:

	private:

		T * ptr;
};

}