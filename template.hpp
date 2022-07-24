/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:02:36 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/23 18:04:44 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#if TEST //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <set>
	#include <vector>
	#include <iterator>
	namespace ft = std;
#else
	#include "set.hpp"
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
#endif

#include <iostream>
#include <typeinfo>

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

template <class T1, class T2>
void	displayMapInfo(ft::map<T1, T2> & myMap)
{
	#if TEST
		std::cout << "std";
	#else
		std::cout << "ft";
	#endif
	std::cout	<< "::map<int,int> details\n"
				<< "Size    : " << myMap.size() << "\n"
				<< "Max Size: " << myMap.max_size() << "\n"
				<< std::boolalpha
				<< "Isempty : " << myMap.empty() << "\n";
}

template <class T1, class T2>
void	displayMapContent(ft::map<T1, T2> & myMap)
{
	typename ft::map<T1, T2>::iterator it = myMap.begin();
	typename ft::map<T1, T2>::iterator ite = myMap.end();

	std::cout << "map content = [ ";
	for (; it != ite; ++it)
		std::cout << it->first << ":" << it->second << " ";
	std::cout << "]" << std::endl;
}

template <class T>
void	displaySetInfo(ft::set<T> & mySet)
{
	#if TEST
		std::cout << "std";
	#else
		std::cout << "ft";
	#endif
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
