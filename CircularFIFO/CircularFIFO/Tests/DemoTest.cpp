/*
* FILE: DemoTest.cpp
* DESCRIPTION: demonstration for FIFO buffer
* NOTE:
*	1. #define MAIN to enable the main() function here
* @author: Jian Zhong
*/

#define MAIN

#ifdef MAIN

# include <vector>
# include <iostream>
# include <string>
# include "../Headers/CircularFIFO.hpp"
# include "../Headers/DemoHelper.hpp"

void demo_fifo_overflow_empty() {

	std::cout << "====== Demo FIFO Overflow and Empty START ======" << std::endl;
	Queue::CircularFIFO<int> test_fifo(3);

	for (int idx = 0; idx < 5; idx++) {
		Queue::errflag_t cur_errflag; 
		int tmp;
		std::cout << "push itr " << idx << " :" << std::endl;
		cur_errflag = test_fifo.push(idx);
		std::cout << "\t" << "test_fifo.push(" << idx << ") : " << helper_fifo_errflag_to_string(cur_errflag) << std::endl;
		cur_errflag = test_fifo.front(&tmp);
		std::cout << "\t" << "test_fifo.front(" << tmp << ") : " << helper_fifo_errflag_to_string(cur_errflag) << std::endl;
		cur_errflag = test_fifo.back(&tmp);
		std::cout << "\t" << "test_fifo.back(" << tmp << ") : " << helper_fifo_errflag_to_string(cur_errflag) << std::endl;
	}

	for (int idx = 0; idx < 7; idx++) {
		Queue::errflag_t cur_errflag;
		int tmp;
		std::cout << "pop itr " << idx << " :" << std::endl;
		cur_errflag = test_fifo.pop(&tmp);
		std::cout << "\t" << "test_fifo.pop(" << tmp << ") : " << helper_fifo_errflag_to_string(cur_errflag) << std::endl;
		cur_errflag = test_fifo.front(&tmp);
		std::cout << "\t" << "test_fifo.front(" << tmp << ") : " << helper_fifo_errflag_to_string(cur_errflag) << std::endl;
		cur_errflag = test_fifo.back(&tmp);
		std::cout << "\t" << "test_fifo.back(" << tmp << ") : " << helper_fifo_errflag_to_string(cur_errflag) << std::endl;
	}

	std::cout << "====== Demo FIFO Overflow and Empty END ======" << std::endl;
	std::cout << std::endl;

}

void demo_choatic_multithread_fifo() {

}


void main() {

	demo_fifo_overflow_empty();

}


#endif