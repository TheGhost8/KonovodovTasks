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
    some_map.erase(10000000000);
}

void SecondExample(std::map<size_t, std::string> &some_map) {
    std::chrono::duration<double> elapsed;
    auto timeStart = std::chrono::high_resolution_clock::now();

    for (size_t i = 1; i < 1000; ++i) {
        some_map.insert({10000000000 + i, "1000000000" + std::to_string(i)});
    }

    auto timeFinish = std::chrono::high_resolution_clock::now();
    elapsed = timeFinish - timeStart;
    std::cout << "Second example elapsed time: " << elapsed.count() << " s\n";

    for (size_t i = 1; i < 6; ++i) {
        some_map.erase(10000000000 + i);
    }

    timeStart = std::chrono::high_resolution_clock::now();

    auto help = some_map.insert({10000000001, "10000000001"});
    for (size_t i = 2; i < 100000; ++i) {
        some_map.insert(help.first, {10000000000 + i, "1000000000" + std::to_string(i)});
    }

    timeFinish = std::chrono::high_resolution_clock::now();
    elapsed = timeFinish - timeStart;
    std::cout << "Second example elapsed hint time: " << elapsed.count() << " s\n";   
}

int main() {
    size_t map_size = 100000;
    std::map<size_t, std::string> some_map;
    for (size_t i = 0; i < map_size; ++i) {
        some_map[i] = std::to_string(i);
    }
    FirstExample(some_map);
    std::cout << "\n\n";
    SecondExample(some_map);
}
