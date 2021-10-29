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

	for (size_t i = 0; i < n; i++)
	{
		std::string tmp;
		std::cin >> tmp;
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](unsigned char c) { return std::tolower(c); });
		if (std::find(a.begin(), a.end(), tmp) == a.end()) a.emplace_back(tmp);
	}

	std::sort(a.begin(), a.end(), pred);
	
	for (auto& f : a) {
		std::cout << f << ' ';
	}

	return 0;
}