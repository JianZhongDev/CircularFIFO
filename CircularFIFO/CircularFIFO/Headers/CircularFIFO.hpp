#pragma once
/*
* FILE: CircularFIFO.hpp
* DESCRIPTION: circular first-in-first-out (FIFO) buffer
* NOTE:
*   1. Current FIFO, the head (push) and tail (pop) should be handled by a single thread each time
* @author: Jian Zhong
*/

#ifndef CIRCULARFIFO_HPP
#define CIRCULARFIFO_HPP

#include<iostream>
#include<atomic>

#include"Queue.hpp"

namespace Queue{

	static const errflag_t ERR_EMPTY_FIFO = 2;
	static const errflag_t ERR_FIFO_OVERFLOW = -3;

	template<typename dtype>
	class CircularFIFO : public Queue<dtype> {
	private:
		// unchanged vairables
		size_t capacity = 1;
		dtype* container = nullptr;

		//// variables keep updating (potentially not thread safe design)
		//size_t length = 0;
		//size_t head = 0;
		//size_t tail = 0;

		// variables keep updating (thread safe design)
		std::atomic<size_t> length = 0;
		std::atomic<size_t> head = 0;
		std::atomic<size_t> tail = 0;

	public:

		CircularFIFO(size_t capacity = 10) {
			capacity = capacity < 2 ? 2 : capacity;
			this->capacity = capacity;
			this->container = new dtype[this->capacity];
			this->length = 0;
			this->head = 0;
			this->tail = 1;
		}

		~CircularFIFO() {
			delete[] this->container;
		}

		// checks whether the container adaptor is empty
		bool empty() override {
			return this->length == 0;
		}

		// returns the number of elements 
		size_t size() override  {
			return this->length;
		}

		// get the capcacity of the container
		size_t get_capacity() {
			return this->capacity;
		}

		// access the first element
		errflag_t front(dtype* dst_data_p) override {
			if (this->empty()) {
				return ERR_EMPTY_FIFO;
			}
			*dst_data_p = this->container[this->tail];
			return SUCCESS;
		}

		// access the last element
		errflag_t back(dtype* dst_data_p) override {
			if (this->empty()) {
				return ERR_EMPTY_FIFO;
			}
			*dst_data_p = this->container[this->head];
			return SUCCESS;
		}

		// inserts element at the end
		errflag_t push(const dtype& src_data) override {
			// calculate the next pos within the current thread before updating the atomic variables
			size_t next_head_pos = this->head;
			next_head_pos = (next_head_pos + 1) % this->capacity;
			if (!this->empty() && next_head_pos == this->tail) {
				return ERR_FIFO_OVERFLOW;
			}

			this->head = next_head_pos;
			//this->head = (this->head + 1) % this->capacity;

			this->container[this->head] = src_data;
			
			++this->length;
			return SUCCESS;
		}

		// removes the first element and returns it
		errflag_t pop(dtype* dst_data_p) override {
			if (this->empty()) {
				return ERR_EMPTY_FIFO;
			}

			// calculate the next pos within the current thread before updating the atomic variables
			size_t next_tail_pos = this->tail;
			next_tail_pos = (next_tail_pos + 1) % this->capacity;

			*dst_data_p = this->container[this->tail];

			//this->tail = (this->tail + 1) % this->capacity;
			this->tail = next_tail_pos;

			--this->length;
			return SUCCESS;
		}

	};
}

#endif

