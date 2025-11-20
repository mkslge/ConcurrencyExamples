#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex;

void job1() {
    if (mutex.try_lock()) {
        std::cout << "job1 executed" << std::endl;
        mutex.unlock();
    }

}

void job2() {
    if (mutex.try_lock()) {
        std::cout << "job2 executed" << std::endl;
        mutex.unlock();
    }
}


/*Notes:
 *There are 2 possible outputs of this programs, either
 *"job1 executed"
 *or "job1 executed, job2 executed"
 *The first output happens when the job2 tries to unlock the
 *mutex while job1 has the lock
 *
 *The second output happens in the (rarish) case that job1 has locked
 *AND also unlocked, meaning that job1 is printed, and then job2 does its
 *try_lock, printing job2 as well.
 *
 */
int main() {
    std::thread t1(job1);
    std::thread t2(job2);

    t1.join();
    t2.join();
    return 0;
}