#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include <iostream>

/*дописать виртуальный деструктор, чтобы удал€ть производные классы

*/


template <typedef T>
class LinkedList {
public:
    LinkedList(/*тут дописать объекты*/){} //конструктор дописать
    virtual void Push() const = 0;
    virtual void Pop()const = 0;
    virtual void GetFront() const = 0;
    virtual void isEmpty() const = 0;
    virtual void Size() = 0;
    // + операци€ присваивани€ из ссылки на список
protected:
    struct Node{

        Node(){} //конструктор дописать
    };
    virtual void Print() const = 0;

};

template <typedef T>
class Stack: public LinkedList<T>{

    //конструктор пустого списка
    //конструктор(?) перемещени€
    //конструктор с наследованием
    Stack(/*тут дописать объекты*/): LinkedList(/*тут дописать объекты*/){}
    Stack(const Stack &s){} //конструктор копировани€
};

template <typedef T>
class Queue: public LinkedList<T>{

    //конструктор пустого списка
    //конструктор(?) перемещени€
    //конструктор с наследованием
    Queue(/*тут дописать объекты*/): LinkedList(/*тут дописать объекты*/){}
    Queue(const Queue &g){} //конструктор копировани€
};
#endif // LINKEDLIST_H_INCLUDED
