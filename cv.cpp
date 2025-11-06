//
// Created by Mark on 11/5/25.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex global_lock;
condition_variable global_cv;


int main() {
    int result = 0;
    bool notified = false;

    //Reporting Thread
    //must wait until work is done be the working thread
    thread reporter([&] {
        cout << "Reporter is now waiting, result is: " << result << endl;
        unique_lock<mutex> lock(global_lock);
        if (!notified) {
            global_cv.wait(lock);
        }
        cout << "Reporter activated.. result is: " << result << endl;
    });

    //Working Thread
    thread worker([&] {
        unique_lock<mutex> lock(global_lock);
        result = 42 + 7;
        //our work is done so now we can notify
        notified = true;
        this_thread::sleep_for(chrono::seconds(5));
        cout << "Work is complete!" << endl;

        //wake up a thread that is waiting for some condition to be true
        global_cv.notify_one();
    });


    reporter.join();
    worker.join();

    return 0;
}