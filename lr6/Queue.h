#pragma once

#include "List.h"

#include "GameRecord.h"

template <typename T=GameRecord>
class Queue
{
public:
	Queue();
	Queue(T firstRecord);
	Queue(List<T> initList);
	~Queue();
	bool push(T newElem);
	T pop();
	T findElemByGenre(string genre);
	bool clearQueue();

	void operator+=(T newRecord);
	Queue<T>& operator--();
	Queue<T> operator--(int);

	template <typename V>
	friend Queue getRecordsYearsBefore(Queue<V> checkedQueue, int beforeYear);

	template <typename V>
	friend void printQueue(Queue<V>& queueForPrinting);
	//
	template <typename V>
	friend ostream& operator << (ostream& os, Queue<V>& outQueue);
	
	template <typename V>
	friend istream& operator >> (std::istream& in, Queue<V>& inQueue);

	void readFromBinary(string fname);
	void writeToBinary(string fname);
	void changeStringBinary(int index, T changedRecord, string fname);
	void deleteStringFromBinary(int index, string fname);

	T findFirstGameYearBinary(string fname);

	//
	void swap(int indexF, int indexS);
	void sortQueue(bool asc = true);

	////
	bool writeToFile(string fname);
	bool readFromFile(string fname);

private:
	List<T> queueElems;
};


template <typename T>
Queue<T>::Queue()
	:queueElems{ List<T>() }
{}

template <typename T>
Queue<T>::Queue(T firstRecord)
	:queueElems{ List<T>(firstRecord) }
{}

template <typename T>
Queue<T>::Queue(List<T> initList)
	:queueElems{ initList }
{}

template <typename T>
Queue<T>::~Queue()
{}

template <typename T>
bool Queue<T>::clearQueue()
{
	this->queueElems.clearList();
	return true;
}

template <typename T>
bool Queue<T>::push(T newElem)
{
	this->queueElems.insertBefore(newElem, 0);
	return true;
}

template <typename T>
T Queue<T>::pop()
{
	T retVal = T();
	retVal = this->queueElems.getElement(this->queueElems.length() - 1);
	this->queueElems.deleteFrom(this->queueElems.length() - 1);
	return retVal;
}

template <typename T>
T Queue<T>::findElemByGenre(string genre)
{
	T tmpRecord;
	T retVal;
	List<T> tmpList = List<T>();
	for (int i = 0; i < this->queueElems.length(); i++) {
		tmpRecord = this->pop();
		if (tmpRecord.genre == genre) {
			retVal = tmpRecord;
		}
		tmpList.insertBefore(tmpRecord, tmpList.length());
	}
	this->queueElems = tmpList;
	return retVal;
}

template <typename T>
void Queue<T>::operator+=(T newRecord)
{
	this->push(newRecord);
}

template <typename T>
Queue<T>& Queue<T>::operator--()
{
	this->pop();
	return *this;
}

template <typename T>
Queue<T> Queue<T>::operator--(int) {
	--*this;
	return *this;
}

template <typename T>
void Queue<T>::readFromBinary(string fname)
{
	this->queueElems.readFromBinary(fname);
}

template <typename T>
void Queue<T>::writeToBinary(string fname)
{
	this->queueElems.writeToBinary(fname);
}

template <typename T>
void Queue<T>::changeStringBinary(int index, T changedRecord, string fname)
{
	this->queueElems.changeStringBinary(index, changedRecord, fname);
}

template <typename T>
void Queue<T>::deleteStringFromBinary(int index, string fname)
{
	this->queueElems.deleteStringFromBinary(index, fname);
}

template <typename T>
T Queue<T>::findFirstGameYearBinary(string fname)
{
	return this->queueElems.findFirstGameYearBinary(fname);
}

template <typename V>
void printQueue(Queue<V>& queueForPrinting)
{
	printList(queueForPrinting.queueElems);
}

template <typename V>
ostream& operator<<(ostream& os, Queue<V>& outQueue)
{
	os << outQueue.queueElems;
	return os;
}

template <typename V>
istream& operator>>(std::istream& in, Queue<V>& inQueue)
{
	in >> inQueue.queueElems;
	return in;
}

template <typename V>
Queue<V> getRecordsYearsBefore(Queue<V> checkedQueue, int beforeYear) {
	List<V> tmpList = getRecordsYearsBefore(checkedQueue.queueElems, beforeYear);
	return Queue<V>(tmpList);
}

template <typename T>
void Queue<T>::swap(int indexF, int indexS) {
	this->queueElems->swap(indexF, indexS);
}

template <typename T>
void Queue<T>::sortQueue(bool asc) {
	this->queueElems.sortList(asc);
}

template <typename T>
bool Queue<T>::writeToFile(string fname) {
	return this->queueElems.writeToFile(fname);
}

template <typename T>
bool Queue<T>::readFromFile(string fname)
{
	return this->queueElems.readFromFile(fname);
}