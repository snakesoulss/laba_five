#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include <iostream>

/*�������� ����������� ����������, ����� ������� ����������� ������

*/


template <typedef T>
class LinkedList {
public:
    LinkedList(/*��� �������� �������*/){} //����������� ��������
    virtual void Push() const = 0;
    virtual void Pop()const = 0;
    virtual void GetFront() const = 0;
    virtual void isEmpty() const = 0;
    virtual void Size() = 0;
    // + �������� ������������ �� ������ �� ������
protected:
    struct Node{

        Node(){} //����������� ��������
    };
    virtual void Print() const = 0;

};

template <typedef T>
class Stack: public LinkedList<T>{

    //����������� ������� ������
    //�����������(?) �����������
    //����������� � �������������
    Stack(/*��� �������� �������*/): LinkedList(/*��� �������� �������*/){}
    Stack(const Stack &s){} //����������� �����������
};

template <typedef T>
class Queue: public LinkedList<T>{

    //����������� ������� ������
    //�����������(?) �����������
    //����������� � �������������
    Queue(/*��� �������� �������*/): LinkedList(/*��� �������� �������*/){}
    Queue(const Queue &g){} //����������� �����������
};
#endif // LINKEDLIST_H_INCLUDED
