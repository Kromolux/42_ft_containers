/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:03:32 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/20 10:31:14 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Utils.hpp"
#include "vector.hpp"
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
	template <class T>
	struct Node {
		T		data;
		Node 	* parent;
		Node 	* left;
		Node 	* right;
		bool	isBlack;
		bool	isLeftChild;
	};

	//template <class K, class V, class Compare = std::less<K>, class Alloc = std::allocator<ft::pair<const K, V> > >
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class RBT
	{
		public:
		typedef T											value_type;
		//typedef K													key_type;					//The first template parameter (Key)
		//typedef V													mapped_type;				//The second template parameter (T)
		//typedef ft::pair<const K, V> 								value_type;					//pair<const key_type,mapped_type>
		typedef Compare		 						key_compare;				//The third template parameter (Compare)	defaults to: less<key_type>
		//typedef typename std::less<extract_value(T)> 								value_compare;				//The second template parameter (Compare)	defaults to: less<value_type>
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

		typedef Node<T> * node_ptr;
	
		protected:
		node_ptr					root;
		std::allocator<Node<T> >	mem_node_control;
		key_compare					mem_compare;
		allocator_type				mem_control;
		//pointer					mem_start;
		size_type					mem_size;

		
		public:
		RBT	(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[RBT] default constructor called.\n" << COLOR_DEFAULT;
			#endif
			this->mem_compare = comp;
			this->mem_control = alloc;
			this->mem_size = 0;
			this->root = NULL;
		}

		// template <class InputIterator>
		// RBT (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_GREEN << "[RBT] InputIterator constructor called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	//TODO
		// 	(void) first;
		// 	(void) last;
		// 	this->mem_compare = comp;
		// 	this->mem_control = alloc;
			
		// }

		RBT (const RBT & Copy)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[RBT] default constructor called.\n" << COLOR_DEFAULT;
			#endif
			*this = Copy;
		}
		
		~RBT(void)
		{
			#if DEBUG
				std::cout << COLOR_RED << "[RBT] deconstructor called.\n" << COLOR_DEFAULT;
			#endif
			clearTree(this->root);
		}
		
		RBT & operator= (const RBT & Copy)
		{
			//TODO
			if (this->mem_size > 0)
				clearTree(this->root);
			this->mem_compare = Copy.mem_compare;
			this->mem_control = Copy.mem_control;
			//this->mem_node_control = Copy.mem_node_control;
			this->mem_size = 0;
			//TODO copy all nodes!
			copyTree(Copy);
			return (*this);
		}

		void copyTree(const RBT & Copy)
		{
			this->root = copyNode(Copy.root);
			if (Copy.root->left)
				copyTree(this->root, Copy.root->left);
			if (Copy.root->right)
				copyTree(this->root, Copy.root->right);
		}
		
		void	copyTree(node_ptr parent, const node_ptr NodeToCopy)
		{
			node_ptr tmp = copyNode(NodeToCopy);
			if (tmp->isLeftChild)
				parent->left = tmp;
			else
				parent->right = tmp;
			tmp->parent = parent;

			if (NodeToCopy->left)
				copyTree(tmp, NodeToCopy->left);
			if (NodeToCopy->right)
				copyTree(tmp, NodeToCopy->right);
		}
		// //***Iterators:
		// //Return iterator to beginning (public member function )
		node_ptr begin(void) const
		{
			return (getLeftNode(this->root));
		}
		node_ptr end(void) const
		{
			return (getRightNode(this->root));
		}
		node_ptr rbegin(void) const
		{
			return (getRightNode(this->root));
		}
		node_ptr rend(void) const
		{
			return (getLeftNode(this->root));
		}
		
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
			return (this->mem_node_control.max_size());
		}
		
		//***Modifiers:
		//Insert elements (public member function )
		/*
		The single element versions (1) return a pair, with its member pair::first set to an iterator pointing
		to either the newly inserted element or to the element with an equivalent key in the rbt.
		The pair::second element in the pair is set to true if a new element was inserted or false if an equivalent key already existed.
		*/
		node_ptr addNode (const value_type & input)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] insert key/value called.\n" << COLOR_DEFAULT;
			#endif
			if (this->root == NULL)
			{
				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] empty tree - creating new root node key: " << extract_key(input) << ".\n" << COLOR_DEFAULT;
				#endif
				this->root = createNode(input);
				this->root->isBlack = true;
				return (this->root);
			}

			node_ptr	checkNode = findNode(input);
			if (checkNode)
			{
				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] node with key:" << extract_key(input) << " already existing.\n" << COLOR_DEFAULT;
				#endif
				return (checkNode);
			}
			checkNode = this->root;
			node_ptr	parentNode;
			bool isLeft = false;
			while (checkNode != NULL)
			{
				if (extract_key(input) < extract_key(checkNode->data))
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
				std::cout << COLOR_YELLOW << "[RBT] new node with key:" << extract_key(input) << " created. Parent-Key: " << extract_key(parentNode->data) << " isLeftChild: " << isLeft << "\n" << COLOR_DEFAULT;
			#endif
			checkNode = createNode(input);
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
			checkColor(checkNode);
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] done with addNode\n" << COLOR_DEFAULT;
			#endif
			return (checkNode);
		}

		// node_ptr addNode (const key_type& k) //overload for SET
		// {
		// 	return (addNode(ft::pair<K, K>(k, k)));
		// }
		// void printTree(void)
		// {
		// 	if (this->root)
		// 	{
		// 		sdt::cout << "[" << root->data.first << ":" << root->data.second << "]\n";
		// 		printTreeNode(this->root);
		// 	}
		// }
		// void printTreeNode(node * nd)
		// {
		// 	//if (nd)
		// 	//	sdt::cout << "[" << nd->data.first << ":" << nd->data.second << "]\n";
		// 	if (nd->left)
		// 		sdt::cout << "[" << nd->left->data.first << ":" << nd->data.second << "]";
		// }
		size_type erase (const value_type& input)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] function erase key: " << extract_key(input) << " called.\n" << COLOR_DEFAULT;
			#endif
			node_ptr	nodeToDelete = this->findNode(input);
			if (nodeToDelete)
			{
				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] found node to delete in tree key:value " << extract_key(nodeToDelete->data) << ":" << extract_value(nodeToDelete->data) << " .\n" << COLOR_DEFAULT;
				#endif

				node_ptr nodeReplaceDeleted = getNextNode(nodeToDelete);
				if (!nodeReplaceDeleted)
				{
					#if DEBUG
						std::cout << COLOR_YELLOW << "[RBT] no node to replace deleted one in Tree.\n" << COLOR_DEFAULT;
					#endif
					if (nodeToDelete == this->root)
						this->root = NULL;
					if (nodeToDelete->isLeftChild)
						nodeToDelete->parent->left = NULL;
					else
						nodeToDelete->parent->right = NULL;
					deleteNode(nodeToDelete);
					//checkColor
					blackNodes();
					return (1);
				}
				
				if (nodeToDelete == this->root)
					this->root = nodeReplaceDeleted;
				node_ptr	nodeMoveUp = getNextNode(nodeReplaceDeleted);
				//node *nodeHelp = NULL;
				if (nodeMoveUp)
				{
					#if DEBUG
						std::cout << COLOR_YELLOW << "[RBT] found nodeMoveUp key:value " << extract_key(nodeMoveUp->data) << ":" << extract_value(nodeMoveUp->data) << " .\n" << COLOR_DEFAULT;
					#endif
					nodeMoveUp->parent = nodeReplaceDeleted->parent;
					if (nodeReplaceDeleted->isLeftChild)
					{
						nodeMoveUp->isLeftChild = true;
						nodeMoveUp->parent->left = nodeMoveUp;
					}
					else
					{
						nodeMoveUp->isLeftChild = false;
						nodeMoveUp->parent->right = nodeMoveUp;
					}
				}
				else
				{
					//nodeHelp = copyNode(*nodeReplaceDeleted);
					if (nodeReplaceDeleted->isLeftChild)
						nodeReplaceDeleted->parent->left = NULL;
					else
						nodeReplaceDeleted->parent->right = NULL;
				}
				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] found nodeReplaceDeleted key:value " << extract_key(nodeReplaceDeleted->data) << ":" << extract_value(nodeReplaceDeleted->data) << " .\n" << COLOR_DEFAULT;
				#endif
				nodeReplaceDeleted->parent = nodeToDelete->parent;
				if (nodeReplaceDeleted->parent)
				{
					if (nodeToDelete->isLeftChild)
					{
						nodeReplaceDeleted->isLeftChild = true;
						nodeReplaceDeleted->parent->left = nodeReplaceDeleted;
					}
					else
					{
						nodeReplaceDeleted->isLeftChild = false;
						nodeReplaceDeleted->parent->right = nodeReplaceDeleted;
					}
				}
				nodeReplaceDeleted->isBlack = true;
				if (nodeToDelete->left != nodeReplaceDeleted)
					nodeReplaceDeleted->left = nodeToDelete->left;
				if (nodeReplaceDeleted->left)
				{
					nodeReplaceDeleted->left->parent = nodeReplaceDeleted;
					//nodeReplaceDeleted->left->isBlack = false;
				}
				nodeReplaceDeleted->right = nodeToDelete->right;
				if (nodeReplaceDeleted->right)
				{
					nodeReplaceDeleted->right->parent = nodeReplaceDeleted;
					//nodeReplaceDeleted->right->isBlack = false;
				}
				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] going to checkColor.\n" << COLOR_DEFAULT;
				#endif
				
				if (nodeMoveUp)
					checkColor(nodeMoveUp);
				else
				{
					//std::cout << "in else branch\n";
					//what to do here????
					// if (nodeReplaceDeleted->left)
					// 	checkColor(*nodeReplaceDeleted->left);
					// if (nodeReplaceDeleted->right)
					// 	checkColor(*nodeReplaceDeleted->right);
					//checkColor(*nodeHelp);
					//deleteNode(nodeHelp);
				}
				deleteNode(nodeToDelete);
				//std::cout << "number of black nodes: " << 
				blackNodes();// << "\n";
				return (1);
			}
			return (0);
		}
		
		node_ptr	copyNode(const node_ptr NodeToCopy)
		{
			node_ptr	newNode = this->mem_node_control.allocate(1);
			this->mem_control.construct(&(newNode->data), NodeToCopy->data);
			++this->mem_size;
			newNode->parent = NodeToCopy->parent;
			newNode->left = NodeToCopy->left;
			newNode->right = NodeToCopy->right;
			newNode->isBlack = NodeToCopy->isBlack;
			newNode->isLeftChild = NodeToCopy->isLeftChild;
			return (newNode);
		}

		node_ptr	getNextNode(node_ptr node)
		{
			if (node->left && node->left->right)
				return (getRightNode(node->left->right));
			if (node->left)
				return (node->left);
			if (node->right)
				return (node->right);
			return (NULL);
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
		void swap (RBT & x)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] swap called.\n" << COLOR_DEFAULT;
			#endif
			RBT &tmp = x;
			x.mem_compare = this->mem_compare;
			x.mem_control = this->mem_control;
			x.mem_node_control = this->mem_node_control;
			x.mem_size = this->mem_size;
			x.root = this->root;
			this->mem_compare = tmp.mem_compare;
			this->mem_control = tmp.mem_control;
			this->mem_node_control = tmp.mem_node_control;
			this->mem_size = tmp.mem_size;
			this->root = tmp.root;
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
		key_compare key_comp(void) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] key_comp called.\n" << COLOR_DEFAULT;
			#endif
			return (key_compare());
		}
		//Return value comparison object (public member function )
		// value_compare value_comp(void) const
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_YELLOW << "[RBT] value_comp called.\n" << COLOR_DEFAULT;
		// 	#endif
		// 	return (value_compare());
		// }

		// //***Operations:
		//Count elements with a specific key (public member function )
		size_type count (const value_type& input) const
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] count called.\n" << COLOR_DEFAULT;
			#endif
			node_ptr nd = this->findNode(input);
			if (nd)
				return (1);
			return (0);
		}

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
		void	checkColor(node_ptr node)
		{
			if (!node)
				return ;
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] checkColor key:value " << extract_key(node->data) << ":" << extract_value(node->data) << " called.\n" << COLOR_DEFAULT;
			#endif
			if (node == this->root)
			{
				if (node->isBlack == false)
					node->isBlack = true;
				return ;
			}
			if (!node->isBlack && !node->parent->isBlack)
				correctTree(node);
			checkColor(node->parent);
		}
		
		void	correctTree(node_ptr node)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] correctTree function called at node: " << extract_key(node->data) << "\n" << COLOR_DEFAULT;
			#endif
			if (node->parent->isLeftChild) //Aunt is node->parent->parent->right
			{
				if (node->parent->parent->right == NULL || node->parent->parent->right->isBlack)
					return (rotate(node));
				if (node->parent->parent->right != NULL)
				{
					node->parent->parent->right->isBlack = true;
					#if DEBUG
						std::cout << COLOR_YELLOW << "[RBT] changed color at " << extract_key(node->parent->parent->right->data) << " to black\n" << COLOR_DEFAULT;
					#endif
				}
				node->parent->parent->isBlack = false;
				node->parent->isBlack = true;
				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] changed color at " << extract_key(node->parent->parent->data) << " to red\n" << COLOR_DEFAULT;
					std::cout << COLOR_YELLOW << "[RBT] changed color at " << extract_key(node->parent->data) << " to black\n" << COLOR_DEFAULT;
					std::cout << COLOR_YELLOW << "[RBT] " << extract_key(node->data) << " parent isLeftChild: true\n" << COLOR_DEFAULT;
				#endif
				return ;
			}
			//Aunt is node->parent->parent->left
			if (node->parent->parent->left == NULL || node->parent->parent->left->isBlack)
				return (rotate(node));
			if (node->parent->parent->left != NULL)
			{
				node->parent->parent->left->isBlack = true;
				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] changed color at " << extract_key(node->parent->parent->left->data) << " to black\n" << COLOR_DEFAULT;
				#endif
			}
			node->parent->parent->isBlack = false;
			node->parent->isBlack = true;
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] changed color at " << extract_key(node->parent->parent->data) << " to red\n" << COLOR_DEFAULT;
				std::cout << COLOR_YELLOW << "[RBT] changed color at " << extract_key(node->parent->data) << " to black\n" << COLOR_DEFAULT;
				std::cout << COLOR_YELLOW << "[RBT] " << extract_key(node->data) << " parent isLeftChild: false\n" << COLOR_DEFAULT;
			#endif
			return ;
		}
		
		void	rotate(node_ptr node)
		{
			if (node->isLeftChild)
			{
				if (node->parent->isLeftChild)
				{
					rightRotate(node->parent->parent);
					node->isBlack = false;
					node->parent->isBlack = true;
					if (node->parent->right != NULL)
						node->parent->right->isBlack = false;
					return ;
				}
				rightLeftRotate(node->parent->parent);
				node->isBlack = true;
				node->right->isBlack = false;
				node->left->isBlack = false;
				return ;
			}
			if (!node->parent->isLeftChild)
			{
				leftRotate(node->parent->parent);
				node->isBlack = false;
				node->parent->isBlack = true;
				if (node->parent->left != NULL)
					node->parent->left->isBlack = false;
				return ;
			}
			leftRightRotate(node->parent->parent);
			node->isBlack = true;
			node->right->isBlack = false;
			node->left->isBlack = false;
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
		void	rightRotate(node_ptr node) //grandparent node
		{
			#if DEBUG
				std::cout << COLOR_BLUE<< "[RBT] rightRotate called - " << extract_key(node->data) << "\n" << COLOR_DEFAULT;
			#endif
			node_ptr tmp = node->left;
			node->left = tmp->right;
			if (node->left != NULL)
			{
				node->left->parent = node;
				node->left->isLeftChild = true;
			}
			if (node->parent == NULL) //Root node
			{
				this->root = tmp;
				tmp->parent = NULL;
				#if DEBUG
					std::cout << COLOR_BLUE<< "[RBT] changed root node - " << extract_key(this->root->data) << "\n" << COLOR_DEFAULT;
				#endif
			}
			else
			{
				tmp->parent = node->parent;
				if (node->isLeftChild)
				{
					tmp->isLeftChild = true;
					tmp->parent->left = tmp;
				}
				else
				{
					tmp->isLeftChild = false;
					tmp->parent->right = tmp;
				}
			}
			tmp->right = node;
			node->isLeftChild = false;
			node->parent = tmp;
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
		void	leftRotate(node_ptr node) //grandparent node
		{
			#if DEBUG
				std::cout << COLOR_BLUE<< "[RBT] leftRotate called - " << extract_key(node->data) << "\n" << COLOR_DEFAULT;
			#endif
			node_ptr tmp = node->right;
			node->right = tmp->left;
			if (node->right != NULL)
			{
				node->right->parent = node;
				node->right->isLeftChild = false;
			}
			if (node->parent == NULL) //Root node
			{
				this->root = tmp;
				tmp->parent = NULL;
				#if DEBUG
					std::cout << COLOR_BLUE<< "[RBT] changed root node - " << extract_key(this->root->data) << "\n" << COLOR_DEFAULT;
				#endif
			}
			else
			{
				tmp->parent = node->parent;
				if (node->isLeftChild)
				{
					tmp->isLeftChild = true;
					tmp->parent->left = tmp;
				}
				else
				{
					tmp->isLeftChild = false;
					tmp->parent->right = tmp;
				}
			}
			tmp->left = node;
			node->isLeftChild = true;
			node->parent = tmp;
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
		void	leftRightRotate(node_ptr node)
		{
			leftRotate(node->left);
			rightRotate(node);
		}
		void	rightLeftRotate(node_ptr node)
		{
			rightRotate(node->right);
			leftRotate(node);
		}

		node_ptr createNode(const value_type & input)
		{
			node_ptr newNode = this->mem_node_control.allocate(1);
			//newNode->data = this->mem_control.allocate(1);
			this->mem_control.construct(&(newNode->data), input);
			++this->mem_size;
			newNode->isBlack = false;
			newNode->isLeftChild = false;
			newNode->parent = NULL;
			newNode->left = NULL;
			newNode->right = NULL;
			return (newNode);
		}
		void	deleteNode(node_ptr node)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] deleteNode called - " << extract_key(node->data) << "\n" << COLOR_DEFAULT;
			#endif
			//this->mem_control.destroy(&(nd->data));
			//this->mem_control.deallocate(nd->data, 1);
			--this->mem_size;
			this->mem_node_control.deallocate(node, 1);
		}
		
		node_ptr getSibling(node_ptr node) const
		{
			if (node->parent == NULL)
				return (NULL);
			if (node->isLeftchild)
				return (node->parent->right);
			return (node->parent->left);
		}
		node_ptr getLeftNode(node_ptr node) const
		{
			if (!node)
				return (NULL);
			node_ptr	tmp = node;
			while (tmp && tmp->left)
				tmp = tmp->left;
			return (tmp);
		}
		
		node_ptr getRightNode(node_ptr node) const
		{
			if (!node)
				return (NULL);
			node_ptr	tmp = node;
			while (tmp && tmp->right)
				tmp = tmp->right;
			return (tmp);
		}
		
		void	clearTree(node_ptr node)
		{
			if (!node)
				return ;
			if (node->left)
				clearTree(node->left);
			if (node->right)
				clearTree(node->right);
			deleteNode(node);
		}
		
		public:
		node_ptr findNode(const value_type & input)
		{
			node_ptr tmp = this->root;
			#if DEBUG
				std::cout << COLOR_BLUE << "findNode called node: " << extract_key(input) << "\n" << COLOR_DEFAULT;
			#endif
			while (tmp)
			{
				#if DEBUG
					std::cout << COLOR_BLUE << "findNode looking at node: " << extract_key(tmp->data) << "\n" << COLOR_DEFAULT;
				#endif
				if (extract_key(tmp->data) == extract_key(input))
				{
					#if DEBUG
						std::cout << COLOR_BLUE << "findNode found node: " << extract_key(tmp->data) << "\n" << COLOR_DEFAULT;
					#endif
					return (tmp);
				}
				if (extract_key(input) < extract_key(tmp->data))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			#if DEBUG
				std::cout << COLOR_BLUE << "findNode could not find node: " << extract_key(tmp) << "\n" << COLOR_DEFAULT;
			#endif
			return (tmp);
		}

		int	height(void)
		{
			if (this->root == NULL)
				return (0);
			return (height(this->root) - 1);
		}

		int	height(node_ptr node)
		{
			if (node == NULL)
				return (0);
			int	leftHeight = height(node->left) + 1;
			int	rightHeight = height(node->right) + 1;
			if (leftHeight > rightHeight)
				return (leftHeight);
			return (rightHeight);
		}
		
		int	blackNodes(void)
		{
			return (blackNodes(this->root));
		}
		
		int	blackNodes(node_ptr node)
		{
			if (node == NULL)
				return (1);
			#if DEBUG
				std::cout << COLOR_BLUE << "blackNodes called node: " << extract_key(node->data) << " isBlack: " << node->isBlack << "\n" << COLOR_DEFAULT;
			#endif
			int	rightBlackNodes = blackNodes(node->right);
			int	leftBlackNodes = blackNodes(node->left);
			if (rightBlackNodes != leftBlackNodes)
			{
				// throw error fix the tree
				#if DEBUG
					std::cout << COLOR_BLUE << "imbalance in RBT! node: " << extract_key(node->data) << "\n" << COLOR_DEFAULT;
				#endif
				if (rightBlackNodes > leftBlackNodes)
				{
					//correctTree(*nd->right->left);
					if (height() > 1)
						leftRotate(node);
					else
					{
						node->right->isBlack = false;
						#if DEBUG
							std::cout << COLOR_BLUE << "changed color to red node: " << extract_key(node->data) << "\n" << COLOR_DEFAULT;
						#endif
					}
					if (node-> parent && node->parent->right)
					{
						node->parent->right->isBlack = true;
						#if DEBUG
							std::cout << COLOR_BLUE << "changed color to black node: " << extract_key(node->data) << "\n" << COLOR_DEFAULT;
						#endif
					}
				}
				else
				{
					rightRotate(node);
					//correctTree(*nd->left->right);
				}
			}
			if (node->isBlack)
				++leftBlackNodes;
			return (leftBlackNodes);
		}

		// void	printTree(void)
		// {
		// 	this->TreePicture.clear();
		// 	this->MaxElementsAtMaxLvl = twoPowerOf(this->height());
		// 	Order = 0;
		// 	for (int i = 0, TreeHeight = this->height(); i <= TreeHeight; ++i)
		// 		TreePicture[i] += whiteSpace(TreeHeight * 2 + 1);
		// 	printTree(this->root, 0, 0);
		// 	for (int i = 0, TreeHeight = this->height(); i <= TreeHeight; ++i)
		// 		std::cout << TreePicture[i] << "\n";
		// }
		
		// void	printTree(node *nd, size_t level, size_t order)
		// {
		// 	TreePicture[level] += "[" + nd->first + "]"
		// 	++level;
		// 	order = order * 2;
		// 	if (nd->left)
		// 		printTree(nd->left, level, order);
		// 	if (nd->right)
		// 		printTree(nd->right, level, order + 1);
		// }
		
		// private:
		// ft::vector<std::string> TreePicture;
		// size_t	MaxElementsAtMaxLvl;
		// size_t	Order;

		// size_t & twoPowerOf(size_t & value)
		// {
		// 	return (1 << value);
		// }
		
	}; // class RBT
	
} // namespace ft
