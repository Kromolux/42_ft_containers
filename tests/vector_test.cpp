/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:27:41 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/01 15:08:39 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers.hpp"

typedef int myType;
void test_vector(t_testTime & myTimer)
{
	myTimer.vector.start = clock();

	std::cout << "1. Testing [Vector] default constructor with size, max_size, empty, capacity:\n";
	ft::vector<myType> myVec;
	std::vector<myType> stdVec;

	BasicVectorStats(myVec, stdVec);
	
	std::cout << "\n\n2. Testing [Vector] reserve:\n";
	myVec.reserve(20);
	stdVec.reserve(20);
	isEqual(myVec.capacity(), stdVec.capacity());
	
	std::cout << "\n\n3. Testing [Vector] push_back:\n";
	for (size_t i = 0; i < 15; ++i)
	{
		myVec.push_back((i + 1) * i);
		stdVec.push_back((i + 1) * i);
	}

	for (size_t i = 0; i < myVec.size(); ++i)
		isEqual(myVec[i], stdVec[i]);
	BasicVectorStats(myVec, stdVec);
		
	std::cout << "\n\n4. Testing [Vector] copy constructor:\n";
	ft::vector<myType> myVec2(myVec);
	std::vector<myType> stdVec2(stdVec);

	BasicVectorStats(myVec2, stdVec2);
	for (size_t i = 0; i < myVec2.size(); ++i)
		isEqual(myVec2[i], stdVec2[i]);

	std::cout << "\n\n5. Testing [Vector] operator[]:\n";
	myVec[0] = 42;
	myVec[1] = 15;
	myVec[2] = INT_MAX;
	myVec[3] = INT_MIN;
	myVec[4] = -1;
	myVec[5] = 0;

	stdVec[0] = 42;
	stdVec[1] = 15;
	stdVec[2] = INT_MAX;
	stdVec[3] = INT_MIN;
	stdVec[4] = -1;
	stdVec[5] = 0;
	
	for (size_t i = 0; i < myVec.size(); ++i)
		isEqual(myVec[i], stdVec[i]);
	BasicVectorStats(myVec, stdVec);

	std::cout << "\n\n6. Testing [Vector] fill constructor:\n";
	ft::vector<myType> myVec3(42, 42);
	std::vector<myType> stdVec3(42, 42);

	BasicVectorStats(myVec3, stdVec3);
	for (size_t i = 0; i < myVec3.size(); ++i)
		isEqual(myVec3[i], stdVec3[i]);


	std::cout << "\n\n7. Testing [Vector] range constructor:\n";
	ft::vector<myType> myVec4(myVec.begin(), myVec.end());
	std::vector<myType> stdVec4(stdVec.begin(), stdVec.end());

	BasicVectorStats(myVec4, stdVec4);
	for (size_t i = 0; i < myVec4.size(); ++i)
		isEqual(myVec4[i], stdVec4[i]);

	std::cout << "\n\n8. Testing [Vector] assignement constructor:\n";
	ft::vector<myType> myVec5 = myVec2;
	std::vector<myType> stdVec5 = stdVec2;
	
	BasicVectorStats(myVec5, stdVec5);
	for (size_t i = 0; i < myVec5.size(); ++i)
		isEqual(myVec5[i], stdVec5[i]);

	std::cout << "\n\n9. Testing [Vector] massive push_back:\n";
	for (int i = 0; i < 10000; ++i)
	{
		myVec.push_back(i);
		stdVec.push_back(i);
	}
	BasicVectorStats(myVec, stdVec);
	isEqual(ft::equal(myVec.begin(), myVec.end(), stdVec.begin()), true);

	std::cout << "\n\n10. Testing [Vector] front and back:\n";

	isEqual(myVec.front(), stdVec.front());
	isEqual(myVec2.front(), stdVec2.front());
	isEqual(myVec3.front(), stdVec3.front());
	isEqual(myVec4.front(), stdVec4.front());
	isEqual(myVec5.front(), stdVec5.front());
	
	isEqual(myVec.back(), stdVec.back());
	isEqual(myVec2.back(), stdVec2.back());
	isEqual(myVec3.back(), stdVec3.back());
	isEqual(myVec4.back(), stdVec4.back());
	isEqual(myVec5.back(), stdVec5.back());


	std::cout << "\n\n11. Testing [Vector] at:\n";

	isEqual(myVec.at(0), stdVec.at(0));
	isEqual(myVec2.at(1), stdVec2.at(1));
	isEqual(myVec3.at(2), stdVec3.at(2));
	isEqual(myVec4.at(3), stdVec4.at(3));
	isEqual(myVec5.at(4), stdVec5.at(4));

	std::cout << "\n\n12. Testing [Vector] resize:\n";
	
	myVec.resize(9);
	myVec2.resize(10);
	myVec3.resize(11);
	myVec4.resize(12);
	myVec5.resize(8);
	stdVec.resize(9);
	stdVec2.resize(10);
	stdVec3.resize(11);
	stdVec4.resize(12);
	stdVec5.resize(8);
	BasicVectorStats(myVec, stdVec);
	BasicVectorStats(myVec2, stdVec2);
	BasicVectorStats(myVec3, stdVec3);
	BasicVectorStats(myVec4, stdVec4);
	BasicVectorStats(myVec5, stdVec5);
	isEqual(ft::equal(myVec.begin(), myVec.end(), stdVec.begin()), true);
	isEqual(ft::equal(myVec2.begin(), myVec2.end(), stdVec2.begin()), true);
	isEqual(ft::equal(myVec3.begin(), myVec3.end(), stdVec3.begin()), true);
	isEqual(ft::equal(myVec4.begin(), myVec4.end(), stdVec4.begin()), true);
	isEqual(ft::equal(myVec5.begin(), myVec5.end(), stdVec5.begin()), true);
	
	{
		std::cout << "\n\n13. Testing [Vector] iterators:\n";
		ft::vector<myType>::iterator my_it = myVec.begin();
		ft::vector<myType>::iterator my_ite = myVec.end();

		std::vector<myType>::iterator std_it = stdVec.begin();
		std::vector<myType>::iterator std_ite = stdVec.end();
		IteratorTest(my_it, my_ite, std_it, std_ite);
	}
	
	{
		std::cout << "\n\n14. Testing [Vector] const_iterators:\n";
		ft::vector<myType>::const_iterator my_it = myVec2.begin();
		ft::vector<myType>::const_iterator my_ite = myVec2.end();

		std::vector<myType>::const_iterator std_it = stdVec2.begin();
		std::vector<myType>::const_iterator std_ite = stdVec2.end();
		IteratorTest(my_it, my_ite, std_it, std_ite);
	}

	{
		std::cout << "\n\n15. Testing [Vector] reverse_iterators rbegin and rend:\n";
		ft::vector<myType>::reverse_iterator my_it = myVec3.rbegin();
		ft::vector<myType>::reverse_iterator my_ite = myVec3.rend();

		std::vector<myType>::reverse_iterator std_it = stdVec3.rbegin();
		std::vector<myType>::reverse_iterator std_ite = stdVec3.rend();
		IteratorTest(my_it, my_ite, std_it, std_ite);
	}
	
	{
		std::cout << "\n\n16. Testing [Vector] const_reverse_iterators rbegin and rend:\n";
		ft::vector<myType>::const_reverse_iterator my_it = myVec4.rbegin();
		ft::vector<myType>::const_reverse_iterator my_ite = myVec4.rend();

		std::vector<myType>::const_reverse_iterator std_it = stdVec4.rbegin();
		std::vector<myType>::const_reverse_iterator std_ite = stdVec4.rend();
		IteratorTest(my_it, my_ite, std_it, std_ite);
	}

	{
		std::cout << "\n\n17. Testing [Vector] compare iterators and const_iterators:\n";
		ft::vector<myType>::iterator my_it = myVec5.begin();
		ft::vector<myType>::const_iterator my_ite = myVec5.end();

		std::vector<myType>::iterator std_it = stdVec5.begin();
		std::vector<myType>::const_iterator std_ite = stdVec5.end();
		IteratorTest(my_it, my_ite, std_it, std_ite);
	}

	{
		std::cout << "\n\n18. Testing [Vector] compare reverse_iterators and const_revese_iterators:\n";
		ft::vector<myType>::reverse_iterator my_it = myVec4.rbegin();
		ft::vector<myType>::const_reverse_iterator my_ite = myVec4.rend();

		std::vector<myType>::reverse_iterator std_it = stdVec4.rbegin();
		std::vector<myType>::const_reverse_iterator std_ite = stdVec4.rend();
		IteratorTest(my_it, my_ite, std_it, std_ite);
	}

	{
		std::cout << "\n\n19. Testing [Vector] erase position and iterators:\n";
		ft::vector<myType>::iterator my_it = myVec.begin();
		ft::vector<myType>::iterator my_ite = myVec.end();

		std::vector<myType>::iterator std_it = stdVec.begin();
		std::vector<myType>::iterator std_ite = stdVec.end();

		myVec.erase(++my_it);
		myVec.erase(--(--my_ite));
		stdVec.erase(++std_it);
		stdVec.erase(--(--std_ite));
		
		my_it = myVec2.begin();
		my_ite = myVec2.end();
		std_it = stdVec2.begin();
		std_ite = stdVec2.end();
		
		myVec2.erase(++(++my_it), --(--my_ite));
		stdVec2.erase(++(++std_it), --(--std_ite));

		my_it = myVec3.begin();
		my_ite = myVec3.end();
		std_it = stdVec3.begin();
		std_ite = stdVec3.end();

		myVec3.erase(--(--my_ite));
		stdVec3.erase(--(--std_ite));

		my_it = myVec4.begin();
		my_ite = myVec4.end();
		std_it = stdVec4.begin();
		std_ite = stdVec4.end();
	
		myVec4.erase(my_it, my_ite);
		stdVec4.erase(std_it, std_ite);
		
		BasicVectorStats(myVec, stdVec);
		BasicVectorStats(myVec2, stdVec2);
		BasicVectorStats(myVec3, stdVec3);
		BasicVectorStats(myVec4, stdVec4);
		BasicVectorStats(myVec5, stdVec5);
		isEqual(ft::equal(myVec.begin(), myVec.end(), stdVec.begin()), true);
		isEqual(ft::equal(myVec2.begin(), myVec2.end(), stdVec2.begin()), true);
		isEqual(ft::equal(myVec3.begin(), myVec3.end(), stdVec3.begin()), true);
		isEqual(ft::equal(myVec4.begin(), myVec4.end(), stdVec4.begin()), true);
		isEqual(ft::equal(myVec5.begin(), myVec5.end(), stdVec5.begin()), true);
	}

	std::cout << "\n\n20. Testing [Vector] pop_back:\n";
	for (int i = 0; i < 2; ++i)
	{
		myVec.pop_back();
		stdVec.pop_back();
	}
	myVec2.pop_back();
	stdVec2.pop_back();
	myVec3.pop_back();
	stdVec3.pop_back();
	// myVec4.pop_back(); //already empty - causes endefined behavior
	// stdVec4.pop_back(); //already empty - causes endefined behavior
	myVec5.pop_back();
	stdVec5.pop_back();
	BasicVectorStats(myVec, stdVec);
	BasicVectorStats(myVec2, stdVec2);
	BasicVectorStats(myVec3, stdVec3);
	BasicVectorStats(myVec4, stdVec4);
	BasicVectorStats(myVec5, stdVec5);
	isEqual(ft::equal(myVec.begin(), myVec.end(), stdVec.begin()), true);
	isEqual(ft::equal(myVec2.begin(), myVec2.end(), stdVec2.begin()), true);
	isEqual(ft::equal(myVec3.begin(), myVec3.end(), stdVec3.begin()), true);
	isEqual(ft::equal(myVec4.begin(), myVec4.end(), stdVec4.begin()), true);
	isEqual(ft::equal(myVec5.begin(), myVec5.end(), stdVec5.begin()), true);


	std::cout << "\n\n201. Testing [Vector] assign:\n";
	
	myVec.assign(6, 42);
	stdVec.assign(6, 42);
	myVec2.assign(1, 5);
	stdVec2.assign(1, 5);
	myVec3.assign(9, 0);
	stdVec3.assign(9, 0);
	myVec4.assign(++myVec.begin(), --myVec.end());
	stdVec4.assign(++stdVec.begin(), --stdVec.end());
	myVec5.assign(myVec.begin(), myVec.end());
	stdVec5.assign(stdVec.begin(), stdVec.end());
	BasicVectorStats(myVec, stdVec);
	BasicVectorStats(myVec2, stdVec2);
	BasicVectorStats(myVec3, stdVec3);
	BasicVectorStats(myVec4, stdVec4);
	BasicVectorStats(myVec5, stdVec5);
	isEqual(ft::equal(myVec.begin(), myVec.end(), stdVec.begin()), true);
	isEqual(ft::equal(myVec2.begin(), myVec2.end(), stdVec2.begin()), true);
	isEqual(ft::equal(myVec3.begin(), myVec3.end(), stdVec3.begin()), true);
	isEqual(ft::equal(myVec4.begin(), myVec4.end(), stdVec4.begin()), true);
	isEqual(ft::equal(myVec5.begin(), myVec5.end(), stdVec5.begin()), true);


	std::cout << "\n\n22. Testing [Vector] insert:\n";
	myVec.insert(++(++myVec.begin()), 420042);
	stdVec.insert(++(++stdVec.begin()), 420042);
	myVec2.insert(--myVec2.end(), 999);
	stdVec2.insert(--stdVec2.end(), 999);
	myVec3.insert(++(++(++myVec3.begin())), 5, 555);
	stdVec3.insert(++(++(++stdVec3.begin())), 5, 555);
	myVec4.insert(--(--myVec4.end()), 6, 666);
	stdVec4.insert(--(--stdVec4.end()), 6, 666);
	myVec5.insert(++myVec5.begin(), ++myVec.begin(), --myVec.end());
	stdVec5.insert(++stdVec5.begin(), ++stdVec.begin(), --stdVec.end());
	BasicVectorStats(myVec, stdVec);
	BasicVectorStats(myVec2, stdVec2);
	BasicVectorStats(myVec3, stdVec3);
	BasicVectorStats(myVec4, stdVec4);
	BasicVectorStats(myVec5, stdVec5);
	isEqual(ft::equal(myVec.begin(), myVec.end(), stdVec.begin()), true);
	isEqual(ft::equal(myVec2.begin(), myVec2.end(), stdVec2.begin()), true);
	isEqual(ft::equal(myVec3.begin(), myVec3.end(), stdVec3.begin()), true);
	isEqual(ft::equal(myVec4.begin(), myVec4.end(), stdVec4.begin()), true);
	isEqual(ft::equal(myVec5.begin(), myVec5.end(), stdVec5.begin()), true);

	std::cout << "\n\n23. Testing [Vector] relational operators:\n";
	
	isEqual(myVec < myVec2, stdVec < stdVec2);
	isEqual(myVec > myVec2, stdVec > stdVec2);
	isEqual(myVec2 > myVec3, stdVec2 > stdVec3);
	isEqual(myVec2 < myVec3, stdVec2 < stdVec3);
	isEqual(myVec3 <= myVec4, stdVec3 <= stdVec4);
	isEqual(myVec3 >= myVec4, stdVec3 >= stdVec4);
	isEqual(myVec4 >= myVec5, stdVec4 >= stdVec5);
	isEqual(myVec4 <= myVec5, stdVec4 <= stdVec5);
	isEqual(myVec5 != myVec, stdVec5 != stdVec);
	isEqual(myVec == myVec, stdVec == stdVec);
	isEqual(myVec != myVec, stdVec != stdVec);

	{
		std::cout << "\n\n24. Testing [Vector] swap:\n";

		ft::vector<myType>::iterator my_it = myVec.begin();
		ft::vector<myType>::iterator my_ite = myVec.end();
		ft::vector<myType>::iterator my_it5 = myVec5.begin();
		ft::vector<myType>::iterator my_ite5 = myVec5.end();
		
		ft::vector<myType>::const_iterator my_it2 = myVec2.begin();
		ft::vector<myType>::const_iterator my_ite2 = myVec2.end();
		ft::vector<myType>::const_iterator my_it3 = myVec3.begin();
		ft::vector<myType>::const_iterator my_ite3 = myVec3.end();
	
		std::vector<myType>::iterator std_it = stdVec.begin();
		//std::vector<myType>::iterator std_ite = stdVec.end();
		std::vector<myType>::iterator std_it5 = stdVec5.begin();
		//std::vector<myType>::iterator std_ite5 = stdVec5.end();

		std::vector<myType>::const_iterator std_it2 = stdVec2.begin();
		//std::vector<myType>::const_iterator std_ite2 = stdVec2.end();
		std::vector<myType>::const_iterator std_it3 = stdVec3.begin();
		//std::vector<myType>::const_iterator std_ite3 = stdVec3.end();

		myVec.swap(myVec5);
		stdVec.swap(stdVec5);
		myVec2.swap(myVec3);
		stdVec2.swap(stdVec3);
		BasicVectorStats(myVec, stdVec);
		BasicVectorStats(myVec2, stdVec2);
		BasicVectorStats(myVec3, stdVec3);
		BasicVectorStats(myVec5, stdVec5);
		isEqual(ft::equal(my_it, my_ite, std_it), true);
		isEqual(ft::equal(my_it2, my_ite2, std_it2), true);
		isEqual(ft::equal(my_it3, my_ite3, std_it3), true);
		isEqual(ft::equal(my_it5, my_ite5, std_it5), true);
	}
	
	std::cout << "\n\n25. Testing [Vector] clear:\n";
	
	myVec.clear();
	stdVec.clear();
	myVec2.clear();
	stdVec2.clear();
	myVec3.clear();
	stdVec3.clear();
	myVec4.clear();
	stdVec4.clear();
	myVec5.clear();
	stdVec5.clear();
	BasicVectorStats(myVec, stdVec);
	BasicVectorStats(myVec2, stdVec2);
	BasicVectorStats(myVec3, stdVec3);
	BasicVectorStats(myVec4, stdVec4);
	BasicVectorStats(myVec5, stdVec5);
	isEqual(ft::equal(myVec.begin(), myVec.end(), stdVec.begin()), true);
	isEqual(ft::equal(myVec2.begin(), myVec2.end(), stdVec2.begin()), true);
	isEqual(ft::equal(myVec3.begin(), myVec3.end(), stdVec3.begin()), true);
	isEqual(ft::equal(myVec4.begin(), myVec4.end(), stdVec4.begin()), true);
	isEqual(ft::equal(myVec5.begin(), myVec5.end(), stdVec5.begin()), true);

	std::cout << "\n\n";
	myTimer.vector.end = clock();
}
