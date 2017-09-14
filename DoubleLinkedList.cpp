#include "DoubleLinkedList.h"

DataNode::DataNode(DataPtr d, int qty) : data(d), count(qty), index(0), next(nullptr), back(nullptr)
{
}

DataNode::DataNode() : data(nullptr), count(0), index(0), next(nullptr), back(nullptr)
{
}

DoubleLinkedList::DoubleLinkedList(DataPtr data, int qty) : head(nullptr), middle(nullptr), end(nullptr)
{
    head = middle = end = new DataNode(data, qty);
    //ctor
}

DoubleLinkedList::~DoubleLinkedList()
{
    deleteList();
    //dtor
}

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& other) : head(nullptr), middle(nullptr), end(nullptr)
{
    copyList(other);
    //copy ctor
}

bool DoubleLinkedList::isEmpty() const
{
    return head == nullptr;
}

DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    deleteList();
    copyList(rhs);
    //assignment operator
    return *this;
}

istream& operator >>(istream& read, DoubleLinkedList& list)
{
   return list.readData(read);
}

ostream& operator <<(ostream& print, const DoubleLinkedList& list)
{
   return list.printData(print);
}

int DoubleLinkedList::dataCount(DataPtr data)
{
    DataPtr found = binarySearch(data, head, middle, end);
    return (found != nullptr) ? found->count : 0;
}

bool DoubleLinkedList::dataFind(DataPtr data)
{
    DataPtr found = binarySearch(data, head, middle, end);
    return found != nullptr;
}

void DoubleLinkedList::dataInsert(DataPtr data, int qty)
{
    if(head == nullptr)
      head = middle = end = new DataNode(data, qty);
    else
    {
       AnyPtr tempHead = new DataNode, iterator = nullptr, newData = nullptr;
       tempHead->next = head;
       head->back = tempHead;

       for(iterator = tempHead; iterator->next != nullptr; iterator = iterator->next)
       {
           if(lessThan(data, iterator->next->data))
           {
               if(equalTo(data, iterator->data))
                  iterator->count += qty;
               else
               {
                   newData = new DataNode(data, qty);
                   newData->index = iterator->next->index;

                   newData->next = iterator->next;
                   newData->back = iterator;

                   iterator->next->back = newData;
                   iterator->next = newData;

                   upgradeIndex(newData);
               }
               break;
           }
       }

       if(iterator->next == nullptr)
       {
           end->next = new DataNode(data, qty)
           end->next->index = end->index + 1;
           end->next->back = end;
           end = end->next;
       }

       head = tempHead->next;
       head->back = nullptr;
       delete tempHead;
       tempHead = nullptr;
       calculateMiddle(head, end);
    }
}

void DoubleLinkedList::dataRemoval(DataPtr data, int qty)
{
    if(head != nullptr)
    {
        AnyPtr tempHead = new DataNode, iterator = nullptr, dataToRemove = nullptr;
        tempHead->next = head;
        head->back = tempHead;

        for(iterator = tempHead; iterator->next != nullptr; iterator = iterator->next)
        {
            if(equalTo(iterator->next->data, data))
            {
                iterator->next->count -= qty;
                if(iterator->next->count < 1)
                {
                   dataToRemove = iterator->next;

                   dataToRemove->next->back = iterator;
                   iterator->next = dataToRemove->next;

                   destroyData(dataToRemove->data);
                   delete dataToRemove;
                   dataToRemove = nullptr;
                   upgradeIndex(iterator);
                }
                break;
            }
        }


    }
}
