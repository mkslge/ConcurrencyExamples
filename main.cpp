#include <iostream>
#include <thread>
#include<vector>
#include <mutex>
#include <atomic>
using namespace std;






atomic<int> multithreaded_count = 0;
mutex global_lock;
void increment_multithread() {
        multithreaded_count++;
}

int main() {


    auto lambda = [](int x ) {
        cout << "Hello from thread!" << this_thread::get_id() << endl;
        cout << "We passed in " << x << endl;
    };





    vector<thread> threads;
    for (int i = 0; i < 1000;i++) {

        threads.push_back(thread(&increment_multithread));

    }
    for (int i = 0; i < threads.size();i++) {
        threads[i].join();
    }



    cout << "Shared Value: " << multithreaded_count << endl;







    return 0;
}