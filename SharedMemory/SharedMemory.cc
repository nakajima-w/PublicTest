#include "SharedMemory.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <iostream>

SharedMemory::SharedMemory() {
}
SharedMemory::~SharedMemory() {
}

bool SharedMemory::Create(char *path, int a_size) {
    memoryMappedFileStatus = true;
	const char *filepath = path;
    size = a_size;

	// ファイルオープン(存在しない場合は作成、R/W、ユーザにRWE)
	if ((fd = open(filepath, O_CREAT | O_RDWR, (mode_t)00700)) == -1) {
        memoryMappedFileStatus = false;
		perror("open");
		// exit(EXIT_FAILURE);
	}

	// ファイル(fd)をメモリにマップ(size:12288,R/W,他プロセスと共有)
	data = static_cast<char*>(mmap
        (NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0));
	if (data == MAP_FAILED) {
        memoryMappedFileStatus = false;
		perror("mmap");
		// exit(EXIT_FAILURE);
	}
    return memoryMappedFileStatus;
}
void SharedMemory::Close() {
	// ファイルをマップしたメモリと同期(MS_SYNC:更新要求から更新完了まで待つ)
	if (msync(data, size, MS_SYNC) == -1) {
		perror("Error sync to disk");
	}

	// メモリをアンマップ
	if (munmap(data, size) == -1) {
		close(fd);
		perror("Error un-mmapping");
		exit(EXIT_FAILURE);
	}
	close(fd);
}
bool SharedMemory::Read(char *read_data, int read_size) {
    bool ret = false;
    if (memoryMappedFileStatus) {
        if (read_size < size) {
            // for (int i=0;i<read_size;i++) {
            //     read_data[i] = data[i];
            // }
            memcpy(read_data, data, read_size);
            ret = true;
        }
    }
    return ret;
}
bool SharedMemory::Write(char *write_data, int write_size) {
    bool ret = false;
    if (memoryMappedFileStatus) {
        if (write_size < size) {
            // for (int i=0;i<write_size;i++) {
            //     data[i] = write_data[i];
            // }
            memcpy(data, write_data, write_size);
            ret = true;
        }
    }
    return ret;
}
