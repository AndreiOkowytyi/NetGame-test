#include "transform.h"
#include "readTXT.h"

enum class Index {

	OneArray,
	TwoArray,
	ThreeArray
};

int main() {

	ReadTXT readTXT;

	std::vector<std::vector<int>> data;

	if (readTXT.readFile(data, "text.txt")) {

		Trasform transform;

		if (data.size() < 4) {

			std::vector<int> vec_unique_elements;

			transform.sort(data[static_cast<int>(Index::OneArray)], data[static_cast<int>(Index::TwoArray)],
				             data[static_cast<int>(Index::ThreeArray)], data[static_cast<int>(Index::OneArray)].begin());

			transform.print(data[static_cast<int>(Index::OneArray)], data[static_cast<int>(Index::TwoArray)],
				              data[static_cast<int>(Index::ThreeArray)], data[static_cast<int>(Index::OneArray)].begin());

			transform.allIntersections(data[static_cast<int>(Index::OneArray)], data[static_cast<int>(Index::TwoArray)],
			                             data[static_cast<int>(Index::ThreeArray)], data[static_cast<int>(Index::OneArray)].begin());

			transform.maxIntersections(data[static_cast<int>(Index::OneArray)], data[static_cast<int>(Index::TwoArray)],
				                         data[static_cast<int>(Index::ThreeArray)], data[static_cast<int>(Index::OneArray)].begin());

			transform.uniqueValues(data[static_cast<int>(Index::OneArray)], data[static_cast<int>(Index::TwoArray)],
				                     data[static_cast<int>(Index::ThreeArray)], vec_unique_elements, data[static_cast<int>(Index::OneArray)].begin());
		}
	}
	return 0;
}