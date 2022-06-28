/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 08:38:15 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/28 10:26:31 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "rbt.hpp"

namespace ft
{
	template <	class T,							// set::key_type/value_type
				class Compare = std::less<T>,		// set::key_compare/value_compare
				class Alloc = std::allocator<T>		// set::allocator_type
				>
	class set
	{
		public:
		typedef T													key_type;				//The first template parameter (T)	
		typedef T													value_type;				//The first template parameter (T)	
		typedef typename less<key_type>								key_compare;			//The second template parameter (Compare)	defaults to: less<key_type>
		typedef typename less<value_type> 							value_compare;			//The second template parameter (Compare)	defaults to: less<value_type>
		typedef Alloc												allocator_type;			//The third template parameter (Alloc)	defaults to: allocator<value_type>
		typedef typename allocator_type::reference					reference;				//for the default allocator: value_type&
		typedef typename allocator_type::const_reference			const_reference;		//for the default allocator: const value_type&
		typedef typename allocator_type::pointer					pointer;				//for the default allocator: value_type*
		typedef typename allocator_type::const_pointer				const_pointer;			//for the default allocator: const value_type*
		typedef typename ft::rbt_iterator<T, T>						iterator;				//a bidirectional iterator to value_type	convertible to const_iterator
		typedef typename ft::rbt_iterator<const T, T>				const_iterator;			//a bidirectional iterator to const value_type	
		typedef typename ft::rbt_reverse_iterator<iterator>			reverse_iterator;		//reverse_iterator<iterator>
		typedef typename ft::rbt_reverse_iterator<const_iterator>	const_reverse_iterator;	//reverse_iterator<const_iterator>	
		typedef typename allocator_type::difference_type			difference_type;		//a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
		typedef typename allocator_type::size_type					size_type				//an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t

		protected:

		public:
		//Member functions
		//(constructor) Construct set (public member function )
		explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		
		template <class InputIterator>
		set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		
		set (const set& x); 
		
		//(destructor) Set destructor (public member function )
		~set(void)
		{
			#if DEBUG
				std::cout << COLOR_RED << "[set] deconstructor called.\n" << COLOR_DEFAULT;
			#endif
			//MEM_destroy(*this);
			//mem_control.deallocate(mem_start, mem_cap);
		}
		
		//operator=	Copy container content (public member function )
		set& operator= (const set& x);
		
		//***Iterators:
		//Return iterator to beginning (public member function )
		iterator begin();
		const_iterator begin() const;
		//Return iterator to end (public member function )
		iterator end();
		const_iterator end() const;
		//Return reverse iterator to reverse beginning (public member function )
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		//Return reverse iterator to reverse end (public member function )
		reverse_iterator rend();
		const_reverse_iterator rend() const;
		//Return const_iterator to beginning (public member function )
		// C++ 11
		//Return const_iterator to end (public member function )
		// C++ 11
		//Return const_reverse_iterator to reverse beginning (public member function )
		// C++ 11
		//Return const_reverse_iterator to reverse end (public member function )
		// C++ 11

		//***Capacity:
		//Test whether container is empty (public member function )
		bool empty() const;
		//Return container size (public member function )
		size_type size() const;
		//Return maximum size (public member function )
		size_type max_size() const;

		//***Modifiers:
		//Insert element (public member function )
		pair<iterator,bool>
		insert (const value_type& val);
		iterator insert (iterator position, const value_type& val);
		
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last);
		
		//Erase elements (public member function )
		void erase (iterator position);

		size_type erase (const value_type& val);

		void erase (iterator first, iterator last);

		//Swap content (public member function )
		void swap (set& x);
		
		//Clear content (public member function )
		void clear();
		//Construct and insert element (public member function )
		// C++ 11
		//Construct and insert element with hint (public member function )
		// C++ 11

		//***Observers:
		//Return comparison object (public member function )
		key_compare key_comp() const;
		//Return comparison object (public member function )
		value_compare value_comp() const;

		//***Operations:
		//Get iterator to element (public member function )
		iterator find (const value_type& val) const;
		//Count elements with a specific value (public member function )
		size_type count (const value_type& val) const;
		//Return iterator to lower bound (public member function )
		iterator lower_bound (const value_type& val) const;
		//Return iterator to upper bound (public member function )
		iterator upper_bound (const value_type& val) const;
		//Get range of equal elements (public member function )
		pair<iterator,iterator> equal_range (const value_type& val) const;

		//***Allocator:
		//Get allocator (public member function )
		allocator_type get_allocator() const;
		
	}; // class set

} // namespace ft
