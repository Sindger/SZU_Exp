#include <iostream>
#include <boost/thread.hpp>
#include <boost/process.hpp>

using namespace std;
using namespace boost;

void print_thread_id(const string& thread_name) {
    cout << thread_name << "的线程id为: " << boost::this_thread::get_id() << endl;
}

void ThreadA() {
    cout << "子线程1开始"  << endl;
    print_thread_id("子线程1");
    auto child_pid = boost::this_process::get_id();
    cout << "子线程1的进程id: " << child_pid << endl;
    boost::thread Thread2(&print_thread_id, "子线程1的子线程");
    Thread2.join();
    cout << "子线程1结束" << endl;
}

void ThreadB() {
    cout << "子线程2开始" << endl;
    print_thread_id("子线程2");
    auto child_pid = boost::this_process::get_id();
    cout << "子线程2的进程id: " << child_pid << endl;
    cout << "子线程2结束" << endl;
}

int main() {
    cout << "主进程开始" << endl;
    print_thread_id("主线程");
    auto main_pid = boost::this_process::get_id();
    cout << "主进程id: " << main_pid << endl;

    boost::thread Thread1(&ThreadA);
    boost::thread Thread2(&ThreadB);

    Thread1.join();
    Thread2.join();

    cout << "主进程结束" << endl;
    return 0;
}
