//
// Created by Mark on 11/7/25.
//
#include <thread>
#include <iostream>
#include <vector>



int g_count = 0;
constexpr int NUM_THREADS = 10;
void incremement_g_count() {
    //occasionally, a data race will ocurr
    /* If Two or more threads wread consecutively, this will cause the incremented
     * value to be off by (num_threads - 1), where num_threads is the number of threads
     * that read consecutively
     */
    g_count++;
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