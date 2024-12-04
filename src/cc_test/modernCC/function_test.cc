#include<iostream>
#include<memory>
#include<algorithm>
#include<string>
#include<functional>
using namespace std;
void free_save(const string &filename)
{
    cout<<"call free fun "<<filename<<endl;
}
class FileSave{
public:
    void member(const string& filename)
    {
        cout<<" call member fun "<<filename<<endl;
    }
};

int main(){
    auto lambda_file=[](const string& filename)->void{
        cout<<"call lambda fun "<<filename<<endl;
        return;
    };
    function<void(const string&)> save1=free_save;
    function<void(const string&)> save2=lambda_file;
    FileSave file_save;
    function<void(const string&)> save3=bind(&FileSave::member,&file_save,std::placeholders::_1);
    save1("1.txt");
    save2("2.txt");
    save3("3.txt");
    return 0;
}