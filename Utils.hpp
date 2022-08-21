/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:59:00 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/21 17:48:20 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "colors.h"
#include <utility>

namespace ft
{

	template <bool flag, class IsTrueType, class IsFalseType>
	struct choose;

	template <class IsTrueType, class IsFalseType>
	struct choose<true, IsTrueType, IsFalseType>
	{
		typedef IsTrueType type;
	};

	template <class IsTrueType, class IsFalseType>
	struct choose<false, IsTrueType, IsFalseType>
	{
		typedef IsFalseType type;
	};

	template <class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		#if DEBUG
			std::cout << COLOR_YELLOW << "[equal] function template 1 called.\n" << COLOR_DEFAULT;
		#endif
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return (false);
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		#if DEBUG
			std::cout << COLOR_YELLOW << "[equal] function template 2 called.\n" << COLOR_DEFAULT;
		#endif
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(pred(*first1 == *first2)))
				return (false);
		}
		return (true);
	}

	//https://cplusplus.com/reference/algorithm/lexicographical_compare/?kw=lexicographical_compare
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		#if DEBUG
			std::cout << COLOR_YELLOW << "[lexicographical_compare] function template 1 called.\n" << COLOR_DEFAULT;
		#endif
		for (; first1 != last1; ++first1, ++first2)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		#if DEBUG
			std::cout << COLOR_YELLOW << "[lexicographical_compare] function template 2 called.\n" << COLOR_DEFAULT;
		#endif
		for (; first1 != last1; ++first1, ++first2)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
		}
		return (first2 != last2);
	}

	//  https://cplusplus.com/reference/type_traits/is_integral/?kw=is_integral
	template <class T, T v>
	struct integral_constant 
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
	};

	template <class T, T v> const 
	T integral_constant<T, v>::value;

	typedef integral_constant<bool, true>  true_type;
	typedef integral_constant<bool, false> false_type;

	template <class T> struct is_integral : public false_type { };

	template <> struct is_integral<bool> : public true_type { };
	template <> struct is_integral<char> : public true_type { };
	template <> struct is_integral<unsigned char> : public true_type { };
	template <> struct is_integral<short> : public true_type { };
	template <> struct is_integral<unsigned short> : public true_type { };
	template <> struct is_integral<int> : public true_type { };
	template <> struct is_integral<unsigned int> : public true_type { };
	template <> struct is_integral<long> : public true_type { };
	template <> struct is_integral<unsigned long> : public true_type { };
	template <> struct is_integral<long long> : public true_type { };
	template <> struct is_integral<unsigned long long> : public true_type { };

	//  https://cplusplus.com/reference/type_traits/enable_if/?kw=enable_if
	//  enable_if - SFINAE
	//  "Substitution Failure Is Not An Error"
	template <bool condition, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if <true, T>
	{
		typedef T type;
	};

	template <typename T, typename U>
	struct is_same
	{
		static const bool value = false;
	};

	template <typename T>
	struct is_same<T, T>
	{
		static const bool value = true;
	};

}

namespace ft {

	template <class T1, class T2>
	class pair
	{
		public:
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair(void) : first(), second()
		{}

		template<class U, class V>
		pair (const pair<U, V> & pr) : first(pr.first), second(pr.second)
		{}

		pair (const first_type& a, const second_type& b) : first(a), second(b)
		{}

		// implicitly declared:
		pair & operator= (const pair & pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}
	
		//C++11 void swap (pair& pr) noexcept ( noexcept(swap(first,pr.first)) && noexcept(swap(second,pr.second)) );

	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	
	// template <class T1, class T2>
	// bool operator== (const std::pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	// {
	// 	return (lhs.first == rhs.first && lhs.second == rhs.second);
	// }
	
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1,T2>(x,y));
	}

	template <class T>
	T extract_key(T key)
	{
		return (key);
	}

	template <class first, class second>
	first extract_key(ft::pair<first, second> pair)
	{
		return (pair.first);
	}

	template <class T>
	T extract_value(T value)
	{
		return (value);
	}

	template <class first, class second>
	second extract_value(ft::pair<first, second> pair)
	{
		return (pair.second);
	}
	
}
