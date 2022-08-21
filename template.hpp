/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:02:36 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/21 17:41:04 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <set>
#include <vector>
#include <iterator>
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"
#include "vector.hpp"

#include <iostream>
#include <typeinfo>

template<class T, class U>
void	isEqual(T const & first, U const & second)
{
	if (first == second)
		std::cout << COLOR_GREEN << "[OK]" << COLOR_DEFAULT;
	else
		std::cout << COLOR_RED << "[KO]" << first << "!=" << second << COLOR_DEFAULT;
}

template<class V1, class V2>
void	BasicVectorStats(V1 const & vector1, V2 const & vector2)
{
	isEqual(vector1.size(), vector2.size());
	isEqual(vector1.max_size(), vector2.max_size());
	isEqual(vector1.empty(), vector2.empty());
	isEqual(vector1.capacity(), vector2.capacity());
}

template<class V1, class V2>
void	BasicStackStats(V1 const & stack1, V2 const & stack2)
{
	isEqual(stack1.empty(), stack2.empty());
	isEqual(stack1.size(), stack2.size());

}

template<class M1, class M2>
void	BasicMapStats(M1 const & map1, M2 const & map2)
{
	isEqual(map1.size(), map2.size());
	isEqual(map1.max_size(), map2.max_size());
	isEqual(map1.empty(), map2.empty());
}

template <class T1, class T2>
void	RelationalTest(T1 const & lhs1, T1 const & rhs1, T2 const & lhs2, T2 const & rhs2)
{
	isEqual(lhs1 != rhs1, lhs2 != rhs2);
	isEqual(lhs1 == rhs1, lhs2 == rhs2);
	isEqual(lhs1 < rhs1, lhs2 < rhs2);
	isEqual(lhs1 <= rhs1, lhs2 <= rhs2);
	isEqual(lhs1 > rhs1, lhs2 > rhs2);
	isEqual(lhs1 >= rhs1, lhs2 >= rhs2);
}

template<class Iter1First, class Iter1Last, class Iter2First, class Iter2Last>
void	IteratorTest(Iter1First my_it, Iter1Last my_ite, Iter2First std_it, Iter2Last std_ite)
{
	isEqual(*my_it, *std_it);
	isEqual(*(my_it++), *(std_it++));
	isEqual(*(++my_it), *(++std_it));
	isEqual(*(--my_ite), *(--std_ite));
	isEqual(*(my_ite--), *(std_ite--));
	isEqual(*(my_ite - 1), *(std_ite - 1));
	isEqual(*(my_ite - 2), *(std_ite - 2));
	isEqual(*(my_ite -= 2), *(std_ite -= 2));
	isEqual(*(my_ite + 1), *(std_ite + 1));
	isEqual(*(my_ite + 2), *(std_ite + 2));
	isEqual(*(my_it + 1), *(std_it + 1));
	isEqual(*(my_it + 2), *(std_it + 2));
	isEqual(*(my_ite += 1), *(std_ite += 1));
	isEqual(*(my_ite += 2), *(std_ite += 2));
	isEqual(*(my_it += 1), *(std_it += 1));
	isEqual(*(my_it += 2), *(std_it += 2));
	isEqual((my_ite - my_it), (std_ite - std_it));
	isEqual((my_it - my_ite), (std_it - std_ite));
	isEqual(*(1 + my_it), *(1 + std_it));
	isEqual(*(2 + my_it), *(2 + std_it));
	isEqual((my_it > my_ite), (std_it > std_ite));
	isEqual((my_it < my_ite), (std_it < std_ite));
	isEqual((my_it >= my_ite), (std_it >= std_ite));
	isEqual((my_it <= my_ite), (std_it <= std_ite));
	isEqual((my_it == my_ite), (std_it == std_ite));
	isEqual((my_it != my_ite), (std_it != std_ite));
}


template<class Iter1First, class Iter1Last, class Iter2First, class Iter2Last>
void	RBTIteratorTest(Iter1First my_it, Iter1Last my_ite, Iter2First std_it, Iter2Last std_ite)
{
	//isEqual(*my_it, *std_it);
	isEqual(my_it->first, std_it->first);
	isEqual(my_it->second, std_it->second);
	isEqual((my_it++)->first, (std_it++)->first);
	isEqual((my_it++)->second, (std_it++)->second);
	isEqual((++my_it)->first, (++std_it)->first);
	isEqual((++my_it)->second, (++std_it)->second);
	isEqual((--my_ite)->first, (--std_ite)->first);
	isEqual((--my_ite)->second, (--std_ite)->second);
	isEqual((my_ite--)->first, (std_ite--)->first);
	isEqual((my_ite--)->second, (std_ite--)->second);
}


template<class Iter1First, class Iter1Last, class Iter2First, class Iter2Last>
void	RBTSetIteratorTest(Iter1First my_it, Iter1Last my_ite, Iter2First std_it, Iter2Last std_ite)
{
	isEqual(*my_it, *std_it);
	isEqual(*(my_it++), *(std_it++));
	isEqual(*(++my_it), *(++std_it));
	isEqual(*(--my_ite), *(--std_ite));
	isEqual(*(my_ite--), *(std_ite--));
}

template <class T>
void	displayInfo(ft::vector<T> & vec )
{
	// #if TEST
	// 	std::cout << "std";
	// #else
	// 	std::cout << "ft";
	// #endif
	std::cout	<< "::vector<" << typeid(T).name() << "> details\n"
				<< "Capacity: " << vec.capacity() << "\n"
				<< "Size    : " << vec.size() << "\n"
				<< "Max Size: " << vec.max_size() << "\n"
				<< std::boolalpha
				<< "Isempty : " << vec.empty() << "\n";
				//<< "Pointer : " << vec.data() << "\n";
}

template <class T>
void	displayContent(ft::vector<T> & vec)
{
	typename ft::vector<T>::iterator it = vec.begin();
	typename ft::vector<T>::iterator ite = vec.end();

	std::cout << "[ ";
	for (; it != ite; ++it)
		std::cout << *it << " ";
	std::cout << "]" << std::endl;
}

template <class Iterator>
void	displayContent(Iterator first, Iterator last)
{
	std::cout << "[ ";
	for (; first != last; ++first)
		std::cout << *first << " ";
	std::cout << "]" << std::endl;
}

template <class T1, class T2>
void	displayMapInfo(ft::map<T1, T2> & myMap)
{

	std::cout	<< "::map<int,int> details\n"
				<< "Size    : " << myMap.size() << "\n"
				<< "Max Size: " << myMap.max_size() << "\n"
				<< std::boolalpha
				<< "Isempty : " << myMap.empty() << "\n";
}

//template <class T1, class T2>
template <class MAP>
void	displayMapContent(MAP & myMap)
{
	typename MAP::iterator it = myMap.begin();
	typename MAP::iterator ite = myMap.end();

	std::cout << "map content = [ ";
	for (; it != ite; ++it)
		std::cout << it->first << ":" << it->second << " ";
	std::cout << "]" << std::endl;
}

template <class T>
void	displaySetInfo(ft::set<T> & mySet)
{

	std::cout	<< "::set<int> details\n"
				<< "Size    : " << mySet.size() << "\n"
				<< "Max Size: " << mySet.max_size() << "\n"
				<< std::boolalpha
				<< "Isempty : " << mySet.empty() << "\n";
}

template <class T>
void	displaySetContent(ft::set<T> & mySet)
{
	typename ft::set<T>::iterator it = mySet.begin();
	typename ft::set<T>::iterator ite = mySet.end();

	std::cout << "[ ";
	for (; it != ite; ++it)
		std::cout << *it << " ";
	std::cout << "]" << std::endl;
}
