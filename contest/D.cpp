#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

bool pred(std::string const& a, std::string const& b)
{
	return a > b;
}

int main() {
	int n;
	std::cin >> n;
	std::vector<std::string> a;
	std::vector<int> rank;

	for (size_t i = 0; i < n; i++)
	{
		std::string tmp;
		std::cin >> tmp;
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](unsigned char c) { return std::tolower(c); });

		auto f = std::find(a.begin(), a.end(), tmp);
		if (f == a.end()) {
			a.emplace_back(tmp);
			rank.emplace_back(1);
		}
		else {
			rank[std::distance(a.begin(), f)]++;
		}
	}

	int ind = 0;
	for (size_t i = 0; i < rank.size(); i++)
	{
		if (rank[i] > rank[ind])
		{
			ind = i;
		}
	}

	std::cout << a[ind] << ' ' << rank[ind];

	return 0;
}