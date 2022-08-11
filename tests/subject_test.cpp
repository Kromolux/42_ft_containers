/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subject_test.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:29:13 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/29 11:55:18 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_STD
# define TEST_STD 0
#endif
#ifndef TEST_FT
# define TEST_FT 0
#endif

#if TEST_STD //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <set>
	#include <stack>
	#include <vector>
	namespace ft = std;
#endif
#if TEST_FT
	#include "../map.hpp"
	#include "../set.hpp"
	#include "../stack.hpp"
	#include "../vector.hpp"
#endif

#include <deque>
#include <ctime>
#include <iostream>
#include <string>
#include <stdlib.h>

typedef struct s_Test {
	clock_t		start;
	clock_t		end;
}				t_Test;

typedef struct s_testTimes {
	struct s_Test	all;
}				t_testTime;

#define MAX_RAM 2147483648
#define BUFFER_SIZE 2048
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

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

int main(int argc, char** argv)
{
	t_testTime	myTimer = {};
	myTimer.all.start = clock();
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return (-1);
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	#if TEST_STD
		std::cout << "TEST STD\n";
	#else
		std::cout << "TEST FT\n";
	#endif

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	std::cout << "COUNT: " << COUNT << "\n";
	
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
		ft::pair<int, int> myPair = ft::make_pair(rand(), rand());
		//std::cout << "i: " << i << " myPair.first: " << myPair.first << " myPair.second: " << myPair.second << "\n";
		map_int.insert(myPair);
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand() % COUNT;
		//std::cout << "access: " << access << " map_int: " << map_int[access] << "\n";
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

	myTimer.all.end = clock();
	std::cout	<< "::Time [all] elapsed: " << static_cast<float>(myTimer.all.end - myTimer.all.start) / CLOCKS_PER_SEC
				<< " seconds\n";
	return (0);
}
