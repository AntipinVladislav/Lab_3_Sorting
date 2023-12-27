#include <vector>
#include <iostream>
#include <random>

using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};


template<typename T>
stats bubble(std::vector<T>& vec) {
	int size = vec.size();
	stats result;
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size - 1; j++) {
			if (vec[j] > vec[j + 1]) {
				std::swap(vec[j], vec[j + 1]);
				result.copy_count++;
			}
			result.comparison_count++;
			
		}
	}
	return result;
}

template<typename T>
stats shella(std::vector<T>& vec) {
	stats result;
	int size = vec.size();
	for (int s = size / 2; s > 0; s /= 2) {
		for (int i = s; i < size; ++i) {
			result.comparison_count += 1;
			for (int j = i - s; j >= 0 && vec[j] > vec[j + s]; j -= s) {
				result.comparison_count += 1;
				result.copy_count++;
				std::swap(vec[j], vec[j + s]);
			}
		}
	}
	return result;
}

template<typename T>
stats hairbruh(vector<T>& vec) {
	stats result;
	double factor = 1.2473309;
	int step = vec.size() - 1;
	while (step >= 1)
	{
		for (int i = 0; i + step < vec.size(); i++)
		{
			result.comparison_count++;
			if (vec[i] > vec[i + step])
			{
				result.copy_count++;
				std::swap(vec[i], vec[i + step]);
			}
		}
		step /= factor;
	}
	return result;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T>& vec) {
	for (int i = 0; i < vec.size(); i++)
		out << vec[i] << endl;

	return out;
}

int main() {
	constexpr int all_size = 100;
	std::vector<int> list[all_size];
	stats all_stats[all_size];
	srand(12345);

	int sizes[13] = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000 };

	for (int j = 0; j < 13; j++) {
		int size = sizes[j];
		uint64_t sum_comparison = 0;
		uint64_t sum_copy = 0;
		int count = 0;
		for (auto& vec : list) {
			vec.clear();
		}

		//random
		/*for (auto& vec : list) {
			for (int i = 0; i < size; i++){
				vec.push_back(rand());
			}
		};*/

		//sorted
		/*for (auto& vec : list) {
			for (int i = 0; i < size; i++) {
				vec.push_back(i);
			}
		}*/

		//reverse
		/*for (auto& vec : list) {
			for (int i = size-1; i >=0; i--) {
				vec.push_back(i);
			}
		}*/

		for (auto vec : list) {
			all_stats[count] = hairbruh(vec);
			sum_comparison += all_stats[count].comparison_count;
			sum_copy += all_stats[count].copy_count;
			count++;
		};


		cout << sum_comparison / static_cast<double>(all_size) << " " << sum_copy / static_cast<double>(all_size) << "" << endl;
	}
}

