//
// Created by Mark on 11/6/25.
//
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

bool buffered_file_loader() {
	size_t bytes_loaded = 0;
	while (bytes_loaded < 20000) {
		std:: cout << "Thread: loading file....." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		bytes_loaded += 1000;
		std::cout << "loaded " << bytes_loaded << " bytes" << std::endl;
	}
    return true;
}

int main() {
    std::future<bool> background_thread = std::async(std::launch::async, buffered_file_loader);


    std::future_status status;


    //our main program loop
    while(true) {

		std::cout << "Main thread is running" << std::endl;

		//artificial sleep for our program (more realistic)
	

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
    	status = background_thread.wait_for(std::chrono::milliseconds(1));

    	if (status == std::future_status::ready) {
    		std::cout << "Our data is ready" << std::endl;
    		break;
    	}
    }


     
    return 0;
}
