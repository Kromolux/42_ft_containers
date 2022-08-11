/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:03:32 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/11 14:41:41 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Utils.hpp"
#include "vector.hpp"

/*
	Rules:
	1. Every node is red or black
	2. Root is always black.
	3. New insertions are always red.
	4. Every path from root - leaf has the same number of black nodes.
	5. No path ca have two consecutive red nodes.
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


	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class RBT
	{
		public:
		typedef T													value_type;
		typedef Compare		 										key_compare;				//The third template parameter (Compare)	defaults to: less<key_type>
		typedef Alloc												allocator_type;				//The fourth template parameter (Alloc)	defaults to: allocator<value_type>
		typedef typename allocator_type::reference					reference;					//for the default allocator: value_type&
		typedef typename allocator_type::const_reference			const_reference;			//for the default allocator: const value_type&
		typedef typename allocator_type::pointer					pointer;					//for the default allocator: value_type*
		typedef typename allocator_type::const_pointer				const_pointer;				//for the default allocator: const value_type*
		typedef typename allocator_type::difference_type			difference_type;			//a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
		typedef typename allocator_type::size_type					size_type;					//an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t

		typedef Node<T> * node_ptr;
	
		protected:
		node_ptr					root;
		std::allocator<Node<T> >	mem_node_control;
		key_compare					mem_compare;
		allocator_type				mem_control;
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

		RBT (const RBT & Copy)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[RBT] default constructor called.\n" << COLOR_DEFAULT;
			#endif
			this->mem_compare = Copy.mem_compare;
			this->mem_control = Copy.mem_control;
			this->mem_node_control = Copy.mem_node_control;
			this->mem_size = 0;
			copyTree(Copy);
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
			if (this->mem_size > 0)
				clearTree(this->root);
			this->mem_compare = Copy.mem_compare;
			this->mem_control = Copy.mem_control;
			this->mem_node_control = Copy.mem_node_control;
			this->mem_size = 0;
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
				std::cout << COLOR_YELLOW << "[RBT] insert key:value " << extract_key(input) << ":" << extract_value(input) << " called.\n" << COLOR_DEFAULT;
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
				if (this->mem_compare(extract_key(input),extract_key(checkNode->data)))
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

		void printTree(void) const
		{
			if (this->root)
			{
				std::cout << "\n###################################\n";
				printTreeNode(this->root, 0);
				std::cout << "\n###################################\n";
			}
		}

		void printTreeNode(node_ptr nd, size_t depth) const
		{
			for (size_t i = 0; i < depth; ++i)
				std::cout << "    ";

			if (nd)
			{
				if (!nd->isLeftChild)
					std::cout << "⇗";
				else
					std::cout << "⇘";
				if (!nd->isBlack)
					std::cout << COLOR_RED;
				std::cout << "[" << extract_key(nd->data) << "]\n" << COLOR_DEFAULT;
			}

			if (nd->right)
				printTreeNode(nd->right, depth +1);
			else
			{
				for (size_t i = 0; i < depth + 1; ++i)
					std::cout << "    ";
				std::cout << "⇗[NULL]\n";
			}

			if (nd->left)
				printTreeNode(nd->left, depth +1);
			else
			{
				for (size_t i = 0; i < depth + 1; ++i)
					std::cout << "    ";
				std::cout << "⇘[NULL]\n";
			}
		}

		void	fixTreeAfterErase(node_ptr leafNode)
		{
			node_ptr sibling = getSibling(leafNode);
			node_ptr nephew = getNephew(leafNode);
			node_ptr niece = getNiece(leafNode);
			node_ptr parent = leafNode->parent;

			while (true)
			{
				sibling = getSibling(leafNode);
				nephew = getNephew(leafNode);
				niece = getNiece(leafNode);
				parent = leafNode->parent;
				if (parent == NULL || leafNode->isBlack == false) //case 0 works
				{
					#if DEBUG
						std::cout << COLOR_YELLOW << "[RBT] case 0 works!\n" << COLOR_DEFAULT;
					#endif
					break;
				}
				if (sibling && sibling->isBlack == false)		//case 1 works
				{
					#if DEBUG
						std::cout << COLOR_YELLOW << "[RBT] case 1 works!\n" << COLOR_DEFAULT;
					#endif
					parent->isBlack = false;
					sibling->isBlack = true;
					
					RotateToParent(sibling);
				}
				else if (nephew && nephew->isBlack == false)	//case 2 works
				{
					#if DEBUG
						std::cout << COLOR_YELLOW << "[RBT] case 2 works!\n" << COLOR_DEFAULT;
						//printTree();
					#endif
					if (sibling)
						sibling->isBlack = parent->isBlack;
					parent->isBlack = true;
					nephew->isBlack = true;
					RotateToParent(sibling);
					leafNode = this->root;
					break;
				}
				else if (niece && niece->isBlack == false)		//case 3
				{
					#if DEBUG
						std::cout << COLOR_YELLOW << "[RBT] case 3 \n" << COLOR_DEFAULT;
					#endif
					niece->isBlack = true;
					if (sibling)
						sibling->isBlack = false;
					RotateToParent(niece);
				}
				else											//case 4 works
				{
					#if DEBUG
						std::cout << COLOR_YELLOW << "[RBT] case 4 works\n" << COLOR_DEFAULT;
					#endif
					if (sibling)
						sibling->isBlack = false;
					leafNode = leafNode->parent;
					//break;
				}
				
			}
			leafNode->isBlack = true;
		}

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
					fixTreeAfterErase(nodeToDelete);
					cutLeaf(nodeToDelete);
					deleteNode(nodeToDelete);
					return (1);
				}

				#if DEBUG
					std::cout << COLOR_YELLOW << "[RBT] node to replace deleted one in Tree " << extract_key(nodeReplaceDeleted->data) << "\n" << COLOR_DEFAULT;
				#endif
				
				swapNodes(nodeToDelete, nodeReplaceDeleted);
				if (nodeReplaceDeleted->left)
				{
					swapNodes(nodeReplaceDeleted, nodeReplaceDeleted->left);
					nodeReplaceDeleted = nodeReplaceDeleted->left;
				}

				fixTreeAfterErase(nodeReplaceDeleted);
				cutLeaf(nodeReplaceDeleted);
				this->root->isBlack = true;
				deleteNode(nodeReplaceDeleted);
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

		//Swap content (public member function )
		void swap (RBT & x)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] swap called.\n" << COLOR_DEFAULT;
			#endif
			node_ptr					tmp_root				= x.root;
			std::allocator<Node<T> >	tmp_mem_node_control	= x.mem_node_control;
			key_compare					tmp_mem_compare			= x.mem_compare;
			allocator_type				tmp_mem_control			= x.mem_control;
			size_type					tmp_mem_size			= x.mem_size;

			x.mem_compare = this->mem_compare;
			x.mem_control = this->mem_control;
			x.mem_node_control = this->mem_node_control;
			x.mem_size = this->mem_size;
			x.root = this->root;

			this->mem_compare = tmp_mem_compare;
			this->mem_control = tmp_mem_control;
			this->mem_node_control = tmp_mem_node_control;
			this->mem_size = tmp_mem_size;
			this->root = tmp_root;
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
		void	getNodeInfo(node_ptr node)
		{
			std::cout << COLOR_GREEN<< "[RBT] function getNodeInfo node: " << extract_key(node->data) << " called.\n" << COLOR_DEFAULT;
			if (node->parent)
				std::cout << COLOR_YELLOW << "[RBT] parent->: [" << extract_key(node->parent->data) << "]\n" << COLOR_DEFAULT;
			else
				std::cout << COLOR_YELLOW << "[RBT] parent->: [NULL]\n" << COLOR_DEFAULT;
			if (node->left)
				std::cout << COLOR_YELLOW << "[RBT] left->  : [" << extract_key(node->left->data) << "]\n" << COLOR_DEFAULT;
			else
				std::cout << COLOR_YELLOW << "[RBT] left->  : [NULL]\n" << COLOR_DEFAULT;
			if (node->right)
				std::cout << COLOR_YELLOW << "[RBT] right-> : [" << extract_key(node->right->data) << "]\n" << COLOR_DEFAULT;
			else
				std::cout << COLOR_YELLOW << "[RBT] right-> : [NULL]\n" << COLOR_DEFAULT;
			std::cout << COLOR_YELLOW << "[RBT] isLeftChild : " << node->isLeftChild << "\n" << COLOR_DEFAULT;
		}

		void	swapNodes(node_ptr nodeA, node_ptr nodeB)
		{
			T tmp(nodeA->data);
			this->mem_control.destroy(&(nodeA->data));
			this->mem_control.construct(&(nodeA->data), nodeB->data);
			this->mem_control.destroy(&(nodeB->data));
			this->mem_control.construct(&(nodeB->data), tmp);
		}

		void	cutLeaf(node_ptr LeafNode)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] cutLeaf key:value " << extract_key(LeafNode->data) << ":" << extract_value(LeafNode->data) << " called.\n" << COLOR_DEFAULT;
				getNodeInfo(LeafNode);
			#endif
			if (LeafNode->parent == NULL)
				this->root = NULL;
			else if (LeafNode->isLeftChild)
				LeafNode->parent->left = NULL;
			else
				LeafNode->parent->right = NULL;
		}

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
				correctTreeShort(node);
			checkColor(node->parent);
		}

		void	correctTreeShort(node_ptr node)
		{
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] correctTree function called at node: " << extract_key(node->data) << "\n" << COLOR_DEFAULT;
			#endif
			node_ptr aunt = getAunt(node);
			#if DEBUG
				if (aunt)
					std::cout << COLOR_MAGENTA << "[RBT] aunt->: [" << extract_key(aunt->data) << "]\n" << COLOR_DEFAULT;
				else
					std::cout << COLOR_MAGENTA << "[RBT] aunt->: [NULL]\n" << COLOR_DEFAULT;
			#endif
			if ((aunt && aunt->isBlack) || !aunt)
				return (rotateShort(node));
			aunt->isBlack = true;
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] changed color at " << extract_key(node->parent->parent->right->data) << " to black\n" << COLOR_DEFAULT;
			#endif
			node->parent->parent->isBlack = false;
			node->parent->isBlack = true;
			#if DEBUG
				std::cout << COLOR_YELLOW << "[RBT] changed color at " << extract_key(node->parent->parent->data) << " to red\n" << COLOR_DEFAULT;
				std::cout << COLOR_YELLOW << "[RBT] changed color at " << extract_key(node->parent->data) << " to black\n" << COLOR_DEFAULT;
				std::cout << COLOR_YELLOW << "[RBT] " << extract_key(node->data) << " parent isLeftChild: true\n" << COLOR_DEFAULT;
			#endif
			return ;
		}

		void	rotateShort(node_ptr node)
		{
			node_ptr parent = node->parent;
			node_ptr sibling;

			if (node->isLeftChild == parent->isLeftChild)
			{
				RotateToParent(node->parent);
				node->isBlack = false;
				parent->isBlack = true;
				sibling = getSibling(node);
				if (sibling != NULL)
					sibling->isBlack = false;
				return ;
			}
			RotateToParent(node);
			RotateToParent(node);
			node->isBlack = true;
			node->right->isBlack = false;
			node->left->isBlack = false;
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

		void	rightRotate(node_ptr node) //grandparent node - node that changes position
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


		void	RotateToParent(node_ptr node)
		{
			#if DEBUG
				std::cout << COLOR_BLUE<< "[RBT] RotateToParent called node: " << extract_key(node->data) << " parent: " << extract_key(node->parent->data) << "\n" << COLOR_DEFAULT;
			#endif
			if (node->isLeftChild)
				rightRotate(node->parent);
			else
				leftRotate(node->parent);
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

		node_ptr createNode(const value_type & input)
		{
			node_ptr newNode = this->mem_node_control.allocate(1);
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
			--this->mem_size;
			this->mem_node_control.deallocate(node, 1);
		}
		
		node_ptr getSibling(node_ptr node) const
		{
			if (node->parent == NULL)
				return (NULL);
			if (node->isLeftChild)
				return (node->parent->right);
			return (node->parent->left);
		}

		node_ptr getAunt(node_ptr node) const
		{
			if (node->parent && node->parent->parent)
			{
				if (node->parent->isLeftChild)
					return (node->parent->parent->right);
				else
					return (node->parent->parent->left);
			}
			return (NULL);
		}

		node_ptr getNephew(node_ptr node) const
		{
			node_ptr sibling = getSibling(node);
			if (sibling)
			{
				if (node->isLeftChild)
					return (sibling->right);
				else
					return (sibling->left);
			}
			return (NULL);
		}

		node_ptr getNiece(node_ptr node) const
		{
			node_ptr sibling = getSibling(node);
			if (sibling)
			{
				if (node->isLeftChild)
					return (sibling->left);
				else
					return (sibling->right);
			}
			return (NULL);
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
		node_ptr findNode(const value_type & input) const
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
				if (!this->mem_compare(extract_key(tmp->data),extract_key(input)) && !this->mem_compare(extract_key(input),extract_key(tmp->data)))
				{
					#if DEBUG
						std::cout << COLOR_BLUE << "findNode found node: " << extract_key(tmp->data) << "\n" << COLOR_DEFAULT;
					#endif
					return (tmp);
				}
				if (this->mem_compare(extract_key(input),extract_key(tmp->data)))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			#if DEBUG
				std::cout << COLOR_BLUE << "findNode could not find node: " << extract_key(tmp) << "\n" << COLOR_DEFAULT;
			#endif
			return (NULL);
		}

		size_t	height(void) const
		{
			if (this->root == NULL)
				return (0);
			return (height(this->root) - 1);
		}

		size_t	height(node_ptr node) const
		{
			if (node == NULL)
				return (0);
			int	leftHeight = height(node->left) + 1;
			int	rightHeight = height(node->right) + 1;
			if (leftHeight > rightHeight)
				return (leftHeight);
			return (rightHeight);
		}
	}; // class RBT
	
} // namespace ft
