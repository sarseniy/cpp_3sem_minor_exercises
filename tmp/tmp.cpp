#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>
#include <list>
#include <random>

template <typename Container>
void print(Container const& v) {
	std::copy(std::begin(v), std::end(v),
		std::ostream_iterator<typename Container::value_type>(std::cout, " "));
	std::cout << '\n';
}

int main()
{
	std::vector<int> v;
	v.resize(10);

	/*struct generator_function {
		int operator()() {
			return value_ *= 3;
		}
	private:
		int value_ = 1;
	};*/

	int value = 1;
	auto gen_func = [&value]() {
		return value *= 3;
	};

	std::generate(std::begin(v), std::end(v), gen_func);
	print(v);

	std::vector<std::string> by_str;

	std::transform(std::begin(v), std::end(v), std::back_inserter(by_str),
		[](int value) -> std::string {
			return "dec_" + std::to_string(value);
		});

	print(by_str);

	std::set<char> prefix;
	char symbol = 'a' - 1;
	std::generate_n(std::inserter(prefix, std::end(prefix)), 'z' - 'a' + 1,
		[&symbol]() { return symbol += 1; });

	print(prefix);

	std::list<std::string> l;

	std::transform(std::begin(by_str), std::end(by_str),
		std::begin(prefix),
		std::back_inserter(l),
		[](std::string const& str, char prefix) {
			return prefix + std::string{ "_" } + str;
		});

	print(l);

	std::reverse(std::begin(l), std::end(l));
	print(l);

	auto trash = std::remove_if(std::begin(l), std::end(l),
		[](auto const& e) {
			return std::find(std::begin(e), std::end(e), '1') != std::end(e);
		}
	);

	print(l);

	l.erase(trash, l.end());
	print(l);



	auto l_copy = l;

	auto pred = [](auto const& lhs, auto const& rhs) {
		return lhs.size() < rhs.size();
	};

	std::sort(std::begin(l), std::end(l), pred);
	print(l);

	std::stable_sort(std::begin(l_copy), std::end(l_copy), pred);
	print(l_copy);

	return 0;
}