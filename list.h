#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <iostream>
#include <stdexcept>

template <typename T>
class List
{
public:
    List();
    List(const List& other);
    List(List&& other) noexcept;
    virtual ~List();

    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;

    virtual void Push(const T& value) = 0;
    virtual void Pop() = 0;
    virtual T& GetFront() = 0;
    virtual const T& GetFront() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual size_t Size() const = 0;

protected:
    struct Node
    {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t list_size;
    virtual void Print() const;
    void ProtectedCopyFrom(const List& other);


private:
    void Clear();
    void CopyFrom(const List& other);

};


template <typename T>
List<T>::List() : head(nullptr), list_size(0) {}

template <typename T>
List<T>::List(const List& other) : head(nullptr), list_size(0)
{
    CopyFrom(other);
}

template <typename T>
List<T>::List(List&& other) noexcept : head(other.head), list_size(other.list_size)
{
    other.head = nullptr;
    other.list_size = 0;
}

template <typename T>
List<T>::~List()
{
    Clear();
}

template <typename T>
List<T>& List<T>::operator=(const List& other)
{
    if (this != &other)
    {
        Clear();
        CopyFrom(other);
    }
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept
{
    if (this != &other)
    {
        Clear();
        head = other.head;
        list_size = other.list_size;
        other.head = nullptr;
        other.list_size = 0;
    }
    return *this;
}

template <typename T>
void List<T>::Print() const
{
    Node* temp = head;
    while (temp)
    {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}


template <typename T>
void List<T>::CopyFrom(const List& other)
{
    if (other.head == nullptr) return;
    Node* temp = other.head;
    Node* new_node = new Node(temp->data);
    head = new_node;
    temp = temp->next;

    while (temp)
    {
        new_node->next = new Node(temp->data);
        new_node = new_node->next;
        temp = temp->next;
    }
    list_size = other.list_size;
}

template <typename T>
void List<T>::ProtectedCopyFrom(const List& other)
{
    CopyFrom(other);
}

template <typename T>
void List<T>::Clear()
{
    while (head)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    list_size = 0;
}

template <typename T>
class Stack : public List<T>
{
public:
    Stack();
    ~ Stack();
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    void Push(const T& value) override;
    void Print() const override;
    void Pop() override;
    T& GetFront() override;
    const T& GetFront() const override;
    bool IsEmpty() const override;
    size_t Size() const override;


private:
    using List<T>::head;
    using List<T>::list_size;
    void CopyFrom(const Stack& other);
    void Clear();

};

template <typename T>
class Queue : public List<T>
{
public:
    Queue();
    ~Queue();
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;

    void Push(const T& value) override;
    void Print() const override;
    void Pop() override;
    T& GetFront() override;
    const T& GetFront() const override;
    bool IsEmpty() const override;
    size_t Size() const override;
private:
    typename List<T>::Node* tail;
    using List<T>::head;
    using List<T>::list_size;

    void CopyFrom(const Queue<T>& other);
    void Clear();
};


//Stack
template <typename T>
Stack<T>::Stack() : List<T>() {}

template <typename T>
Stack<T>::Stack(const Stack& other) : List<T>(other) {}

template <typename T>
Stack<T>::Stack(Stack&& other) noexcept : List<T>(std::move(other)) {}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other)
{
    if (this != &other)
    {
        List<T>::operator=(other);
    }
    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept
{
    if (this != &other)
    {
        List<T>::operator=(std::move(other));
    }
    return *this;
}

template <typename T>
Stack<T>::~Stack() {}

template <typename T>
void Stack<T>::Push(const T& value)
{
    typename List<T>::Node* new_node = new typename List<T>::Node(value);
    new_node->next = this->head;
    this->head = new_node;
    this->list_size++;
}

template <typename T>
void Stack<T>::Pop()
{
    if (IsEmpty())
    {
        throw std::runtime_error("Stack is empty");
    }
    typename List<T>::Node* temp = this->head;
    this->head = this->head->next;
    delete temp;
    this->list_size--;
}

template <typename T>
T& Stack<T>::GetFront()
{
    if (IsEmpty()) throw std::runtime_error("Stack is empty");
    return this->head->data;
}

template <typename T>
const T& Stack<T>::GetFront() const
{
    if (IsEmpty()) throw std::runtime_error("Stack is empty");
    return this->head->data;
}

template <typename T>
bool Stack<T>::IsEmpty() const
{
    return this->head == nullptr;
}

template <typename T>
size_t Stack<T>::Size() const
{
    return this->list_size;
}

template <typename T>
void Stack<T>::Print() const
{
    typename List<T>::Node* temp = head;
    while (temp)
    {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}


//Queue

template <typename T>
Queue<T>::Queue() : List<T>(), tail(nullptr){}

template <typename T>
Queue<T>::Queue(const Queue& other) : List<T>(other), tail(nullptr)
{
    if (other.head == nullptr)
    {
        return;
    }
    typename List<T>::Node* temp = this->head;
    while (temp->next)
    {
        temp = temp->next;
    }
    tail = temp;
}

template <typename T>
Queue<T>::Queue(Queue&& other) noexcept : List<T>(std::move(other)), tail(other.tail)
{
    other.tail = nullptr;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other)
{
    if (this != &other)
    {
        List<T>::operator=(other);

        typename List<T>::Node* temp = this->head;
        while (temp && temp->next)
        {
            temp = temp->next;
        }
        tail = temp;
    }
    return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept
{
    if (this != &other)
    {
        List<T>::operator=(std::move(other));
        tail = other.tail;
        other.tail = nullptr;
    }
    return *this;
}

template <typename T>
Queue<T>::~Queue() {}

template <typename T>
void Queue<T>::Push(const T& value)
{
    typename List<T>::Node* new_node = new typename List<T>::Node(value);
    if (this->IsEmpty())
    {
        this->head = new_node;
    }
    else
    {
        tail->next = new_node;
    }
    tail = new_node;
    this->list_size++;
}

template <typename T>
void Queue<T>::Pop()
{
    if (IsEmpty())
    {
        throw std::runtime_error("Queue is empty");
    }
    typename List<T>::Node* temp = this->head;
    this->head = this->head->next;
    delete temp;

    if (this->head == nullptr)
    {
        tail = nullptr;
    }

    this->list_size--;
}

template <typename T>
T& Queue<T>::GetFront()
{
    if (IsEmpty()) throw std::runtime_error("Queue is empty");
    return this->head->data;
}
template <typename T>
const T& Queue<T>::GetFront() const
{
    if (IsEmpty()) throw std::runtime_error("Queue is empty");
    return this->head->data;
}

template <typename T>
bool Queue<T>::IsEmpty() const
{
    return this->head == nullptr;
}

template <typename T>
size_t Queue<T>::Size() const
{
    return this->list_size;
}

template <typename T>
void Queue<T>::Print() const
{
    typename List<T>::Node* temp = head;
    while (temp)
    {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

template <typename T>
void Queue<T>::CopyFrom(const Queue<T>& other)
{
    this->ProtectedCopyFrom(other);
    typename List<T>::Node* temp = this->head;
    while (temp && temp->next)
    {
        temp = temp->next;
    }
    tail = temp;
}

#endif // LIST_H_INCLUDED
