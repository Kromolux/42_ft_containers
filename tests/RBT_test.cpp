/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:32:21 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/11 14:42:28 by rkaufman         ###   ########.fr       */
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
	//displayMapContent(mp);
	mp.printTree();
	mp.erase(6);
	mp.printTree();
	mp.erase(12);
	mp.printTree();
	mp.erase(20);
	mp.printTree();
	mp.erase(30);
	mp.printTree();
	mp.erase(42);
	mp.printTree();
	mp.erase(56);
	mp.printTree();
	mp.erase(72);
	mp.printTree();
	mp.erase(90);
	mp.printTree();
	// mp[5] = "1";
	// mp[8] = "2";
	// mp[15] = "3";
	// mp[12] = "4";
	// mp[19] = "5";
	// mp[9] = "6";
	// mp[13] = "7";
	// mp[23] = "8";

	// mp.printTree();
	// mp.erase(5);
	// mp.printTree();
	// mp.erase(12);
	// mp.printTree();
	// mp.erase(19);
	// mp.printTree();
	// mp.erase(9);
	// mp.printTree();
	// mp[10] = "new";

	// mp.printTree();
	// //return;
	// mp[42] = "lol";

	// mp[50] = "mdr";
	// mp[25] = "funny";


	// mp[18] = "bee";
	// mp[23] = "coconut";
	// mp[28] = "diary";
	// mp[35] = "fiesta";
	// mp[44] = "hello";
	// mp[48] = "world";
	// mp[53] = "this is a test";
	// mp[80] = "hey";

	// mp[46] = "bunny";
	// mp[21] = "fizz";
	// mp[30] = "buzz";
	// mp[55] = "fuzzy";


	// mp[43] = "1";
	// mp[45] = "2";
	// mp[47] = "3";
	// mp[49] = "4";
	// mp[51] = "5";
	// mp[54] = "6";
	// mp[60] = "7";
	// mp[90] = "8";

	// mp[12] = "no";
	// mp[20] = "idea";
	// mp[22] = "123";
	// mp[24] = "345";
	// mp[27] = "27";
	// mp[29] = "29";
	// mp[33] = "33";
	// mp[38] = "38";
	//return ;
	//printSize(mp);

}
