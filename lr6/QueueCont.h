#pragma once

#include "ListCont.h"

#include "GameRecord.h"

template <typename T=GameRecord>
class QueueCont
{
public:
	QueueCont();
	QueueCont(T firstRecord);
	QueueCont(ListCont<T> initList);
	~QueueCont();
	bool push(T newElem);
	T pop();
	T findElemByGenre(string genre);
	bool clearQueue();

	void operator+=(T newRecord);
	QueueCont<T>& operator--();
	QueueCont<T> operator--(int);

	template <typename V>
	friend QueueCont getRecordsYearsBefore(QueueCont<V> checkedQueueCont, int beforeYear);

	template <typename V>
	friend void printQueue(QueueCont<V>& QueueContForPrinting);
	//
	template <typename V>
	friend ostream& operator << (ostream& os, QueueCont<V>& outQueueCont);
	
	template <typename V>
	friend istream& operator >> (std::istream& in, QueueCont<V>& inQueueCont);

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
	ListCont<T> QueueContElems;
};


template <typename T>
QueueCont<T>::QueueCont()
	:QueueContElems{ ListCont<T>() }
{}

template <typename T>
QueueCont<T>::QueueCont(T firstRecord)
	:QueueContElems{ ListCont<T>(firstRecord) }
{}

template <typename T>
QueueCont<T>::QueueCont(ListCont<T> initList)
	:QueueContElems{ initList }
{}

template <typename T>
QueueCont<T>::~QueueCont()
{}

template <typename T>
bool QueueCont<T>::clearQueue()
{
	this->QueueContElems.clearList();
	return true;
}

template <typename T>
bool QueueCont<T>::push(T newElem)
{
	this->QueueContElems.insertBefore(newElem, 0);
	return true;
}

template <typename T>
T QueueCont<T>::pop()
{
	T retVal = T();
	retVal = this->QueueContElems.getElement(this->QueueContElems.length() - 1);
	this->QueueContElems.deleteFrom(this->QueueContElems.length() - 1);
	return retVal;
}

template <typename T>
T QueueCont<T>::findElemByGenre(string genre)
{
	T tmpRecord;
	T retVal;
	ListCont<T> tmpList = ListCont<T>();
	for (int i = 0; i < this->QueueContElems.length(); i++) {
		tmpRecord = this->pop();
		if (tmpRecord.genre == genre) {
			retVal = tmpRecord;
		}
		tmpList.insertBefore(tmpRecord, tmpList.length());
	}
	this->QueueContElems = tmpList;
	return retVal;
}

template <typename T>
void QueueCont<T>::operator+=(T newRecord)
{
	this->push(newRecord);
}

template <typename T>
QueueCont<T>& QueueCont<T>::operator--()
{
	this->pop();
	return *this;
}

template <typename T>
QueueCont<T> QueueCont<T>::operator--(int) {
	--*this;
	return *this;
}

template <typename T>
void QueueCont<T>::readFromBinary(string fname)
{
	this->QueueContElems.readFromBinary(fname);
}

template <typename T>
void QueueCont<T>::writeToBinary(string fname)
{
	this->QueueContElems.writeToBinary(fname);
}

template <typename T>
void QueueCont<T>::changeStringBinary(int index, T changedRecord, string fname)
{
	this->QueueContElems.changeStringBinary(index, changedRecord, fname);
}

template <typename T>
void QueueCont<T>::deleteStringFromBinary(int index, string fname)
{
	this->QueueContElems.deleteStringFromBinary(index, fname);
}

template <typename T>
T QueueCont<T>::findFirstGameYearBinary(string fname)
{
	return this->QueueContElems.findFirstGameYearBinary(fname);
}

template <typename V>
void printQueue(QueueCont<V>& QueueContForPrinting)
{
	printList(QueueContForPrinting.QueueContElems);
}

template <typename V>
ostream& operator<<(ostream& os, QueueCont<V>& outQueueCont)
{
	os << outQueueCont.QueueContElems;
	return os;
}

template <typename V>
istream& operator>>(std::istream& in, QueueCont<V>& inQueueCont)
{
	in >> inQueueCont.QueueContElems;
	return in;
}

template <typename V>
QueueCont<V> getRecordsYearsBefore(QueueCont<V> checkedQueueCont, int beforeYear) {
	ListCont<V> tmpList = getRecordsYearsBefore(checkedQueueCont.QueueContElems, beforeYear);
	return QueueCont<V>(tmpList);
}

template <typename T>
void QueueCont<T>::swap(int indexF, int indexS) {
	this->QueueContElems->swap(indexF, indexS);
}

template <typename T>
void QueueCont<T>::sortQueue(bool asc) {
	this->QueueContElems.sortList(asc);
}

template <typename T>
bool QueueCont<T>::writeToFile(string fname) {
	return this->QueueContElems.writeToFile(fname);
}

template <typename T>
bool QueueCont<T>::readFromFile(string fname)
{
	return this->QueueContElems.readFromFile(fname);
}