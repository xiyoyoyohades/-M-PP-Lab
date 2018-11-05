#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CPPEX1.h"

using namespace std;


void initSTACK(STACK *const p, int m){
    p->elems = (int*)malloc(m*sizeof(int));
    p->max = m;
    p->pos = 0;
}

void initSTACK(STACK *const p, const STACK &s){
    p->elems = (int*)malloc(sizeof(int)*s.max);
    p->pos = s.pos;
    for(int i=0; i<s.pos; i++){
        p->elems[i] = s.elems[i];
    }
}

int size (const STACK *const p){
    return p->max;
}

int howMany (const STACK *const p){
    return p->pos;
}

int getelem (const STACK *const p, int x){

    if(x >= p->max){
        throw logic_error("index exceeds max value");
    }
    return p->elems[x];
}

STACK *const push(STACK *const p, int e){
    if(p->pos == p->max){
            return NULL;
    }
    p->elems[p->pos] = e;
    (p->pos)++;
    return p;
}

STACK *const pop(STACK *const p, int &e){
    if(!(p->pos)){
        return NULL;
    }
    (p->pos)--;
    e = p->elems[p->pos];
    return p;
}

STACK *const assign(STACK*const p, const STACK&s){
    p->max = s.max;
    p->pos = s.pos;
    free(p->elems);
    p->elems = (int*)malloc(sizeof(int)*p->max);
    for(int i=0; i<s.pos; i++){
        p->elems[i] = s.elems[i];
    }
    return p;
}

void print(const STACK *const p){
    for(int i=0; i < p->pos; i++){
        if (i != p->pos-1){
            printf("%d  ",p->elems[i]);
        }else{
            printf("%d",p->elems[i]);
        }
    }
}

void destroySTACK(STACK*const p){
    free(p->elems);
    p->elems=NULL;
    p->max = 0;
    p->pos = 0;
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
                            if(strlen(next_arg.c_str())>=2){
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
            fprintf(stderr, "argument not valid or reach the end of the param list\n");
            return -1;
        }catch(invalid_argument inv){
            fprintf(stderr, "reach the end of the sub-param list\n");
            return 0;
        }
            return 1;

}


int main(int argc, char *argv[])
{
    string argument;
    int arg_param=0;
    int if_valid;
    STACK *stack = new STACK;

    freopen("U201614808_1.TXT","w",stdout);


    try{
        for(int i=1; i<argc; i++){
            argument = string(argv[i]);
            if((argument=="-s") || (argument=="-S")){
                    if(check_after(i, argc,argv)){
                        i++;
                        argument=string(argv[i]);
                        if_valid=convert(argument, arg_param);
                        if(if_valid){
                            initSTACK(stack, arg_param);
                            printf("S  %d", arg_param);
                        }else{
                            if(if_valid==-1){
                                throw logic_error("invalid parameter");
                            }

                        }
                    }else{
                        //throw logic_error("invalid argument");
                    }

            } else if((argument=="-i") || (argument=="-I")){
                printf("  I");
                if(check_after(i, argc,argv)){
                for(++i; i<argc; i++){
                    argument=string(argv[i]);
                    if(!(if_valid=convert(argument, arg_param))){
                        break;
                    }
                    else{
                            if(!push(stack, arg_param)){
                                throw logic_error("push failure: full stack");
                            }
                    }
                }
                if(if_valid==-1) throw logic_error("invalid parameter");
                if(i<argc){
                    i--;

                }
                if(howMany(stack)){
                    printf("  ");
                    print(stack);
                }
                }
            } else if((argument=="-o") || (argument=="-O")){
                printf("  O");
                if(check_after(i, argc, argv)){
                        i++;
                        argument=string(argv[i]);
                        if_valid=convert(argument, arg_param);
                        if(if_valid){
                            int abandon;
                            for(int j=0; j<arg_param; j++){
                                if(!pop(stack, abandon)){
                                    throw logic_error("pop failure: empty stack");
                                }

                            }
                            if(howMany(stack)){
                                printf("  ");
                                print(stack);
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
                STACK* NewStack=new STACK;
                initSTACK(NewStack, *stack);
                stack= NewStack;
                printf("  C");
                if(howMany(stack)){
                    printf("  ");
                    print(stack);
                }

            } else if((argument=="-a") || (argument=="-A")){
                printf("  A");
                if(check_after(i, argc, argv)){
                    i++;
                    argument=string(argv[i]);
                    if_valid=convert(argument, arg_param);
                    if(if_valid){
                        STACK* NewStack=new STACK;
                        initSTACK(NewStack, arg_param);
                        assign(NewStack, *stack);
                        stack= NewStack;

                        if(howMany(stack)){
                            printf("  ");
                            print(stack);
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
                printf("  N");
                printf("  %d",howMany(stack));

            } else if((argument=="-g") || (argument=="-G")){
                printf("  G");
                if(check_after(i, argc, argv)){
                    i++;
                    argument=string(argv[i]);
                    if_valid=convert(argument, arg_param);
                    if(if_valid){
                        printf("  %d", getelem(stack, arg_param));

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
        printf("  E");
        fprintf(stderr, "%s\n", error_caught.what());
        fclose(stdout);
        return 1;
    }

    fclose(stdout);
    //getchar();
    return 0;
}
