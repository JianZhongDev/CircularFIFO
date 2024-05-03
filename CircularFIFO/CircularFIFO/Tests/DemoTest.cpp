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
# include <sstream>
# include <thread>
# include <chrono>
# include "../Headers/CircularFIFO.hpp"
# include "../Headers/DemoHelper.hpp"


// Demo of push(), pop(), front(), back() functions and report of buffer overflow, empty errors
void demo_fifo_overflow_empty() {

	std::cout << "====== Demo FIFO Overflow and Empty START ======" << std::endl;
	Queue::CircularFIFO<int> test_fifo(3);

	for (int idx = 0; idx < 5; idx++) {
		Queue::errflag_t cur_errflag; 
		int tmp;
		std::cout << "push itr " << idx << " :" << std::endl;
		cur_errflag = test_fifo.push(idx);
		std::cout << "\t" << "fifo.push(" << idx << ") : " << helper_fifo_errflag_to_string(cur_errflag) << std::endl;
		cur_errflag = test_fifo.front(&tmp);
		std::cout << "\t" << "fifo.front(" << tmp << ") : " << helper_fifo_errflag_to_string(cur_errflag) << std::endl;
		cur_errflag = test_fifo.back(&tmp);
		std::cout << "\t" << "fifo.back(" << tmp << ") : " << helper_fifo_errflag_to_string(cur_errflag) << std::endl;
	}

	for (int idx = 0; idx < 7; idx++) {
		Queue::errflag_t cur_errflag;
		int tmp;
		std::cout << "pop itr " << idx << " :" << std::endl;
		cur_errflag = test_fifo.pop(&tmp);
		std::cout << "\t" << "fifo.pop(" << tmp << ") : " << helper_fifo_errflag_to_string(cur_errflag) << std::endl;
		cur_errflag = test_fifo.front(&tmp);
		std::cout << "\t" << "fifo.front(" << tmp << ") : " << helper_fifo_errflag_to_string(cur_errflag) << std::endl;
		cur_errflag = test_fifo.back(&tmp);
		std::cout << "\t" << "fifo.back(" << tmp << ") : " << helper_fifo_errflag_to_string(cur_errflag) << std::endl;
	}

	std::cout << "====== Demo FIFO Overflow and Empty END ======" << std::endl;
	std::cout << std::endl;

}

// Producer thread function for multithreading demonstrations
int rand_int(int min = 0, int max = 100) {
	return (std::rand() % (max - min)) + min;
}

float rand_float(float min = 0.0f, float max = 1.0f, int granularity = 100) {
	int rand_int_num = std::rand() % granularity;
	float rand_unit_float = (1.0f * rand_int_num) / (1.0f * granularity);
	float rand_float = rand_unit_float * (max - min) + min;
	return rand_float;
}

template<typename dtype>
void producer_run(std::vector<dtype>* data_vec_p, Queue::CircularFIFO<dtype>* fifo_p, size_t nof_itrs) {
	for (size_t itr = 0; itr < nof_itrs; ++itr) {
		std::stringstream message_sstream;
		Queue::errflag_t cur_errflag = Queue::ERR_NULL;
		dtype tmp;

		message_sstream << "producer: itr " << itr << " : \n";
		if (data_vec_p->empty()) {
			message_sstream << "\t producer data_vec is empty, exit producer thread \n";
			message_sstream << "\n";
			std::cout << message_sstream.str();
			break;
		}
		message_sstream << "\t begin: data_vec = " << helper_vector_to_string<dtype>(*data_vec_p) << "\n";
		tmp = data_vec_p->back();
		data_vec_p->pop_back();
		cur_errflag = fifo_p->push(tmp);
		message_sstream << "\t fifo.push(";
		if (cur_errflag == Queue::SUCCESS) {
			message_sstream << tmp;
		}
		message_sstream << ") : " << helper_fifo_errflag_to_string(cur_errflag) << "\n";
		message_sstream << "\t end: data_vec = " << helper_vector_to_string<dtype>(*data_vec_p) << "\n";
		message_sstream << "\n";
		std::cout << message_sstream.str();

		std::this_thread::sleep_for(std::chrono::milliseconds(rand_int(0, 500)));
	}
}

// Consumer thread function for multithreading demonstrations
template<typename dtype>
void consumer_run(std::vector<dtype>* data_vec_p, Queue::CircularFIFO<dtype>* fifo_p, size_t nof_itrs) {
	for (size_t itr = 0; itr < nof_itrs; ++itr) {
		std::stringstream message_sstream;
		Queue::errflag_t cur_errflag = Queue::ERR_NULL;
		dtype tmp;
		message_sstream << "consumer: itr " << itr << " : \n";
		message_sstream << "\t begin: data_vec = " << helper_vector_to_string<dtype>(*data_vec_p) << "\n";
		cur_errflag = fifo_p->pop(&tmp);
		message_sstream << "\t fifo.pop(";
		if (cur_errflag == Queue::SUCCESS) {
			message_sstream << tmp; 
			data_vec_p->push_back(tmp);
		}		
		message_sstream << ") : " << helper_fifo_errflag_to_string(cur_errflag) << "\n";
		message_sstream << "\t end: data_vec = " << helper_vector_to_string<dtype>(*data_vec_p) << "\n";
		message_sstream << "\n";
		std::cout << message_sstream.str();

		std::this_thread::sleep_for(std::chrono::milliseconds(rand_int(0,500)));
	}
}


// Main function for multithreading operations
void demo_multithread_fifo() {
	std::vector<int> producer_data_vector = { -2, -1, 0, 1, 2, 3};
	std::vector<int> consumer_data_vector;

	Queue::CircularFIFO<int> transfer_fifo(5);

	size_t nof_producer_itrs = 10;
	size_t nof_consumer_itrs = 10;

	std::cout << "====== Demo Multithreading FIFO START ======" << std::endl;

	std::thread producer_thread(producer_run<int>, &producer_data_vector, &transfer_fifo, nof_producer_itrs);
	std::thread consumer_thread(consumer_run<int>, &consumer_data_vector, &transfer_fifo, nof_consumer_itrs);
	
	producer_thread.join();
	consumer_thread.join();

	std::cout << "====== Demo Multithreading FIFO END ======" << std::endl;

}


void main() {

	//demo_fifo_overflow_empty();
	demo_multithread_fifo();

}


#endif