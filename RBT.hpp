/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:03:32 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/10 21:02:03 by rkaufman         ###   ########.fr       */
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
	template <class K, class V, class Compare = std::less<K>, class Alloc = std::allocator<ft::pair<const K, V> > >
	class RBT
	{
		public:
		
		typedef K													key_type;					//The first template parameter (Key)
		typedef V													mapped_type;				//The second template parameter (T)
		typedef ft::pair<const K, V> 								value_type;					//pair<const key_type,mapped_type>
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
					std::cout << COLOR_YELLOW << "[RBT] empty tree - creating new root node key: " << val.first << ".\n" << COLOR_DEFAULT;
				#endif
				this->root = createNode(val);
				this->root->isBlack = true;
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
				std::cout << COLOR_YELLOW << "[RBT] new node with key:" << val.first << " created. Parent-Key: " << parentNode->data.first << " isLeftChild: " << isLeft << "\n" << COLOR_DEFAULT;
			#endif
			checkNode = createNode(val);
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
			checkColor(*checkNode);
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] done with addNode\n" << COLOR_DEFAULT;
			#endif
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
		/*
		Rebalance:
		Black Aunt => Rotate.
		Red Aunt => ColorFlip.

		After rotation
		Parent = black
		children = red

		After colorFlip
		Parent = red
		children = black

		if nd.isLeftChild && nd.parent.isLeftchild => right right rotation
		if !nd.isLeftChild && !nd.parent.isLeftchild => left left rotation
		if !nd.isLeftChild && nd.parent.isLeftchild => left right rotation
		if nd.isLeftChild && !nd.parent.isLeftchild => right left rotation
		*/

		private:
		void	checkColor(node & nd)
		{
			if (&nd == this->root)
			{
				if (nd.isBlack == false)
					nd.isBlack = true;
				return ;
			}
			if (!nd.isBlack && !nd.parent->isBlack)
				correctTree(nd);
			checkColor(*nd.parent);
		}
		
		void	correctTree(node & nd)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] correctTree function called at node: " << nd.data.first << "\n" << COLOR_DEFAULT;
			#endif
			if (nd.parent->isLeftChild) //Aunt is nd.parent.parent.right
			{
				if (nd.parent->parent->right == NULL || nd.parent->parent->right->isBlack)
					return (rotate(nd));
				if (nd.parent->parent->right != NULL)
				{
					nd.parent->parent->right->isBlack = true;
					#if DEBUG
						std::cout << COLOR_YELLOW << "[RBT] changed color at " << nd.parent->parent->right->data.first << " to black\n" << COLOR_DEFAULT;
					#endif
				}
				nd.parent->parent->isBlack = false;
				nd.parent->isBlack = true;
				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] changed color at " << nd.parent->parent->data.first << " to red\n" << COLOR_DEFAULT;
					std::cout << COLOR_YELLOW << "[RBT] changed color at " << nd.parent->data.first << " to black\n" << COLOR_DEFAULT;
					std::cout << COLOR_YELLOW << "[RBT] " << nd.data.first << " parent isLeftChild: true\n" << COLOR_DEFAULT;
				#endif
				return ;
			}
			//Aunt is nd.parent.parent.left
			if (nd.parent->parent->left == NULL || nd.parent->parent->left->isBlack)
				return (rotate(nd));
			if (nd.parent->parent->left != NULL)
			{
				nd.parent->parent->left->isBlack = true;
				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] changed color at " << nd.parent->parent->left->data.first << " to black\n" << COLOR_DEFAULT;
				#endif
			}
			nd.parent->parent->isBlack = false;
			nd.parent->isBlack = true;
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] changed color at " << nd.parent->parent->data.first << " to red\n" << COLOR_DEFAULT;
				std::cout << COLOR_YELLOW << "[RBT] changed color at " << nd.parent->data.first << " to black\n" << COLOR_DEFAULT;
				std::cout << COLOR_YELLOW << "[RBT] " << nd.data.first << " parent isLeftChild: false\n" << COLOR_DEFAULT;
			#endif
			return ;
		}
		
		void	rotate(node & nd)
		{
			if (nd.isLeftChild)
			{
				if (nd.parent->isLeftChild)
				{
					rightRotate(*nd.parent->parent);
					nd.isBlack = false;
					nd.parent->isBlack = true;
					if (nd.parent->right != NULL)
						nd.parent->right->isBlack = false;
					return ;
				}
				rightLeftRotate(*nd.parent->parent);
				nd.isBlack = true;
				nd.right->isBlack = false;
				nd.left->isBlack = false;
				return ;
			}
			if (!nd.parent->isLeftChild)
			{
				leftRotate(*nd.parent->parent);
				nd.isBlack = false;
				nd.parent->isBlack = true;
				if (nd.parent->left != NULL)
					nd.parent->left->isBlack = false;
				return ;
			}
			leftRightRotate(*nd.parent->parent);
			nd.isBlack = true;
			nd.right->isBlack = false;
			nd.left->isBlack = false;
			return ;
		}
		/*
		before rotation
				  (A) <- root node
				  /
				(B) <- grand parent of new node passed to leftRotate nd
				/
			  (C) <- tmp pointer
			  /
			(D) <- violation causing node

		after rotation
				 (A)
				 /
			   (C)
			   / \
			 (D) (B)
		*/
		void	rightRotate(node & nd) //grandparent node
		{
			#if DEBUG
				std::cout << COLOR_BLUE<< "[RBT] rightRotate called - " << nd.data.first << "\n" << COLOR_DEFAULT;
			#endif
			node & tmp = *nd.left;
			nd.left = tmp.right;
			if (nd.left != NULL)
			{
				nd.left->parent = &nd;
				nd.left->isLeftChild = true;
			}
			if (nd.parent == NULL) //Root node
			{
				this->root = &tmp;
				tmp.parent = NULL;
				#if DEBUG
					std::cout << COLOR_BLUE<< "[RBT] changed root node - " << this->root->data.first << "\n" << COLOR_DEFAULT;
				#endif
			}
			else
			{
				tmp.parent = nd.parent;
				if (nd.isLeftChild)
				{
					tmp.isLeftChild = true;
					tmp.parent->left = &tmp;
				}
				else
				{
					tmp.isLeftChild = false;
					tmp.parent->right = &tmp;
				}
			}
			tmp.right = &nd;
			nd.isLeftChild = false;
			nd.parent = &tmp;
		}

		/*
		https://www.youtube.com/watch?v=fpESZSHrsp0
		before rotation
		  (A) <- root node
			\
			(B) <- grand parent of new node passed to leftRotate
			  \
			  (C) <- tmp pointer
				\
				(D) <- violation causing node

		after rotation
			(A)
			  \
			   (C)
			   / \
			 (B) (D)
		*/
		void	leftRotate(node & nd) //grandparent node
		{
			#if DEBUG
				std::cout << COLOR_BLUE<< "[RBT] leftRotate called - " << nd.data.first << "\n" << COLOR_DEFAULT;
			#endif
			node & tmp = *nd.right;
			nd.right = tmp.left;
			if (nd.right != NULL)
			{
				nd.right->parent = &nd;
				nd.right->isLeftChild = false;
			}
			if (nd.parent == NULL) //Root node
			{
				this->root = &tmp;
				tmp.parent = NULL;
				#if DEBUG
					std::cout << COLOR_BLUE<< "[RBT] changed root node - " << this->root->data.first << "\n" << COLOR_DEFAULT;
				#endif
			}
			else
			{
				tmp.parent = nd.parent;
				if (nd.isLeftChild)
				{
					tmp.isLeftChild = true;
					tmp.parent->left = &tmp;
				}
				else
				{
					tmp.isLeftChild = false;
					tmp.parent->right = &tmp;
				}
			}
			tmp.left = &nd;
			nd.isLeftChild = true;
			nd.parent = &tmp;
		}
		/*
		https://www.youtube.com/watch?v=4I_vnGpS-Io
		before rotation
		  (A) <- root node
			\
			(B) <- grand parent of new node passed to leftRotate
			/
		  (C) <- tmp pointer
			\
			(D) <- violation causing node
			
		intermediate step
		  (A) <- root node
			\
			(B) <- grand parent of new node passed to leftRotate
		    /
		  (D) <- tmp pointer
		  /
		(C) <- violation causing node

		after rotation
			(A)
			  \
			   (D)
			   / \
			 (C) (B)
		*/
		void	leftRightRotate(node & nd)
		{
			leftRotate(*nd.left);
			rightRotate(nd);
		}
		void	rightLeftRotate(node & nd)
		{
			rightRotate(*nd.right);
			leftRotate(nd);
		}

		node * createNode(const value_type & val)
		{
			node * newNode = this->mem_node_control.allocate(1);
			//newNode->data = this->mem_control.allocate(1);
			this->mem_control.construct(&(newNode->data), val);
			++this->mem_size;
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
				std::cout << COLOR_YELLOW << "[RBT] deleteNode called - " << nd->data.first << "\n" << COLOR_DEFAULT;
			#endif
			//this->mem_control.destroy(&(nd->data));
			//this->mem_control.deallocate(nd->data, 1);
			this->mem_node_control.deallocate(nd, 1);
		}
		node * findNode(const K & k)
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
			if (!nd)
				return (NULL);
			node	*tmp = nd;
			while (tmp && tmp->left)
				tmp = tmp->left;
			return (tmp);
		}
		node * getRightNode(node * nd) const
		{
			if (!nd)
				return (NULL);
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
	}; // class RBT
	
} // namespace ft
