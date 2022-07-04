/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:06:27 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/30 09:44:38 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <memory>
#include "iterator.hpp"
#include "algorithm.hpp"

namespace ft
{

	template <	class T,
				class Alloc = std::allocator<T>
				>
	class vector
	{

		public:
		typedef	T												value_type;
		typedef	Alloc											allocator_type;				//defaults to: allocator<value_type>
		typedef	typename allocator_type::reference				reference;					//for the default allocator: value_type&
		typedef	typename allocator_type::const_reference		const_reference;			//for the default allocator: const value_type&
		typedef	typename allocator_type::pointer				pointer;					//for the default allocator: value_type*
		typedef	typename allocator_type::const_pointer			const_pointer;				//for the default allocator: const value_type*
		typedef	typename ft::iterator<T, T>						iterator;					//a random access iterator to value_type convertible to const_iterator
		typedef	typename ft::iterator<const T, T>				const_iterator;				//a random access iterator to const value_type
		typedef	typename ft::reverse_iterator<iterator>			reverse_iterator;			//reverse_iterator<iterator>;
		typedef	typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;		//reverse_iterator<const_iterator>;
		typedef	typename allocator_type::difference_type		difference_type;			//a signed integral type, identical to: usually the same as ptrdiff_t
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
		vector (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		: mem_control(alloc)
		{
			this->mem_size = static_cast<size_type>(last - first);
			this->mem_cap = this->mem_size;
			this->mem_start = this->mem_control.allocate(this->mem_cap);

			size_type	i = 0;
			for (; first != last; ++first, ++i)
				this->mem_control.construct(this->mem_start + i, *first);
			#if DEBUG
				std::cout << COLOR_GREEN << "[vector] InputIterator constructor called. Size: " << this->mem_size << " Sizeof T: " << sizeof(*first) << " Pointer: " << this->mem_start << "\n" << COLOR_DEFAULT;
			#endif
		}
		
		vector (const vector & x)
		: mem_control(x.mem_control), mem_start(NULL), mem_size(0), mem_cap(0)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[vector] copy constructor called. Size: " << x.mem_size << " Sizeof T: " << sizeof(x[0]) << " Pointer: " << mem_start << "\n" << COLOR_DEFAULT;
			#endif
			// mem_start = mem_control.allocate(mem_cap);
			// for (size_t i = 0; i < this->mem_size; i++)
			// 	mem_control.construct(mem_start + i, x[i]);
			*this = x;
		}
		//Vector destructor (public member function )
		~vector(void)
		{
			#if DEBUG
				std::cout << COLOR_RED << "[vector] deconstructor called.\n" << COLOR_DEFAULT;
			#endif
			MEM_destroy(*this);
			mem_control.deallocate(mem_start, mem_cap);
		}
		//Assign content (public member function )
		vector & operator= (const vector & x)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[vector] assignement constructor called. Size: " << x.mem_size << " Sizeof T: " << sizeof(x[0]) << " Pointer: " << x.mem_start << "\n" << COLOR_DEFAULT;
			#endif
			if (this->mem_size > 0)
				MEM_destroy(*this);
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
		//template < class T, class Alloc = std::allocator<T> >
		//template <const class T>
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
		//template <iterator<T
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
			return (reverse_iterator(this->mem_start + this->mem_size));
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
			return (reverse_iterator(this->mem_start));
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
			return (this->mem_size);
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
		void resize (size_type n, value_type val = value_type())
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] resize called.\n" << COLOR_DEFAULT;
			#endif
			if (n < this->mem_size)
				MEM_destroy(*this, n);
			else if (n > this->mem_cap)
			{
				MEM_reallocate(*this, n);
				for (size_type i = this->mem_size; i < n; i++)
				mem_control.construct(this->mem_start + i, val);
			}
			this->mem_size = n;
		}
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
		void reserve (size_type n)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] reserve called.\n" << COLOR_DEFAULT;
			#endif
			if (n < this->mem_cap)
				return ;
			MEM_reallocate(*this, n);
		}
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

		//template <typename Integer, ft::enable_if<ft::is_integral<Integer>::value, bool> = true>
		void assign (size_type n, const value_type& val)
		{
			if (this->mem_size > 0)
				MEM_destroy(*this);
			if (n > this->mem_cap)
			{
				this->mem_control.deallocate(this->mem_start, this->mem_cap);
				this->mem_cap = n;
				this->mem_start = this->mem_control.allocate(this->mem_cap);
			}
			for (size_type i = 0; i < n; i++)
				this->mem_control.construct(this->mem_start + i, val);
			this->mem_size = n;
		}
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			help_assign(first, last, ft::is_integral<InputIterator>());
		}
		private:
		template <class InputIterator>
		void	help_assign(InputIterator first, InputIterator last, ft::false_type)
		{
			size_type	tmp_cap = static_cast<size_type>(last - first);

			if (this->mem_size > 0)
				MEM_destroy(*this);
			if (tmp_cap > this->mem_cap)
			{
				this->mem_control.deallocate(this->mem_start, this->mem_cap);
				this->mem_cap = tmp_cap;
				this->mem_start = this->mem_control.allocate(this->mem_cap);
			}
			for (size_type i = 0; first != last; ++first, ++i)
				this->mem_control.construct(this->mem_start + i, *first);
			this->mem_size = tmp_cap;
		}
		template <class Integer>
		void	help_assign(Integer n, Integer val, ft::true_type)
		{
			size_type	tmp = static_cast<size_type>(n);
			if (this->mem_size > 0)
				MEM_destroy(*this);
			if (tmp > this->mem_cap)
			{
				this->mem_control.deallocate(this->mem_start, this->mem_cap);
				this->mem_cap = tmp;
				this->mem_start = this->mem_control.allocate(this->mem_cap);
			}
			for (size_type i = 0; i < tmp; i++)
				this->mem_control.construct(this->mem_start + i, val);
			this->mem_size = tmp;
		}
		public:
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
				if (this->mem_cap == 0)
					MEM_reallocate(*this, 1);
				MEM_reallocate(*this, 2 * this->mem_cap);
				mem_control.construct(mem_start + this->mem_size, val);
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
		iterator insert (iterator position, const value_type& val)
		{
			vector		copy(*this);
			size_type	pos = position - this->begin();
			this->mem_size++;
			if (this->mem_size > this->mem_cap)
			{
				MEM_destroy(*this);
				this->mem_control.deallocate(this->mem_start, this->mem_cap);
				this->mem_cap = 2 * (this->mem_size - 1);
				this->mem_start = this->mem_control.allocate(this->mem_cap);
				iterator	it = copy.begin();
				size_type	i = 0;
				for (; i != pos; ++it, ++i)
					this->mem_control.construct(this->mem_start + i, *it);
				this->mem_control.construct(this->mem_start + i, val);
				++i;
				for (; i < this->mem_size; ++it, ++i)
					this->mem_control.construct(this->mem_start + i, *it);
			}
			else
			{
				iterator	tmp = position;
				size_type	i = pos + 1;
				size_type	ii = pos;

				MEM_destroy(*this, pos);
				//this->mem_control.destroy(tmp.address());
				this->mem_control.construct(tmp.address(), val);
				for (; i < this->mem_size; ++ii, ++i)
				{
					//this->mem_control.destroy(this->mem_start + i);
					this->mem_control.construct(this->mem_start + i, copy[ii]);
				}
			}
			return (iterator(this->mem_start + pos));
		}
		void insert (iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last)
		{
			help_insert(position, first, last, ft::is_integral<InputIterator>());
		}
		private:
		template <class InputIterator>
		void	help_insert(iterator position, InputIterator first, InputIterator last, ft::false_type)
		{
			vector		copy(*this);
			size_type	pos = position - this->begin();

			size_type	size_to = static_cast<size_type>(last - first);
			if (this->mem_size + size_to > this->mem_cap)
			{
				MEM_destroy(*this);
				this->mem_control.deallocate(this->mem_start, this->mem_cap);
				this->mem_cap = 2 * this->mem_size + size_to;
				this->mem_start = this->mem_control.allocate(this->mem_cap);
				iterator	it = copy.begin();
				size_type	i = 0;
				for (; i != pos; ++it, ++i)
					this->mem_control.construct(this->mem_start + i, *it);
				this->mem_size += size_to;
				for (; first != last; ++first, ++i)
					this->mem_control.construct(this->mem_start + i, *first);
				for (; i < this->mem_size; ++it, ++i)
					this->mem_control.construct(this->mem_start + i, *it);
			}
			else
			{
				//iterator	tmp = position;
				size_type	i = pos;
				size_type	ii = pos;
				MEM_destroy(*this, pos);
				this->mem_size += size_to;
				//this->mem_control.destroy(tmp.address());
				//this->mem_control.construct(tmp.address(), val);
				for (; first != last; ++first, ++i)
				{
					//this->mem_control.destroy(this->mem_start + i);
					this->mem_control.construct(this->mem_start + i, *first);
				}
				for (; i < this->mem_size; ++ii, ++i)
				{
					//this->mem_control.destroy(this->mem_start + i);
					this->mem_control.construct(this->mem_start + i, copy[ii]);
				}
			}
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] insert iterator range called.\n" << COLOR_DEFAULT;
			#endif
		}
		void 	help_insert(iterator position, size_type n, const value_type& val, ft::true_type)
		{
			vector		copy(*this);
			size_type	pos = position - this->begin();

			if (this->mem_size + n > this->mem_cap)
			{
				MEM_destroy(*this);
				this->mem_control.deallocate(this->mem_start, this->mem_cap);
				this->mem_cap = 2 * this->mem_size + n;
				this->mem_start = this->mem_control.allocate(this->mem_cap);
				iterator	it = copy.begin();
				size_type	i = 0;
				for (; i != pos; ++it, ++i)
					this->mem_control.construct(this->mem_start + i, *it);
				this->mem_size += n;
				for (size_type ii = 0; ii < n; ++ii, ++pos)
					this->mem_control.construct(this->mem_start + pos, val);
				for (; pos < this->mem_size; ++it, ++pos)
					this->mem_control.construct(this->mem_start + i, *it);
			}
			else
			{
				//iterator	tmp = position;
				size_type	i = pos;
				size_type	ii = 0;
				MEM_destroy(*this, pos);
				this->mem_size += n;
				//this->mem_control.destroy(tmp.address());
				//this->mem_control.construct(tmp.address(), val);
				for (; ii < n; ++i, ++ii)
				{
					//this->mem_control.destroy(this->mem_start + i);
					this->mem_control.construct(this->mem_start + i, val);
				}
				for (; i < this->mem_size; ++pos, ++i)
				{
					//this->mem_control.destroy(this->mem_start + i);
					this->mem_control.construct(this->mem_start + i, copy[pos]);
				}
			}
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] insert iterator n val called.\n" << COLOR_DEFAULT;
			#endif
		}
		public:
		//Erase elements (public member function )
		iterator erase (iterator position)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] erase position called.\n" << COLOR_DEFAULT;
			#endif
			iterator it = position;
			this->mem_control.destroy(position.address());
			
			iterator ite = this->end();
			++it;
			while (it != ite)
			{
				this->mem_control.construct(it.address() - 1, *it);
				this->mem_control.destroy(it.address());
				it++;
			}
			this->mem_size--;
			return (position);
		}
		iterator erase (iterator first, iterator last)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] erase first - last called.\n" << COLOR_DEFAULT;
			#endif
			iterator it = first;
			iterator ite = this->end();
			for (; it != last; ++it)
			{
				this->mem_control.destroy(it.address());
				this->mem_size--;
			}
			iterator it_to = first;
			it = last;
			while (it != ite)
			{
				this->mem_control.construct(it_to.address(), *it);
				this->mem_control.destroy(it.address());
				++it;
				++it_to;
			}
			return (last);
		}
		//Swap content (public member function )
		void swap (vector& x)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] swap called.\n" << COLOR_DEFAULT;
			#endif
			allocator_type	tmp_control = this->mem_control;
			pointer			tmp_start = this->mem_start;
			size_type		tmp_size = this->mem_size;
			size_type		tmp_cap = this->mem_cap;
			
			this->mem_control = x.mem_control;
			this->mem_start = x.mem_start;
			this->mem_size = x.mem_size;
			this->mem_cap = x.mem_cap;
			
			x.mem_control = tmp_control;
			x.mem_start = tmp_start;
			x.mem_size = tmp_size;
			x.mem_cap = tmp_cap;
		}
		//Clear content (public member function )
		void clear(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[vector] clear called.\n" << COLOR_DEFAULT;
			#endif
			MEM_destroy(*this);
			this->mem_size = 0;
		}
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
		protected:
		void	MEM_destroy(vector & x, size_type i = 0)
		{
			for (; i < x.mem_size; i++)
				mem_control.destroy(x.mem_start + i);
		}
		void	MEM_reallocate(vector & x, size_type const & n)
		{
			vector	tmp(x);

			MEM_destroy(x);
			if (x.mem_cap > 0)
				mem_control.deallocate(x.mem_start, x.mem_cap);
			x.mem_cap = n;
			x.mem_start = x.mem_control.allocate(x.mem_cap);
			for (size_type i = 0; i < tmp.mem_size; i++)
				x.mem_control.construct(x.mem_start + i, tmp[i]);
		}
	};
	

	//Non-member function overloads
	//https://cplusplus.com/reference/vector/vector/operators/
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
	bool operator<  (const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator<= (const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>  (const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>= (const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		return !(lhs < rhs);
	}
	//Exchange contents of vectors (function template )
	template <class T, class Alloc>
	void swap (ft::vector<T,Alloc> & x, ft::vector<T,Alloc> & y)
	{
		#if DEBUG
			std::cout << COLOR_BLUE << "[vector] void swap template called.\n" << COLOR_DEFAULT;
		#endif
		x.swap(y);
	}
}
