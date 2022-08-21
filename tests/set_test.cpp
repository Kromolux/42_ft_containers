/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:31:31 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/19 15:52:35 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers.hpp"

typedef int myType;
void test_set(t_testTime & myTimer)
{
	myTimer.set.start = clock();

	std::cout << "1. Testing [Set] default constructor with size, max_size, empty:\n";
	ft::set<myType> mySet;
	std::set<myType> stdSet;
	
	BasicMapStats(mySet, stdSet);
	
	std::cout << "\n\n2. Testing [Set] populating set with insert:\n";
	{
		ft::pair<ft::set<myType>::iterator, bool> returnmySet;
		std::pair<std::set<myType>::iterator, bool> returnstdSet;
		for (size_t i = 0; i < 15; ++i)
		{
			returnmySet = mySet.insert((i + 1) * i);
			returnstdSet = stdSet.insert((i + 1) * i);
			isEqual(returnmySet.second, returnstdSet.second);
		}
		returnmySet = mySet.insert(12);
		returnstdSet = stdSet.insert(12);
		isEqual(returnmySet.second, returnstdSet.second);
	}
	{
		ft::set<myType>::iterator ft_it = mySet.begin();
		ft::set<myType>::iterator ft_ite = mySet.end();
		std::set<myType>::iterator std_it = stdSet.begin();

		for (; ft_it != ft_ite; ++ft_it, ++std_it)
			isEqual(*ft_it, *std_it);
		BasicMapStats(mySet, stdSet);
	}
	
	std::cout << "\n\n3. Testing [Set] copy constructor:\n";
	ft::set<myType> mySet2(mySet);
	std::set<myType> stdSet2(stdSet);
	
	{
		ft::set<myType>::iterator ft_it = mySet2.begin();
		ft::set<myType>::iterator ft_ite = mySet2.end();
		std::set<myType>::iterator std_it = stdSet2.begin();

		for (; ft_it != ft_ite; ++ft_it, ++std_it)
			isEqual(*ft_it, *std_it);
		BasicMapStats(mySet2, stdSet2);
	}

	// std::cout << "\n\n4. Testing [Set] operator[]:\n";
	// mySet[0] = -1;
	// mySet[5] = 42;
	// mySet[10] = 1515;
	// mySet[20] = 6000;
	
	// stdSet[0] = -1;
	// stdSet[5] = 42;
	// stdSet[10] = 1515;
	// stdSet[20] = 6000;

	// {
	// 	ft::set<myType>::iterator ft_it = mySet.begin();
	// 	ft::set<myType>::iterator ft_ite = mySet.end();
	// 	std::set<myType>::iterator std_it = stdSet.begin();

	// 	for (; ft_it != ft_ite; ++ft_it, ++std_it)
	// 		isEqual(ft_it, std_it);
	// 	BasicMapStats(mySet, stdSet);
	// }

	std::cout << "\n\n5. Testing [Set] assginement constructor:\n";
	ft::set<myType> mySet3 = mySet;
	std::set<myType> stdSet3 = stdSet;
	
	{
		ft::set<myType>::iterator ft_it = mySet3.begin();
		ft::set<myType>::iterator ft_ite = mySet3.end();
		std::set<myType>::iterator std_it = stdSet3.begin();

		for (; ft_it != ft_ite; ++ft_it, ++std_it)
			isEqual(*ft_it, *std_it);
		BasicMapStats(mySet3, stdSet3);
	}

	std::cout << "\n\n6. Testing [Set] insert position, val:\n";
	{
		ft::set<myType>::iterator ft_it = mySet3.begin();
		ft::set<myType>::iterator ft_ite = mySet3.end();
		ft::set<myType>::iterator ft_return;
		std::set<myType>::iterator std_it = stdSet3.begin();
		std::set<myType>::iterator std_ite = stdSet3.end();
		std::set<myType>::iterator std_return;

		ft_return = mySet3.insert(ft_ite, 999);
		std_return = stdSet3.insert(std_ite, 999);
		isEqual(*ft_return, *std_return);

		ft_return = mySet3.insert(ft_it, 111);
		std_return = stdSet3.insert(std_it, 111);
		isEqual(*ft_return, *std_return);

		ft_return = mySet3.insert(++ft_it, 111);
		std_return = stdSet3.insert(++std_it, 111);
		isEqual(*ft_return, *std_return);

		for (; ft_it != ft_ite; ++ft_it, ++std_it)
			isEqual(*ft_it, *std_it);
		BasicMapStats(mySet3, stdSet3);
	}
	
	std::cout << "\n\n7. Testing [Set] range constructor:\n";
	ft::set<myType> mySet4(mySet.begin(), mySet.end());
	std::set<myType> stdSet4(stdSet.begin(), stdSet.end());

	{
		ft::set<myType>::iterator ft_it = mySet4.begin();
		ft::set<myType>::iterator ft_ite = mySet4.end();
		std::set<myType>::iterator std_it = stdSet4.begin();

		for (; ft_it != ft_ite; ++ft_it, ++std_it)
			isEqual(*ft_it, *std_it);
		BasicMapStats(mySet4, stdSet4);
	}

	std::cout << "\n\n8. Testing [Set] Iterator insert:\n";
	{
		ft::set<myType>::iterator ft_it = mySet3.begin();
		ft::set<myType>::iterator ft_ite = mySet3.end();
		std::set<myType>::iterator std_it = stdSet3.begin();
		std::set<myType>::iterator std_ite = stdSet3.end();

		mySet.insert(ft_it, ft_ite);
		stdSet.insert(std_it, std_ite);
		for (; ft_it != ft_ite; ++ft_it, ++std_it)
			isEqual(*ft_it, *std_it);
		BasicMapStats(mySet, stdSet);
	}
	
	std::cout << "\n\n9. Testing [Set] relational operators:\n";

	RelationalTest(mySet, mySet2, stdSet, stdSet2);
	RelationalTest(mySet2, mySet3, stdSet2, stdSet3);
	RelationalTest(mySet3, mySet4, stdSet3, stdSet4);
	RelationalTest(mySet4, mySet, stdSet4, stdSet);
	RelationalTest(mySet2, mySet4, stdSet2, stdSet4);
	RelationalTest(mySet3, mySet, stdSet3, stdSet);
	RelationalTest(mySet4, mySet, stdSet4, stdSet);
	
	{
		std::cout << "\n\n10. Testing [Set] iterators:\n";
		ft::set<myType>::iterator my_it = mySet.begin();
		ft::set<myType>::iterator my_ite = mySet.end();

		std::set<myType>::iterator std_it = stdSet.begin();
		std::set<myType>::iterator std_ite = stdSet.end();
		RBTSetIteratorTest(my_it, my_ite, std_it, std_ite);
	}
	
	{
		std::cout << "\n\n11. Testing [Set] const_iterators:\n";
		ft::set<myType>::const_iterator my_it = mySet2.begin();
		ft::set<myType>::const_iterator my_ite = mySet2.end();

		std::set<myType>::const_iterator std_it = stdSet2.begin();
		std::set<myType>::const_iterator std_ite = stdSet2.end();
		RBTSetIteratorTest(my_it, my_ite, std_it, std_ite);
	}

	{
		std::cout << "\n\n12. Testing [Set] reverse_iterators rbegin and rend:\n";
		ft::set<myType>::reverse_iterator my_it = mySet3.rbegin();
		ft::set<myType>::reverse_iterator my_ite = mySet3.rend();

		std::set<myType>::reverse_iterator std_it = stdSet3.rbegin();
		std::set<myType>::reverse_iterator std_ite = stdSet3.rend();
		RBTSetIteratorTest(my_it, my_ite, std_it, std_ite);
	}
	
	{
		std::cout << "\n\n13. Testing [Set] const_reverse_iterators rbegin and rend:\n";
		ft::set<myType>::const_reverse_iterator my_it = mySet4.rbegin();
		ft::set<myType>::const_reverse_iterator my_ite = mySet4.rend();

		std::set<myType>::const_reverse_iterator std_it = stdSet4.rbegin();
		std::set<myType>::const_reverse_iterator std_ite = stdSet4.rend();
		RBTSetIteratorTest(my_it, my_ite, std_it, std_ite);
	}

	{
		std::cout << "\n\n14. Testing [Set] compare iterators and const_iterators:\n";
		ft::set<myType>::iterator my_it = mySet.begin();
		ft::set<myType>::const_iterator my_ite = mySet.end();

		std::set<myType>::iterator std_it = stdSet.begin();
		std::set<myType>::const_iterator std_ite = stdSet.end();
		RBTSetIteratorTest(my_it, my_ite, std_it, std_ite);
	}

	{
		std::cout << "\n\n15. Testing [Set] compare reverse_iterators and const_revese_iterators:\n";
		ft::set<myType>::reverse_iterator my_it = mySet4.rbegin();
		ft::set<myType>::const_reverse_iterator my_ite = mySet4.rend();

		std::set<myType>::reverse_iterator std_it = stdSet4.rbegin();
		std::set<myType>::const_reverse_iterator std_ite = stdSet4.rend();
		RBTSetIteratorTest(my_it, my_ite, std_it, std_ite);
	}

	{
		std::cout << "\n\n16. Testing [Set] erase position and iterators:\n";
		ft::set<myType>::iterator my_it = mySet.begin();
		ft::set<myType>::iterator my_ite = mySet.end();

		std::set<myType>::iterator std_it = stdSet.begin();
		std::set<myType>::iterator std_ite = stdSet.end();

		mySet.erase(++my_it);
		mySet.erase(--(--my_ite));
		stdSet.erase(++std_it);
		stdSet.erase(--(--std_ite));
		
		my_it = mySet2.begin();
		my_ite = mySet2.end();
		std_it = stdSet2.begin();
		std_ite = stdSet2.end();
		
		mySet2.erase(++(++my_it), --(--my_ite));
		stdSet2.erase(++(++std_it), --(--std_ite));
		
		my_it = mySet3.begin();
		my_ite = mySet3.end();
		std_it = stdSet3.begin();
		std_ite = stdSet3.end();

		mySet3.erase(--(--my_ite));
		stdSet3.erase(--(--std_ite));

		my_it = mySet4.begin();
		my_ite = mySet4.end();
		std_it = stdSet4.begin();
		std_ite = stdSet4.end();
	
		mySet4.erase(my_it, my_ite);
		stdSet4.erase(std_it, std_ite);
	
		BasicMapStats(mySet, stdSet);
		BasicMapStats(mySet2, stdSet2);
		BasicMapStats(mySet3, stdSet3);
		BasicMapStats(mySet4, stdSet4);
		isEqual(ft::equal(mySet.begin(), mySet.end(), stdSet.begin()), true);
		isEqual(ft::equal(mySet2.begin(), mySet2.end(), stdSet2.begin()), true);
		isEqual(ft::equal(mySet3.begin(), mySet3.end(), stdSet3.begin()), true);
		isEqual(ft::equal(mySet4.begin(), mySet4.end(), stdSet4.begin()), true);
	}

	{
		std::cout << "\n\n17. Testing [Set] find:\n";
		
		ft::set<myType>::iterator myFind;
		ft::set<myType>::const_iterator const_myFind;
		
		std::set<myType>::iterator stdFind;
		std::set<myType>::const_iterator const_stdFind;

		myFind = mySet.find(0);
		const_myFind = mySet.find(0);
		
		stdFind = stdSet.find(0);
		const_stdFind = stdSet.find(0);

		isEqual(*myFind, *const_myFind);
		isEqual(*stdFind, *const_stdFind);
		isEqual(*stdFind, *const_myFind);
		isEqual(*myFind, *const_stdFind);
		isEqual(*const_myFind, *const_stdFind);

		//find element in the set
		myFind = mySet.find(11);
		const_myFind = mySet.find(11);
		
		//find element thats not in the set
		stdFind = stdSet.find(11);
		const_stdFind = stdSet.find(11);
		//will segfault without protection
		if (myFind != mySet.end())
		{
			isEqual(*myFind, *const_myFind);
			isEqual(*stdFind, *const_stdFind);
			isEqual(*stdFind, *const_myFind);
			isEqual(*myFind, *const_stdFind);
			isEqual(*const_myFind, *const_stdFind);
		}

		myFind = mySet.find(156);
		const_myFind = mySet.find(156);
		
		stdFind = stdSet.find(156);
		const_stdFind = stdSet.find(156);

		isEqual(*myFind, *const_myFind);
		isEqual(*stdFind, *const_stdFind);
		isEqual(*stdFind, *const_myFind);
		isEqual(*myFind, *const_stdFind);
		isEqual(*const_myFind, *const_stdFind);
	}
	
	std::cout << "\n\n18. Testing [Set] count:\n";
	
	isEqual(mySet.count(5), stdSet.count(5));
	isEqual(mySet.count(20), stdSet.count(20));
	isEqual(mySet.count(111), stdSet.count(111));
	isEqual(mySet.count(-5), stdSet.count(-5));
	isEqual(mySet.count(4242), stdSet.count(4242));
	
	{
		std::cout << "\n\n19. Testing [Set] swap:\n";

		ft::set<myType>::iterator my_it = mySet.begin();
		ft::set<myType>::iterator my_ite = mySet.end();
		ft::set<myType>::iterator my_it4 = mySet4.begin();
		ft::set<myType>::iterator my_ite4 = mySet4.end();
		
		ft::set<myType>::const_iterator my_it2 = mySet2.begin();
		ft::set<myType>::const_iterator my_ite2 = mySet2.end();
		ft::set<myType>::const_iterator my_it3 = mySet3.begin();
		ft::set<myType>::const_iterator my_ite3 = mySet3.end();
	
		std::set<myType>::iterator std_it = stdSet.begin();
		std::set<myType>::iterator std_it4 = stdSet4.begin();

		std::set<myType>::const_iterator std_it2 = stdSet2.begin();
		std::set<myType>::const_iterator std_it3 = stdSet3.begin();

		mySet.swap(mySet4);
		stdSet.swap(stdSet4);
		mySet2.swap(mySet3);
		stdSet2.swap(stdSet3);
		BasicMapStats(mySet, stdSet);
		BasicMapStats(mySet2, stdSet2);
		BasicMapStats(mySet3, stdSet3);
		BasicMapStats(mySet4, stdSet4);
		isEqual(ft::equal(my_it, my_ite, std_it), true);
		isEqual(ft::equal(my_it2, my_ite2, std_it2), true);
		isEqual(ft::equal(my_it3, my_ite3, std_it3), true);
		isEqual(ft::equal(my_it4, my_ite4, std_it4), true);
	}
	
	{
		std::cout << "\n\n20. Testing [Set] lower_bound - upper_bound - equal_range\n";
		
		ft::set<myType>::iterator myLowerBound;
		ft::set<myType>::const_iterator const_myLowerBound;
		ft::set<myType>::iterator myUpperBound;
		ft::set<myType>::const_iterator const_myUpperBound;
		ft::pair<ft::set<myType>::iterator, ft::set<myType>::iterator> myEqualRange;
		ft::pair<ft::set<myType>::const_iterator, ft::set<myType>::const_iterator> const_myEqualRange;
		
		std::set<myType>::iterator stdLowerBound;
		std::set<myType>::const_iterator const_stdLowerBound;
		std::set<myType>::iterator stdUpperBound;
		std::set<myType>::const_iterator const_stdUpperBound;
		std::pair<std::set<myType>::iterator, std::set<myType>::iterator> stdEqualRange;
		std::pair<std::set<myType>::const_iterator, std::set<myType>::const_iterator> const_stdEqualRange;

		myLowerBound = mySet4.lower_bound(42);
		const_myLowerBound = mySet4.lower_bound(42);
		myUpperBound = mySet4.upper_bound(42);
		const_myUpperBound = mySet4.upper_bound(42);
		myEqualRange = mySet4.equal_range(42);
		const_myEqualRange = mySet4.equal_range(42);

		stdLowerBound = stdSet4.lower_bound(42);
		const_stdLowerBound = stdSet4.lower_bound(42);
		stdUpperBound = stdSet4.upper_bound(42);
		const_stdUpperBound = stdSet4.upper_bound(42);
		stdEqualRange = stdSet4.equal_range(42);
		const_stdEqualRange = stdSet4.equal_range(42);

		isEqual(*myLowerBound, *stdLowerBound);
		isEqual(*const_myLowerBound, *const_stdLowerBound);
		isEqual(*myUpperBound, *stdUpperBound);
		isEqual(*const_myUpperBound, *const_stdUpperBound);
		isEqual(*myEqualRange.first, *stdEqualRange.first);
		isEqual(*const_myEqualRange.first, *const_stdEqualRange.first);
	}
	
	std::cout << "\n\n21. Testing [Set] clear:\n";
	
	mySet.clear();
	stdSet.clear();
	mySet2.clear();
	stdSet2.clear();
	mySet3.clear();
	stdSet3.clear();
	mySet4.clear();
	stdSet4.clear();
	BasicMapStats(mySet, stdSet);
	BasicMapStats(mySet2, stdSet2);
	BasicMapStats(mySet3, stdSet3);
	BasicMapStats(mySet4, stdSet4);
	isEqual(ft::equal(mySet.begin(), mySet.end(), stdSet.begin()), true);
	isEqual(ft::equal(mySet2.begin(), mySet2.end(), stdSet2.begin()), true);
	isEqual(ft::equal(mySet3.begin(), mySet3.end(), stdSet3.begin()), true);
	isEqual(ft::equal(mySet4.begin(), mySet4.end(), stdSet4.begin()), true);

	std::cout << "\n\n22. Testing [Set] default constructor different datatype with size, max_size, empty:\n";
	ft::set<char> mySet11;
	std::set<char> stdSet11;

	mySet11.insert('a');
	mySet11.insert('b');
	mySet11.insert('c');
	mySet11.insert('d');
	
	stdSet11.insert('a');
	stdSet11.insert('b');
	stdSet11.insert('c');
	stdSet11.insert('d');
	
	{
		ft::set<char>::iterator ft_it = mySet11.begin();
		ft::set<char>::iterator ft_ite = mySet11.end();
		std::set<char>::iterator std_it = stdSet11.begin();
		for (; ft_it != ft_ite; ++ft_it, ++std_it)
			isEqual(*ft_it, *std_it);
		BasicMapStats(mySet11, stdSet11);
	}
	
	std::cout << "\n\n23. Testing [Set] copy constructor different datatype:\n";
	ft::set<char> mySet12(mySet11);
	std::set<char> stdSet12(stdSet11);
	
	mySet11.insert(42);
	stdSet11.insert(42);
	
	{
		ft::set<char>::iterator ft_it = mySet12.begin();
		ft::set<char>::iterator ft_ite = mySet12.end();
		std::set<char>::iterator std_it = stdSet12.begin();
		for (; ft_it != ft_ite; ++ft_it, ++std_it)
			isEqual(*ft_it, *std_it);
		BasicMapStats(mySet12, stdSet12);
	}
	
	std::cout << "\n\n24. Testing [Set] relational operators different datatype:\n";

	RelationalTest(mySet11, mySet12, stdSet11, stdSet12);
	RelationalTest(mySet12, mySet11, stdSet12, stdSet11);
	RelationalTest(mySet11, mySet11, stdSet11, stdSet11);
	RelationalTest(mySet12, mySet12, stdSet12, stdSet12);
	
	std::cout << "\n\n";

	myTimer.set.end = clock();
}
