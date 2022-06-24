/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:02:36 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/24 21:58:37 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#if TEST //CREATE A REAL STL EXAMPLE
	#include <vector>
	#include <iterator>
	namespace ft = std;
#else
	//#include <map.hpp>
	//#include "stack.hpp"
	#include "vector.hpp"
	#include "iterator.hpp"
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
void	displayContent(ft::vector<T> & vec )
{
	typename ft::vector<T>::iterator it = vec.begin();
	typename ft::vector<T>::iterator ite = vec.end();

	std::cout << "[ ";
	for (; it != ite; it++)
		std::cout << *it << " ";
	std::cout << "]" << std::endl;
}

