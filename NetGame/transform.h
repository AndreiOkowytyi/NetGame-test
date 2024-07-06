#pragma once

#ifndef TRANSFORM
#define TRANSFORM

#include <memory>
#include <iostream>
#include <algorithm>
#include <vector>

// Abstract class for implementing array manipulations.

template<class iterator>
class ArrayTransformer {
 public:
	virtual void transform(iterator array_one_begin, iterator array_one_end,
		                     iterator array_two_begin, iterator array_two_end,
		                       iterator array_three_begin, iterator array_three_end,
		                         std::vector<int>* container = nullptr) = 0;

	virtual ~ArrayTransformer() {}
};

// Block array manipulation implementation.

template<class iterator>
class  ArrayPrint : public ArrayTransformer<iterator> {
 public:
	void transform(iterator array_one_begin, iterator array_one_end,
		             iterator array_two_begin, iterator array_two_end,
		               iterator array_three_begin, iterator array_three_end,
		                 std::vector<int>* container = nullptr) override;
};

template<class iterator>
void ArrayPrint<iterator>::transform(iterator array_one_begin, iterator array_one_end,
	                                   iterator array_two_begin, iterator array_two_end,
	                                     iterator array_three_begin, iterator array_three_end,
	                                       std::vector<int>* container) {

	auto print = [&](iterator begin_iterator, iterator end_iterator) {

		for (auto it = begin_iterator; it != end_iterator; ++it) std::cout << *it << std::endl;
	};

	print(array_one_begin, array_one_end);
	print(array_two_begin, array_two_end);
	print(array_three_begin, array_three_end);
}

template<class iterator>
class  ArraySort : public ArrayTransformer<iterator> {
 public:
	void transform(iterator array_one_begin, iterator array_one_end,
		             iterator array_two_begin, iterator array_two_end,
		               iterator array_three_begin, iterator array_three_end,
		                 std::vector<int>* container = nullptr) override;
};

template<class iterator>
void ArraySort<iterator>::transform(iterator array_one_begin, iterator array_one_end,
	                                  iterator array_two_begin, iterator array_two_end,
	                                    iterator array_three_begin, iterator array_three_end,
	                                      std::vector<int>* container) {

	auto sort_array = [&](iterator begin_iterator, iterator end_iterator) {

		bool swapped;
		iterator iter_end = end_iterator;
		do {
			swapped = false;
			for (iterator it = begin_iterator; std::next(it) != iter_end; ++it) {
				if (*it > *(std::next(it))) {
					std::iter_swap(it, std::next(it));
					swapped = true;
				}
			}
			--iter_end;
		} while (swapped);
	};

	sort_array(array_one_begin, array_one_end);
	sort_array(array_two_begin, array_two_end);
	sort_array(array_three_begin, array_three_end);
}

template<class iterator>
class  ArrayIntersections : public ArrayTransformer<iterator> {
 public:
	void transform(iterator array_one_begin, iterator array_one_end,
		             iterator array_two_begin, iterator array_two_end,
		               iterator array_three_begin, iterator array_three_end,
		                 std::vector<int>* container = nullptr) override;
};

template<class iterator>
void ArrayIntersections<iterator>::transform(iterator array_one_begin, iterator array_one_end,
	                                           iterator array_two_begin, iterator array_two_end,
	                                             iterator array_three_begin, iterator array_three_end,
	                                               std::vector<int>* container) {

	std::vector<typename std::iterator_traits<iterator>::value_type> array_one;
	std::vector<typename std::iterator_traits<iterator>::value_type> array_two;
	std::vector<typename std::iterator_traits<iterator>::value_type> result;

	array_one.reserve(std::distance(array_one_begin, array_one_end));
	array_two.reserve(std::distance(array_two_begin, array_two_end));

	result.reserve(array_one.capacity() + array_two.capacity());

	std::copy(array_one_begin, array_one_end, std::back_inserter(array_one));
	std::copy(array_two_begin, array_two_end, std::back_inserter(array_two));

	std::sort(array_one.begin(), array_one.end());
	std::sort(array_two.begin(), array_two.end());

	std::set_intersection(array_one.begin(), array_one.end(),
		                    array_two.begin(), array_two.end(),
		                      std::back_inserter(result));

	if(container != nullptr) for (auto& it : result) std::cout << it << std::endl;

	else {
		std::vector<typename std::iterator_traits<iterator>::value_type> array_three;
		std::vector<typename std::iterator_traits<iterator>::value_type> result_all;

		result.reserve(result.capacity() + array_three.capacity());
		array_three.reserve(std::distance(array_three_begin, array_three_end));

		std::copy(array_two_begin, array_two_end, std::back_inserter(array_three));
		std::sort(array_three.begin(), array_three.end());

		std::set_intersection(result.begin(), result.end(),
			                    array_three.begin(), array_three.end(),
			                      std::back_inserter(result_all));

		for (auto& it : result_all) std::cout << it << std::endl;
	}
}

template<class iterator>
class  ArrayUniqueValues : public ArrayTransformer<iterator> {
 public:
	void transform(iterator array_one_begin, iterator array_one_end,
		             iterator array_two_begin, iterator array_two_end,
		               iterator array_three_begin, iterator array_three_end,
		                 std::vector<int>* container = nullptr) override;
};

template<class iterator>
void ArrayUniqueValues<iterator>::transform(iterator array_one_begin, iterator array_one_end,
	                                          iterator array_two_begin, iterator array_two_end,
	                                            iterator array_three_begin, iterator array_three_end,
	                                              std::vector<int>* container) {

	std::vector<typename std::iterator_traits<iterator>::value_type> combined;

	combined.reserve(std::distance(array_one_begin, array_one_end) +
		               std::distance(array_two_begin, array_two_end) +
		                 std::distance(array_three_begin, array_three_end));

	std::copy(array_one_begin,   array_one_end,   std::back_inserter(combined));
	std::copy(array_two_begin,   array_two_end,   std::back_inserter(combined));
	std::copy(array_three_begin, array_three_end, std::back_inserter(combined));

	std::sort(combined.begin(), combined.end());

	auto last = std::unique(combined.begin(), combined.end()); combined.erase(last, combined.end());

	std::vector<typename std::iterator_traits<iterator>::value_type> result(combined.rbegin(), combined.rend());

	*container = std::move(result);
}

// Block Factory creating objects for manipulating arrays.

template<class iterator>
class TransformerFactory {
 public:
	std::unique_ptr<ArrayTransformer<iterator>> createArrayPrint();
	std::unique_ptr<ArrayTransformer<iterator>> createArraySort();
	std::unique_ptr<ArrayTransformer<iterator>> createArrayIntersections();
	std::unique_ptr<ArrayTransformer<iterator>> createArrayUniqueValues();
};

template<class iterator> std::unique_ptr<ArrayTransformer<iterator>> TransformerFactory<iterator>::createArrayPrint() {

	return std::make_unique<ArrayPrint<iterator>>();
}

template<class iterator> std::unique_ptr<ArrayTransformer<iterator>> TransformerFactory<iterator>::createArraySort() {

	return std::make_unique<ArraySort<iterator>>();
}

template<class iterator> std::unique_ptr<ArrayTransformer<iterator>> TransformerFactory<iterator>::createArrayIntersections() {

	return std::make_unique<ArrayIntersections<iterator>>();
}

template<class iterator> std::unique_ptr<ArrayTransformer<iterator>> TransformerFactory<iterator>::createArrayUniqueValues() {

	return std::make_unique<ArrayUniqueValues<iterator>>();
}

// Block Interface Trasform for working with arrays.

class Trasform {
 public:
	template<class type, class iterator> void print(type& array_one, type& array_two, type& array_three, iterator);
	template<class type, class iterator> void sort (type& array_one, type& array_two, type& array_three, iterator);
	template<class type, class iterator> void uniqueValues (type& array_one, type& array_two, type& array_three, 
		                                                                                     std::vector<int>& vec, iterator);
	template<class type, class iterator> void allIntersections(type& array_one, type& array_two, type& array_three, iterator);
	template<class type, class iterator> void maxIntersections(type& array_one, type& array_two, type& array_three, iterator);

 private:
	template<class type>bool examination(type& array_one, type& array_two, type& array_three);
};

template<class type, class iterator>
void Trasform::print(type& array_one, type& array_two, type& array_three, iterator) {

	if (examination(array_one, array_two, array_three)) return;

	TransformerFactory<iterator>().createArrayPrint()->transform(array_one.begin(), array_one.end(),

		array_two.begin(), array_two.end(), array_three.begin(), array_three.end());
}

template<class type, class iterator>
void Trasform::sort(type& array_one, type& array_two, type& array_three, iterator) {

	if (examination(array_one, array_two, array_three)) return;

	TransformerFactory<iterator>().createArraySort()->transform(array_one.begin(), array_one.end(),

		array_two.begin(), array_two.end(), array_three.begin(), array_three.end());
}

// Creating a reverse sorted array with unique numbers and writing it to - std::vector<int>& vec.

template<class type, class iterator> 
void Trasform::uniqueValues(type& array_one, type& array_two, type& array_three, std::vector<int>& vec, iterator) {

	if (examination(array_one, array_two, array_three)) return;

	TransformerFactory<iterator>().createArrayUniqueValues()->transform(array_one.begin(), array_one.end(),

		array_two.begin(), array_two.end(), array_three.begin(), array_three.end(), &vec);
}

// Finding the intersection of all three arrays.

template<class type, class iterator> 
void Trasform::allIntersections(type& array_one, type& array_two, type& array_three, iterator) {

	if (examination(array_one, array_two, array_three)) return;

	TransformerFactory<iterator>().createArrayIntersections()->transform(array_one.begin(), array_one.end(),

		array_two.begin(), array_two.end(), array_three.begin(), array_three.end());
}

// Find the intersection of two largest arrays.

template<class type, class iterator>
void Trasform::maxIntersections(type& array_one, type& array_two, type& array_three, iterator) {

	if (examination(array_one, array_two, array_three)) return;

	std::vector<int>  flag;
	std::vector<type> container{ array_one, array_two, array_three };

	auto smallest = std::min_element(container.begin(), container.end(), [](type &a, type &b) {

		return a.size() < b.size();
		});

	if(smallest != container.end()) {

		container.erase(smallest);

		TransformerFactory<iterator>().createArrayIntersections()->transform(container[0].begin(), container[0].end(),

			container[1].begin(), container[1].end(), array_two.begin(), array_two.end(), &flag);
	}
}

template<class type> bool Trasform::examination(type& array_one, type& array_two, type& array_three) {

	if (array_one.empty() && array_two.empty() && array_three.empty()) return true;

	else return false;
}

#endif