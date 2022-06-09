/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:06:27 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/09 22:05:55 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iterator>
#include <memory>

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class vector
{

	public:
		typedef	T									value_type;
		typedef	Alloc								allocator_type;				//defaults to: allocator<value_type>
		typedef	typename allocator_type::reference			reference;					//for the default allocator: value_type&
		typedef	typename allocator_type::const_reference		const_reference;			//for the default allocator: const value_type&
		typedef	typename allocator_type::pointer				pointer;					//for the default allocator: value_type*
		typedef	typename allocator_type::const_pointer		const_pointer;				//for the default allocator: const value_type*
		typedef	typename std::iterator<std::random_access_iterator_tag, T>					iterator;					//a random access iterator to value_type convertible to const_iterator
		typedef	typename std::iterator<std::random_access_iterator_tag, T>			const_iterator;				//a random access iterator to const value_type
		typedef	std::reverse_iterator<iterator>			reverse_iterator;			//reverse_iterator<iterator>;
		typedef	std::reverse_iterator<const_iterator>	const_reverse_iterator;		//reverse_iterator<const_iterator>;
		typedef	typename allocator_type::difference_type			difference_type;			//a signed integral type, identical to: usually the same as ptrdiff_t
		typedef	typename allocator_type::size_type				size_type;					//an unsigned integral type that can represent any non-negative value of difference_type usually the same as size_t
	
	protected:
		allocator_type	mem_control;
		pointer			mem_start;
		size_type		mem_size;
		size_type		mem_cap;

	public:
	//Member functions
	//Construct vector (public member function )
		explicit vector (const allocator_type & alloc = allocator_type()) : mem_control(alloc), mem_start(NULL), mem_size(0), mem_cap(0)
		{
			std::cout << "default constructor called\n";
		}
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type());
		vector (const vector & x);
	//Vector destructor (public member function )
		~vector(void) { std::cout << "deconstructor called\n"; }
	//Assign content (public member function )
		vector & operator= (const vector & x);

	//Iterators:
	//Return iterator to beginning (public member function )
		iterator begin(void);
		const_iterator begin(void) const;
	//Return iterator to end (public member function )
		iterator end(void);
		const_iterator end(void) const;
	//Return reverse iterator to reverse beginning (public member function )
		reverse_iterator rbegin(void);
		const_reverse_iterator rbegin(void) const;
	//Return reverse iterator to reverse end (public member function )
		reverse_iterator rend(void);
		const_reverse_iterator rend(void) const;
	//Return const_iterator to beginning (public member function )
		//C++11
	//Return const_iterator to end (public member function )
		//C++11
	//Return const_reverse_iterator to reverse beginning (public member function )
		//C++11
	//Return const_reverse_iterator to reverse end (public member function )
		//C++11

	//Capacity:
	//Return size (public member function )
		size_type size(void) const;
	//Return maximum size (public member function )
		size_type max_size(void) const;
	//Change size (public member function )
		void resize (size_type n, value_type val = value_type());
	//Return size of allocated storage capacity (public member function )
		size_type capacity(void) const;
	//Test whether vector is empty (public member function )
		bool empty(void) const;
	//Request a change in capacity (public member function )
		void reserve (size_type n);
	//Shrink to fit (public member function )
		//C++11

	//Element access:
	//Access element (public member function )
		reference operator[] (size_type n);
		const_reference operator[] (size_type n) const;
	//Access element (public member function )
		reference at (size_type n);
		const_reference at (size_type n) const;
	//Access first element (public member function )
		reference front(void);
		const_reference front(void) const;
	//Access last element (public member function )
		reference back(void);
		const_reference back(void) const;
	//Access data (public member function )
		//C++11

	//Modifiers:
	//Assign vector content (public member function )
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);
		void assign (size_type n, const value_type& val);
	//Add element at the end (public member function )
		void push_back (const value_type& val);
	//Delete last element (public member function )
		void pop_back(void);
	//Insert elements (public member function )
		iterator insert (iterator position, const value_type& val);
		void insert (iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last);
	//Erase elements (public member function )
		iterator erase (iterator position);
		iterator erase (iterator first, iterator last);
	//Swap content (public member function )
		void swap (vector& x);
	//Clear content (public member function )
		void clear(void);
	//Construct and insert element (public member function )
		//C++11
	//Construct and insert element at the end (public member function )
		//C++11
	
	//Allocator:
	//Get allocator (public member function )
		allocator_type get_allocator() const;

	//Non-member function overloads
	//Relational operators for vector (function template )
		//template <class T, class Alloc>
		friend bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		//template <class T, class Alloc>
		friend bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		//template <class T, class Alloc>
		friend bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		//template <class T, class Alloc>
		friend bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		//template <class T, class Alloc>
		friend bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		//template <class T, class Alloc>
		friend bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	//Exchange contents of vectors (function template )
		//template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
};
}
