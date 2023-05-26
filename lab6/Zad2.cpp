#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

std::mutex m;
std::condition_variable cv;
std::queue<int> q;
bool finished = false;

int produceData() {
    static int i = 0;
    return i++;
}

void produce() {
    std::unique_lock<std::mutex> lock(m);
    int data = produceData();
    q.push(data);
    std::cout << "Produced: " << data << std::endl;
    lock.unlock();
    cv.notify_all();
}

void consume() {
    std::unique_lock<std::mutex> lock(m);
    while (q.empty() && !finished) {
        cv.wait(lock);
    }
    if (!q.empty()) {
        int val = q.front();
        q.pop();
        std::cout << "Consumed: " << val << std::endl;
    }
}
void alternate(int n, bool startWithProduce) {
    for (int i = 0; i < n; i++) {
        if ((i + startWithProduce) % 2 == 0) {
            produce();
        }
        else {
            consume();   
        }
    }
    finished = true;
    cv.notify_all();
}

int main() {
    int numSwitches = 11;
    std::thread t1(alternate, numSwitches, false);
    std::thread t2(alternate, numSwitches, true);
    t1.join();
    t2.join();
    return 0;
}
