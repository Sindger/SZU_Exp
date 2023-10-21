#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>

using namespace std;
using namespace boost::interprocess;

int main()
{
	//���������ڴ�
	shared_memory_object share_mem{ open_or_create,"Boost",read_write };
	//���������ڴ��С
	share_mem.truncate(1000);
	//����ӳ�����1
	mapped_region mem1{ share_mem,read_write };
	cout << mem1.get_address() << endl;
	cout << mem1.get_size() << endl;
	//����ӳ�����2
	mapped_region mem2{ share_mem,read_write };
	cout << mem2.get_address() << endl;
	cout << mem2.get_size() << endl;
	return 0;
}