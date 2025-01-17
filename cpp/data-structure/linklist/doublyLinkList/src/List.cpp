#include <iostream>
#include <iomanip>
#include <exception>
#include "List.h"
using namespace std;

List::List()
{
    head = NULL;
}

void List::addNewElement(int data)
{
    Node *tmp = new Node(data);
    if (head == NULL)
    {
        head = tmp;
    }
    else
    {
        Node *cur = head;

        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = tmp;
        tmp->prev = cur;
    }
}

ostream &operator<<(ostream &os, List &list)
{
    os << setw(15) << "düğüm adresi" << setw(15) << "veri" << setw(15) << "önceki" << setw(15) << "sonraki" << endl;

    Node *tmp = list.head;

    while (tmp != NULL)
    {
        os << setw(15) << tmp << setw(15) << tmp->data << setw(15) << tmp->prev << setw(15) << tmp->next << endl;
        tmp = tmp->next;
    }
    os << "------------------------" << endl;

    return os;
}

void List::deleteElement()
{
    if (head == nullptr)
        return;
    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }
    else
    {
        Node *tmp = head;

        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        tmp->prev->next = nullptr;
        delete tmp;
    }
}

void List::deleteElement(int index)
{
    Node *tmp = getNode(index);
    if (!tmp)
        return;
    else
    {
        Node *tmpNext = tmp->next;
        Node *tmpPrev = tmp->prev;
        if (tmpNext)
            tmpNext->prev = tmpPrev;
        if (tmpPrev)
            tmpPrev->next = tmpNext;
        else
            head = tmpNext;
        delete tmp;
    }
}

List::~List()
{
    Node *tmp = head;
    while (tmp != 0)
    {
        Node *ditem = tmp;
        tmp = tmp->next;
        delete ditem;
    }
}

int List::getHeadValue()
{
    if (head != nullptr)
    {
        return head->data;
    }
    else
    {
        throw std::out_of_range("List::getHeadValue(): This List is empty right now!");
    }
}

Node *List::getNode(int index)
{

    Node *tmp = head;
    while (index >= 0 && tmp != NULL)
    {
        if (index == 0)
            return tmp;

        tmp = tmp->next;
        index--;
    }
    return NULL;
}

void List::addToFront(int index, int data)
{
    Node *tmp = getNode(index);
    if (tmp)
    {
        Node *tmpPrev = tmp->prev;
        Node *item = new Node(data);
        tmp->prev = item;
        item->next = tmp;
        item->prev = tmpPrev;
        if (tmpPrev)
        {
            tmpPrev->next = item;
        }
        else
        {
            head = item;
        }
    }
}