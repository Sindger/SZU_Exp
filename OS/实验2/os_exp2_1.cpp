#include <iostream>
#include <string>
#include <vector>
#include <boost/thread/thread.hpp>

using namespace std;

// 定义全局变量缓冲区
vector<string> buffer;

// 定义互斥锁和条件变量
boost::mutex Mutex;
boost::condition_variable_any cond;

// 主线程不断读取客户端输入，并将数据保存到缓冲区内
void input_thread() {
    while (true) {
        string data;
        getline(cin, data);
        {
            // 加锁保护临界区
            boost::unique_lock<boost::mutex> lock(Mutex);
            buffer.push_back(data);
            // 发送信号通知等待的线程
            cond.notify_one();
        }
    }
}

// 子线程1读取缓冲区信息
void output_thread1() {
    while (true) {
        // 加锁保护临界区
        boost::unique_lock<boost::mutex> lock(Mutex);
        // 等待缓冲区有数据
        while (buffer.empty()) {
            cond.wait(lock);
        }
        // 输出线程1的id和缓冲区的第一条数据
        cout << "线程1: " << buffer.front() << endl;
        buffer.erase(buffer.begin());
        // 释放锁
        lock.unlock();
        // 休眠一段时间
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
}

// 子线程2读取缓冲区信息
void output_thread2() {
    while (true) {
        // 加锁保护临界区
        boost::unique_lock<boost::mutex> lock(Mutex);
        // 等待缓冲区有数据
        while (buffer.empty()) {
            cond.wait(lock);
        }
        // 输出线程2的id和缓冲区的第一条数据
        cout << "线程2: " << buffer.front() << endl;
        buffer.erase(buffer.begin());
        // 释放锁
        lock.unlock();
        // 休眠一段时间
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
}

int main() {
    // 启动主线程和子线程
    boost::thread input(input_thread);
    boost::thread output1(output_thread1);
    boost::thread output2(output_thread2);
    // 等待子线程结束
    input.join();
    output1.join();
    output2.join();
    return 0;
}
