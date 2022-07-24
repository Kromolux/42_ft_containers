/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:49:13 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/23 18:00:47 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "vector.hpp"

namespace ft
{

	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
		typedef	T			value_type;		//The first template parameter (T)	Type of the elements
		typedef	Container	container_type;	//The second template parameter (Container)	Type of the underlying container
		typedef	size_t		size_type;		//an unsigned integral type	usually the same as size_t
		
		protected:
		container_type	c;
		
		public:

		//Member functions
		//(constructor)
		explicit stack (const container_type& ctnr = container_type())// : c(ctnr)
		{
			#if DEBUG
				std::cout << COLOR_GREEN << "[stack] default constructor called.\n" << COLOR_DEFAULT;
			#endif
			this->c = ctnr;
		}

		~stack(void) {}

		//empty
		bool empty(void) const
		{
			return (c.size() == 0);
		}
		//size
		size_type size(void) const
		{
			return (c.size());
		}
		//top
		value_type& top(void)
		{
			return (c.back());
		}
		const value_type& top(void) const
		{
			return (c.back());
		}
		//push
		void push (const value_type& val)
		{
			c.push_back(val);
		}

		//emplace 
		//C++ 11
		
		//pop
		void pop(void)
		{
			c.pop_back();
		}
		
		//swap 
		//C++ 11

		//swap (stack) 
		//C++ 11

		//Non-member function overloads
		//relational operators
		//template <class T, class Container>
		bool operator== (const stack<T,Container>& rhs) const
		{
			return (this->c == rhs.c);
		}
		//template <class T, class Container>
		bool operator!= (const stack<T,Container>& rhs) const
		{
			return (!(*this == rhs));
		}

		//template <class T, class Container>
		bool operator<  (const stack<T,Container>& rhs) const
		{
			return (this->c < rhs.c);
		}
		//template <class T, class Container>
		bool operator<= (const stack<T,Container>& rhs) const
		{
			return !(rhs < *this);
		}
		//template <class T, class Container>
		bool operator>  (const stack<T,Container>& rhs) const
		{
			return (rhs < *this);
		}
		//template <class T, class Container>
		bool operator>= (const stack<T,Container>& rhs) const
		{
			return !(*this < rhs);
		}
	};

}
