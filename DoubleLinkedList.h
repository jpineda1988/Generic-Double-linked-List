#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <iostream>
using std::istream;
using std::ostream;

typedef void* DataPtr;
struct DataNode
{
    DataPtr data;
    int count, index;
    DataNode *next, *back;
    DataNode(DataPtr d, int qty);
    DataNode();
    DataNode(const DataNode&);
    DataNode& operator =(const DataNode&);
};

typedef DataNode* AnyPtr;

class DoubleLinkedList
{
    public:
        /** Default constructor */
        DoubleLinkedList(int qty);
        DoubleLinkedList();
        /** Default destructor */
        virtual ~DoubleLinkedList();
        /** Copy constructor
         *  \param other Object to copy from
         */
        DoubleLinkedList(const DoubleLinkedList& other);
        bool isEmpty() const;
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        DoubleLinkedList& operator=(const DoubleLinkedList& other);
        friend istream& operator >>(istream& read, DoubleLinkedList& list);
        friend ostream& operator <<(ostream& print, const DoubleLinkedList& list);
    protected:
        int dataCount(DataPtr data);
        bool dataFind(DataPtr data);
        void dataInsert(DataPtr data, int qty);
        void dataRemoval(DataPtr data, int qty);
        DataPtr findData(DataPtr data);
        virtual bool lessThan(DataPtr data, DataPtr data2) = 0;
        virtual bool greaterThan(DataPtr data, DataPtr data2) = 0;
        virtual bool equalTo(DataPtr data, DataPtr data2) = 0;
        virtual void destroyData(DataPtr& data);
        virtual istream& readData(istream& in) = 0;
        virtual ostream& printData(ostream& out) = 0;
    private:
        AnyPtr head, middle, end; //!< Member variable "root"
        DataPtr binarySearch(DataPtr data, const AnyPtr& begin, const AnyPtr& mid, const AnyPtr& last);
        void calculateMiddle(const AnyPtr& begin, const AnyPtr& last);
        void updateIndex(const AnyPtr& update);
        void deleteList();
        void copyList(const DoubleLinkedList& list);
};

#endif // DOUBLELINKEDLIST_H
