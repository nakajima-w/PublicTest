#include <unistd.h>
#include <iostream>
#include "./SharedMemory.h"

int main(int argc, char *argv[]) {
    char path[]="/workspace/sharedfile";
	char size = 20;
	char data[size];
	char write_data[]="1234567";

    SharedMemory shm1;
    shm1.Create(path, 12288);

 #if 1
    shm1.Read(data, size);
	std::cout << "Read:";
	for(int i = 0; i < size; i++) {
		std::cout << data[i];
	}
	std::cout << std::endl;

	std::cout << "Sleep 10sec..." << std::flush;
    sleep(10);
	std::cout << "finish." << std::endl;

	std::cout << "Write:" << write_data << std::endl;
	shm1.Write(write_data, 5);

    shm1.Read(data, size);
	std::cout << "Read:";
	for(int i = 0; i < size; i++) {
		std::cout << data[i];
	}
	std::cout << std::endl;
#else
    shm1.Read(data, size);
	std::cout << "Read:";
	for(int i = 0; i < size; i++) {
		printf("x%x", data[i]);
	}
	std::cout << std::endl;

	TEST_STRUCT test_data;
    shm1.ReadStruct<TEST_STRUCT>(&test_data);
	std::cout << "Read int:" << test_data.intData
		<< " byteData:" << test_data.byteData
		<< " boolData:" << test_data.boolData << std::endl;

	TEST_STRUCT write_struct_data;
	write_struct_data.intData = 100;
	write_struct_data.byteData = 55;
	write_struct_data.boolData = true;

    shm1.WriteStruct<TEST_STRUCT>(&write_struct_data);
    shm1.ReadStruct<TEST_STRUCT>(&test_data);
	std::cout << "Read int:" << test_data.intData
		<< " byteData:" << test_data.byteData
		<< " boolData:" << test_data.boolData << std::endl;
#endif
	shm1.Close();
}
