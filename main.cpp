/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:06:34 by rkaufman          #+#    #+#             */
/*   Updated: 2022/06/10 22:25:17 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
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

int	main(void)
{
	ft::vector<int> vec(5);

	//template < class T>
	//void	details(ft::vector<int> const & vec)
	//{
	#if TEST
		std::cout << "std";
	#else
		std::cout << "ft";
	#endif
	std::cout	<< "::vector<int> details\n"
				<< "Capacity: " << vec.capacity() << "\n"
				<< "Size    : " << vec.size() << "\n"
				<< "Max Size: " << vec.max_size() << "\n"
				<< std::boolalpha
				<< "Isempty : " << vec.empty() << "\n"
				<< "Pointer : " << vec.data() << "\n";

	ft::vector<int>::iterator it = vec.begin();
	ft::vector<int>::iterator ite = vec.end();
	
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

	ft::vector<int> vec2(vec);
	
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

	it = vec.begin();
	ite = vec.end();

	std::cout << "[ ";
	for (; it != ite; it++)
		std::cout << *it << " ";
	//std::for_each(vec.begin(), vec.end(), [](T x) {std::cout << x << " ";});
	std::cout << "]" << std::endl;

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
	
	it = vec2.begin();
	ite = vec2.end();
	
	std::cout << "[ ";
	for (; it != ite; it++)
		std::cout << *it << " ";
	std::cout << "]" << std::endl;

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