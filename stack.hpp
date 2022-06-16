/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:49:13 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/16 18:32:36 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack
{
	public:
		typedef	T			value_type;		//The first template parameter (T)	Type of the elements
		typedef	Container	container_type;	//The second template parameter (Container)	Type of the underlying container
		typedef	size_t		size_type;		//an unsigned integral type	usually the same as size_t
		
		//Member functions
		//(constructor)
		explicit stack (const container_type& ctnr = container_type()) : c(ctnr)
		{
		}
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

	protected:
		container_type	c;

	private:
};

	//Non-member function overloads
	//relational operators
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(rhs < lhs);
	}
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs < rhs);
	}
	
}
