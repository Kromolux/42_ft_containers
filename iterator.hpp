/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:36:54 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/06 14:34:14 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iterator>
#include <cstddef>
#include "colors.h"
//#include "reverse_iterator.hpp"
//#include "algorithm.hpp"


// class reverse_iterator;
// class algorithm;
namespace ft
{
	//class template <iterator>
	//std::iterator_traits

	struct input_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};
	struct output_iterator_tag {};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef random_access_iterator_tag		iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef random_access_iterator_tag		iterator_category;
	};

}

namespace ft
{

	template <class T, class nonconst_T>
	class iterator
	{
		public:
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T *								pointer;
		typedef T &								reference;
		typedef random_access_iterator_tag		iterator_category;

		private:
		T * ptr;

		public:
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
		// template <class It>
		// iterator(const iterator<It, nonconst_T>& i,
		// typename ft::enable_if<ft::is_same<It, nonconst_T>::value>::type* = NULL) : ptr(i.address())
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_GREEN << "[iterator] const constructor called.\n" << COLOR_DEFAULT;
		// 	#endif
		// }
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
		iterator &	operator++(void)
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
		iterator &	operator--(void)
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

	};

}

namespace ft
{

	template <class Iterator>
	class reverse_iterator
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
		reverse_iterator(void)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[reverse_iterator] default constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		explicit reverse_iterator (iterator_type it) : _base(it)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[reverse_iterator] constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		reverse_iterator (const reverse_iterator<Iterator>& rev_it) : _base(rev_it._base)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[reverse_iterator] copy constructor called.\n" << COLOR_DEFAULT;
			#endif
		}

		iterator_type base() const
		{
			return (this->_base);
		}
		
		// iterator const & operator=(iterator const & rhs)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] operator= called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	this->ptr = rhs.ptr;
		// 	return (*this);
		// }
		// pointer	address(void) const
		// {
		// 	return (this->ptr);
		// }
		reference	operator*() const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator* called.\n" << COLOR_DEFAULT;
			#endif
			iterator_type	tmp(this->_base);
			--tmp;
			return (*tmp);
		}
		// Returns a reverse iterator pointing to the element located n positions away from
		// the element the iterator currently points to.
		// Internally, the function applies the binary operator- on the base iterator and returns
		// a reverse iterator constructed with the resulting iterator value.
		reverse_iterator operator+ (difference_type n) const
		{
			return (reverse_iterator(this->_base - n));
		}
		
		// friend iterator	operator+(difference_type n, iterator const & rhs)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] difference_type operator+ called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (iterator (rhs.ptr + n));
		// }
		// iterator	operator+(difference_type n)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] iterator operator+ called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (iterator (this->ptr + n));
		// }
		reverse_iterator &	operator++()
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator++() called.\n" << COLOR_DEFAULT;
			#endif
			--(this->_base);
			return (*this);
		}
		reverse_iterator	operator++(int)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator++(int) called.\n" << COLOR_DEFAULT;
			#endif
			reverse_iterator tmp(this->_base);
			--(this->_base);
			return (tmp);
		}
		reverse_iterator& operator+= (difference_type n)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] iterator operator+= called.\n" << COLOR_DEFAULT;
			#endif
			this->_base -= n;
			return (*this);
		}
		// Subtraction operator
		// Returns a reverse iterator pointing to the element located n positions
		// before the element the iterator currently points to.
		// Internally, the function applies the binary operator+ on the base iterator
		// and returns a reverse iterator constructed with the resulting iterator value.
		reverse_iterator operator- (difference_type n) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] iterator operator- called.\n" << COLOR_DEFAULT;
			#endif
			return (reverse_iterator (this->_base + n));
		}
		// typename reverse_iterator<Iterator>::difference_type operator- (
		// const reverse_iterator<Iterator>& lhs,
		// const reverse_iterator<Iterator>& rhs);
		difference_type	operator-(reverse_iterator const & rhs)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] difference_type operator- called.\n" << COLOR_DEFAULT;
			#endif
			return (this->_base + rhs._base);
		}
		reverse_iterator& operator--()
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator--() called.\n" << COLOR_DEFAULT;
			#endif
			++(this->_base);
			return (*this);
		}
		reverse_iterator  operator--(int)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator--(int) called.\n" << COLOR_DEFAULT;
			#endif
			reverse_iterator tmp(this->_base);
			++(this->_base);
			return (tmp);
		}
		reverse_iterator& operator-= (difference_type n)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] iterator operator-= called.\n" << COLOR_DEFAULT;
			#endif
			this->_base += n;
			return (*this);
		}
		pointer operator->() const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator-> called.\n" << COLOR_DEFAULT;
			#endif
			return &(operator*());
		}
		// reference operator[] (difference_type n) const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] operator[] called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (*this->base()[-n -1]);
		// }

		// difference_type	operator+(iterator const & rhs)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] difference_type operator+ called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (this->ptr + rhs.ptr);
		// }
		// difference_type	operator-=(iterator const & rhs)
		// {
		// 	return (this->ptr - rhs.prt);
		// }

		// difference_type	operator+=(iterator const & rhs)
		// {
		// 	return (this->ptr + rhs.prt);
		// }

		protected:

		private:

	};

	// Addition operator
	// Returns a reverse iterator pointing to the element located n positions away from the element pointed to by rev_it.
	// The function returns the same as: rev_it+n (see reverse_iterator::operator+).
	// This operator is also overloaded as a member function to return a reverse iterator offset by -n element positions (see reverse_iterator::operator-).
	// template <class Iterator>
	// reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
	// 									const reverse_iterator<Iterator>& rev_it)
	// {
	// 	return ( (rev_it + n) );
	// }
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		#if DEBUG
			std::cout << COLOR_MAGENTA << "[reverse_iterator] operator== called.\n" << COLOR_DEFAULT;
		#endif
		return (lhs.base() == rhs.base());
	}
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		#if DEBUG
			std::cout << COLOR_MAGENTA << "[reverse_iterator] operator!= called.\n" << COLOR_DEFAULT;
		#endif
		return !(lhs.base() == rhs.base());
	}
	// bool	operator!=(iterator & rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] operator!= called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return (this->ptr != rhs.ptr);
	// }
	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		#if DEBUG
			std::cout << COLOR_MAGENTA << "[reverse_iterator] operator< called.\n" << COLOR_DEFAULT;
		#endif
		return (lhs.base() > rhs.base());
	}
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		#if DEBUG
			std::cout << COLOR_MAGENTA << "[reverse_iterator] operator<= called.\n" << COLOR_DEFAULT;
		#endif
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		#if DEBUG
			std::cout << COLOR_MAGENTA << "[reverse_iterator] operator> called.\n" << COLOR_DEFAULT;
		#endif
		return (lhs.base() < rhs.base());
	}
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		#if DEBUG
			std::cout << COLOR_MAGENTA << "[reverse_iterator] operator>= called.\n" << COLOR_DEFAULT;
		#endif
		return (lhs.base() >= rhs.base());
	}

}
