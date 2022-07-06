/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:03:32 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/06 16:52:58 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Utils.hpp"
//#include "rbt_iterator.hpp"
//#include <memory>
//#include <map>
//#include <functional>
//#include "algorithm.hpp"»
//#include "pair.hpp"

//std::map<double, int> map;


/*
	Rules:
	1. Every node is red or black
	2. Root is always black.
	3. New insertions are always red.
	4. Every path from root - leaf has the same number of black nodes.
	5. No paht ca have two consecutive red nodes.
	6. NULLs are black.
	
	Rebalance:
	Black Aunt => Rotate.
	Red Aunt => ColorFlip.

	After rotation
	Parent = black
	children = red

	After colorFlip
	Parent = red
	children = black
	
*/


namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class RBT
	{
		public:
		
		typedef Key													key_type;					//The first template parameter (Key)
		typedef T													mapped_type;				//The second template parameter (T)
		typedef ft::pair<const Key, T> 								value_type;					//pair<const key_type,mapped_type>
		typedef typename std::less<key_type> 						key_compare;				//The third template parameter (Compare)	defaults to: less<key_type>
		typedef typename std::less<value_type> 						value_compare;				//The second template parameter (Compare)	defaults to: less<value_type>
		typedef Alloc												allocator_type;				//The fourth template parameter (Alloc)	defaults to: allocator<value_type>
		typedef typename allocator_type::reference					reference;					//for the default allocator: value_type&
		typedef typename allocator_type::const_reference			const_reference;			//for the default allocator: const value_type&
		typedef typename allocator_type::pointer					pointer;					//for the default allocator: value_type*
		typedef typename allocator_type::const_pointer				const_pointer;				//for the default allocator: const value_type*
		//typedef typename ft::rbt_iterator<const Key, T>				iterator;					//a bidirectional iterator to value_type	convertible to const_iterator
		//typedef typename std::map<const Key, T>::iterator				iterator;
		//typedef typename ft::rbt_iterator<const Key, T>			const_iterator;				//a bidirectional iterator to const value_type
		//typedef typename ft::rbt_iterator<iterator>			reverse_iterator;			//reverse_iterator<iterator>
		//typedef typename ft::rbt_iterator<const_iterator>	const_reverse_iterator;		//reverse_iterator<const_iterator>
		typedef typename allocator_type::difference_type			difference_type;			//a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
		typedef typename allocator_type::size_type					size_type;					//an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t
	
		struct node {
			value_type	data;
			node 	* parent;
			node 	* left;
			node 	* right;
			bool	isBlack;
			bool	isLeftChild;
		};

		protected:
		node 					* root;
		std::allocator<node>	mem_node_control;
		key_compare				mem_compare;
		allocator_type			mem_control;
		//pointer					mem_start;
		size_type				mem_size;

		private:

		node * createNode(const value_type & val)
		{
			node * newNode = this->mem_node_control.allocate(1);
			//newNode->data = this->mem_control.allocate(1);
			this->mem_control.construct(&(newNode->data), val);
			newNode->isBlack = false;
			newNode->isLeftChild = false;
			newNode->parent = NULL;
			newNode->left = NULL;
			newNode->right = NULL;
			return (newNode);
		}
		void	deleteNode(node * nd)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] deleteNode called - " << nd->data->first << "\n" << COLOR_DEFAULT;
			#endif
			//this->mem_control.destroy(&(nd->data));
			//this->mem_control.deallocate(nd->data, 1);
			this->mem_node_control.deallocate(nd, 1);
		}
		node * findNode(const Key & k)
		{
			node *tmp = this->root;

			while (tmp)
			{
				if (tmp->data.first == k)
					return (tmp);
				if (k < tmp->data.first)
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return (tmp);
		}
		node * getSibling(node & nd) const
		{
			if (nd->parent == NULL)
				return (NULL);
			if (nd->isLeftchild)
				return (nd->parent->right);
			return (nd->parent->left);
		}
		node * getLeftNode(node * nd) const
		{
			node	*tmp = nd;
			while (tmp && tmp->left)
				tmp = tmp->left;
			return (tmp);
		}
		node * getRightNode(node * nd) const
		{
			node	*tmp = nd;
			while (tmp && tmp->right)
				tmp = tmp->right;
			return (tmp);
		}
		void	clearTree(node * nd)
		{
			if (nd->left)
				clearTree(nd->left);
			if (nd->right)
				clearTree(nd->right);
			deleteNode(nd);
		}
		public:
		RBT	(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[RBT] default constructor called.\n" << COLOR_DEFAULT;
			#endif
			mem_compare = comp;
			mem_control = alloc;
			mem_size = 0;
			root = NULL;
		}

		template <class InputIterator>
		RBT (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[RBT] InputIterator constructor called.\n" << COLOR_DEFAULT;
			#endif
			//TODO
			(void) first;
			(void) last;
			mem_compare = comp;
			mem_control = alloc;
			
		}

		RBT (const RBT & copy)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[RBT] default constructor called.\n" << COLOR_DEFAULT;
			#endif
			*this = copy;
		}
		
		~RBT(void)
		{
			#if DEBUG
				std::cout << COLOR_RED << "[RBT] deconstructor called.\n" << COLOR_DEFAULT;
			#endif
			clearTree(this->root);
		}
		
		RBT & operator= (const RBT & copy)
		{
			//TODO
			(void) copy;
			return (*this);
		}


		// //***Iterators:
		// //Return iterator to beginning (public member function )
		node * begin(void) const
		{
			return (getLeftNode(this->root));
		}
		node * end(void) const
		{
			return (getRightNode(this->root));
		}
		node * rbegin(void) const
		{
			return (getRightNode(this->root));
		}
		node * rend(void) const
		{
			return (getLeftNode(this->root));
		}
		// iterator begin(void)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] iterator begin called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (iterator(this->root));
		// }
		// const_iterator begin() const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] const_iterator begin called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (const_iterator(this->root));
		// }
		// //Return iterator to end (public member function )
		// iterator end(void)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] iterator end called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (iterator(NULL));
		// }
		// const_iterator end(void) const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] const_iterator end called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (const_iterator(NULL));
		// }
		// //Return reverse iterator to reverse beginning (public member function )
		// reverse_iterator rbegin(void)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] reverse_iterator rbegin called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (reverse_iterator(this->root));
		// }
		// const_reverse_iterator rbegin(void) const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] const_reverse_iterator rbegin called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (const_reverse_iterator(this->root));
		// }
		// //Return reverse iterator to reverse end (public member function )
		// reverse_iterator rend(void)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] reverse_iterator rend called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (reverse_iterator(NULL));
		// }
		// const_reverse_iterator rend(void) const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] const_reverse_iterator rend called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (const_reverse_iterator(NULL));
		// }
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
				std::cout << COLOR_YELLOW << "[RBT] empty called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_size == 0);
		}
		//Return container size (public member function )
		size_type size() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] size called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_size);
		}
		//Return maximum size (public member function )
		size_type max_size() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] max_size called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_control.max_size());
		}

		//***Element access:
		//operator[] Access element (public member function )
		mapped_type& operator[] (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] reference operator[] called.\n" << COLOR_DEFAULT;
			#endif
			//TODO
			node * tmp = findNode(k);
			if (tmp)
				return (tmp->data->second);
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
		node * addNode (const value_type& val)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] insert key/value called.\n" << COLOR_DEFAULT;
			#endif
			if (this->root == NULL)
			{
				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] creating new root node key: " << val.first << ".\n" << COLOR_DEFAULT;
				#endif
				this->root = createNode(val);
				++(this->mem_size);
				return (this->root);
			}
			node * checkNode = findNode(val.first);
			if (checkNode)
			{
				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] node with key:" << val.first << " already existing.\n" << COLOR_DEFAULT;
				#endif
				return (checkNode);
			}
			checkNode = this->root;
			node *parentNode;
			bool isLeft = false;
			while (checkNode != NULL)
			{
				if (val.first < checkNode->data.first)
				{
					parentNode = checkNode;
					checkNode = checkNode->left;
					isLeft = true;
				}
				else
				{
					parentNode = checkNode;
					checkNode = checkNode->right;
					isLeft = false;
				}
			}
				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] new node with key:" << val.first << " created. Parent-Key: " << parentNode->data.first << "\n" << COLOR_DEFAULT;
				#endif
			checkNode = createNode(val);
			++(this->mem_size);
			if (isLeft)
			{
				parentNode->left = checkNode;
				checkNode->isLeftChild = true;
			}
			else
			{
				parentNode->right = checkNode;
				checkNode->isLeftChild = false;
			}
			checkNode->isBlack = false;
			checkNode->parent = parentNode;
			return (checkNode);
		}

		// iterator insert (iterator position, const value_type& val);

		// template <class InputIterator>
		// void insert (InputIterator first, InputIterator last);
		//Erase elements (public member function )
		// void erase (iterator position)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] erase position called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	(void) position;
		// }
		size_type erase (const key_type& k)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] erase key called.\n" << COLOR_DEFAULT;
			#endif
			(void) k;
			return (0);
		}

		// void erase (iterator first, iterator last)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] erase first - last called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	(void) first;
		// 	(void) last;
		// }
		//Swap content (public member function )
		void swap (RBT& x)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] swap called.\n" << COLOR_DEFAULT;
			#endif
			(void) x;
		}
		//Clear content (public member function )
		void clear(void)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] clear called.\n" << COLOR_DEFAULT;
			#endif
			clearTree(this->root);
			this->root = NULL;
		}
		//Construct and insert element (public member function )
		// C++ 11
		//Construct and insert element with hint (public member function )
		// C++ 11

		//***Observers:

		//Return key comparison object (public member function )
		// key_compare key_comp(void) const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] key_comp called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (NULL);
		// }
		// //Return value comparison object (public member function )
		// value_compare value_comp(void) const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] value_comp called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (NULL);
		// }

		// //***Operations:
		// //Get iterator to element (public member function )
		// iterator find (const key_type& k)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] find called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (iterator(findNode(k)));
		// }
		// const_iterator find (const key_type& k) const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] const find called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	(void) k;
		// 	return (const_iterator(NULL));
		// }
		// //Count elements with a specific key (public member function )
		// size_type count (const key_type& k) const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] count called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	(void) k;
		// 	return (0);
		// }
		// //Return iterator to lower bound (public member function )
		// iterator lower_bound (const key_type& k)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] lower_bound called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	(void) k;
		// 	return (iterator(NULL));
		// }
		// const_iterator lower_bound (const key_type& k) const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] const lower_bound called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	(void) k;
		// 	return (const_iterator(NULL));
		// }
		// //Return iterator to upper bound (public member function )
		// iterator upper_bound (const key_type& k)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] upper_bound called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	(void) k;
		// 	return (iterator(NULL));
		// }
		// const_iterator upper_bound (const key_type& k) const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] const upper_bound called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	(void) k;
		// 	return (const_iterator(NULL));
		// }
		// //Get range of equal elements (public member function )
		// pair<const_iterator, const_iterator>	equal_range (const key_type& k) const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] equal_range called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	(void) k;
		// 	return (ft::make_pair(const_iterator(NULL), const_iterator(NULL)));
		// }
		// pair<iterator, iterator>				equal_range (const key_type& k)
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] equal_range called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	(void) k;
		// 	return (ft::make_pair(iterator(NULL), iterator(NULL)));
		// }

		//***Allocator:
		//Get allocator (public member function )
		allocator_type get_allocator() const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] get_allocator called.\n" << COLOR_DEFAULT;
			#endif
			return (this->mem_control);
		}

	}; // class RBT
	
} // namespace ft
