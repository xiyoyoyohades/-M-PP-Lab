#ifndef CPPEX4_HPP_INCLUDED
#define CPPEX4_HPP_INCLUDED
class STACK{
    int  *const  elems;	//�����ڴ����ڴ��ջ��Ԫ��
    const  int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
    int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
STACK(int m);		//��ʼ��ջ�����m��Ԫ��
STACK(const STACK&s); 			//��ջs������ʼ��ջ
virtual int  size ( ) const;			//����ջ�����Ԫ�ظ���max
virtual operator int ( ) const;			//����ջ��ʵ��Ԫ�ظ���pos
virtual int operator[ ] (int x) const;	//ȡ�±�x����ջԪ��
virtual STACK& operator<<(int e); 	//��e��ջ,������ջ
virtual STACK& operator>>(int &e);	//��ջ��e,������ջ
virtual STACK& operator=(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
virtual void print( ) const;			//��ӡջ
virtual ~STACK( );					//����ջ
};

class QUEUE: public STACK{
    STACK  s2;
public:
QUEUE(int m); //ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��
QUEUE(const QUEUE&s); 			//�ö���s������ʼ������
virtual operator int ( ) const;			//���ض��е�ʵ��Ԫ�ظ���
virtual int full ( ) const;		       //���ض����Ƿ�������������1�����򷵻�0
virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ�أ���1��Ԫ���±�Ϊ0
virtual QUEUE& operator<<(int e);  //��e�����,�����ض���
virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
virtual QUEUE& operator=(const QUEUE&s); //��s������,�����ر���ֵ�Ķ���
virtual void print( ) const;			//��ӡ����
virtual ~QUEUE( );					//���ٶ���
};



#endif // CPPEX4_HPP_INCLUDED
