#include <iostream>
#include <unistd.h>

#include "./SharedMemory.h"

int main(int argc, char *argv[])
{
    char path[]="/workspace/sharedfile";
	char size = 20;
	char data[size];
	char write_data[]="1234567";

    SharedMemory shm1;
    shm1.Create(path,12288);


 #if 1
    shm1.Read(data,size);
	std::cout<<"Read:";
	for(int i=0;i<size;i++) {
		std::cout<<data[i];
	}
	std::cout<<std::endl;

	std::cout<<"Sleep 10sec..."<<std::flush;
    sleep(10);
	std::cout<<"finish."<<std::endl;

	std::cout<<"Write:"<<write_data<<std::endl;
	shm1.Write(write_data,5);

    shm1.Read(data,size);
	std::cout<<"Read:";
	for(int i=0;i<size;i++) {
		std::cout<<data[i];
	}
	std::cout<<std::endl;
#else
    shm1.Read(data,size);
	std::cout<<"Read:";
	for(int i=0;i<size;i++) {
		printf("x%x",data[i]);
	}
	std::cout<<std::endl;

	TEST_STRUCT test_data;
    shm1.ReadStruct<TEST_STRUCT>(&test_data);
	std::cout<<"Read int:"<<test_data.intData<<" byteData:"<<test_data.byteData<<" boolData:"<<test_data.boolData<<std::endl;

	TEST_STRUCT write_struct_data;
	write_struct_data.intData = 100;
	write_struct_data.byteData = 55;
	write_struct_data.boolData = true;

    shm1.WriteStruct<TEST_STRUCT>(&write_struct_data);
    shm1.ReadStruct<TEST_STRUCT>(&test_data);
	std::cout<<"Read int:"<<test_data.intData<<" byteData:"<<test_data.byteData<<" boolData:"<<test_data.boolData<<std::endl;

#endif

	shm1.Close();
}

#if 0
int main(int argc, char *argv[])
{
	int fd;
	int index;
	char *data;
	// const char *filepath = "/tmp/sharedfile";
	const char *filepath = "/workspace/sharedfile";

	// ファイルオープン(存在しない場合は作成、R/W、ユーザにRWE)
	if ((fd = open(filepath, O_CREAT | O_RDWR, (mode_t)00700)) == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	// ファイル(fd)をメモリにマップ(size:12288,R/W,他プロセスと共有)
	data = (char *)mmap(NULL, 12288, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	for (index = 0; index < 200; index++) {
		data[index] = 'C';
	}

    sleep(10);

	// We must see 'Goose' at the beginning of memory-mapped file.
	for (index = 0; index < 200; index++) {
		fprintf(stdout, "%c", data[index]);
	}

	for (index = 0; index < 200; index++) {
		data[index] = 'B';
	}

	// ファイルをマップしたメモリと同期(MS_SYNC:更新要求から更新完了まで待つ)
	if (msync(data, 12288, MS_SYNC) == -1) {
		perror("Error sync to disk");
	}

	// メモリをアンマップ
	if (munmap(data, 12288) == -1) {
		close(fd);
		perror("Error un-mmapping");
		exit(EXIT_FAILURE);
	}
	close(fd);
	return 0;
}
#endif
