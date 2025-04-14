#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>

int main () {
    std::vector<std::thread> threads;
    // start up threads
    int nThreads = 4;
    for(int i = 0; i < nThreads; ++i) {
        threads.emplace_back(std::thread([]() {
            while (true){
                std::this_thread::sleep_for(std::chrono::microseconds(100));
            }
        }));
    }
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });

}   