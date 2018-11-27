
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <stdexcept>
#include "CPPEX3.hpp"

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


int main(int argc, char *argv[])
{
    string argument;
    int arg_param=0;
    int if_valid=1;
    STACK *stack = nullptr;

    ofstream outputfile;
    outputfile.open("U201614808_3.TXT");

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
                            stack= new STACK(arg_param);
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
                            //stack->push(arg_param);
                            (*stack)<<arg_param;
                    }
                }
                if(if_valid==-1) throw logic_error("invalid parameter");
                if(i<argc){
                    i--;

                }
                if(int(*stack)){
                    std::cout<<"  ";
                    stack->print();
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
                                (*stack)>>(abandon);
                            }
                            if(int(*stack)){
                                std::cout<<"  ";
                                stack->print();
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
                STACK* NewStack=new STACK(*stack);
                delete stack;
                stack= NewStack;
                std::cout<<"  C";
                if(int(*stack)){
                    std::cout<<"  ";
                    stack->print();
                }

            } else if((argument=="-a") || (argument=="-A")){
                std::cout<<"  A";
                if(check_after(i, argc, argv)){
                    i++;
                    argument=string(argv[i]);
                    if_valid=convert(argument, arg_param);
                    if(if_valid){
                        STACK* NewStack=new STACK(arg_param);
                        //NewStack->assign(*stack);
                        *NewStack=*stack;
                        delete stack;
                        stack= NewStack;

                        if(int(*stack)){
                            std::cout<<"  ";
                            stack->print();
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
                std::cout<<"  "<<int(*stack);

            } else if((argument=="-g") || (argument=="-G")){
                std::cout<<"  G";
                if(check_after(i, argc, argv)){
                    i++;
                    argument=string(argv[i]);
                    if_valid=convert(argument, arg_param);
                    if(if_valid){
                        //std::cout<<"  "<<stack->getelem(arg_param);
                        std::cout<<"  "<<(*stack)[arg_param];

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
