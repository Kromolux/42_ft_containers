/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:32:21 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/19 15:59:07 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers.hpp"

typedef int T1;
typedef std::string T2;

void	testRBT(void)
{
	ft::map<T1, T2> mp;
	for (size_t i = 0; i < 15; ++i)
	{
		mp.insert(ft::pair<T1, T2>((i + 1) * i, "0"));
		//std::cout << "insert: " << (i + 1) * i < "\n";
	}
	/*
	insert: 0
	insert: 2
	insert: 6
	insert: 12
	insert: 20
	insert: 30
	insert: 42
	insert: 56
	insert: 72
	insert: 90
	insert: 110
	insert: 132
	insert: 156
	insert: 182
	insert: 210

	map content = [ 0:0 2:0 6:0 12:0 20:0 30:0 42:0 56:0 72:0 90:0 110:0 132:0 156:0 182:0 210:0 ]
	*/
	std::cout << "\n\n1. Testing [RBT] populating map with insert:\n";
	displayMapContent(mp);
	mp.printTree();
	
	std::cout << "\n\n2. Testing [RBT] deleting 6:\n";
	mp.erase(6);
	mp.printTree();
	
	std::cout << "\n\n3. Testing [RBT] deleting 12:\n";
	mp.erase(12);
	mp.printTree();
	
	std::cout << "\n\n4. Testing [RBT] deleting 20:\n";
	mp.erase(20);
	mp.printTree();

	std::cout << "\n\n5. Testing [RBT] deleting 30:\n";
	mp.erase(30);
	mp.printTree();

	std::cout << "\n\n6. Testing [RBT] deleting 42:\n";
	mp.erase(42);
	mp.printTree();

	std::cout << "\n\n7. Testing [RBT] deleting 56:\n";
	mp.erase(56);
	mp.printTree();

	std::cout << "\n\n8. Testing [RBT] deleting 72:\n";
	mp.erase(72);
	mp.printTree();

	std::cout << "\n\n9. Testing [RBT] deleting 90:\n";
	mp.erase(90);
	mp.printTree();
	displayMapContent(mp);
}
