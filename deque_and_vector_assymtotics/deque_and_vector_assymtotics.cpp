#include <random>
#include <vector>
#include <deque>
#include <chrono>
#include <fstream>

#include <iostream>

class TimeMeasure {
public:
	void start() {
		start_time_ = std::chrono::high_resolution_clock::now();
	}
	void stop() {
		stop_time_ = std::chrono::high_resolution_clock::now();
	}
	size_t elapsed() const {
		auto elapsed_time = stop_time_ - start_time_;
		return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count();
	}
private:
	std::chrono::high_resolution_clock::time_point start_time_, stop_time_;
};

class RandomGenerator {
public:
	static int create_integer(int min, int max) {
		std::mt19937_64 engine(42);
		std::uniform_int_distribution<int> distr(min, max);
		int v;
		v = distr(engine);
		return v;
	}
};

int main()
{
	int num_of_series = 10000000;
	TimeMeasure t;

	std::ofstream outf("res.txt");
	for (size_t i = 1; i < 1000000; i++)
	{
		std::vector<std::vector<int>> a(num_of_series, std::vector<int>(i, 0));
		int f = RandomGenerator::create_integer(0, i - 1);
		t.start();
		for (size_t j = 0; j < num_of_series; j++)
		{
			a[j][f];
		}
		t.stop();
		double time_gone = t.elapsed();
		double res = time_gone / static_cast<double>(num_of_series);
		std::cout << i << ' ' << res << '\n';
		outf << i << ' ' << res << '\n';
	}

	return 0;
}