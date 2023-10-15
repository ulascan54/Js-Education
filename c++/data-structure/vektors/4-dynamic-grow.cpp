#include <iostream>
using namespace std;

template <class T>
class vectore
{
    T *data;
    int cap;      // dizi boyutu
    int index;    // sıradaki elemanın indexi
    void growth() // dinamik büyüme
    {
        if (size() >= capacity())
        {
            cap *= 2;
            T *tmp = new T[cap];
            for (int i = 0; i < size(); i++)
            {
                tmp[i] = data[i];
            }
            delete[] data;
            data = tmp;
        }
    }

public:
    vectore() : data(NULL), index(0), cap(1)
    {
        data = new T[cap];
    }
    int size() const { return index; }
    int capacity() const { return cap; }

    void push_back(const T &value)
    {
        growth();
        data[index++] = value;
    }

    void pop_back() { index--; }

    bool isEmpty() const
    {
        return (size() == 0);
    }

    T front() const
    {
        if (isEmpty())
            throw "Error: vector is empty";
        return data[0];
    }

    T back() const
    {
        if (isEmpty())
            throw "Error: vector is empty";
        return data[index - 1];
    }
};

int main()
{
    try
    {
        vectore<int> v;
        cout << v.size() << " - ";
        cout << v.capacity() << endl;

        v.push_back(2);
        cout << v.size() << " - ";
        cout << v.capacity() << endl;

        v.push_back(5);
        cout << v.size() << " - ";
        cout << v.capacity() << endl;

        v.push_back(10);
        cout << v.size() << " - ";
        cout << v.capacity() << endl;

        v.push_back(50);
        cout << v.size() << " - ";
        cout << v.capacity() << endl;

        cout << v.front() << endl;
        cout << v.back() << endl;
    }
    catch (const char *exception)
    {
        cout << exception << endl;
    }

    return 0;
}