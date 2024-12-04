#include<iostream>
#include<chrono>
#include<thread>
#include<functional>
#include<cpp-httplib/httplib.h>


class Download
{
private:
    /* data */
public:
    Download(/* args */);
    ~Download();
    void download(const std::string& host,const std::string& path,const 
                  std::function<void(const std::string&,const std::string&)> &callback)
    {
        std::cout<<"thread id "<<std::this_thread::get_id()<<std::endl;
        httplib::Client client(host);
        auto response = client.Get(path);
        if(response&&response->status==200){
            callback(path,response->body);
        }

    };
    void start_download(const std::string& host,const std::string& path,const 
                  std::function<void(const std::string&,const std::string&)> &callback)
    {
        auto download_fun=std::bind(&Download::download,this,
                            std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
        std::thread download_thread(download_fun,host,path,callback);
        download_thread.detach();
    };
};

Download::Download(/* args */)
{
}

Download::~Download()
{
}
int main()
{
    auto download=Download();
    auto word_download=[](const std::string &path,const std::string& result)->void{
        std::cout<<"finish download"<<path<<result.length()<<" "<<result.substr(0,3)<<std::endl;
    };
    download.start_download("http://localhost:8000","/novel1.txt",word_download);
    download.start_download("http://localhost:8000","/novel2.txt",word_download);
    download.start_download("http://localhost:8000","/novel3.txt",word_download);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000*10));
    return 0;
}

