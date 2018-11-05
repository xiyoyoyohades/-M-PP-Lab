#ifndef CPPEX1_H_INCLUDED
#define CPPEX1_H_INCLUDED

typedef struct TYPE_STACK{
    int *elems;
    int max;
    int pos;
}STACK;

void initSTACK(STACK *const p, int m);	            //��ʼ��pָ���ջ�����m��Ԫ��
void initSTACK(STACK *const p, const STACK&s);      //��ջs��ʼ��pָ���ջ
int  size (const STACK *const p);		            //����pָ���ջ�����Ԫ�ظ���max
int  howMany (const STACK *const p);	            //����pָ���ջ��ʵ��Ԫ�ظ���pos
int  getelem (const STACK *const p, int x);	        //ȡ�±�x����ջԪ��
STACK *const push(STACK *const p, int e); 	        //��e��ջ��������p
STACK *const pop(STACK *const p, int &e); 	        //��ջ��e��������p
STACK *const assign(STACK*const p, const STACK&s);  //��s��pָ��ջ,������p
void print(const STACK*const p);			        //��ӡpָ���ջ
void destroySTACK(STACK*const p);		            //����pָ���ջ




#endif // CPPEX1_H_INCLUDED
