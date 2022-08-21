/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 08:36:13 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/21 18:41:22 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <functional>
#include "RBT.hpp"
#include "rbt_iterator.hpp"

namespace ft
{

	// https://cplusplus.com/reference/map/map/?kw=map
	// https://en.cppreference.com/w/cpp/container/map
	template <	class Key,												// map::key_type
				class T,												// map::mapped_type
				class Compare = std::less<Key>,							// map::key_compare
				class Alloc = std::allocator<ft::pair<const Key,T> >	// map::allocator_type
				>
	class map
	{
		public:
		typedef Key														key_type;					//The first template parameter (Key)
		typedef T														mapped_type;				//The second template parameter (T)
		typedef pair<const key_type, mapped_type> 						value_type;					//pair<const key_type,mapped_type>
		typedef Compare													key_compare;				//The third template parameter (Compare)	defaults to: less<key_type>
		//class 															value_compare;				//Nested function class to compare elements	see value_comp
		typedef Alloc													allocator_type;				//The fourth template parameter (Alloc)	defaults to: allocator<value_type>
		typedef typename allocator_type::reference						reference;					//for the default allocator: value_type&
		typedef typename allocator_type::const_reference				const_reference;			//for the default allocator: const value_type&
		typedef typename allocator_type::pointer						pointer;					//for the default allocator: value_type*
		typedef typename allocator_type::const_pointer					const_pointer;				//for the default allocator: const value_type*
		typedef RBT<value_type, Compare> 								tree_type;
		typedef typename ft::rbt_iterator<value_type, false>			iterator;					//a bidirectional iterator to value_type	convertible to const_iterator
		typedef typename ft::rbt_iterator<value_type, true>				const_iterator;				//a bidirectional iterator to const value_type
		typedef typename ft::rbt_reverse_iterator<iterator>				reverse_iterator;			//reverse_iterator<iterator>
		typedef typename ft::rbt_reverse_iterator<const_iterator>		const_reverse_iterator;	
		typedef typename allocator_type::difference_type				difference_type;			//a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
		typedef typename allocator_type::size_type						size_type;					//an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t
	
		private:
		tree_type		c;
		allocator_type	mem_alloc;
		
		private:
		//The comparison object returned is an object of the member type map::value_compare, 
		//which is a nested class that uses the internal comparison object to generate the appropriate comparison functional class.
		//template <class KeyC, class TC, class CompareC, class AllocC>
		class value_compare : public std::binary_function<value_type,value_type,bool>
		{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			//friend class map;

			public:
				Compare comp;
				value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;

				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
		};
		
		public:
		//***Member functions
		//(constructor)	Construct map (public member function )
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: c(comp), mem_alloc(alloc)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[map] default constructor called.\n" << COLOR_DEFAULT;
			#endif
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: c(comp, alloc), mem_alloc(alloc)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[map] InputIterator constructor called.\n" << COLOR_DEFAULT;
			#endif
			for (; first != last; ++first)
				this->c.addNode(*first);
		}

		map (const map& Copy)
		: c(Copy.c), mem_alloc(Copy.mem_alloc)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[map] copy constructor called.\n" << COLOR_DEFAULT;
			#endif
		}

		//(destructor)	Map destructor (public member function )
		~map(void)
		{
			#if DEBUG
				std::cout << COLOR_RED << "[map] deconstructor called.\n" << COLOR_DEFAULT;
			#endif
		}

		map& operator= (const map& Copy)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[map] assignement constructor called.\n" << COLOR_DEFAULT;
			#endif
			this->c = Copy.c;
			return (*this);
		}

		//***Iterators:
		//Return iterator to beginning (public member function )
		iterator begin(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] iterator begin called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator(this->c.begin(), this->c.begin(), this->c.end()));
		}
		//template <const value_type>
		const_iterator begin(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] const_iterator begin called.\n" << COLOR_DEFAULT;
			#endif
			return (const_iterator(this->c.begin(), this->c.begin(), this->c.end()));
		}

		//Return iterator to end (public member function )
		iterator end(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] iterator end called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator(NULL, this->c.begin(), this->c.end()));
		}
		const_iterator end(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] const_iterator end called.\n" << COLOR_DEFAULT;
			#endif
			return (const_iterator(NULL, this->c.begin(), this->c.end()));
		}
	
		//Return reverse iterator to reverse beginning (public member function )
		reverse_iterator rbegin(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] reverse_iterator rbegin called.\n" << COLOR_DEFAULT;
			#endif
			//return (reverse_iterator(this->c.end(), this->c.begin(), this->c.end()));
			return (reverse_iterator(this->end()));
		}
		const_reverse_iterator rbegin(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] const_reverse_iterator rbegin called.\n" << COLOR_DEFAULT;
			#endif
			//return (const_reverse_iterator(this->c.end(), this->c.begin(), this->c.end()));
			return (const_reverse_iterator(this->end()));
		}

		//Return reverse iterator to reverse end (public member function )
		reverse_iterator rend(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] reverse_iterator rend called.\n" << COLOR_DEFAULT;
			#endif
			//return (reverse_iterator(this->c.begin(), this->c.begin(), this->c.end()));
			return (reverse_iterator(this->begin()));
		}
		const_reverse_iterator rend(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] const_reverse_iterator rend called.\n" << COLOR_DEFAULT;
			#endif
			//return (const_reverse_iterator(this->c.begin(), this->c.begin(), this->c.end()));
			return (const_reverse_iterator(this->begin()));
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
				std::cout << COLOR_YELLOW << "[map] empty called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.empty());
		}

		//Return container size (public member function )
		size_type size() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] size called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.size());
		}

		//Return maximum size (public member function )
		size_type max_size() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] max_size called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.max_size());
		}

		//***Element access:
		//operator[] Access element (public member function )
		mapped_type& operator[] (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] reference operator[] called.\n" << COLOR_DEFAULT;
			#endif
			return ( (*( (this->insert(ft::make_pair(k, mapped_type()))).first)).second );
		}

		//at Access element (public member function )
		// C++ 11

		//***Modifiers:
		//Insert elements (public member function )
		/*
		The single element versions (1) return a pair, with its member pair::first set to an iterator pointing
		to either the newly inserted element or to the element with an equivalent key in the map.
		The pair::second element in the pair is set to true if a new element was inserted or false if an equivalent key already existed.
		*/
		pair<iterator, bool> insert (const value_type& val)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] insert value called [Key:Val] [" << val.first << ":" << val.second << "]\n" << COLOR_DEFAULT;
			#endif
			iterator it;
			it = iterator(this->c.findNode(val), this->c.begin(), this->c.end());
			if (it != iterator())
				return (ft::make_pair(it, false));
			it = iterator(this->c.addNode(val), this->c.begin(), this->c.end());
			return (ft::make_pair(it, true));
		}

		iterator insert (iterator position, const value_type& val)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] insert position called [Key:Val] [" << val.first << ":" << val.second << "]\n" << COLOR_DEFAULT;
			#endif
			static_cast<void>(position);
			//if (position != iterator())
				return (iterator(this->c.addNode(val), this->c.begin(), this->c.end()));
			//return (position);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] insert iterator called.\n" << COLOR_DEFAULT;
			#endif
			for (; first != last; ++first)
				this->c.addNode(*first);
		}
		
		//Erase elements (public member function )
		void erase (iterator position)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] erase position called.\n" << COLOR_DEFAULT;
			#endif
			this->c.erase(*position);
		}

		size_type erase (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] erase key called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.erase(ft::make_pair(k, mapped_type())));
		}

		void erase (iterator first, iterator last)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] erase first - last called.\n" << COLOR_DEFAULT;
			#endif
			size_t SizeToDelete = 0;
			iterator tmp = first;
			for (; tmp != last; ++tmp)
				++SizeToDelete;
			Key KeysToDelete[SizeToDelete];
			tmp = first;
			for (size_t i = 0; tmp != last; ++tmp, ++i)
			{
				KeysToDelete[i] = tmp->first;
			}
			for (size_t i = 0; i < SizeToDelete; ++i)
				this->c.erase((ft::make_pair(KeysToDelete[i], mapped_type())));
				
			// //is not working in all cases because of the value swap before rebalancing
			// iterator tmp = first;
			// for (; first != last;)
			// {
			// 	tmp = first++;
			// 	#if DEBUG
			// 		std::cout << COLOR_YELLOW << "[map] erase first - last key in for loop: " << tmp->first << ".\n" << COLOR_DEFAULT;
			// 	#endif
			// 	//this->c.printTree();
			// 	this->c.erase(*tmp);
			// }
			
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] erase first - last key done!\n" << COLOR_DEFAULT;
			#endif
		}

		//Swap content (public member function )
		void swap (map& x)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] swap called.\n" << COLOR_DEFAULT;
			#endif
			this->c.swap(x.c);
		}

		//Clear content (public member function )
		void clear()
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] clear called.\n" << COLOR_DEFAULT;
			#endif
			this->c.clear();
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
				std::cout << COLOR_YELLOW << "[map] key_comp called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.key_comp());
		}

		//Return value comparison object (public member function )
		value_compare value_comp(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] value_comp called.\n" << COLOR_DEFAULT;
			#endif
			return (value_compare(key_comp()));
		}

		//***Operations:
		//Get iterator to element (public member function )
		iterator find (const key_type & k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] find called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator(this->c.findNode(ft::make_pair(k, mapped_type())), this->c.begin(), this->c.end()));
		}
		const_iterator find (const key_type& k) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] const find called.\n" << COLOR_DEFAULT;
			#endif
			return (const_iterator(this->c.findNode(ft::make_pair(k, mapped_type())), this->c.begin(), this->c.end()));
		}

		//Count elements with a specific key (public member function )
		size_type count (const key_type& k) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] count called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.count(ft::make_pair(k, mapped_type())));
		}

		//Return iterator to lower bound (public member function )
		iterator lower_bound (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] lower_bound called.\n" << COLOR_DEFAULT;
			#endif
			iterator it = this->begin();
			iterator ite = this->end();
			for (; it != ite; ++it)
				if (this->c.key_comp()(it->first, k) == false)
					break;
			return (it);
		}
		const_iterator lower_bound (const key_type& k) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] const lower_bound called.\n" << COLOR_DEFAULT;
			#endif
			const_iterator it = this->begin();
			const_iterator ite = this->end();
			for (; it != ite; ++it)
				if (this->c.key_comp()(it->first, k) == false)
					break;
			return (it);
		}

		//Return iterator to upper bound (public member function )
		iterator upper_bound (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] upper_bound called.\n" << COLOR_DEFAULT;
			#endif
			iterator it = this->begin();
			iterator ite = this->end();
			for (; it != ite; ++it)
				if (this->c.key_comp()(k, it->first))
					break;
			return (it);
		}
		const_iterator upper_bound (const key_type& k) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] const upper_bound called.\n" << COLOR_DEFAULT;
			#endif
			const_iterator it = this->begin();
			const_iterator ite = this->end();
			for (; it != ite; ++it)
				if (this->c.key_comp()(k, it->first))
					break;
			return (it);
		}

		//Get range of equal elements (public member function )
		pair<iterator, iterator>				equal_range (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] equal_range called.\n" << COLOR_DEFAULT;
			#endif
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}
		pair<const_iterator, const_iterator>	equal_range (const key_type& k) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] equal_range called.\n" << COLOR_DEFAULT;
			#endif
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		//***Allocator:
		//Get allocator (public member function )
		allocator_type get_allocator(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[map] get_allocator called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_alloc);
		}
			
		bool operator==(map const & rhs) const
		{
			if (this->size() != rhs.size())
				return (false);
			return (ft::equal(this->begin(), this->end(), rhs.begin()));
		}

		bool operator!=(map const & rhs) const
		{
			if (this->size() != rhs.size())
				return (true);
			return (!ft::equal(this->begin(), this->end(), rhs.begin()));
		}
		
		bool operator<(map const & rhs) const
		{
			// const_iterator it_lhs = this->begin();
			// const_iterator ite_lhs = this->end();
			// const_iterator it_rhs = rhs.begin();
			// const_iterator ite_rhs = rhs.end();

			// while (it_lhs != ite_lhs)
			// {
			// 	if (it_rhs == ite_rhs)
			// 		return (false);
			// 	if (*it_lhs < *it_rhs)
			// 		return (true);
			// 	if (*it_lhs > *it_rhs)
			// 		return (false);
			// 	++it_lhs;
			// 	++it_rhs;
			// }
			// return (it_rhs != ite_rhs);
			if (ft::is_same<Key, T>::value == true)
				return (ft::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end(), value_compare(this->c.key_comp())));
			return (ft::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end()));
		}
		
		bool operator<=(map const & rhs) const
		{
			return !(rhs < *this);
		}
		
		bool operator>(map const & rhs) const
		{
			return (rhs < *this);
		}
		
		bool operator>=(map const & rhs) const
		{
			return !(*this < rhs);
		}

		//additional functions for testing the red black tree
		// int	height(void)
		// {
		// 	return (this->c.height());
		// }

		// int	blackNodes(void)
		// {
		// 	return (this->c.blackNodes());
		// }
		
		void printTree(void)
		{
			this->c.printTree();
		}
	
	}; // class map

} // namespace ft
