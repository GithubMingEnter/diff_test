
#include"Person.pb.h"
class fileTest{

    public:
    void test(){
        Erbing::Person p;
        //serialize
        p.set_id(10);
        p.set_sex("man");
        p.set_age(32);
        p.add_name();
        p.set_name(0,"ming");
        p.add_name("gogo");
        p.add_name("swinming");
        p.mutable_addr()->set_addr("China");
        p.mutable_addr()->set_num(1001);
        p.set_color(Erbing::Color::Blue);
        std::string output;
        p.SerializeToString(&output);
        std::cout<<"serialize string"<<output<<std::endl;
        //Deserialize
        Erbing::Person pd;
        pd.ParseFromString(output);
        std::cout<<pd.id() <<"."<<pd.sex()<<"."<<pd.age()<<std::endl;
        std::cout<<pd.addr().addr()<<" , "<<pd.addr().num()<<std::endl;
        int size=pd.name_size();
        for(int i=0;i<size;i++)
        {
            std::cout<<pd.name(i)<<std::endl;
        }
        
        std::cout<<pd.color()<<std::endl;
    }

};

int main(int argc, char** argv)
{
    fileTest file_test;
    file_test.test();
    return 0;
}








