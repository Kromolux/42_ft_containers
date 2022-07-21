/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:36:54 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/21 22:38:37 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iterator>
#include <cstddef>
#include "Utils.hpp"
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
	struct bidirectional_iterator_tag	: public input_iterator_tag {};
	struct random_access_iterator_tag	: public forward_iterator_tag {};
	struct output_iterator_tag			: public bidirectional_iterator_tag {};

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

	template <typename T, bool isConst>
	class iterator
	{
		public:
		typedef T												value_type;
		typedef ptrdiff_t										difference_type;
		typedef typename choose<isConst, const T *, T *>::type	pointer;
		typedef typename choose<isConst, const T &, T &>::type	reference;
		typedef random_access_iterator_tag						iterator_category;

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
		
		template<typename TypeT, bool TypeIsConst>
		iterator(iterator<TypeT, TypeIsConst> const & other) : ptr(other.address())
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[iterator] template constructor called.\n" << COLOR_DEFAULT;
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

		// operator iterator<const T>() const
		// {
		// 	return iterator<const T>((const T*)this->ptr);
		// }

		// operator iterator<T>() const
		// {
		// 	return iterator<T>((T*)this->ptr);
		// }

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
		template<typename TypeT, bool TypeIsConst>
		bool	operator==(iterator<TypeT, TypeIsConst> const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator== called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr == rhs.address());
		}
		template<typename TypeT, bool TypeIsConst>
		bool	operator!=(iterator<TypeT, TypeIsConst> const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator!= called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr != rhs.address());
		}
		// bool	operator!=(iterator & rhs)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_MAGENTA << "[iterator] operator!= called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (this->ptr != rhs.ptr);
		// }
		template<typename TypeT, bool TypeIsConst>
		bool	operator<(iterator<TypeT, TypeIsConst> const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator< called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr < rhs.address());
		}
		template<typename TypeT, bool TypeIsConst>
		bool	operator<=(iterator<TypeT, TypeIsConst> const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator<= called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr <= rhs.address());
		}
		template<typename TypeT, bool TypeIsConst>
		bool	operator>(iterator<TypeT, TypeIsConst> const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator> called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr > rhs.address());
		}
		template<typename TypeT, bool TypeIsConst>
		bool	operator>=(iterator<TypeT, TypeIsConst> const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator>= called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr >= rhs.address());
		}
		template<typename TypeT, bool TypeIsConst>
		difference_type	operator-(iterator<TypeT, TypeIsConst> const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] difference_type operator- called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr - rhs.address());
		}
		iterator	operator-(difference_type n) const
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
		template<typename TypeT, bool TypeIsConst>
		friend iterator	operator-(difference_type n, iterator<TypeT, TypeIsConst> const & rhs)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] difference_type operator+ called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator (rhs.ptr - n));
		}
		//does it works??
		template<typename TypeT, bool TypeIsConst>
		friend iterator	operator+(difference_type n, iterator<TypeT, TypeIsConst> const & rhs)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] difference_type operator+ called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator (rhs.ptr + n));
		}
		iterator	operator+(difference_type n) const
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

	// template<typename Iter1<typename TypeT, bool TypeIsConst>, typename Iter2<typename TypeT, bool TypeIsConst>>
	// typename iterator<Iter1>::difference_type	operator-(iterator<Iter1> const & lhs, iterator<Iter2> const & rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[iterator] difference_type operator- called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return (lhs.address() - rhs.address());
	// }

	// template<class iter1, class iter2>
	// bool	operator==(iterator<iter1> const & lhs, iterator<iter1> const & rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[iterator] operator== called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return (lhs.address() == rhs.address());
	// }

	// template<class T>
	// bool	operator!=(iterator<T> const & lhs, iterator<const T> const & rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[iterator] operator!= called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return (lhs.address() != rhs.address());
	// }
	
	// template<class T>
	// bool	operator<(iterator<T> const & lhs, iterator<const T> const & rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[iterator] operator< called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return (lhs.address() < rhs.address());
	// }
	
	// template<class T>
	// bool	operator<=(iterator<T> const & lhs, iterator<const T> const & rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[iterator] operator<= called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return (lhs.address() <= rhs.address());
	// }
	
	// template<class T>
	// bool	operator>(iterator<T> const & lhs, iterator<const T> const & rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[iterator] operator> called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return lhs.address() > rhs.address();
	// }
	
	// template<class T>
	// bool	operator>=(iterator<T> const & lhs, iterator<const T> const & rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[iterator] operator>= called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return lhs.address() >= rhs.address();
	// }
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
		template<typename Iter>
		reverse_iterator (const reverse_iterator<Iter>& other) : _base(other.base())
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[reverse_iterator] copy constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		
		// operator reverse_iterator<const Iterator>() const
		// {
		// 	return reverse_iterator<const Iterator>((const Iterator *)this->_base);
		// }

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

		pointer operator->() const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator-> called.\n" << COLOR_DEFAULT;
			#endif
			return &(operator*());
		}

		// Returns a reverse iterator pointing to the element located n positions away from
		// the element the iterator currently points to.
		// Internally, the function applies the binary operator- on the base iterator and returns
		// a reverse iterator constructed with the resulting iterator value.
		reverse_iterator operator+ (difference_type n) const
		{
			return (reverse_iterator(this->_base - n));
		}
		
		template<typename Iter>
		friend reverse_iterator	operator+(difference_type n, reverse_iterator<Iter> const & rhs)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] difference_type operator+ called.\n" << COLOR_DEFAULT;
			#endif
			return (reverse_iterator(rhs.base() - n));
		}
		// reverse_iterator	operator+(difference_type n)
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
		// template<typename Iter>
		// difference_type	operator-(reverse_iterator<Iter> const & rhs)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] difference_type operator- called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (this->_base + rhs.base());
		// }
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

		reference operator[] (difference_type n) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator[] called.\n" << COLOR_DEFAULT;
			#endif
			return (this->base()[-n -1]);
		}

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
		template<typename Iter>
		bool operator==(const reverse_iterator<Iter>& other) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator== called.\n" << COLOR_DEFAULT;
			#endif
			return (this->_base == other.base());
		}
		template<typename Iter>
		bool operator!=(const reverse_iterator<Iter>& other) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator!= called.\n" << COLOR_DEFAULT;
			#endif
			return (this->_base != other.base());
		}
		template<typename Iter>
		bool	operator<(const reverse_iterator<Iter>& rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator< called.\n" << COLOR_DEFAULT;
			#endif
			return (this->_base > rhs.base());
		}
		template<typename Iter>
		bool	operator<=(const reverse_iterator<Iter>& rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator<= called.\n" << COLOR_DEFAULT;
			#endif
			return (this->_base >= rhs.base());
		}
		template<typename Iter>
		bool	operator>(const reverse_iterator<Iter>& rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator> called.\n" << COLOR_DEFAULT;
			#endif
			return (this->_base < rhs.base());
		}
		template<typename Iter>
		bool	operator>=(const reverse_iterator<Iter>& rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[iterator] operator>= called.\n" << COLOR_DEFAULT;
			#endif
			return (this->_base <= rhs.base());
		}

		protected:

		private:

	};

	template<typename Iter1, typename Iter2>
	typename reverse_iterator<Iter1>::difference_type	operator-(reverse_iterator<Iter1> const & lhs, reverse_iterator<Iter2> const & rhs)
	{
		#if DEBUG
			std::cout << COLOR_MAGENTA << "[reverse_iterator] difference_type operator- called.\n" << COLOR_DEFAULT;
		#endif
		return (rhs.base() - lhs.base());
	}
	
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
	//template<class Iter1, class Iter2>
	
	// template <class Iterator>
	// bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] operator== called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return (lhs.base() == rhs.base());
	// }
	// template <class Iterator>
	// bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] operator!= called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return !(lhs.base() == rhs.base());
	// }
	// bool	operator!=(iterator & rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] operator!= called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return (this->ptr != rhs.ptr);
	// }
	// template <class Iterator>
	// bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] operator< called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return (lhs.base() > rhs.base());
	// }
	// template <class Iterator>
	// bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] operator<= called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return (lhs.base() >= rhs.base());
	// }
	// template <class Iterator>
	// bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] operator> called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return (lhs.base() < rhs.base());
	// }
	// template <class Iterator>
	// bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	// {
	// 	#if DEBUG
	// 		std::cout << COLOR_MAGENTA << "[reverse_iterator] operator>= called.\n" << COLOR_DEFAULT;
	// 	#endif
	// 	return (lhs.base() >= rhs.base());
	// }

}
