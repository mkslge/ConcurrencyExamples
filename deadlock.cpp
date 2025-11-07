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
    g_mutex.lock();
    try {

        g_count++;
        //what if an error occurs in our atomic code?
        //this may cause the unlock line to not execute, meaning
        //other threads will be infinitely waiting for the mutex
        //this is called a deadlock,
        //this can be fixed using a try lock :)
        throw "Simulating error...";

    } catch (...) {
        return;
    }

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