#include <iostream>
#include <unistd.h>
#include <cstring>

#define	BUF_SIZE	4096
#define	ACL_TLS_OUT_OF_INDEXES          0xffffffff

/**
 * 程序运行过程中获得可执行程序存储于文件系统中的全路径
 * @return {std::string} "": 无法获得; != "": 返回值即是程序在
 *    文件系统上的存储全路径
 */
std::string acl_process_path()
{
    const char *file_name="acl_process_path";
    char buf_ptr[BUF_SIZE];
    int ret;
    ret = readlink("/proc/self/exe",buf_ptr,BUF_SIZE);
    if(ret<0){
        printf("%s(%d): readlink error(%s)",file_name,__LINE__,strerror(errno));
        return "";
    }
    return buf_ptr;
}

/**
 * 程序运行过程中获得其运行路径
 * @return {std::string} "": 无法获得; != "": 返回值即为程序的运行路径
 */
std::string acl_getcwd()
{
    const char *myname = "acl_getcwd";
    char buf_ptr[BUF_SIZE];
    char *ptr;

    ptr = getcwd(buf_ptr, BUF_SIZE);
    if (ptr == NULL) {
        printf("%s(%d): getcwd error(%s)",
                      myname, __LINE__, strerror(errno));
    }
    return (ptr);
}

int main(int argc,char** argv)
{
    std::string ptr = acl_process_path();
    std::string ptr1 = acl_getcwd();

    printf("current process file's path: %s, getcwd: %s\n",
           !ptr.empty() ? ptr.c_str() : "unknown", 
           !ptr1.empty() ? ptr1.c_str() : "unknown");

    return 0;
}
