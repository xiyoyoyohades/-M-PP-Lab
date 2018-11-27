

#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <stdexcept>
#include "CPPEX4.hpp"

using namespace std;


STACK::STACK(int m): elems(new int[m]), max(m), pos(0) {
}

STACK::STACK(const STACK &s): elems(new int[s.max]), max(s.max), pos(s.pos){
    for(int i = 0; i < pos; i++)
    {
        elems[i]=s.elems[i];
    }
}

int STACK::size() const{
    return max;
}

STACK::operator int() const{
    return pos;
}

int STACK::operator[ ] (int x) const  {
    if(x>=pos){
        throw logic_error("index out of range");
    }
    return elems[x];
}

STACK& STACK::operator<<(int e){
    if(pos==max){
        throw logic_error("push error, full stack");
    }
    elems[pos++]=e;
    return *this;
}

STACK& STACK::operator>>(int &e){
    if(!pos){
        throw logic_error("pop error, empty stack");
    }
    e=elems[--pos];
    return *this;
}

STACK& STACK::operator=(const STACK&s){
    int* capacity=const_cast<int* >(&max);
    *capacity=s.max;
    pos=s.pos;
    delete []elems;
    int** st=const_cast<int** >(&elems);
    *st=new int[s.max];


    for(int i=0; i<s.pos; i++){
        elems[i]=s.elems[i];
    }
    return *this;
}

void STACK::print( ) const {
    for(int i=0; i<pos; i++){
        if (i != pos-1){
            std::cout<<elems[i]<<"  ";
        }else{
            std::cout<<elems[i];
        }
    }

}

STACK::~STACK() {
    delete []elems;
}



QUEUE::QUEUE(int m) : STACK(m), s2(m) {
    return;
}

QUEUE::QUEUE(const QUEUE &s) : STACK(static_cast<STACK>(s)), s2(s.s2) {
    return;
}

QUEUE::operator int() const {
    return STACK::operator int() + s2.operator int();
}

int QUEUE::full() const {
    return STACK::operator int() == STACK::size() && s2.operator int();
}

int QUEUE::operator [](int x) const {
    if (x >= STACK::operator int() + s2.operator int()){
        throw std::logic_error("invalid index");
    }

    if (x >= int(s2))
        return STACK::operator [](x - int(s2));
    else
        return s2[int(s2) - x - 1];
}

QUEUE &QUEUE::operator <<(int e) {

    if(this->full()) throw std::logic_error("enqueue failed, currently not allowed");

    if (STACK::operator int() == STACK::size()) {
        int trans;
        int fullsize = STACK::operator int();
        for (int i = 0; i < fullsize; ++i) {
            STACK::operator >>(trans);
            s2 << trans;
        }
    }

    STACK::operator <<(e);
    return *this;
}

QUEUE &QUEUE::operator >>(int &e) {
    if(!(STACK::operator int() + s2.operator int())) throw std::logic_error("dequeue failed, empty queue");
    if (int(s2)) {
        s2 >> e;
    } else {
        int trans;
        int cursize = STACK::operator int();
        for (int i = 0; i < cursize - 1; ++i) {
            STACK::operator >>(trans);
            s2 << trans;
        }
        STACK::operator >>(e);
    }
    return *this;
}

QUEUE &QUEUE::operator =(const QUEUE &s) {
    STACK::operator=(static_cast<STACK>(s));
    s2 = s.s2;
    return *this;
}

void QUEUE::print() const {


    for (int i = 0; i < int(s2); ++i) {
        if (i)  cout << "  ";
        cout << s2[int(s2) - i - 1];
    }

    if (int(s2) && STACK::operator int())   cout << "  ";

    for (int i = 0; i < STACK::operator int(); ++i) {
        if (i)  cout << "  ";
        cout << STACK::operator [](i);
    }
    cout << flush;
}

QUEUE::~QUEUE() {
    return;
}



bool check_after(int index, const int argc, char** argv){
            string cur_arg= string(argv[index]);
            string next_arg;

            if(index == argc-1){
                throw logic_error("argument not complete");
                return false;
            }else{
                next_arg= string(argv[index+1]);
                if(!((cur_arg=="-C")||(cur_arg=="-c")||(cur_arg=="-A")||(cur_arg=="-a")||(cur_arg=="-N")||(cur_arg=="-n"))){
                    if(next_arg.c_str()[0]=='-'){
                        if((cur_arg=="-o"|| cur_arg=="-O")){
                            throw logic_error("invalid argument");

                        }else if((cur_arg=="-i"|| cur_arg=="-I")){
                            if(next_arg.length()>=2){
                                if(next_arg.c_str()[1]>='0'&&next_arg.c_str()[1]<='9'){
                                    return true;
                                }
                                else{
                                    throw logic_error("invalid argument");
                                }
                            }else{
                                throw logic_error("invalid argument");

                            }
                                //throw logic_error("invalid argument");
                        }else{
                                throw logic_error("invalid argument");
                        }
                    }else{
                        return true;
                    }
                }
                else{
                    return true;
                }

            }
}

int convert(const string &param, int &true_param){
    try{
            true_param=atoi(param.c_str());
            if(param.c_str()[0]=='-' && (param.c_str()[1]<'0'||param.c_str()[1]>'9')){
                throw invalid_argument("reach the end of the sub-param list");
            }
        } catch(out_of_range toolong){
            std::cerr<<"argument not valid or reach the end of the param list\n";
            return -1;
        }catch(invalid_argument inv){
            std::cerr<<"reach the end of the sub-param list\n";
            return 0;
        }
            return 1;

}

int PrimeCheck(int num){
    if(num==1) return 0;
    for(int i=2; i*i<=num; i++){
        if(num%i==0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if(argc!=1){
    string argument;
    int arg_param=0;
    int if_valid=1;
    QUEUE *queue = nullptr;

    ofstream outputfile;
    outputfile.open("U201614808_4.TXT");

    auto backup=std::cout.rdbuf();
    auto outbuf=outputfile.rdbuf();
    std::cout.rdbuf(outbuf);

    try{
        for(int i=1; i<argc; i++){
            argument = string(argv[i]);
            if((argument=="-s") || (argument=="-S")){
                    std::cout<<"S";
                    if(check_after(i, argc,argv)){
                        i++;
                        argument=string(argv[i]);
                        if_valid=convert(argument, arg_param);
                        if(if_valid){
                            queue= new QUEUE(arg_param);
                            std::cout<<"  "<<arg_param;
                        }else{
                            if(if_valid==-1){
                                throw logic_error("invalid parameter");
                            }

                        }
                    }else{
                        //throw logic_error("invalid argument");
                    }

            } else if((argument=="-i") || (argument=="-I")){
                std::cout<<"  I";
                if(check_after(i, argc,argv)){
                for(++i; i<argc; i++){
                    argument=string(argv[i]);
                    if(!(if_valid=convert(argument, arg_param))){
                        break;
                    }
                    else{
                            (*queue)<<arg_param;
                    }
                }
                if(if_valid==-1) throw logic_error("invalid parameter");
                if(i<argc){
                    i--;

                }
                if(int(*queue)){
                    std::cout<<"  ";
                    queue->print();
                }
                }
            } else if((argument=="-o") || (argument=="-O")){
                std::cout<<"  O";
                if(check_after(i, argc, argv)){
                        i++;
                        argument=string(argv[i]);
                        if_valid=convert(argument, arg_param);
                        if(if_valid){
                            int abandon;
                            for(int j=0; j<arg_param; j++){
                                //stack->pop(abandon);
                                (*queue)>>(abandon);
                            }
                            if(int(*queue)){
                                std::cout<<"  ";
                                queue->print();
                            }


                        }else{
                            if(if_valid==-1){
                                throw logic_error("invalid parameter");
                            }

                        }
                    } else{
                        throw logic_error("invalid argument");
                    }

            } else if((argument=="-c") || (argument=="-C")){
                QUEUE* NewQueue=new QUEUE(*queue);
                delete queue;
                queue= NewQueue;
                std::cout<<"  C";
                if(int(*queue)){
                    std::cout<<"  ";
                    queue->print();
                }

            } else if((argument=="-a") || (argument=="-A")){
                std::cout<<"  A";
                if(check_after(i, argc, argv)){
                    i++;
                    argument=string(argv[i]);
                    if_valid=convert(argument, arg_param);
                    if(if_valid){
                        QUEUE* NewQueue=new QUEUE(arg_param);
                        //NewStack->assign(*stack);
                        *NewQueue=*queue;
                        delete queue;
                        queue= NewQueue;

                        if(int(*queue)){
                            std::cout<<"  ";
                            queue->print();
                        }


                    }else{
                        if(if_valid==-1){
                            throw logic_error("invalid parameter");
                        }

                    }


                }else{
                    throw logic_error("invalid argument");
                }

            } else if((argument=="-n") || (argument=="-N")){
                std::cout<<"  N";
                std::cout<<"  "<<int(*queue);

            } else if((argument=="-g") || (argument=="-G")){
                std::cout<<"  G";
                if(check_after(i, argc, argv)){
                    i++;
                    argument=string(argv[i]);
                    if_valid=convert(argument, arg_param);
                    if(if_valid){
                        std::cout<<"  "<<(*queue)[arg_param];

                    }else{
                        if(if_valid==-1){
                            throw logic_error("invalid parameter");
                        }

                    }


                }else{
                    throw logic_error("invalid argument");
                }


            }else{
                throw logic_error("unsupported argument");
            }


        }
    }catch(logic_error error_caught){
        std::cout<<"  E";
        std::cerr<<error_caught.what()<<endl;
        cout.rdbuf(backup);
        outputfile.close();
        return 1;
    }catch(bad_alloc error_caught){
        std::cout<<"  E";
        std::cerr<<error_caught.what()<<endl;
        cout.rdbuf(backup);
        outputfile.close();
        return 1;
    }

    cout.rdbuf(backup);
    outputfile.close();
    //getchar();
    return 0;
    }
    else{
        int man_num, woman_num, m, f;
        while (true) {
            cout << "Enter the number of gentleman: " << flush;
            cin  >> man_num;
            if (!PrimeCheck(man_num)) {
                cout << man_num<<" is not a prime number." << endl;
            } else{
                break;
            }

        }
         while (true) {
            cout << "Enter the number of ladies: " << flush;
            cin  >> woman_num;
            if (!PrimeCheck(woman_num)) {
                cout << woman_num <<" is not a prime number." << endl;
            } else if(man_num==woman_num){
                cout << "The number of gentleman should not be equal to the number of ladies." << endl;
            }else{
                break;
            }

        }

        while (true) {
            cout << "Enter m (m>=1): " << flush;
            cin >> m;
            if (m <= 0 || m > man_num) {
                cout << "invalid m, out of range(" <<man_num<<")"<< endl;
            } else{
                break;
            }
        }

        while (true) {
            cout << "Enter f (f>=1): " << flush;
            cin >> f;
            if (f <= 0 || f > woman_num) {
                cout << "invalid f, out of range(" << woman_num<<")"<<endl;
            } else{
                break;
            }
        }

        QUEUE ManQueue(man_num);
        QUEUE WomanQueue(woman_num);
        int mancur, womancur, counter=1;

        for(int i=0;i<man_num;i++){
            ManQueue<<(i+1);
        }
        for(int i=0;i<woman_num;i++){
            WomanQueue<<(i+1);
        }

        while(1){
            ManQueue>>mancur;
            WomanQueue>>womancur;
            if(mancur==m && womancur==f){
                cout<< "man m and woman f met at round "<<counter<<endl;
                break;
            }
            ManQueue<<mancur;
            WomanQueue<<womancur;
            counter++;
        }
        return 0;

    }
}
