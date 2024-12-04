#include <iostream>
#include<sys/ipc.h>
#include<sys/shm.h>

/*  IPC Inter-Process Communication
 当只有IPC_CREAT选项打开时,不管是否已存在该块共享内存，则都返回该共享内存的ID，若不存在则创建共享内存

当只有IPC_EXCL选项打开时，不管有没有该快共享内存，shmget()都返回-1

所以当IPC_CREAT | IPC_EXCL时, 如果没有该块共享内存，则创建，并返回共享内存ID。
                            若已有该块共享内存，则返回-1。
 */
int main() {
    // 创建共享内存的key
    key_t key = ftok("shared_mem_example",1234);

    // 创建共享内存区域
    int shmid = shmget(key,sizeof(int),IPC_CREAT|0666);
    if(shmid == -1){
      std::cerr << "Failed to create shared memory segment." << std::endl;
        return 1;
    }
    // 将共享内存映射到进程的地址空间
    int* shared_data = (int*)shmat(shmid,NULL,0);
    if(shared_data == (int*)-1)
    {
      std::cerr<<"Failed to attach shared memory segment." <<std::endl;
    }
    //写入数据到共享内存
    *shared_data = 42;

    // 断开与共享内存的连接
    if(shmdt(shared_data) == -1)
    {
      std::cerr << "Failed to detach shared memory segment. "<<std::endl;
      return 1;
    }

    /* 删除共享内存，删除后，另一段程序无法读取到 */
    // if(shmctl(shmid,IPC_RMID,NULL) == -1){
    //   std::cerr<<"Failed to delete shared memory segment. "<<std::endl;
    //   return 1;
    // }


 
    return 0;
}