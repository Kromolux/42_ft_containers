/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:06:34 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/06 16:18:40 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <ctime>
//#include <deque>
#include "template.hpp"

#ifndef TEST
# define TEST 0
#endif
#if TEST //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <set>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "set.hpp"
	#include "stack.hpp"
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

// template<typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

typedef struct s_Test {
	clock_t		start;
	clock_t		end;
}				t_Test;

typedef struct s_testTimes {
	struct s_Test	all;
	struct s_Test	vector;
	struct s_Test	stack;
	struct s_Test	pair;
	struct s_Test	map;
	struct s_Test	set;
}				t_testTime;

void test_vector(t_testTime & myTimer);
void test_stack(t_testTime & myTimer);
void test_pair(t_testTime & myTimer);
void test_map(t_testTime & myTimer);
void test_set(t_testTime & myTimer);
void initTimer(t_testTime & myTimer);

typedef int myType;
int	main(void)
{
	t_testTime	myTimer = {};
	initTimer(myTimer);
	std::string	testCase;
	#if TEST
		testCase = "std";
	#else
		testCase = "ft";
	#endif

	myTimer.all.start = clock();

	std::cout << testCase << "::Test started at: " << myTimer.all.start << "\n";
	
	//test_vector(myTimer);
	//test_stack(myTimer);
	//test_pair(myTimer);
	test_map(myTimer);
	//test_set(myTimer);

	
	myTimer.all.end = clock();
	
	std::cout	<< testCase << "::Time [all] elapsed: " << static_cast<float>(myTimer.all.end - myTimer.all.start) / CLOCKS_PER_SEC
				<< " seconds\n";
	std::cout	<< testCase << "::Time [vector] elapsed: " << static_cast<float>(myTimer.vector.end - myTimer.vector.start) / CLOCKS_PER_SEC
				<< " seconds\n";
	std::cout	<< testCase << "::Time [stack] elapsed: " << static_cast<float>(myTimer.stack.end - myTimer.stack.start) / CLOCKS_PER_SEC
				<< " seconds\n";
	std::cout	<< testCase << "::Time [pair] elapsed: " << static_cast<float>(myTimer.pair.end - myTimer.pair.start) / CLOCKS_PER_SEC
				<< " seconds\n";
	std::cout	<< testCase << "::Time [map] elapsed: " << static_cast<float>(myTimer.map.end - myTimer.map.start) / CLOCKS_PER_SEC
				<< " seconds\n";
	return (0);
}
void initTimer(t_testTime & myTimer)
{
	
	myTimer.all.start = 0;
	myTimer.all.end = 0;
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

void test_vector(t_testTime & myTimer)
{
	myTimer.vector.start = clock();

	ft::vector<myType> vec(5);

	displayInfo(vec);
	displayContent(vec);
	ft::vector<myType>::iterator it = vec.begin();
	ft::vector<myType>::iterator ite = vec.end();
	ft::vector<myType>::reverse_iterator rit = vec.rbegin();
	ft::vector<myType>::reverse_iterator rite = vec.rend();
	
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

	displayContent(vec);
	for (size_t i = 0; rit != rite; rit++, i++)
		std::cout << "i= " << i << " = " << *rit << " ";
	
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
	//const ft::vector<myType> cvector = const_cast<ft::vector<myType>&>(vec2);
	//TODO const_iterator not working anymore! WHY?
	// ft::vector<myType>::const_iterator cit = vec2.begin();
	// ft::vector<myType>::const_iterator cite = vec2.end();
	// // *cit = 555;
	// std::cout << "[ ";
	// for (; cit != cite; cit++)
	// 	std::cout << *cit << " ";
	// std::cout << "]" << std::endl;

	
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
	displayInfo(vec2);
	displayContent(vec2);
	vec2.clear();
	for (size_t i = 0; i < vec2.capacity(); i++)
		vec2.push_back(i);
	vec2.push_back(1234567989);
	displayInfo(vec2);
	displayContent(vec2);
	it = vec2.begin();
	ite = vec2.end();
	std::cout << "testing insert\n";
	it = vec2.insert(it + 3, 42);
	std::cout << "it points to " << *it << "\n";
	displayInfo(vec2);
	displayContent(vec2);

	vec2.erase(it);
	displayInfo(vec2);
	displayContent(vec2);
	it = vec2.insert(it + 3, 42);
	std::cout << "it points to " << *it << "\n";
	displayInfo(vec2);
	displayContent(vec2);

	std::cout << "insert numbers into vec2\n";
	vec2.insert(it, 5, 999);
	std::cout << "vec2\n";
	displayInfo(vec2);
	displayContent(vec2);
	std::cout << "vec\n";
	displayInfo(vec);
	displayContent(vec);
	vec2.insert(vec2.begin(), vec.begin(), vec.end());
	std::cout << "vec2\n";
	displayInfo(vec2);
	displayContent(vec2);
	std::cout << "vector constructor InputIterator test\n";
	it = vec2.begin();
	ite = vec2.end();
	ft::vector<myType> vec3(it, ite);
	displayInfo(vec3);
	displayContent(vec3);
	myTimer.vector.end = clock();
}

void test_stack(t_testTime & myTimer)
{
	myTimer.stack.start = clock();
	
	std::cout << "\nTesting stack\n";
	
	ft::stack<myType>	myStack;
	ft::stack<myType>	my2Stack;

	#if TEST
		std::cout << "std";
	#else
		std::cout << "ft";
	#endif
	std::cout	<< "::stack<" << typeid(myType).name() << "> details\n"
				<< "Size    : " << myStack.size() << "\n"
				//<< "Capacity: " << myStack.c.capacity() << "\n"
				//<< "Max Size: " << myStack.c.max_size() << "\n"
				<< std::boolalpha
				<< "Isempty : " << myStack.empty() << "\n";
	std::cout << "push(42)\n";
	myStack.push(42);
	my2Stack.push(42);
	std::cout << (myStack < my2Stack) << " < comparison\n";
	std::cout << (myStack > my2Stack) << " > comparison\n";
	std::cout << (myStack <= my2Stack) << " <= comparison\n";
	std::cout << (myStack >= my2Stack) << " >= comparison\n";
	std::cout << "push(4242)\n";
	myStack.push(4242);
	std::cout << "top element: " << myStack.top() << "\n";
	myStack.pop();
	std::cout << "pop()\n";
	std::cout << "top element: " << myStack.top() << "\n";
	std::cout << "populating stack\n";
	for (size_t i = 0; i < 7; ++i)
		myStack.push(i);
	std::cout << "iterating through stack and poping elements\n";
	while (myStack.empty() == false)
	{
		std::cout << "top element: " << myStack.top() << "\n";
		myStack.pop();
	}
	myTimer.stack.end = clock();
}

void test_pair(t_testTime & myTimer)
{
	myTimer.pair.start = clock();
	ft::pair<std::string, int> myPair;

	myPair.first = "Key";
	myPair.second = 42;

	std::cout	<< "Test with pairs\n"
				<< "myPair.first = " << myPair.first << "\n"
				<< "myPair.second = " << myPair.second << "\n";

	ft::pair<std::string, int> secondPair =  myPair;

	myPair.first = "Next Test";
	myPair.second = 4200;
	
	std::cout	<< "Test with pairs\n"
			<< "myPair.first = " << myPair.first << "\n"
			<< "myPair.second = " << myPair.second << "\n"
			<< "secondPair.first = " << secondPair.first << "\n"
			<< "secondPair.second = " << secondPair.second << "\n";
	ft::pair<std::string, int> thirdPair("Argument constructor", 888);
	ft::pair<std::string, int> forthPair(thirdPair);
	std::cout	<< "Test with pairs\n"
			<< "thirdPair.first = " << thirdPair.first << "\n"
			<< "thirdPair.second = " << thirdPair.second << "\n"
			<< "forthPair.first = " << forthPair.first << "\n"
			<< "forthPair.second = " << forthPair.second << "\n";

	ft::pair <int, float> pairMake;
	pairMake = ft::make_pair(42, 42.42);
	std::cout	<< "Test with pairs\n"
			<< "pairMake.first = " << pairMake.first << "\n"
			<< "pairMake.second = " << pairMake.second << "\n";
	std::cout << (myPair == secondPair) << "\n";
	std::cout << (myPair > secondPair) << "\n";
	myTimer.pair.end = clock();
}

void test_map(t_testTime & myTimer)
{
	myTimer.map.start = clock();

	ft::map<int, int> myMap;
	
	std::cout << "Testing MAP\n";

	displayMapInfo(myMap);
	myMap.insert(ft::pair<int, int>(50, 1));
	myMap.insert(ft::pair<int, int>(30, 2));
	myMap.insert(ft::pair<int, int>(70, 3));
	myMap.insert(ft::pair<int, int>(20, 4));
	myMap.insert(ft::pair<int, int>(80, 5));
	myMap.insert(ft::pair<int, int>(40, 6));
	myMap.insert(ft::pair<int, int>(60, 7));
	myMap.insert(ft::pair<int, int>(31, 8));
	myMap.insert(ft::pair<int, int>(55, 9));
	myMap.insert(ft::pair<int, int>(75, 10));
	displayMapInfo(myMap);
	// ft::map<int, int>::iterator it = myMap.begin();
	// ft::map<int, int>::iterator ite = myMap.end();
	// --ite;
	// while (it != ite)
	// {
	// 	std::cout << "begin points to: " << it->first << ":" << it->second << " end points to: " << ite->first << ":" << ite->second << "\n";
	// 	++it;
	// }
	displayMapContent(myMap);

	//myMap.insert(ft::pair<int, int>(5, 1));
	//displayMapContent(myMap);

	myTimer.map.end = clock();
}

void test_set(t_testTime & myTimer)
{
	myTimer.set.start = clock();

	ft::set<int> mySet;
	
	std::cout << "Testing SET\n";

	displaySetInfo(mySet);
	//displaySetContent(mySet);

	//mySet.insert(5);
	//displaySetContent(mySet);

	myTimer.set.end = clock();
}
