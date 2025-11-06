#include <iostream>
#include <future>


int square(int x) {
    return x * x;
}
int main() {

    //the generic of future should tyhe type of the result
    //we expect from out computation
    std::future<int> async_function = std::async(&square, 5);

    //simulating some irrelevant work
    for (int i = 0; i < 100;i++) {
        std::cout << square(i) << std::endl;

    }

    //we are blocked at the get opereation until our result has been computed
    int result = async_function.get();

    std::cout << "Result of our future " << result << std::endl;
    return 0;
}
