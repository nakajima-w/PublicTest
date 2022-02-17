#include <string.h>

class SharedMemory
{
  public:
    SharedMemory();
    ~SharedMemory();
    bool Create(char *path,int a_size);
    void Close();
    bool Read(char *read_data,int read_size);
    bool Write(char *write_data,int write_size);
    template <typename T>
    bool ReadStruct(T *read_data) {
        bool ret = false;
        if(memoryMappedFileStatus) {
          memcpy(read_data, data, sizeof(T));
          ret = true;
        }
        return ret;
    }
    template <typename T>
    bool WriteStruct(T *write_data) {
        bool ret = false;
        if(memoryMappedFileStatus) {
          memcpy(data,write_data,sizeof(T));
          ret = true;
        }
        return ret;
    }

  private:
    int fd;
    bool memoryMappedFileStatus;
    char *data;
    int size;
};
typedef struct{
    int intData;
    char byteData;
    bool boolData;
} TEST_STRUCT;
