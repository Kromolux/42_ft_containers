/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:29:54 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/19 10:32:47 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers.hpp"
#include <list>
#include <deque>

typedef int myType;
void test_stack(t_testTime & myTimer)
{
	myTimer.stack.start = clock();
	
	{
		std::cout << "1. Testing [Stack] default constructor with size, empty with underlaying ft::vector:\n";
		ft::stack<myType> mySta;
		std::stack<myType> stdSta;

		BasicStackStats(mySta, stdSta);
		
		std::cout << "\n\n2. Testing [Stack] push with underlaying ft::vector:\n";
		for (int i = 0; i < 100; ++i)
		{
			mySta.push(i);
			stdSta.push(i);
		}
		
		BasicStackStats(mySta, stdSta);
		isEqual(mySta.top(), stdSta.top());
		
		std::cout << "\n\n3. Testing [Stack] pop and top with underlaying ft::vector:\n";
		for (size_t i = 0; i < 5; ++i)
		{
			mySta.pop();
			stdSta.pop();
		}
		BasicStackStats(mySta, stdSta);
		isEqual(mySta.top(), stdSta.top());
		
		for (size_t i = 0; i < 9; ++i)
		{
			mySta.pop();
			stdSta.pop();
		}
		BasicStackStats(mySta, stdSta);
		isEqual(mySta.top(), stdSta.top());

		std::cout << "\n\n4. Testing [Stack] relational operators with underlaying ft::vector:\n";
		ft::stack<myType> mySta2;
		std::stack<myType> stdSta2;

		ft::stack<myType> mySta3;
		std::stack<myType> stdSta3;

		for (int i = 0; i < 10; ++i)
		{
			mySta3.push(i);
			stdSta3.push(i);
		}
		
		isEqual(mySta < mySta2, stdSta < stdSta2);
		isEqual(mySta > mySta2, stdSta > stdSta2);
		isEqual(mySta <= mySta2, stdSta <= stdSta2);
		isEqual(mySta >= mySta2, stdSta >= stdSta2);
		isEqual(mySta != mySta2, stdSta != stdSta2);
		isEqual(mySta == mySta2, stdSta == stdSta2);

		isEqual(mySta3 < mySta2, stdSta3 < stdSta2);
		isEqual(mySta3 > mySta2, stdSta3 > stdSta2);
		isEqual(mySta3 <= mySta2, stdSta3 <= stdSta2);
		isEqual(mySta3 >= mySta2, stdSta3 >= stdSta2);
		isEqual(mySta3 != mySta2, stdSta3 != stdSta2);
		isEqual(mySta3 == mySta2, stdSta3 == stdSta2);
	
	}

	{
		std::cout << "\n\n5. Testing [Stack] default constructor with underlaying std::list:\n";
		ft::stack<myType, std::list<myType> > mySta;
		std::stack<myType, std::list<myType> > stdSta;

		BasicStackStats(mySta, stdSta);
		
		std::cout << "\n\n6. Testing [Stack] push with underlaying std::list:\n";
		for (int i = 0; i < 100; ++i)
		{
			mySta.push(i);
			stdSta.push(i);
		}
		
		BasicStackStats(mySta, stdSta);
		isEqual(mySta.top(), stdSta.top());
		
		std::cout << "\n\n7. Testing [Stack] pop and top with underlaying std::list:\n";
		for (size_t i = 0; i < 5; ++i)
		{
			mySta.pop();
			stdSta.pop();
		}
		BasicStackStats(mySta, stdSta);
		isEqual(mySta.top(), stdSta.top());
		
		for (size_t i = 0; i < 9; ++i)
		{
			mySta.pop();
			stdSta.pop();
		}
		BasicStackStats(mySta, stdSta);
		isEqual(mySta.top(), stdSta.top());

		std::cout << "\n\n8. Testing [Stack] relational operators with underlaying std::list:\n";
		ft::stack<myType, std::list<myType> > mySta2;
		std::stack<myType, std::list<myType> > stdSta2;
	
		ft::stack<myType, std::list<myType> > mySta3;
		std::stack<myType, std::list<myType> > stdSta3;

		for (int i = 0; i < 10; ++i)
		{
			mySta3.push(i);
			stdSta3.push(i);
		}

		isEqual(mySta < mySta2, stdSta < stdSta2);
		isEqual(mySta > mySta2, stdSta > stdSta2);
		isEqual(mySta <= mySta2, stdSta <= stdSta2);
		isEqual(mySta >= mySta2, stdSta >= stdSta2);
		isEqual(mySta != mySta2, stdSta != stdSta2);
		isEqual(mySta == mySta2, stdSta == stdSta2);
	
		isEqual(mySta3 < mySta2, stdSta3 < stdSta2);
		isEqual(mySta3 > mySta2, stdSta3 > stdSta2);
		isEqual(mySta3 <= mySta2, stdSta3 <= stdSta2);
		isEqual(mySta3 >= mySta2, stdSta3 >= stdSta2);
		isEqual(mySta3 != mySta2, stdSta3 != stdSta2);
		isEqual(mySta3 == mySta2, stdSta3 == stdSta2);
	}
	

	{
		std::cout << "\n\n9. Testing [Stack] default constructor with underlaying std::deque:\n";
		ft::stack<myType, std::deque<myType> > mySta;
		std::stack<myType, std::deque<myType> > stdSta;

		BasicStackStats(mySta, stdSta);
		
		std::cout << "\n\n10. Testing [Stack] push with underlaying std::deque:\n";
		for (int i = 0; i < 100; ++i)
		{
			mySta.push(i);
			stdSta.push(i);
		}
		
		BasicStackStats(mySta, stdSta);
		isEqual(mySta.top(), stdSta.top());
		
		std::cout << "\n\n11. Testing [Stack] pop and top with underlaying std::deque:\n";
		for (size_t i = 0; i < 5; ++i)
		{
			mySta.pop();
			stdSta.pop();
		}
		BasicStackStats(mySta, stdSta);
		isEqual(mySta.top(), stdSta.top());
		
		for (size_t i = 0; i < 9; ++i)
		{
			mySta.pop();
			stdSta.pop();
		}
		BasicStackStats(mySta, stdSta);
		isEqual(mySta.top(), stdSta.top());

		std::cout << "\n\n12. Testing [Stack] relational operators with underlaying std::deque:\n";
		ft::stack<myType, std::deque<myType> > mySta2;
		std::stack<myType, std::deque<myType> > stdSta2;
		
		ft::stack<myType, std::deque<myType> > mySta3;
		std::stack<myType, std::deque<myType> > stdSta3;

		for (int i = 0; i < 10; ++i)
		{
			mySta3.push(i);
			stdSta3.push(i);
		}

		isEqual(mySta < mySta2, stdSta < stdSta2);
		isEqual(mySta > mySta2, stdSta > stdSta2);
		isEqual(mySta <= mySta2, stdSta <= stdSta2);
		isEqual(mySta >= mySta2, stdSta >= stdSta2);
		isEqual(mySta != mySta2, stdSta != stdSta2);
		isEqual(mySta == mySta2, stdSta == stdSta2);
	
		isEqual(mySta3 < mySta2, stdSta3 < stdSta2);
		isEqual(mySta3 > mySta2, stdSta3 > stdSta2);
		isEqual(mySta3 <= mySta2, stdSta3 <= stdSta2);
		isEqual(mySta3 >= mySta2, stdSta3 >= stdSta2);
		isEqual(mySta3 != mySta2, stdSta3 != stdSta2);
		isEqual(mySta3 == mySta2, stdSta3 == stdSta2);
	}

	{
		std::cout << "\n\n13. Testing [Stack] default constructor with underlaying std::vector:\n";
		ft::stack<myType, std::vector<myType> > mySta;
		std::stack<myType, std::vector<myType> > stdSta;

		BasicStackStats(mySta, stdSta);
		
		std::cout << "\n\n14. Testing [Stack] push with underlaying std::vector:\n";
		for (int i = 0; i < 100; ++i)
		{
			mySta.push(i);
			stdSta.push(i);
		}
		
		BasicStackStats(mySta, stdSta);
		isEqual(mySta.top(), stdSta.top());
		
		std::cout << "\n\n15. Testing [Stack] pop and top with underlaying std::vector:\n";
		for (size_t i = 0; i < 5; ++i)
		{
			mySta.pop();
			stdSta.pop();
		}
		BasicStackStats(mySta, stdSta);
		isEqual(mySta.top(), stdSta.top());
		
		for (size_t i = 0; i < 9; ++i)
		{
			mySta.pop();
			stdSta.pop();
		}
		BasicStackStats(mySta, stdSta);
		isEqual(mySta.top(), stdSta.top());

		std::cout << "\n\n16. Testing [Stack] relational operators with underlaying std::vector:\n";
		ft::stack<myType, std::vector<myType> > mySta2;
		std::stack<myType, std::vector<myType> > stdSta2;
		
		ft::stack<myType, std::vector<myType> > mySta3;
		std::stack<myType, std::vector<myType> > stdSta3;

		for (int i = 0; i < 10; ++i)
		{
			mySta3.push(i);
			stdSta3.push(i);
		}

		isEqual(mySta < mySta2, stdSta < stdSta2);
		isEqual(mySta > mySta2, stdSta > stdSta2);
		isEqual(mySta <= mySta2, stdSta <= stdSta2);
		isEqual(mySta >= mySta2, stdSta >= stdSta2);
		isEqual(mySta != mySta2, stdSta != stdSta2);
		isEqual(mySta == mySta2, stdSta == stdSta2);
	
		isEqual(mySta3 < mySta2, stdSta3 < stdSta2);
		isEqual(mySta3 > mySta2, stdSta3 > stdSta2);
		isEqual(mySta3 <= mySta2, stdSta3 <= stdSta2);
		isEqual(mySta3 >= mySta2, stdSta3 >= stdSta2);
		isEqual(mySta3 != mySta2, stdSta3 != stdSta2);
		isEqual(mySta3 == mySta2, stdSta3 == stdSta2);
	}
	
	std::cout << "\n\n";

	myTimer.stack.end = clock();
}
