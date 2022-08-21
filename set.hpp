/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 08:38:15 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/21 19:08:52 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "RBT.hpp"
#include "rbt_iterator.hpp"

namespace ft
{

	// https://cplusplus.com/reference/set/set/?kw=set
	// https://en.cppreference.com/w/cpp/container/set
	template <	class T,							// set::key_type/value_type
				class Compare = std::less<T>,		// set::key_compare/value_compare
				class Alloc = std::allocator<T>		// set::allocator_type
				>
	class set
	{
		private:
		typedef RBT<T, Compare> tree_type;
		
		public:
		typedef T															key_type;				//The first template parameter (T)	
		typedef T															value_type;				//The first template parameter (T)	
		typedef Compare														key_compare;			//The second template parameter (Compare)	defaults to: less<key_type>
		typedef Compare					 									value_compare;			//The second template parameter (Compare)	defaults to: less<value_type>
		typedef Alloc														allocator_type;			//The third template parameter (Alloc)	defaults to: allocator<value_type>
		typedef typename allocator_type::reference							reference;				//for the default allocator: value_type&
		typedef typename allocator_type::const_reference					const_reference;		//for the default allocator: const value_type&
		typedef typename allocator_type::pointer							pointer;				//for the default allocator: value_type*
		typedef typename allocator_type::const_pointer						const_pointer;			//for the default allocator: const value_type*
		typedef typename ft::rbt_iterator<value_type, true>					iterator;				//a bidirectional iterator to value_type	convertible to const_iterator
		typedef typename ft::rbt_iterator<value_type, true>					const_iterator;			//a bidirectional iterator to const value_type
		typedef typename ft::rbt_reverse_iterator<iterator>					reverse_iterator;		//reverse_iterator<iterator>
		typedef typename ft::rbt_reverse_iterator<const_iterator>			const_reverse_iterator;	
		

		typedef typename allocator_type::difference_type					difference_type;		//a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
		typedef typename allocator_type::size_type							size_type;				//an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t

		private:
		tree_type c;
		
		public:

		//Member functions
		//(constructor) Construct set (public member function )
		explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: c(comp, alloc)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[set] default constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		
		template <class InputIterator>
		set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: c(comp, alloc)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[set] InputIterator constructor called.\n" << COLOR_DEFAULT;
			#endif
			for (; first != last; ++first)
				this->c.addNode(*first);
		}
		
		set (const set& Copy)
		: c(Copy.c)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[set] copy constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		
		//(destructor) Set destructor (public member function )
		~set(void)
		{
			#if DEBUG
				std::cout << COLOR_RED << "[set] deconstructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		
		//operator=	Copy container content (public member function )
		set& operator= (const set& Copy)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[set] assignement constructor called.\n" << COLOR_DEFAULT;
			#endif
			this->c = Copy.c;
			return (*this);
		}
		
		//***Iterators:
		//Return iterator to beginning (public member function )
		iterator begin(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] iterator begin called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator(this->c.begin(), this->c.begin(), this->c.end()));
		}
		const_iterator begin(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] const_iterator begin called.\n" << COLOR_DEFAULT;
			#endif
			return (const_iterator(this->c.begin(), this->c.begin(), this->c.end()));
		}

		//Return iterator to end (public member function )
		iterator end(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] iterator end called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator(NULL, this->c.begin(), this->c.end()));
		}
		const_iterator end(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] const_iterator end called.\n" << COLOR_DEFAULT;
			#endif
			return (const_iterator(NULL, this->c.begin(), this->c.end()));
		}

		//Return reverse iterator to reverse beginning (public member function )
		reverse_iterator rbegin(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] reverse_iterator rbegin called.\n" << COLOR_DEFAULT;
			#endif
			return (reverse_iterator(this->end()));
		}
		const_reverse_iterator rbegin(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] const_reverse_iterator rbegin called.\n" << COLOR_DEFAULT;
			#endif
			return (const_reverse_iterator(this->end()));
		}

		//Return reverse iterator to reverse end (public member function )
		reverse_iterator rend(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] reverse_iterator rend called.\n" << COLOR_DEFAULT;
			#endif
			return (reverse_iterator(this->begin()));
		}
		const_reverse_iterator rend(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] const_reverse_iterator rend called.\n" << COLOR_DEFAULT;
			#endif
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
		bool empty(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] empty called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.empty());
		}

		//Return container size (public member function )
		size_type size(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] size called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.size());
		}

		//Return maximum size (public member function )
		size_type max_size(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] max_size called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.max_size());
		}

		//***Modifiers:
		//Insert element (public member function )
		pair<iterator,bool>	insert (const value_type& val)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] insert value called.\n" << COLOR_DEFAULT;
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
				std::cout << COLOR_YELLOW << "[set] insert position called [Key] [" << val << ":" << "]\n" << COLOR_DEFAULT;
			#endif
			(void) position;
			return (iterator(this->c.addNode(val), this->c.begin(), this->c.end()));
		}
		
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] insert iterator called.\n" << COLOR_DEFAULT;
			#endif
			for (; first != last; ++first)
			{
				this->c.addNode(*first);
			}
		}
		
		//Erase elements (public member function )
		void erase (iterator position)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] erase position called.\n" << COLOR_DEFAULT;
			#endif
			this->c.erase(*position);
		}

		size_type erase (const value_type& val)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] erase val called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.erase(val));
		}

		void erase (iterator first, iterator last)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] erase first: " << *first << "- last: " << *last << " called \n" << COLOR_DEFAULT;
			#endif
			iterator tmp = first;
			size_t elements = 0;
			for (; tmp != last; ++tmp, ++elements)
				;
			T elementsToDelete[elements];
			for (size_t i = 0; i < elements; ++i, ++first)
			{
				elementsToDelete[i] = *first;
				#if DEBUG
					std::cout << COLOR_YELLOW << "[set] elementsToDelete[" << i << "] : [" << *first << "]\n" << COLOR_DEFAULT;
					
				#endif
			}
			for (size_t i = 0; i < elements; ++i)
				this->c.erase(elementsToDelete[i]);
		}

		//Swap content (public member function )
		void swap (set& x)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] swap called.\n" << COLOR_DEFAULT;
			#endif
			this->c.swap(x.c);
		}
		
		//Clear content (public member function )
		void clear()
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] clear called.\n" << COLOR_DEFAULT;
			#endif
			this->c.clear();
		}

		//Construct and insert element (public member function )
		// C++ 11
		//Construct and insert element with hint (public member function )
		// C++ 11

		//***Observers:
		//Return comparison object (public member function )
		key_compare key_comp() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] key_comp called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.key_comp());
		}

		//Return comparison object (public member function )
		value_compare value_comp() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] value_comp called.\n" << COLOR_DEFAULT;
			#endif
			return (value_compare());
		}

		//***Operations:
		//Get iterator to element (public member function )
		iterator find (const value_type& val) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] find called.\n" << COLOR_DEFAULT;
			#endif
			return (iterator(this->c.findNode(val), this->c.begin(), this->c.end()));
		}

		//Count elements with a specific value (public member function )
		size_type count (const value_type& val) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] count called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.count(val));
		}

		//Return iterator to lower bound (public member function )
		iterator lower_bound (const value_type& val)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] lower_bound called.\n" << COLOR_DEFAULT;
			#endif
			iterator it = this->begin();
			iterator ite = this->end();
			for (; it != ite; ++it)
				if (this->c.key_comp()(*it, val) == false)
					break;
			return (it);
		}
		const_iterator lower_bound (const value_type& val) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] lower_bound called.\n" << COLOR_DEFAULT;
			#endif
			const_iterator it = this->begin();
			const_iterator ite = this->end();
			for (; it != ite; ++it)
				if (this->c.key_comp()(*it, val) == false)
					break;
			return (it);
		}

		//Return iterator to upper bound (public member function )
		iterator upper_bound (const value_type& val)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] upper_bound called.\n" << COLOR_DEFAULT;
			#endif
			iterator it = this->begin();
			iterator ite = this->end();
			for (; it != ite; ++it)
				if (this->c.key_comp()(val, *it))
					break;
			return (it);
		}
		const_iterator upper_bound (const value_type& val) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] upper_bound called.\n" << COLOR_DEFAULT;
			#endif
			const_iterator it = this->begin();
			const_iterator ite = this->end();
			for (; it != ite; ++it)
				if (this->c.key_comp()(val, *it))
					break;
			return (it);
		}

		//Get range of equal elements (public member function )
		pair<iterator,iterator> equal_range (const value_type& val)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] equal_range called.\n" << COLOR_DEFAULT;
			#endif
			return (ft::make_pair(lower_bound(val), upper_bound(val)));
		}
		pair<const_iterator, const_iterator> equal_range (const value_type& val) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] equal_range called.\n" << COLOR_DEFAULT;
			#endif
			return (ft::make_pair(lower_bound(val), upper_bound(val)));
		}

		//***Allocator:
		//Get allocator (public member function )
		allocator_type get_allocator(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[set] get_allocator called.\n" << COLOR_DEFAULT;
			#endif
			return (this->c.get_allocator());
		}
		
		bool operator==(set const & rhs) const
		{
			if (this->size() != rhs.size())
				return (false);
			return (ft::equal(this->begin(), this->end(), rhs.begin()));
		}

		bool operator!=(set const & rhs) const
		{
			if (this->size() != rhs.size())
				return (true);
			return (!ft::equal(this->begin(), this->end(), rhs.begin()));
		}
		
		bool operator<(set const & rhs) const
		{
			return (ft::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end(), key_compare()));
		}
		
		bool operator<=(set const & rhs) const
		{
			return !(rhs < *this);
		}
		
		bool operator>(set const & rhs) const
		{
			return (rhs < *this);
		}
		
		bool operator>=(set const & rhs) const
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
		
		// void printTree(void)
		// {
		// 	this->c.printTree();
		// }

	}; // class set

} // namespace ft
