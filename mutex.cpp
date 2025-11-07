//
// Created by Mark on 11/7/25.
//
#include <thread>
#include <iostream>
#include <vector>
#include <mutex>


int g_count = 0;
std::mutex g_mutex = std::mutex();
constexpr int NUM_THREADS = 10;
void incremement_g_count() {
    /* To prevent a datarace here, we use a mutex to lock line "g_count++;",
     * which disallows other threads from accessing it, leading to deterministic output.
     */
    g_mutex.lock();
    g_count++;
    g_mutex.unlock();
}

int main() {
    std::vector<std::thread> threads(NUM_THREADS);
    for (int i = 0; i < NUM_THREADS;i++) {

        threads[i] = std::thread(&incremement_g_count);
    }

    for (int i = 0; i < NUM_THREADS;i++) {
        threads[i].join();
    }


    std::cout << "Global count is " << g_count <<
        ", we used " << NUM_THREADS << " threads" << std::endl;
}