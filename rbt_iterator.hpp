/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 09:52:47 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/19 16:30:18 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//#include <iterator>
#include <cstddef>
#include "RBT.hpp"
//#include "pair.hpp"
//#include "algorithm.hpp"
//#include "rbt_reverse_iterator.hpp"
//class RBT;

namespace ft
{
	//template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	//class RBT;
	template <class Key, class Tree>
	class rbt_iterator //: public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
		typedef Key 																					key_type;
		//typedef T																						mapped_type;
		typedef typename Tree::value_type 																value_type;
		//typedef ft::pair<const key_type, mapped_type>													value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference				reference;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category		iterator_category;
		
		//typedef typename ft::RBT<key_type, mapped_type>::node * node_ptr;
		//typedef value_type *node_ptr;
		private:
		// node_ptr ptr;
		// node_ptr smallest;
		// node_ptr biggest;
		typedef Node<Key> * node_ptr;
		
		node_ptr ptr;
		node_ptr smallest;
		node_ptr biggest;
		
		public:
		rbt_iterator(void) : ptr(NULL), smallest(NULL), biggest(NULL)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_iterator] default constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		rbt_iterator(node_ptr input, node_ptr small, node_ptr big) : ptr(input), smallest(small), biggest(big)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_iterator] constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		rbt_iterator(rbt_iterator const & copy) : ptr(copy.ptr), smallest(copy.smallest), biggest(copy.biggest)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_iterator] copy constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		// template <class It>
		// rbt_iterator(const rbt_iterator<It, nonconst_T>& i,
		// typename ft::enable_if<ft::is_same<It, nonconst_T>::value>::type* = NULL) : ptr(i.address())
		// {
		// 	#if DEBUG
		// 		std::cout << COLOR_GREEN << "[rbt_iterator] const constructor called.\n" << COLOR_DEFAULT;
		// 	#endif
		// }
		~rbt_iterator(void)
		{
			#if DEBUG
				std::cout << COLOR_RED << "[rbt_iterator] deconstructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		rbt_iterator const & operator=(rbt_iterator const & rhs)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[rbt_iterator] operator= called.\n" << COLOR_DEFAULT;
			#endif
			this->ptr = rhs.ptr;
			this->smallest = rhs.smallest;
			this->biggest = rhs.biggest;
			return (*this);
		}
		pointer	address(void) const
		{
			return (this->ptr);
		}

		rbt_iterator &	operator++(void)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[rbt_iterator] operator++() called.\n" << COLOR_DEFAULT;
			#endif
			increment();
			return (*this);
		}
		rbt_iterator	operator++(int)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[rbt_iterator] operator++(int) called.\n" << COLOR_DEFAULT;
			#endif
			rbt_iterator tmp = *this;
			increment();
			return (tmp);
		}
		rbt_iterator &	operator--(void)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[rbt_iterator] operator--() called.\n" << COLOR_DEFAULT;
			#endif
			decrement();
			return (*this);
		}
		rbt_iterator	operator--(int)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[rbt_iterator] operator--(int) called.\n" << COLOR_DEFAULT;
			#endif
			rbt_iterator tmp = *this;
			decrement();
			return (tmp);
		}

		key_type *	operator->()
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[rbt_iterator] operator-> called.\n" << COLOR_DEFAULT;
			#endif
			return (&(this->ptr->data));
		}

		key_type &	operator*()
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[rbt_iterator] operator* called.\n" << COLOR_DEFAULT;
			#endif
			//return (static_cast<node_ptr>(this->ptr)->data);
			return (this->ptr->data);
		}
		
		bool	operator==(rbt_iterator const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[rbt_iterator] operator== called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr == rhs.ptr);
		}
		bool	operator!=(rbt_iterator const & rhs) const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[rbt_iterator] operator!= called.\n" << COLOR_DEFAULT;
			#endif
			return (this->ptr != rhs.ptr);
		}

		private:
		void increment(void)
		{
			if (!this->ptr)
				this->ptr = this->smallest;
			else if (this->ptr->right)
			{
				this->ptr = this->ptr->right;
				while (this->ptr->left)
					this->ptr = this->ptr->left;
			}
			else
			{
				node_ptr tmp = this->ptr->parent;
				while (tmp && this->ptr == tmp->right)
				{
					this->ptr = tmp;
					tmp = tmp->parent;
				}
				this->ptr = tmp;
			}
		}
		
		void decrement(void)
		{
			if (!this->ptr)
				this->ptr = this->biggest;
			else if (this->ptr->left)
			{
				this->ptr = this->ptr->left;
				while (this->ptr->right)
					this->ptr = this->ptr->right;
			}
			else
			{
				node_ptr tmp = this->ptr->parent;
				while (tmp && this->ptr == tmp->left)
				{
					this->ptr = tmp;
					tmp = tmp->parent;
				}
				this->ptr = tmp;
			}
		}
	}; //rbt_iterator

} // namespace ft


namespace ft
{
	template <class Iterator>
	class rbt_reverse_iterator
	{
		public:
		typedef Iterator												iterator_type;		//Iterator's type
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;	//Preserves Iterator's category
		typedef typename iterator_traits<Iterator>::value_type			value_type;			//Preserves Iterator's value type
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;	//Preserves Iterator's difference type
		typedef typename iterator_traits<Iterator>::pointer				pointer;			//Preserves Iterator's pointer type
		typedef typename iterator_traits<Iterator>::reference			reference;			//Preserves Iterator's reference type
		/*
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T *								pointer;
			typedef T &								reference;
			typedef random_access_iterator_tag		iterator_category;
		*/
		private:
		iterator_type	_base;

		public:
		rbt_reverse_iterator(void)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_reverse_iterator] default constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		explicit rbt_reverse_iterator (iterator_type it) : _base(it)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_reverse_iterator] constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		rbt_reverse_iterator (const reverse_iterator<Iterator>& rev_it) : _base(rev_it._base)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_reverse_iterator] copy constructor called.\n" << COLOR_DEFAULT;
			#endif
		}

		iterator_type base() const
		{
			return (this->_base);
		}
	}; //rbt_reverse_iterator

} // namespace ft
