/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:30:35 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/11 15:30:37 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers.hpp"

typedef int myType;
void test_map(t_testTime & myTimer)
{
	myTimer.map.start = clock();

	std::cout << "1. Testing [Map] default constructor with size, max_size, empty:\n";
	ft::map<myType, myType> myMap;
	std::map<myType, myType> stdMap;
	
	BasicMapStats(myMap, stdMap);
	
	std::cout << "\n\n2. Testing [Map] populating map with insert:\n";
	{
		ft::pair<ft::map<myType, myType>::iterator, bool> returnMyMap;
		std::pair<std::map<myType, myType>::iterator, bool> returnStdMap;
		for (size_t i = 0; i < 15; ++i)
		{
			returnMyMap = myMap.insert(ft::pair<myType, myType>((i + 1) * i, i));
			returnStdMap = stdMap.insert(std::pair<myType, myType>((i + 1) * i, i));
			isEqual(returnMyMap.second, returnStdMap.second);
		}
		returnMyMap = myMap.insert(ft::pair<myType, myType>(12, 12));
		returnStdMap = stdMap.insert(std::pair<myType, myType>(12, 12));
		isEqual(returnMyMap.second, returnStdMap.second);
	}
	{
		ft::map<myType, myType>::iterator ft_it = myMap.begin();
		ft::map<myType, myType>::iterator ft_ite = myMap.end();
		std::map<myType, myType>::iterator std_it = stdMap.begin();

		for (; ft_it != ft_ite; ++ft_it, ++std_it)
		{
			isEqual(ft_it->first, std_it->first);
			isEqual(ft_it->second, std_it->second);
		}
		BasicMapStats(myMap, stdMap);
	}
	// std::cout << "\n 1ft_";
	// displayMapContent(myMap);
	// std::cout << "\n1std_";
	// displayMapContent(stdMap);
	
	std::cout << "\n\n3. Testing [Map] copy constructor:\n";
	ft::map<myType, myType> myMap2(myMap);
	std::map<myType, myType> stdMap2(stdMap);
	
	{
		ft::map<myType, myType>::iterator ft_it = myMap2.begin();
		ft::map<myType, myType>::iterator ft_ite = myMap2.end();
		std::map<myType, myType>::iterator std_it = stdMap2.begin();

		for (; ft_it != ft_ite; ++ft_it, ++std_it)
		{
			isEqual(ft_it->first, std_it->first);
			isEqual(ft_it->second, std_it->second);
		}
		BasicMapStats(myMap2, stdMap2);
	}

	std::cout << "\n\n4. Testing [Map] operator[]:\n";
	myMap[0] = -1;
	myMap[5] = 42;
	myMap[10] = 1515;
	myMap[20] = 6000;
	
	stdMap[0] = -1;
	stdMap[5] = 42;
	stdMap[10] = 1515;
	stdMap[20] = 6000;

	// std::cout << "\n 1ft_";
	// displayMapContent(myMap);
	// std::cout << "\n1std_";
	// displayMapContent(stdMap);

	{
		ft::map<myType, myType>::iterator ft_it = myMap.begin();
		ft::map<myType, myType>::iterator ft_ite = myMap.end();
		std::map<myType, myType>::iterator std_it = stdMap.begin();

		for (; ft_it != ft_ite; ++ft_it, ++std_it)
		{
			isEqual(ft_it->first, std_it->first);
			isEqual(ft_it->second, std_it->second);
		}
		BasicMapStats(myMap, stdMap);
	}

	std::cout << "\n\n4. Testing [Map] assginement constructor:\n";
	ft::map<myType, myType> myMap3 = myMap;
	std::map<myType, myType> stdMap3 = stdMap;
	
	{
		ft::map<myType, myType>::iterator ft_it = myMap3.begin();
		ft::map<myType, myType>::iterator ft_ite = myMap3.end();
		std::map<myType, myType>::iterator std_it = stdMap3.begin();

		for (; ft_it != ft_ite; ++ft_it, ++std_it)
		{
			isEqual(ft_it->first, std_it->first);
			isEqual(ft_it->second, std_it->second);
		}
		BasicMapStats(myMap3, stdMap3);
	}

	std::cout << "\n\n5. Testing [Map] insert position, val:\n";
	{
		ft::map<myType, myType>::iterator ft_it = myMap3.begin();
		ft::map<myType, myType>::iterator ft_ite = myMap3.end();
		ft::map<myType, myType>::iterator ft_return;
		std::map<myType, myType>::iterator std_it = stdMap3.begin();
		std::map<myType, myType>::iterator std_ite = stdMap3.end();
		std::map<myType, myType>::iterator std_return;

		ft_return = myMap3.insert(ft_ite, ft::pair<myType, myType>(999, 999));
		std_return = stdMap3.insert(std_ite, std::pair<myType, myType>(999, 999));
		isEqual(ft_return->first, std_return->first);
		isEqual(ft_return->second, std_return->second);

		ft_return = myMap3.insert(ft_it, ft::pair<myType, myType>(111, 111));
		std_return = stdMap3.insert(std_it, std::pair<myType, myType>(111, 111));
		isEqual(ft_return->first, std_return->first);
		isEqual(ft_return->second, std_return->second);

		ft_return = myMap3.insert(++ft_it, ft::pair<myType, myType>(111, 666));
		std_return = stdMap3.insert(++std_it, std::pair<myType, myType>(111, 666));
		isEqual(ft_return->first, std_return->first);
		isEqual(ft_return->second, std_return->second);

		for (; ft_it != ft_ite; ++ft_it, ++std_it)
		{
			isEqual(ft_it->first, std_it->first);
			isEqual(ft_it->second, std_it->second);
		}
		//isEqual(ft::equal(myMap3.begin(), myMap3.end(), stdMap3.begin()), true);
		BasicMapStats(myMap3, stdMap3);
	}
	// std::cout << "\n 3ft_";
	// displayMapContent(myMap3);
	// std::cout << "\n3std_";
	// displayMapContent(stdMap3);
	
	std::cout << "\n\n5. Testing [Map] range constructor:\n";
	ft::map<myType, myType> myMap4(myMap.begin(), myMap.end());
	std::map<myType, myType> stdMap4(stdMap.begin(), stdMap.end());

	{
		ft::map<myType, myType>::iterator ft_it = myMap4.begin();
		ft::map<myType, myType>::iterator ft_ite = myMap4.end();
		std::map<myType, myType>::iterator std_it = stdMap4.begin();

		for (; ft_it != ft_ite; ++ft_it, ++std_it)
		{
			isEqual(ft_it->first, std_it->first);
			isEqual(ft_it->second, std_it->second);
		}
		BasicMapStats(myMap4, stdMap4);
	}

	std::cout << "\n\n5. Testing [Map] Iterator insert:\n";
	{
		ft::map<myType, myType>::iterator ft_it = myMap3.begin();
		ft::map<myType, myType>::iterator ft_ite = myMap3.end();
		std::map<myType, myType>::iterator std_it = stdMap3.begin();
		std::map<myType, myType>::iterator std_ite = stdMap3.end();

		myMap.insert(ft_it, ft_ite);
		stdMap.insert(std_it, std_ite);
		for (; ft_it != ft_ite; ++ft_it, ++std_it)
		{
			isEqual(ft_it->first, std_it->first);
			isEqual(ft_it->second, std_it->second);
		}
		BasicMapStats(myMap, stdMap);
	}
	
	std::cout << "\n\n6. Testing [Map] relational operators:\n";
	// std::cout << "\n 4ft_";
	// displayMapContent(myMap4);
	// std::cout << "\n4std_";
	// displayMapContent(stdMap4);

	RelationalTest(myMap, myMap2, stdMap, stdMap2);
	RelationalTest(myMap2, myMap3, stdMap2, stdMap3);
	RelationalTest(myMap3, myMap4, stdMap3, stdMap4);
	RelationalTest(myMap4, myMap, stdMap4, stdMap);
	RelationalTest(myMap2, myMap4, stdMap2, stdMap4);
	RelationalTest(myMap3, myMap, stdMap3, stdMap);
	RelationalTest(myMap4, myMap, stdMap4, stdMap);
	
	{
		std::cout << "\n\n13. Testing [Map] iterators:\n";
		ft::map<myType, myType>::iterator my_it = myMap.begin();
		ft::map<myType, myType>::iterator my_ite = myMap.end();

		std::map<myType, myType>::iterator std_it = stdMap.begin();
		std::map<myType, myType>::iterator std_ite = stdMap.end();
		RBTIteratorTest(my_it, my_ite, std_it, std_ite);
	}
	
	{
		std::cout << "\n\n14. Testing [Map] const_iterators:\n";
		ft::map<myType, myType>::const_iterator my_it = myMap2.begin();
		ft::map<myType, myType>::const_iterator my_ite = myMap2.end();

		std::map<myType, myType>::const_iterator std_it = stdMap2.begin();
		std::map<myType, myType>::const_iterator std_ite = stdMap2.end();
		RBTIteratorTest(my_it, my_ite, std_it, std_ite);
	}

	{
		std::cout << "\n\n15. Testing [Map] reverse_iterators rbegin and rend:\n";
		ft::map<myType, myType>::reverse_iterator my_it = myMap3.rbegin();
		ft::map<myType, myType>::reverse_iterator my_ite = myMap3.rend();

		std::map<myType, myType>::reverse_iterator std_it = stdMap3.rbegin();
		std::map<myType, myType>::reverse_iterator std_ite = stdMap3.rend();
		RBTIteratorTest(my_it, my_ite, std_it, std_ite);
	}
	
	{
		std::cout << "\n\n16. Testing [Map] const_reverse_iterators rbegin and rend:\n";
		ft::map<myType, myType>::const_reverse_iterator my_it = myMap4.rbegin();
		ft::map<myType, myType>::const_reverse_iterator my_ite = myMap4.rend();

		std::map<myType, myType>::const_reverse_iterator std_it = stdMap4.rbegin();
		std::map<myType, myType>::const_reverse_iterator std_ite = stdMap4.rend();
		RBTIteratorTest(my_it, my_ite, std_it, std_ite);
	}

	{
		std::cout << "\n\n17. Testing [Map] compare iterators and const_iterators:\n";
		ft::map<myType, myType>::iterator my_it = myMap.begin();
		ft::map<myType, myType>::const_iterator my_ite = myMap.end();

		std::map<myType, myType>::iterator std_it = stdMap.begin();
		std::map<myType, myType>::const_iterator std_ite = stdMap.end();
		RBTIteratorTest(my_it, my_ite, std_it, std_ite);
	}

	{
		std::cout << "\n\n18. Testing [Map] compare reverse_iterators and const_revese_iterators:\n";
		ft::map<myType, myType>::reverse_iterator my_it = myMap4.rbegin();
		ft::map<myType, myType>::const_reverse_iterator my_ite = myMap4.rend();

		std::map<myType, myType>::reverse_iterator std_it = stdMap4.rbegin();
		std::map<myType, myType>::const_reverse_iterator std_ite = stdMap4.rend();
		RBTIteratorTest(my_it, my_ite, std_it, std_ite);
	}

	{
		std::cout << "\n\n19. Testing [Map] erase position and iterators:\n";
		ft::map<myType, myType>::iterator my_it = myMap.begin();
		ft::map<myType, myType>::iterator my_ite = myMap.end();

		std::map<myType, myType>::iterator std_it = stdMap.begin();
		std::map<myType, myType>::iterator std_ite = stdMap.end();

		myMap.erase(++my_it);
		myMap.erase(--(--my_ite));
		stdMap.erase(++std_it);
		stdMap.erase(--(--std_ite));
		
		my_it = myMap2.begin();
		my_ite = myMap2.end();
		std_it = stdMap2.begin();
		std_ite = stdMap2.end();
		
		myMap2.erase(++(++my_it), --(--my_ite));
		stdMap2.erase(++(++std_it), --(--std_ite));
		
		my_it = myMap3.begin();
		my_ite = myMap3.end();
		std_it = stdMap3.begin();
		std_ite = stdMap3.end();

		myMap3.erase(--(--my_ite));
		stdMap3.erase(--(--std_ite));
		
		// std::cout << "\n 4ft_";
		// displayMapContent(myMap4);
		// std::cout << "my_it: " << myMap4.begin()->first << ":" << myMap4.begin()->second << "\n";
		// std::cout << "\n4std_";
		// displayMapContent(stdMap4);

		my_it = myMap4.begin();
		my_ite = myMap4.end();
		std_it = stdMap4.begin();
		std_ite = stdMap4.end();
	
		myMap4.erase(my_it, my_ite);
		stdMap4.erase(std_it, std_ite);
		
		// std::cout << "my_it: " << my_it->first << ":" << my_it->second << "\n";
		// std::cout << "std_it: " << std_it->first << ":" << std_it->second << "\n";

		// std::cout << "\n 4ft_";
		// displayMapContent(myMap4);
		// std::cout << "\n4std_";
		// displayMapContent(stdMap4);
	
		BasicMapStats(myMap, stdMap);
		BasicMapStats(myMap2, stdMap2);
		BasicMapStats(myMap3, stdMap3);
		BasicMapStats(myMap4, stdMap4);
		isEqual(ft::equal(myMap.begin(), myMap.end(), stdMap.begin()), true);
		isEqual(ft::equal(myMap2.begin(), myMap2.end(), stdMap2.begin()), true);
		isEqual(ft::equal(myMap3.begin(), myMap3.end(), stdMap3.begin()), true);
		isEqual(ft::equal(myMap4.begin(), myMap4.end(), stdMap4.begin()), true);
	}
	
	//displayMapContent(myMap);
	{
		std::cout << "\n\nxxx. Testing [Map] find:\n";
		
		ft::map<myType, myType>::iterator myFind;
		ft::map<myType, myType>::const_iterator const_myFind;
		
		std::map<myType, myType>::iterator stdFind;
		std::map<myType, myType>::const_iterator const_stdFind;

		myFind = myMap.find(0);
		const_myFind = myMap.find(0);
		
		stdFind = stdMap.find(0);
		const_stdFind = stdMap.find(0);

		isEqual(myFind->first, const_myFind->first);
		isEqual(stdFind->first, const_stdFind->first);
		isEqual(stdFind->first, const_myFind->first);
		isEqual(myFind->first, const_stdFind->first);
		isEqual(const_myFind->first, const_stdFind->first);

		//find element in the map
		myFind = myMap.find(11);
		const_myFind = myMap.find(11);
		
		//find element thats not in the map
		stdFind = stdMap.find(11);
		const_stdFind = stdMap.find(11);
		//will segfault without protection
		if (myFind != myMap.end())
		{
			isEqual(myFind->first, const_myFind->first);
			isEqual(stdFind->first, const_stdFind->first);
			isEqual(stdFind->first, const_myFind->first);
			isEqual(myFind->first, const_stdFind->first);
			isEqual(const_myFind->first, const_stdFind->first);
		}

		myFind = myMap.find(156);
		const_myFind = myMap.find(156);
		
		stdFind = stdMap.find(156);
		const_stdFind = stdMap.find(156);

		isEqual(myFind->first, const_myFind->first);
		isEqual(stdFind->first, const_stdFind->first);
		isEqual(stdFind->first, const_myFind->first);
		isEqual(myFind->first, const_stdFind->first);
		isEqual(const_myFind->first, const_stdFind->first);
	}
	
	std::cout << "\n\nYYY. Testing [Map] count:\n";
	
	isEqual(myMap.count(5), stdMap.count(5));
	isEqual(myMap.count(20), stdMap.count(20));
	isEqual(myMap.count(111), stdMap.count(111));
	isEqual(myMap.count(-5), stdMap.count(-5));
	isEqual(myMap.count(4242), stdMap.count(4242));
	
	{
		std::cout << "\n\n. Testing [Map] swap:\n";

		ft::map<myType, myType>::iterator my_it = myMap.begin();
		ft::map<myType, myType>::iterator my_ite = myMap.end();
		ft::map<myType, myType>::iterator my_it4 = myMap4.begin();
		ft::map<myType, myType>::iterator my_ite4 = myMap4.end();
		
		ft::map<myType, myType>::const_iterator my_it2 = myMap2.begin();
		ft::map<myType, myType>::const_iterator my_ite2 = myMap2.end();
		ft::map<myType, myType>::const_iterator my_it3 = myMap3.begin();
		ft::map<myType, myType>::const_iterator my_ite3 = myMap3.end();
	
		std::map<myType, myType>::iterator std_it = stdMap.begin();
		//std::map<myType, myType>::iterator std_ite = stdMap.end();
		std::map<myType, myType>::iterator std_it4 = stdMap4.begin();
		//std::map<myType, myType>::iterator std_ite5 = stdMap5.end();

		std::map<myType, myType>::const_iterator std_it2 = stdMap2.begin();
		//std::map<myType, myType>::const_iterator std_ite2 = stdMap2.end();
		std::map<myType, myType>::const_iterator std_it3 = stdMap3.begin();
		//std::map<myType, myType>::const_iterator std_ite3 = stdMap3.end();

		myMap.swap(myMap4);
		stdMap.swap(stdMap4);
		myMap2.swap(myMap3);
		stdMap2.swap(stdMap3);
		BasicMapStats(myMap, stdMap);
		BasicMapStats(myMap2, stdMap2);
		BasicMapStats(myMap3, stdMap3);
		BasicMapStats(myMap4, stdMap4);
		isEqual(ft::equal(my_it, my_ite, std_it), true);
		isEqual(ft::equal(my_it2, my_ite2, std_it2), true);
		isEqual(ft::equal(my_it3, my_ite3, std_it3), true);
		isEqual(ft::equal(my_it4, my_ite4, std_it4), true);
	}
	
	//displayMapContent(myMap4);
	
	{
		std::cout << "\n\nWWW. Testing [Map] lower_bound - upper_bound - equal_range\n";
		
		ft::map<myType, myType>::iterator myLowerBound;
		ft::map<myType, myType>::const_iterator const_myLowerBound;
		ft::map<myType, myType>::iterator myUpperBound;
		ft::map<myType, myType>::const_iterator const_myUpperBound;
		ft::pair<ft::map<myType, myType>::iterator, ft::map<myType, myType>::iterator> myEqualRange;
		ft::pair<ft::map<myType, myType>::const_iterator, ft::map<myType, myType>::const_iterator> const_myEqualRange;
		
		std::map<myType, myType>::iterator stdLowerBound;
		std::map<myType, myType>::const_iterator const_stdLowerBound;
		std::map<myType, myType>::iterator stdUpperBound;
		std::map<myType, myType>::const_iterator const_stdUpperBound;
		std::pair<std::map<myType, myType>::iterator, std::map<myType, myType>::iterator> stdEqualRange;
		std::pair<std::map<myType, myType>::const_iterator, std::map<myType, myType>::const_iterator> const_stdEqualRange;

		myLowerBound = myMap4.lower_bound(42);
		const_myLowerBound = myMap4.lower_bound(42);
		myUpperBound = myMap4.upper_bound(42);
		const_myUpperBound = myMap4.upper_bound(42);
		myEqualRange = myMap4.equal_range(42);
		const_myEqualRange = myMap4.equal_range(42);

		stdLowerBound = stdMap4.lower_bound(42);
		const_stdLowerBound = stdMap4.lower_bound(42);
		stdUpperBound = stdMap4.upper_bound(42);
		const_stdUpperBound = stdMap4.upper_bound(42);
		stdEqualRange = stdMap4.equal_range(42);
		const_stdEqualRange = stdMap4.equal_range(42);

		isEqual(myLowerBound->first, stdLowerBound->first);
		isEqual(myLowerBound->second, stdLowerBound->second);
		isEqual(const_myLowerBound->first, const_stdLowerBound->first);
		isEqual(const_myLowerBound->second, const_stdLowerBound->second);
		isEqual(myUpperBound->first, stdUpperBound->first);
		isEqual(myUpperBound->second, stdUpperBound->second);
		isEqual(const_myUpperBound->first, const_stdUpperBound->first);
		isEqual(const_myUpperBound->second, const_stdUpperBound->second);
		isEqual(myEqualRange.first->first, stdEqualRange.first->first);
		isEqual(myEqualRange.second->first, stdEqualRange.second->first);
		isEqual(const_myEqualRange.first->first, const_stdEqualRange.first->first);
		isEqual(const_myEqualRange.second->first, const_stdEqualRange.second->first);
		
	}
	
	std::cout << "\n\n. Testing [Map] clear:\n";
	
	myMap.clear();
	stdMap.clear();
	myMap2.clear();
	stdMap2.clear();
	myMap3.clear();
	stdMap3.clear();
	myMap4.clear();
	stdMap4.clear();
	BasicMapStats(myMap, stdMap);
	BasicMapStats(myMap2, stdMap2);
	BasicMapStats(myMap3, stdMap3);
	BasicMapStats(myMap4, stdMap4);
	isEqual(ft::equal(myMap.begin(), myMap.end(), stdMap.begin()), true);
	isEqual(ft::equal(myMap2.begin(), myMap2.end(), stdMap2.begin()), true);
	isEqual(ft::equal(myMap3.begin(), myMap3.end(), stdMap3.begin()), true);
	isEqual(ft::equal(myMap4.begin(), myMap4.end(), stdMap4.begin()), true);

	std::cout << "\n\n. Testing [Map] default constructor different datatype with size, max_size, empty:\n";
	ft::map<char, myType> myMap11;
	std::map<char, myType> stdMap11;

	myMap11['a'] = 2;
	myMap11['b'] = 3;
	myMap11['c'] = 4;
	myMap11['d'] = 5;
	
	stdMap11['a'] = 2;
	stdMap11['b'] = 3;
	stdMap11['c'] = 4;
	stdMap11['d'] = 5;
	
	{
		ft::map<char, myType>::iterator ft_it = myMap11.begin();
		ft::map<char, myType>::iterator ft_ite = myMap11.end();
		std::map<char, myType>::iterator std_it = stdMap11.begin();
		for (; ft_it != ft_ite; ++ft_it, ++std_it)
			{
				isEqual(ft_it->first, std_it->first);
				isEqual(ft_it->second, std_it->second);
			}
			//isEqual(ft::equal(myMap3.begin(), myMap3.end(), stdMap3.begin()), true);
			BasicMapStats(myMap11, stdMap11);
	}
	
	std::cout << "\n\n. Testing [Map] copy constructor different datatype:\n";
	ft::map<char, myType> myMap12(myMap11);
	std::map<char, myType> stdMap12(stdMap11);
	
	(++(++myMap11.begin()))->second = 42;
	(++(++stdMap11.begin()))->second = 42;
	
	{
		ft::map<char, myType>::iterator ft_it = myMap12.begin();
		ft::map<char, myType>::iterator ft_ite = myMap12.end();
		std::map<char, myType>::iterator std_it = stdMap12.begin();
		for (; ft_it != ft_ite; ++ft_it, ++std_it)
			{
				isEqual(ft_it->first, std_it->first);
				isEqual(ft_it->second, std_it->second);
			}
			//isEqual(ft::equal(myMap3.begin(), myMap3.end(), stdMap3.begin()), true);
			BasicMapStats(myMap12, stdMap12);
	}
	
	std::cout << "\n\n. Testing [Map] relational operators different datatype:\n";
	// std::cout << "\n 11ft_";
	// displayMapContent(myMap11);
	// std::cout << "\n11std_";
	// displayMapContent(stdMap11);
	// std::cout << "\n 12ft_";
	// displayMapContent(myMap12);
	// std::cout << "\n12std_";
	// displayMapContent(stdMap12);

	RelationalTest(myMap11, myMap12, stdMap11, stdMap12);
	RelationalTest(myMap12, myMap11, stdMap12, stdMap11);
	RelationalTest(myMap11, myMap11, stdMap11, stdMap11);
	RelationalTest(myMap12, myMap12, stdMap12, stdMap12);
	// RelationalTest(myMap2, myMap4, stdMap2, stdMap4);
	// RelationalTest(myMap3, myMap, stdMap3, stdMap);
	// RelationalTest(myMap4, myMap, stdMap4, stdMap);
	
	std::cout << "\n\n";
	//displayMapInfo(myMap);
	//std::cout << "height: " << myMap.height() << " blackNodes: " << myMap.blackNodes() << "\n";
	// myMap.insert(ft::pair<int, int>(50, 1));
	// //std::cout << "height: " << myMap.height() << " blackNodes: " << myMap.blackNodes() << "\n";
	// myMap.insert(ft::pair<int, int>(30, 2));
	// myMap.insert(ft::pair<int, int>(70, 3));
	// //std::cout << "height: " << myMap.height() << " blackNodes: " << myMap.blackNodes() << "\n";
	// myMap.insert(ft::pair<int, int>(20, 4));
	// myMap.insert(ft::pair<int, int>(80, 5));
	// myMap.insert(ft::pair<int, int>(40, 6));
	// myMap.insert(ft::pair<int, int>(60, 7));
	// //std::cout << "height: " << myMap.height() << " blackNodes: " << myMap.blackNodes() << "\n";
	// myMap.insert(ft::pair<int, int>(31, 8));
	// myMap.insert(ft::pair<int, int>(55, 9));
	// myMap.insert(ft::pair<int, int>(75, 10));
	// myMap.insert(ft::pair<int, int>(53, 11));
	// //std::cout << "height: " << myMap.height() << " blackNodes: " << myMap.blackNodes() << "\n";
	// myMap.insert(ft::pair<int, int>(76, 12));
	// myMap.insert(ft::pair<int, int>(35, 13));
	// myMap.insert(ft::pair<int, int>(57, 14));
	// std::cout << "insert 30\n";
	// myMap.insert(ft::pair<int, int>(30, 1));

	// std::cout << "insert 50\n";
	// myMap.insert(ft::pair<int, int>(50, 1));

	// myMap.printTree();
	// std::cout << "insert 60\n";
	// myMap.insert(ft::pair<int, int>(60, 1));

	// myMap.printTree();
	// //return ;
	// std::cout << "insert 70\n";
	// myMap.insert(ft::pair<int, int>(70, 1));
	// myMap.printTree();
	// std::cout << "erase 50\n";
	// myMap.erase(50);

	// myMap.printTree();
	// //return ;
	// std::cout << "insert 20\n";
	// myMap.insert(ft::pair<int, int>(20, 1));
	// myMap.printTree();
	// std::cout << "erase 70\n";
	// myMap.erase(70);
	
	// myMap.printTree();
	// //return ;
	// myMap.insert(ft::pair<int, int>(50, 1));
	// std::cout << "insert 50\n";
	// myMap.insert(ft::pair<int, int>(70, 1));
	// std::cout << "insert 70\n";
	// myMap.printTree();
	// //return ;
	// myMap.erase(20);
	// std::cout << "erase 20\n";
	// myMap.printTree();
	// //return ;
	// std::cout << "erase 60\n";
	// myMap.erase(60);
	// //return ;
	// myMap.printTree();
	// //return ;
	// myMap.insert(ft::pair<int, int>(20, 1));
	// std::cout << "insert 20\n";
	// myMap.insert(ft::pair<int, int>(40, 1));
	// std::cout << "insert 40\n";
	// myMap.insert(ft::pair<int, int>(60, 1));
	// std::cout << "insert 60\n";
	// myMap.insert(ft::pair<int, int>(80, 1));
	// std::cout << "insert 80\n";
	// myMap.insert(ft::pair<int, int>(100, 1));
	// std::cout << "insert 100\n";

	// myMap.printTree();
	// //return ;
	// std::cout << "erase 70\n";
	// myMap.erase(70);
	// //return;
	// //std::cout << "before print Tree\n";
	// myMap.printTree();
	//return ;
	//std::cout << "height: " << myMap.height() << " blackNodes: " << myMap.blackNodes() << "\n";
	// myMap.insert(ft::pair<int, int>(50, 1));
	// myMap.insert(ft::pair<int, int>(70, 2));
	// myMap.insert(ft::pair<int, int>(80, 3));
	// myMap.insert(ft::pair<int, int>(90, 4));
	// myMap.insert(ft::pair<int, int>(100, 5));
	// myMap.insert(ft::pair<int, int>(50, 1));
	// myMap.insert(ft::pair<int, int>(40, 2));
	// myMap.insert(ft::pair<int, int>(30, 3));
	// myMap.insert(ft::pair<int, int>(20, 4));
	// myMap.insert(ft::pair<int, int>(10, 5));
	
	// displayMapInfo(myMap);
	// displayMapContent(myMap);
	
	// std::cout << "iterator created it begin\n";
	// ft::map<int, int>::iterator it = myMap.begin();
	// it->second = 666;
	// std::cout << "iterator created ite end\n";
	// ft::map<int, int>::iterator ite = myMap.end();
	
	// std::cout << "\ncopying map:\n";
	// std::cout << "first using copy constructor\n";
	// ft::map<int, int> myMap2(myMap);
	// displayMapInfo(myMap2);
	// displayMapContent(myMap2);
	
	// std::cout << "\ncopying map:\n";
	// std::cout << "second using assingment constructor\n";
	// ft::map<int, int> myMap3 = myMap;
	// displayMapInfo(myMap3);
	// displayMapContent(myMap3);

	// std::cout << "\ncopying map:\n";
	// std::cout << "third using iterator constructor\n";
	
	// ft::map<int, int> myMap4(it, ite);
	// displayMapInfo(myMap4);
	// displayMapContent(myMap4);
	// std::cout << "\n\n";
	
	// myMap[50] = 42;

	
	// ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> myRange = myMap.equal_range(75);
	// std::cout << "lower_bound of 40 = " << myMap.lower_bound(40)->first << " upper_bound of 40 = " << myMap.upper_bound(40)->first << "\n";
	// std::cout << "lower_bound of 50 = " << myMap.lower_bound(50)->first << " upper_bound of 50 = " << myMap.upper_bound(50)->first << "\n";
	// std::cout << "equal_range of 75 = " << myRange.first->first << " = " << myRange.second->first << "\n";
	// std::cout << "\n\niterator test start\n";
	// std::cout << "printing with standard iterator forward\n";
	
	// while (it != ite)
	// {
	// 	std::cout << it->first << ":" << it->second << " ";
	// 	++it;
	// }
	
	// std::cout << "\nbackwards\n";
	// // it = myMap.begin();
	// // ++it;
	// // ++it;
	// // ++it;
	// --it;
	// while (it != ite)
	// {
	// 	std::cout << it->first << ":" << it->second << " ";
	// 	--it;
	// }

	
	// std::cout << "\n\nconst_iterator created cit begin\n";
	// ft::map<int, int>::const_iterator cit = myMap.begin();
	// std::cout << "const_iterator created cite end\n";
	// ft::map<int, int>::const_iterator cite = myMap.end();
	// //cit->second = 666; //compiler error because of const iterator
	// while (cit != cite)
	// {
	// 	std::cout << cit->first << ":" << cit->second << " ";
	// 	++cit;
	// }
	
	// std::cout << "\nbackwards\n";
	// cit = myMap.end();
	// --cit;
	// int mapSize = myMap.size();
	// std::cout << "myMap.size()= " << mapSize << "\n";
	// //std::cout << cit->first << ":" << cit->second << " ";
	// for (int i = 1; i < mapSize; ++i)
	// {
	// 	std::cout << cit->first << ":" << cit->second << " ";
	// 	++cit;
	// }
	// std::cout << cit->first << ":" << cit->second << " ";
	// std::cout << "\n\n";
	//--cit;
	
	// while (cit != cite)
	// {
	// 	std::cout << cit->first << ":" << cit->second << " ";
	// 	--cit;
	// }
	
	// std::cout << "\n\nreverse_iterator created rit begin\n";
	// ft::map<int, int>::reverse_iterator rit = myMap.rbegin();
	// std::cout << "reverse_iterator created rite end\n";
	// ft::map<int, int>::reverse_iterator rite = myMap.rend();
	// //cit->second = 666;
	// while (rit != rite)
	// {
	// 	std::cout << rit->first << ":" << rit->second << " ";
	// 	++rit;
	// }
	
	// std::cout << "\nbackwards\n";
	// --rit;
	// while (rit != rite)
	// {
	// 	std::cout << rit->first << ":" << rit->second << " ";
	// 	--rit;
	// }

	// std::cout << "\n\nconst_reverse_iterator created crit begin\n";
	// ft::map<int, int>::const_reverse_iterator crit = myMap.rbegin();
	// std::cout << "const_reverse_iterator created crite end\n";
	// ft::map<int, int>::const_reverse_iterator crite = myMap.rend();
	// //cit->second = 666;
	// while (crit != crite)
	// {
	// 	std::cout << crit->first << ":" << crit->second << " ";
	// 	++crit;
	// }
	//crit->second = 666;
	// std::cout << "\nbackwards\n";
	// --crit;
	// while (crit != crite)
	// {
	// 	std::cout << crit->first << ":" << crit->second << " ";
	// 	--crit;
	// }
	// std::cout << "\n";

	
	// myMap.erase(55);
	// std::cout << "deleted number 55\n\n";
	// std::cout << "lower_bound of 40 = " << myMap.lower_bound(40)->first << " upper_bound of 40 = " << myMap.upper_bound(40)->first << "\n";
	// displayMapContent(myMap);
	// ft::map<int, int>::iterator erase_it = myMap.find(75);
	// myMap.erase(erase_it);
	// std::cout << "erase key 75 with iterator\n";
	// displayMapContent(myMap);
	// std::cout << "iterator tests\n";
	// it = myMap.begin();
	// ite = myMap.end();
	
	//--ite;
	// while (it != ite)
	// {
	// 	std::cout << it->first << ":" << it->second << " ";
	// 	++it;
	// }
	//++it;
	// std::cout << "\n using the same iterators by incrementing it again going forwards\n";
	// while (it != ite)
	// {
	// 	std::cout << it->first << ":" << it->second << " ";
	// 	++it;
	// }
	// --it;
	//it = myMap.end();
	// --it;
	// std::cout << "\n";
	// ite = myMap.begin();
	// --ite;
	// //std::cout << "\n using the same iterators by decremeting it againg going backwards\n";
	// while (it != ite)
	// {
	// 	std::cout << it->first << ":" << it->second << " ";
	// 	--it;
	// }
	// std::cout << "\ndone with iterators\n";
	
	//displayMapContent(myMap);

	// it = myMap.begin();
	// ite = myMap.end();
	// ++it;
	// ++it;
	// //++it;
	// //++it;
	// --ite;
	// --ite;
	// std::cout << "deleting map content with iterators start: " << it->first << " end: " << ite->first << "\n";
	// myMap.erase(it, ite);
	// myMap.insert(ft::pair<int, int>(90, 99));
	// // myMap.erase(it);
	// // myMap.erase(60);
	// // myMap.erase(70);
	// // myMap.erase(80);
	// displayMapContent(myMap);
	// //myMap.insert(ft::pair<int, int>(5, 1));
	// //displayMapContent(myMap);
	// //std::cout << "height: " << myMap.height() << " blackNodes: " << myMap.blackNodes() << "\n";
	myTimer.map.end = clock();
}
