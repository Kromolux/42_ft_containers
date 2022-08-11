/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:06:34 by rkaufman          #+#    #+#             */
/*   Updated: 2022/08/11 14:10:30 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"

int	main(void)
{
	t_testTime	myTimer = {};

	myTimer.all.start = clock();

	#if TEST_VECTOR || TEST_ALL
		//test_vector(myTimer);
	#endif
	#if TEST_STACK || TEST_ALL
		//test_stack(myTimer);
	#endif
	#if TEST_MAP || TEST_ALL
		test_map(myTimer);
	#endif
	#if TEST_SET || TEST_ALL
		//test_set(myTimer);
	#endif
	#if TEST_RBT
		testRBT();
	#endif
	
	myTimer.all.end = clock();
	
	std::cout	<< "::Time [all] elapsed: " << static_cast<float>(myTimer.all.end - myTimer.all.start) / CLOCKS_PER_SEC
				<< " seconds\n";
	return (0);
}
