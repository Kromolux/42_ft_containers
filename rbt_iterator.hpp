/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 09:52:47 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/21 19:09:47 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstddef>
#include "RBT.hpp"

namespace ft
{
	template <class Key, bool isConst>
	class rbt_iterator
	{
		public:
		typedef Key 																					key_type;
		typedef const key_type																			const_key_type;
		typedef	key_type																				normal_key_type;
		typedef typename choose<isConst, const_key_type, normal_key_type>::type							value_type;
		typedef typename std::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
		typedef typename std::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
		typedef typename std::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
		typedef typename std::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
		
		private:
		typedef const Node<Key>		const_node;
		typedef Node<Key>			normal_node;
		typedef typename choose<isConst, const_node, normal_node>::type * node_ptr;
		
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

		template<typename TypeKey, bool TypeIsConst>
		rbt_iterator(rbt_iterator<TypeKey, TypeIsConst> const & other) : ptr(other.getPtr()), smallest(other.getSmall()), biggest(other.getBig())
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_iterator] template constructor called.\n" << COLOR_DEFAULT;
			#endif
		}

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

		node_ptr	getPtr(void) const
		{
			return (this->ptr);
		}
		
		node_ptr	getSmall(void) const
		{
			return (this->smallest);
		}

		node_ptr	getBig(void) const
		{
			return (this->biggest);
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

		value_type *	operator->() const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[rbt_iterator] operator-> called.\n" << COLOR_DEFAULT;
			#endif
			return (&(this->ptr->data));
		}

		value_type &	operator*() const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[rbt_iterator] operator* called.\n" << COLOR_DEFAULT;
			#endif
			return ((this->ptr->data));
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
		typedef Iterator													iterator_type;		//Iterator's type
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;	//Preserves Iterator's category
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;			//Preserves Iterator's value type
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;	//Preserves Iterator's difference type
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;			//Preserves Iterator's pointer type
		typedef typename ft::iterator_traits<Iterator>::reference			reference;			//Preserves Iterator's reference type

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

		rbt_reverse_iterator (const rbt_reverse_iterator<Iterator>& rev_it) : _base(rev_it._base)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_reverse_iterator] copy constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		
		template< class Iter >
		rbt_reverse_iterator(const rbt_reverse_iterator<Iter>& rev_it) : _base(rev_it.base())
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[rbt_reverse_iterator] template constructor called.\n" << COLOR_DEFAULT;
			#endif
		}
		
		rbt_reverse_iterator const & operator=(rbt_reverse_iterator const & rhs)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[rbt_iterator] operator= called.\n" << COLOR_DEFAULT;
			#endif
			this->_base = rhs._base;
			return (*this);
		}

		iterator_type base() const
		{
			return (this->_base);
		}
		
		reference	operator*() const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator* called.\n" << COLOR_DEFAULT;
			#endif
			iterator_type	tmp(this->_base);
			--tmp;
			return (*tmp);
		}
		
		pointer operator->() const
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator-> called.\n" << COLOR_DEFAULT;
			#endif
			return (&(operator*()));
		}

		rbt_reverse_iterator &	operator++()
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator++() called.\n" << COLOR_DEFAULT;
			#endif
			--(this->_base);
			return (*this);
		}
		
		rbt_reverse_iterator	operator++(int)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator++(int) called.\n" << COLOR_DEFAULT;
			#endif
			rbt_reverse_iterator tmp(this->_base);
			--(this->_base);
			return (tmp);
		}
		
		rbt_reverse_iterator& operator--()
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator--() called.\n" << COLOR_DEFAULT;
			#endif
			++(this->_base);
			return (*this);
		}
		
		rbt_reverse_iterator  operator--(int)
		{
			#if DEBUG
				std::cout << COLOR_MAGENTA << "[reverse_iterator] operator--(int) called.\n" << COLOR_DEFAULT;
			#endif
			rbt_reverse_iterator tmp(this->_base);
			++(this->_base);
			return (tmp);
		}
		

	}; //rbt_reverse_iterator

	template <class Iterator>
	bool operator== (const rbt_reverse_iterator<Iterator>& lhs, const rbt_reverse_iterator<Iterator>& rhs)
	{
		#if DEBUG
			std::cout << COLOR_MAGENTA << "[reverse_iterator] operator== called.\n" << COLOR_DEFAULT;
		#endif
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!= (const rbt_reverse_iterator<Iterator>& lhs, const rbt_reverse_iterator<Iterator>& rhs)
	{
		#if DEBUG
			std::cout << COLOR_MAGENTA << "[reverse_iterator] operator!= called.\n" << COLOR_DEFAULT;
		#endif
		return !(lhs.base() == rhs.base());
	}

} // namespace ft
