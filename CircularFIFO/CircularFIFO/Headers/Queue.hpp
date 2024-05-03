#pragma once
/*
* FILE: Queue.hpp
* DESCRIPTION: abstract base class for queue data structure 
* NOTE:
* @author: Jian Zhong
*/


#ifndef QUEUE_HPP
#define QUEUE_HPP

#include<iostream>



namespace Queue {

	typedef int errflag_t; // use errflag_t to pass err code instead of using exception for better performance

	static const errflag_t SUCCESS = 1;
	static const errflag_t ERR_NULL = 0;
	static const errflag_t FAILED = -1;

	// base pure virtual class for queue data structure
	template <typename dtype>
	class Queue {
	public:
		

		// checks whether the container adaptor is empty
		// Override this function in subclass
		virtual bool empty() = 0;

		// returns the number of elements 
		// Override this function in subclass
		virtual size_t size() = 0;

		// access the first element
		// Override this function in subclass
		virtual errflag_t front(dtype* dst_data_p) = 0;

		// access the last element
		// Override this function in subclass
		virtual errflag_t back(dtype* dst_data_p) = 0;

		// inserts element at the end
		// Override this function in subclass
		virtual errflag_t push(const dtype& src_data) = 0;

		// removes the first element
		// Override this function in subclass
		virtual errflag_t pop(dtype* data_data_p) = 0;

	};
}

#endif
