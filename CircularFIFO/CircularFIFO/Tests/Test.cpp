/*
* FILE: Test.cpp
* DESCRIPTION: quick test for FIFO buffer
* NOTE:
*	1. #define MAIN to enable the main() function here
* @author: Jian Zhong
*/

//#define MAIN

#ifdef MAIN

# include <iostream>
# include "../Headers/CircularFIFO.hpp"


void main() {
	Queue::CircularFIFO<int> test_fifo(5);
	for (int i = 0; i < 8; ++i) {
		int tmp = 0;
		std::cout << "itr: " << i << std::endl;
		std::cout << "push(): err flag: " << test_fifo.push(i + 1)  << std::endl;
		std::cout << "back(): err flag: " << test_fifo.back(&tmp) << std::endl;
		std::cout << "back(): result: " << tmp << std::endl;
		std::cout << "front(): err flag: " << test_fifo.front(&tmp)  << std::endl;
		std::cout << "front() result: " << tmp << std::endl;
		std::cout << "pop(): err flag: " << test_fifo.pop(&tmp) << std::endl;
		std::cout << "pop() result: " << tmp << std::endl;
		std::cout << std::endl;
	}
	
}

#endif