#include <stdio.h>
#include <iostream>
#include <set>
#include <vector>
#include <tuple>

struct Printer {
	std::string str() const;

	template<typename T>
	Printer& format(const T& val) {
		Printer
	}

	template<typename T>
	Printer& format(const std::set<T>& set) {
		
	}

	template<typename T>
	Printer& format(const std::vector<T>& vec) {
		
	}

	template<typename T1, typename T2>
	Printer& format(const std::pair<T1, T2>& pair) {
		
	}

	template <typename Head, typename... Tail>
	Printer& format(const std::tuple<Head,Tail...>& val) {
		
	}
}

template<typename T>
std::string format(const T& t) {
	return Printer().format(t).str();
}

int main() {
	std::tuple<std::string, int, int> t = {"xyz", 1, 2};
	std::vector<std::pair<int, int> > v = {{1, 4}, {5, 6}};
	std::string s1 = Printer().format(" vector: ").format(v).str();
	// " vector: [ (1, 4), (5, 6) ]"
	std::string s2 = Printer().format(t).format(" ! ").format(0).str();
	// "( xyz, 1, 2 ) ! 0"
}