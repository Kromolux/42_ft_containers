/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:03:32 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/01 11:07:11 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include <functional>
#include "algorithm.hpp"
#include "rbt_iterator.hpp"
#include "pair.hpp"


namespace ft
{
	template <class Key>
	struct s_node {
		Key	   * key;
		s_node * parent;
		s_node * left;
		s_node * right;
		bool	isBlack;
	};

	template <class Key, class Compare, class Alloc>
	class rbt
	{
		public:
		typedef Key													key_type;					//The first template parameter (Key)
		typedef Key													mapped_type;				//The second template parameter (T)
		typedef Key													value_type;
		typedef typename std::less<key_type> 						key_compare;				//The third template parameter (Compare)	defaults to: less<key_type>
		typedef typename std::less<value_type> 						value_compare;				//The second template parameter (Compare)	defaults to: less<value_type>
		typedef Alloc												allocator_type;				//The fourth template parameter (Alloc)	defaults to: allocator<value_type>
		typedef typename allocator_type::reference					reference;					//for the default allocator: value_type&
		typedef typename allocator_type::const_reference			const_reference;			//for the default allocator: const value_type&
		typedef typename allocator_type::pointer					pointer;					//for the default allocator: value_type*
		typedef typename allocator_type::const_pointer				const_pointer;				//for the default allocator: const value_type*
		typedef typename ft::rbt_iterator<Key, Key>					iterator;					//a bidirectional iterator to value_type	convertible to const_iterator
		typedef typename ft::rbt_iterator<const Key, Key>			const_iterator;				//a bidirectional iterator to const value_type
		typedef typename ft::rbt_reverse_iterator<iterator>			reverse_iterator;			//reverse_iterator<iterator>
		typedef typename ft::rbt_reverse_iterator<const_iterator>	const_reverse_iterator;		//reverse_iterator<const_iterator>
		typedef typename allocator_type::difference_type			difference_type;			//a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
		typedef typename allocator_type::size_type					size_type;					//an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t
	
		protected:
		struct s_node<key_type> * root;
		key_compare		mem_compare;
		allocator_type	mem_control;
		pointer			mem_start;
		size_type		mem_size;

		public:
		rbt	(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt] default constructor called.\n" << COLOR_DEFAULT;
			#endif
			mem_compare = comp;
			mem_control = alloc;
			mem_start = NULL;
			mem_size = 0;
			root = NULL;
		}

		template <class InputIterator>
		rbt (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt] InputIterator constructor called.\n" << COLOR_DEFAULT;
			#endif
			mem_compare = comp;
			mem_control = alloc;
			
		}

		rbt (const rbt & copy)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt] default constructor called.\n" << COLOR_DEFAULT;
			#endif
			*this = copy;
		}
		
		~rbt(void)
		{
			#if DEBUG
				std::cout << COLOR_RED << "[rbt] deconstructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		
		rbt & operator= (const rbt & copy)
		{
			//TODO
			return (*this);
		}


		//***Iterators:
		//Return iterator to beginning (public member function )
		iterator begin(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] iterator begin called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator(this->root));
		}
		const_iterator begin() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] const_iterator begin called.\n" << COLOR_DEFAULT;
			#endif
			return (const_iterator(this->root));
		}
		//Return iterator to end (public member function )
		iterator end(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] iterator end called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator(NULL));
		}
		const_iterator end(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] const_iterator end called.\n" << COLOR_DEFAULT;
			#endif
			return (const_iterator(NULL));
		}
		//Return reverse iterator to reverse beginning (public member function )
		reverse_iterator rbegin(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] reverse_iterator rbegin called.\n" << COLOR_DEFAULT;
			#endif
			return (reverse_iterator(this->root));
		}
		const_reverse_iterator rbegin(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] const_reverse_iterator rbegin called.\n" << COLOR_DEFAULT;
			#endif
			return (const_reverse_iterator(this->root));
		}
		//Return reverse iterator to reverse end (public member function )
		reverse_iterator rend(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] reverse_iterator rend called.\n" << COLOR_DEFAULT;
			#endif
			return (reverse_iterator(NULL));
		}
		const_reverse_iterator rend(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] const_reverse_iterator rend called.\n" << COLOR_DEFAULT;
			#endif
			return (const_reverse_iterator(NULL));
		}
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
		bool empty() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] empty called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_size == 0);
		}
		//Return container size (public member function )
		size_type size() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] size called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_size);
		}
		//Return maximum size (public member function )
		size_type max_size() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] max_size called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_control.max_size());
		}

		//***Element access:
		//operator[] Access element (public member function )
		mapped_type& operator[] (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] reference operator[] called.\n" << COLOR_DEFAULT;
			#endif
			return (NULL);
		}
		//at Access element (public member function )
		// C++ 11

		
		//***Modifiers:
		//Insert elements (public member function )
		/*
		The single element versions (1) return a pair, with its member pair::first set to an iterator pointing
		to either the newly inserted element or to the element with an equivalent key in the rbt.
		The pair::second element in the pair is set to true if a new element was inserted or false if an equivalent key already existed.
		*/
		pair<iterator, bool> insert (const key_type& key);
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[rbt] insert key/value called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (pair<, true>);
		// }

		iterator insert (iterator position, const value_type& val);

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last);
		//Erase elements (public member function )
		void erase (iterator position)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] erase position called.\n" << COLOR_DEFAULT;
			#endif
			(void) position;
		}
		size_type erase (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] erase key called.\n" << COLOR_DEFAULT;
			#endif
			(void) k;
			return (0);
		}

		void erase (iterator first, iterator last)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] erase first - last called.\n" << COLOR_DEFAULT;
			#endif
			(void) first;
			(void) last;
		}
		//Swap content (public member function )
		void swap (rbt& x)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] swap called.\n" << COLOR_DEFAULT;
			#endif
			(void) x;
		}
		//Clear content (public member function )
		void clear()
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] clear called.\n" << COLOR_DEFAULT;
			#endif
			
		}
		//Construct and insert element (public member function )
		// C++ 11
		//Construct and insert element with hint (public member function )
		// C++ 11

		//***Observers:

		//Return key comparison object (public member function )
		key_compare key_comp(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] key_comp called.\n" << COLOR_DEFAULT;
			#endif
			return (NULL);
		}
		//Return value comparison object (public member function )
		value_compare value_comp(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] value_comp called.\n" << COLOR_DEFAULT;
			#endif
			return (NULL);
		}

		//***Operations:
		//Get iterator to element (public member function )
		iterator find (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] find called.\n" << COLOR_DEFAULT;
			#endif
			(void) k;
			return (iterator(NULL));
		}
		const_iterator find (const key_type& k) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] const find called.\n" << COLOR_DEFAULT;
			#endif
			(void) k;
			return (const_iterator(NULL));
		}
		//Count elements with a specific key (public member function )
		size_type count (const key_type& k) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] count called.\n" << COLOR_DEFAULT;
			#endif
			(void) k;
			return (0);
		}
		//Return iterator to lower bound (public member function )
		iterator lower_bound (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] lower_bound called.\n" << COLOR_DEFAULT;
			#endif
			(void) k;
			return (iterator(NULL));
		}
		const_iterator lower_bound (const key_type& k) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] const lower_bound called.\n" << COLOR_DEFAULT;
			#endif
			(void) k;
			return (const_iterator(NULL));
		}
		//Return iterator to upper bound (public member function )
		iterator upper_bound (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] upper_bound called.\n" << COLOR_DEFAULT;
			#endif
			(void) k;
			return (iterator(NULL));
		}
		const_iterator upper_bound (const key_type& k) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] const upper_bound called.\n" << COLOR_DEFAULT;
			#endif
			(void) k;
			return (const_iterator(NULL));
		}
		//Get range of equal elements (public member function )
		pair<const_iterator, const_iterator>	equal_range (const key_type& k) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] equal_range called.\n" << COLOR_DEFAULT;
			#endif
			(void) k;
			return (ft::make_pair(const_iterator, const_iterator));
		}
		pair<iterator, iterator>				equal_range (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] equal_range called.\n" << COLOR_DEFAULT;
			#endif
			(void) k;
			return (ft::make_pair(iterator, iterator));
		}

		//***Allocator:
		//Get allocator (public member function )
		allocator_type get_allocator() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[rbt] get_allocator called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_control);
		}
	}; // class rbt
	
} // namespace ft
