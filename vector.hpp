/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:06:27 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/11 16:04:44 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "iterator.hpp"
#include "algorithm.hpp"
#include <memory>
#include "colors.h"

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
		typedef	typename ft::iterator<T>					iterator;					//a random access iterator to value_type convertible to const_iterator
		typedef	typename ft::iterator<T>			const_iterator;				//a random access iterator to const value_type
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
		explicit vector (const allocator_type & alloc = allocator_type())
		: mem_control(alloc), mem_start(NULL), mem_size(0), mem_cap(0)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[vector] default constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		explicit vector (size_type n, const value_type & val = value_type(), const allocator_type& alloc = allocator_type())
		: mem_control(alloc), mem_start(NULL), mem_size(n), mem_cap(n)
		{
			mem_start = mem_control.allocate(mem_cap);
			for (size_t i = 0; i < this->mem_size; i++)
				mem_control.construct(mem_start + i, val);
			#if DEBUG
				std::cout << COLOR_GREEN << "[vector] argument constructor called. Size: " << n << " Sizeof T: " << sizeof(val) << " Pointer: " << mem_start << "\n" << COLOR_DEFAULT;
			#endif
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type());
		vector (const vector & x)
		: mem_control(x.mem_control), mem_start(NULL), mem_size(0), mem_cap(0)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[vector] copy constructor called. Size: " << mem_size << " Sizeof T: " << sizeof(x[0]) << " Pointer: " << mem_start << "\n" << COLOR_DEFAULT;
			#endif
			// mem_start = mem_control.allocate(mem_cap);
			// for (size_t i = 0; i < this->mem_size; i++)
			// 	mem_control.construct(mem_start + i, x[i]);
			*this = x;
		}
	//Vector destructor (public member function )
		~vector(void)
		{
			for (size_t i = 0; i < this->mem_size; i++)
				mem_control.destroy(this->mem_start + i);
			mem_control.deallocate(mem_start, mem_cap);
			#if DEBUG
				std::cout << COLOR_RED << "[vector] deconstructor called.\n" << COLOR_DEFAULT;
			#endif
		}
	//Assign content (public member function )
		vector & operator= (const vector & x)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[vector] assignement constructor called. Size: " << x.mem_size << " Sizeof T: " << sizeof(x[0]) << " Pointer: " << x.mem_start << "\n" << COLOR_DEFAULT;
			#endif
			if (this->mem_size > 0)
			{
				for (size_t i = 0; i < this->mem_size; i++)
					mem_control.destroy(this->mem_start + i);
			}
			if (this->mem_cap > 0)
				mem_control.deallocate(mem_start, mem_cap);
			this->mem_control = x.mem_control;
			this->mem_size = x.mem_size;
			this->mem_cap = x.mem_cap;
			this->mem_start = mem_control.allocate(mem_cap);
			for (size_t i = 0; i < this->mem_size; i++)
				mem_control.construct(mem_start + i, x[i]);
			return (*this );
		}
	//Iterators:
	//Return iterator to beginning (public member function )
		iterator begin(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] iterator begin called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator(this->mem_start));
		}
		const_iterator begin(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] const_iterator begin called.\n" << COLOR_DEFAULT;
			#endif
			return (const_iterator(this->mem_start));
		}
	//Return iterator to end (public member function )
		iterator end(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] iterator end called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator(this->mem_start + this->mem_size));
		}
		const_iterator end(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] const_iterator end called.\n" << COLOR_DEFAULT;
			#endif
			return (const_iterator(this->mem_start + this->mem_size));
		}
	//Return reverse iterator to reverse beginning (public member function )
		reverse_iterator rbegin(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] reverse_iterator rbegin called.\n" << COLOR_DEFAULT;
			#endif
			return (reverse_iterator(this->mem_start));
		}
		const_reverse_iterator rbegin(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] const_reverse_iterator rbegin called.\n" << COLOR_DEFAULT;
			#endif
			return (const_reverse_iterator(this->mem_start));
		}
	//Return reverse iterator to reverse end (public member function )
		reverse_iterator rend(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] reverse_iterator rend called.\n" << COLOR_DEFAULT;
			#endif
			return (reverse_iterator(this->mem_start + this->mem_size));
		}
		const_reverse_iterator rend(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] const_reverse_iterator rend called.\n" << COLOR_DEFAULT;
			#endif
			return (const_reverse_iterator(this->mem_start + this->mem_size));
		}
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
		size_type size(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] size called.\n" << COLOR_DEFAULT;
			#endif
			return (mem_size);
		}
	//Return maximum size (public member function )
		size_type max_size(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] max_size called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_control.max_size());
		}
	//Change size (public member function )
		// void resize (size_type n, value_type val = value_type())
		// {
		// 	for (size_t = )
		// }
	//Return size of allocated storage capacity (public member function )
		size_type capacity(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] capacity called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_cap);
		}
	//Test whether vector is empty (public member function )
		bool empty(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] empty called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_size == 0);
		}
	//Request a change in capacity (public member function )
		void reserve (size_type n);
	//Shrink to fit (public member function )
		//C++11

	//Element access:
	//Access element (public member function )
		reference operator[] (size_type n)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] reference operator[] called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_start[n]);
		}
		const_reference operator[] (size_type n) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] const_reference operator[] called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_start[n]);
		}
	//Access element (public member function )
		reference at (size_type n)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] reference at called.\n" << COLOR_DEFAULT;
			#endif
			if (n >= this->mem_size)
				throw std::out_of_range("vector::Index out of bounds!");
			return (this->mem_start[n]);
		}
		const_reference at (size_type n) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] const_reference at called.\n" << COLOR_DEFAULT;
			#endif
			if (n >= this->mem_size)
				throw std::out_of_range("vector::Index out of bounds!");
			return (this->mem_start[n]);
		}
	//Access first element (public member function )
		reference front(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] reference front called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_start[0]);
		}
		const_reference front(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] const_reference front called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_start[0]);
		}
	//Access last element (public member function )
		reference back(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] reference back called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_start[this->mem_size - 1]);
		}
		const_reference back(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] const_reference back called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_start[this->mem_size - 1]);
		}
	//Access data (public member function )
		pointer data()
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] pointer data called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_start);
		}
		const_pointer data() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] const_pointer data called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_start);
		}

	//Modifiers:
	//Assign vector content (public member function )
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);
		void assign (size_type n, const value_type& val);
	//Add element at the end (public member function )
		void push_back (const value_type& val)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] push_back called.\n" << COLOR_DEFAULT;
			#endif
			if (this->mem_size < this->mem_cap)
			{
				mem_control.construct(mem_start + this->mem_size, val);
				this->mem_size++;
			}
			else
			{
				vector	tmp(*this);
				for (size_t i = 0; i < this->mem_size; i++)
					mem_control.destroy(this->mem_start + i);
				if (this->mem_cap > 0)
					mem_control.deallocate(mem_start, mem_cap);
				mem_cap = 2 * mem_cap;
				mem_start = mem_control.allocate(mem_cap);
				for (size_t i = 0; i < tmp.mem_size; i++)
					mem_control.construct(mem_start + i, tmp[i]);
				mem_control.construct(mem_start + tmp.mem_size, val);
				this->mem_size++;
			}
		}
	//Delete last element (public member function )
		void pop_back(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] pop_back called.\n" << COLOR_DEFAULT;
			#endif
			this->mem_size--;
			mem_control.destroy(this->mem_start + this->mem_size);
		}
	//Insert elements (public member function )
		iterator insert (iterator position, const value_type& val);
		void insert (iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last);
	//Erase elements (public member function )
		iterator erase (iterator position)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] erase called.\n" << COLOR_DEFAULT;
			#endif
			this->mem_control.destroy(position.address());
			iterator it = position;
			iterator ite = this->end();
			while (it != ite)
			{
				it++;
				this->mem_control.construct(it.address() - 1, *it);
				this->mem_control.destroy(it.address());
			}
			this->mem_size--;
			return (position);
		}
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
		allocator_type get_allocator() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] get_allocator called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_control);
		}
};
	

	//Non-member function overloads
	//Relational operators for vector (function template )
		template <class T, class Alloc>
		bool operator== (const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
		{
			#if DEBUG
				std::cout << COLOR_BLUE << "[vector] bool operator== called.\n" << COLOR_DEFAULT;
			#endif
			if (lhs.size() == rhs.size())
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			return (false);
		}
		template <class T, class Alloc>
		bool operator!= (const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
		{
			#if DEBUG
				std::cout << COLOR_BLUE << "[vector] bool operator!= called.\n" << COLOR_DEFAULT;
			#endif
			if (lhs.size() != rhs.size())
				return (true);
			return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
		template <class T, class Alloc>
		bool operator<  (const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs);
		template <class T, class Alloc>
		bool operator<= (const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs);
		template <class T, class Alloc>
		bool operator>  (const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs);
		template <class T, class Alloc>
		bool operator>= (const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs);
	//Exchange contents of vectors (function template )
		template <class T, class Alloc>
		void swap (ft::vector<T,Alloc> & x, ft::vector<T,Alloc> & y);
}