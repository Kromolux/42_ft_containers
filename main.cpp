/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:06:34 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/13 18:46:00 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include "template.hpp"

#ifndef TEST
# define TEST 0
#endif
#if TEST //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	//#include <map.hpp>
	//#include <stack.hpp>
	#include "vector.hpp"
#endif

#include <stdlib.h>


#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))
/*
template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};
*/

typedef long long myType;
int	main(void)
{
	ft::vector<myType> vec(5);

	displayInfo(vec);
	displayContent(vec);
	ft::vector<myType>::iterator it = vec.begin();
	ft::vector<myType>::iterator ite = vec.end();
	
	try
	{
		std::cout << vec.at(-1) << "\n";
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	for (size_t i = 0; it != ite; it++, i++)
		vec.at(i) = i + 1;
	
	ft::vector<myType> vec2(vec);
	displayContent(vec2);
	
	vec2 = vec;
	
	displayContent(vec2);

	it = vec2.begin();
	ite = vec2.end();

	for (size_t i = 0; it != ite; it++, i++)
		*it = i + 42;

	vec[0] = 42;
	std::cout << "Value of vec[0] = " << vec[0] << std::endl;
	std::cout << "Value of vec.front() = " << vec.front() << std::endl;
	std::cout << "Value of vec[4] = " << vec[4] << std::endl;
	std::cout << "Value of vec.end() = " << vec.back() << std::endl;
	
	std::cout << "[ ";
	for (size_t i = 0; i < 5; i++)
		std::cout << vec[i] << " ";
	std::cout << "]\n";
	
	std::cout << "[ ";
	for (size_t i = 0; i < 5; i++)
		std::cout << vec2[i] << " ";
	std::cout << "]\n";

	it = vec.end();
	ite = vec.end();
	displayContent(vec);

	std::cout << "===[iterator tests]===\n";
	std::cout << "*(it - 1) = " << *(it - 1) << "\n";
	std::cout << "*(it - 2) = " << *(it - 2) << "\n";
	std::cout << "*(it -= 2) = " << *(it -= 2) << "\n";
	std::cout << "*(it -= 3) = " << *(it -= 3) << "\n";
	std::cout << "*(it + 1) = " << *(it + 1) << "\n";
	std::cout << "*(it + 2) = " << *(it + 2) << "\n";
	std::cout << "*(it += 2) = " << *(it += 1) << "\n";
	std::cout << "*(it += 2) = " << *(it += 2) << "\n";
	std::cout << "(ite - it) = " << (ite - it) << "\n";
	std::cout << "(it - ite) = " << (it - ite) << "\n";
	std::cout << "(it - ite) = " << (it - ite) << "\n";
	std::cout << "*(1 + it) = " << *(1 + it) << "\n";
	//std::cout << "(ite + it) = " << (ite + it) << "\n";
	//std::cout << "(ite -= it) = " << (ite -= it) << "\n";
	//std::cout << "(ite += it) = " << (ite += it) << "\n";
	std::cout	<< "it > ite   " << (it > ite) << "\n";
	std::cout	<< "it < ite   " << (it < ite) << "\n";
	std::cout	<< "ite >= ite " << (ite >= ite) << "\n";
	std::cout	<< "it <= it   " << (it <= it) << "\n";
	std::cout	<< "it != it   " << (it != it) << "\n";
	std::cout	<< "it == ite   " << (it == ite) << "\n";
	
	displayContent(vec2);
	
	it = vec2.end();
	ite = vec2.end();
	
	it -= 3;
	std::cout << "*it = " << *it << "\n";
	vec2.erase(it);
	std::cout << "*it = " << *it << "\n";

	it = vec2.begin();
	ite = vec2.end();
	
	std::cout << "[ ";
	for (; it != ite; it++)
		std::cout << *it << " ";
	std::cout << "]" << std::endl;
	std::cout << "pushback\n";
	
	displayInfo(vec);
	vec.push_back(4242);
	vec.push_back(4242);
	displayInfo(vec);
	
	vec.pop_back();
	vec.pop_back();

	vec.pop_back();
	vec.pop_back();
	
	vec.pop_back();
	vec.pop_back();

	//vec.pop_back();
	
	displayContent(vec);
	
	std::cout << "vector.get_allocator = " << typeid(vec.get_allocator()).name() << "\n";

	vec.reserve(15);
	displayInfo(vec);
	displayContent(vec);
	
	vec.swap(vec2);
	displayInfo(vec);
	displayContent(vec);
	
	ft::swap(vec, vec2);
	displayInfo(vec);
	displayContent(vec);
	
	vec.clear();
	displayInfo(vec);
	displayContent(vec);

	vec2.resize(10, 999);
	displayInfo(vec2);
	displayContent(vec2);

	vec2.resize(5);
	displayInfo(vec2);
	displayContent(vec2);

	it = vec2.begin() + 1;
	ite = vec2.begin() + 3;

	std::cout	<< "*it  = " << *it << "\n"
				<< "*ite = " << *ite << "\n";

	vec2.erase(it, ite);
	std::cout	<< "*it  = " << *it << "\n"
				<< "*ite = " << *ite << "\n";
	displayInfo(vec2);
	displayContent(vec2);

	for (size_t i = 0; i < vec.capacity(); i++)
		vec.push_back(i);
	displayInfo(vec);
	displayContent(vec);

	it = vec.begin();
	ite = vec.begin() + 3;

	std::cout	<< "*it  = " << *it << "\n"
				<< "*ite = " << *ite << "\n";

	vec.erase(it, ite);
	std::cout	<< "*it  = " << *it << "\n"
				<< "*ite = " << *ite << "\n";
	displayInfo(vec);
	displayContent(vec);


	it = vec.begin() + 3;
	ite = vec.end() - 1;

	std::cout	<< "*it  = " << *it << "\n"
				<< "*ite = " << *ite << "\n";

	vec.erase(it, ite);
	std::cout	<< "*it  = " << *it << "\n"
				<< "*ite = " << *ite << "\n";
	displayInfo(vec);
	displayContent(vec);
	std::cout << "testing assign with int\n";
	try
	{
		vec.assign(5, 42);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	displayInfo(vec);
	displayContent(vec);

	displayInfo(vec2);
	displayContent(vec2);
	it = vec2.begin();
	ite = vec2.end();
	std::cout << "testing assign with iterators\n";
	vec.assign(it, ite);
	displayInfo(vec);
	displayContent(vec);
	return (0);
}

/*
int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}
*/