#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <array>

/*bool pred(int a, int b)
{
	return a < b;
}

void print(int a, int b, int c, int d)
{
	std::vector<int> tmp = { a, b, c, d };
	std::sort(tmp.begin(), tmp.end());
	for (size_t i = 0; i < 4; i++)
	{
		std::cout << tmp[i] << ' ';
	}
	std::cout << '\n';
}*/

int main() {
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	std::set<std::vector<int>> elems;

	for (size_t i = 0; i < n; i++)
	{
		std::cin >> a[i];
	}

	int sum;
	std::cin >> sum;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = i + 1; j < n; j++)
		{
			for (size_t k = j + 1; k < n; k++)
			{
				for (size_t l = k + 1; l < n; l++)
				{
					if (a[i] + a[j] + a[k] + a[l] == sum)
					{
						std::vector<int> m(4);
						m[0] = a[i]; m[1] = a[j]; m[2] = a[k]; m[3] = a[l];
						std::sort(m.begin(), m.end());
						elems.emplace(m);
					}
				}
			}
		}
	}

	for (auto const& q: elems)
	{
		for (auto const& w : q)
		{
			std::cout << w << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}