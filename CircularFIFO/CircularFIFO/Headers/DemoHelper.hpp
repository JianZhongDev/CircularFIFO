#pragma once
/*
* FILE: DemoHelper.hpp
* DESCRIPTION: helper functions for demonstration
* NOTE:
*	1. #define MAIN to enable the main() function here
* @author: Jian Zhong
*/

#ifndef DEMOHELPER_HPP

#define DEMOHELPER_HPP

#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include"CircularFIFO.hpp"

template<typename dtype>
std::string helper_vector_to_string(std::vector<dtype>& src_vec) {
	std::stringstream tmp_sstream;
	size_t vec_len = src_vec.size();
	
	tmp_sstream << "{";
	for (size_t idx = 0; idx < vec_len; ++idx) {
		tmp_sstream << src_vec[idx];
		if (idx < vec_len - 1) tmp_sstream << ", ";
	}
	tmp_sstream << "}";

	return tmp_sstream.str();
}

std::string helper_fifo_errflag_to_string(Queue::errflag_t err_flag) {
	std::string err_string;
	
	switch (err_flag) {
	case Queue::SUCCESS:
		err_string = "success";
		break;
	case Queue::ERR_NULL:
		err_string = "null";
		break;
	case Queue::FAILED:
		err_string = "failed";
		break;
	case Queue::ERR_EMPTY_FIFO:
		err_string = "empty_fifo";
		break;
	case Queue::ERR_FIFO_OVERFLOW:
		err_string = "fifo_overflow";
		break;
	default:
		err_string = "unknown";
		break;
	}
	return err_string;
}


#endif