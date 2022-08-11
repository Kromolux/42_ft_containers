/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   containers.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:50:49 by rkaufman          #+#    #+#             */
/*   Updated: 2022/07/28 19:14:44 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <ctime>
//#include <deque>
#include <limits.h>
#include "template.hpp"

#ifndef TEST_VECTOR
# define TEST_VECTOR 0
#endif
#ifndef TEST_STACK
# define TEST_STACK 0
#endif
#ifndef TEST_MAP
# define TEST_MAP 0
#endif
#ifndef TEST_SET
# define TEST_SET 0
#endif
#ifndef TEST_ALL
# define TEST_ALL 0
#endif
#ifndef TEST_STD
# define TEST_STD 0
#endif
#ifndef TEST_FT
# define TEST_FT 0
#endif
#ifndef TEST_RBT
# define TEST_RBT 0
#endif

// #if !TEST_STD
// 	#include "Utils.hpp"
// #endif


//#if TEST //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <set>
	#include <stack>
	#include <vector>
	//namespace ft = std;
//#if !TEST_STD
	#include "map.hpp"
	#include "set.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
//#endif

#include "colors.h"
#include <stdlib.h>

typedef struct s_Test {
	clock_t		start;
	clock_t		end;
}				t_Test;

typedef struct s_testTimes {
	struct s_Test	all;
	struct s_Test	vector;
	struct s_Test	stack;
	struct s_Test	map;
	struct s_Test	set;
}				t_testTime;

void test_vector(t_testTime & myTimer);
void test_stack(t_testTime & myTimer);
void test_map(t_testTime & myTimer);
void test_set(t_testTime & myTimer);
//void test_subject(int argc, char ** argv, t_testTime & myTimer);
void testRBT(void);
