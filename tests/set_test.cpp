/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:31:31 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/28 17:12:41 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers.hpp"

typedef int myType;
void test_set(t_testTime & myTimer)
{
	myTimer.set.start = clock();

	// std::list<T1> lst;
	// unsigned int lst_size = 10;
	// for (unsigned int i = 0; i < lst_size; ++i)
	// 	lst.push_back(std::string((lst_size - i), i + 65));
	// ft::set<T1> st(lst.begin(), lst.end());
	// printSize(st);
	// st.printTree();
	// ft_erase(st, ++st.begin());
	// st.printTree();
	// ft_erase(st, st.begin());
	// st.printTree();
	// ft_erase(st, --st.end());
	// std::cout << "begin points to: " << *st.begin() << " 3 times ++ points to: " << *(++(++(++st.begin()))) <<  "\n";
	// st.printTree();
	// ft_erase(st, st.begin(), ++(++(++st.begin())));
	
	// ft_erase(st, --(--(--st.end())), --st.end());

	// st.insert("Hello");
	// st.insert("Hi there");
	// printSize(st);
	// ft_erase(st, --(--(--st.end())), st.end());

	// st.insert("ONE");
	// st.insert("TWO");
	// st.insert("THREE");
	// st.insert("FOUR");
	// printSize(st);
	// ft_erase(st, st.begin(), st.end());

	ft::set<myType> st;

	st.insert(42);

	st.insert(50);
	st.insert(25);

	st.insert(46);
	st.insert(21);
	st.insert(30);
	st.insert(55);

	st.insert(18);
	st.insert(23);
	st.insert(28);
	st.insert(35);
	st.insert(44);
	st.insert(48);
	st.insert(53);
	st.insert(80);

	st.insert(12);
	st.insert(20);
	st.insert(22);
	st.insert(24);
	st.insert(27);
	st.insert(29);
	st.insert(33);
	st.insert(38);

	st.insert(43);
	st.insert(45);
	st.insert(47);
	st.insert(49);
	st.insert(51);
	st.insert(54);
	st.insert(60);
	st.insert(90);
	// ft::set<int> mySet;
	
	// std::cout << "Testing SET\n";

	// displaySetInfo(mySet);
	// displaySetContent(mySet);

	// mySet.insert(50);
	// mySet.insert(30);
	// mySet.insert(70);
	// mySet.insert(20);
	// mySet.insert(80);
	// mySet.insert(40);
	// mySet.insert(60);
	// mySet.insert(31);
	// mySet.insert(55);
	// mySet.insert(75);
	// mySet.insert(53);
	// mySet.insert(76);
	// mySet.insert(35);
	// mySet.insert(57);
	// displaySetInfo(mySet);
	// displaySetContent(mySet);

	// std::cout << "iterator created it begin\n";
	// ft::set<int>::iterator it = mySet.begin();
	// std::cout << "iterator created ite end\n";
	// ft::set<int>::iterator ite = mySet.end();
	
	// std::cout << "\ncopying SET:\n";
	// std::cout << "first using copy constructor\n";
	// ft::set<int> mySet2(mySet);
	// displaySetInfo(mySet2);
	// displaySetContent(mySet2);
	
	// std::cout << "\ncopying SET:\n";
	// std::cout << "second using assingment constructor\n";
	// ft::set<int> mySet3 = mySet;
	// displaySetInfo(mySet3);
	// displaySetContent(mySet3);

	// std::cout << "\ncopying SET:\n";
	// std::cout << "third using iterator constructor\n";
	
	// ft::set<int> mySet4(it, ite);
	// displaySetInfo(mySet4);
	// displaySetContent(mySet4);
	// std::cout << "\n\n";


	myTimer.set.end = clock();
}

// #define T1 int
// #define T2 std::string
// typedef ft::map<T1, T2>::value_type T3;

// template <typename MAP>
// void	ft_erase(MAP &mp, const T1 param)
// {
// 	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
// 	mp.erase(param);
// 	//printSize(mp);
// }
