#include <thread>
#include <iostream>
#include <string>

#include <unistd.h>

class thread_guard {
private:
    std::thread &t;
public:
    thread_guard(std::thread &_t) : t(_t) {}
    thread_guard(const std::thread &) = delete;
    thread_guard& operator=(const std::thread&) = delete;
    ~thread_guard() {
        if(t.joinable()) {
            std::cout << "~thread_guard thread join\n";
            t.join();
        }
        std::cout << "~thread_guard ok \n";
    }  
};

void thread_func(const int &a, const std::string &str) {
    std::cout << "thread_func thread: a address: 0x" << std::hex << &a << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main() {

    /* thread_guard */
    std::thread td([](){
        std::cout << "thread running \n";
        sleep(2);
        std::cout << "thread exit \n";    
    });

    thread_guard td_guard(td);
    thread_guard td_guard1(td);

    /* argument pass */
    int a = 10;
    std::string str = "hello thread!";
    std::cout << "main thread: a address: 0x" << std::hex << &a << "\n";
    std::thread td2(thread_func, a, str);
    {    
        thread_guard td_guard(td2);
    }
    
    std::thread td3(thread_func, std::ref(a), str);
    {    
        thread_guard td_guard(td3);
    }
    return 0;
}