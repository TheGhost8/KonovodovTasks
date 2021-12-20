#include <stdio.h>
#include <iostream>
#include <map>
#include <chrono>



void FirstExample(std::map<size_t, std::string> &some_map) {
    std::chrono::duration<double> elapsed;
    auto timeStart = std::chrono::high_resolution_clock::now();

    some_map.insert({10000000000, "10000000000"});

    auto timeFinish = std::chrono::high_resolution_clock::now();
    elapsed = timeFinish - timeStart;
    std::cout << "First example elapsed time: " << elapsed.count() << " s\n";

    some_map.erase(10000000000);
    auto help = some_map.upper_bound(some_map.lower_bound(some_map.lower_bound(10000000000)->first)->first);

    timeStart = std::chrono::high_resolution_clock::now();

    some_map.insert(help, {10000000000, "10000000000"});

    timeFinish = std::chrono::high_resolution_clock::now();
    elapsed = timeFinish - timeStart;
    std::cout << "First example elapsed hint time: " << elapsed.count() << " s\n";

}

int main() {
    size_t map_size = 100000;
    std::map<size_t, std::string> some_map;
    for (size_t i = 0; i < map_size; ++i) {
        some_map[i] = std::to_string(i);
    }
    FirstExample(some_map);
}
