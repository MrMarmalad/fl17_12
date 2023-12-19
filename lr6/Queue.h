#pragma once

#include "List.h"

template <typename T>
class Queue
{
public:
	Queue();
	Queue(T firstRecord);
	Queue(List initList);
	~Queue();
	bool push(T newElem);
	T pop();
	T findElemByGenre(string genre);
	bool clearQueue();

	void operator+=(T newRecord);
	Queue& operator--();
	Queue operator--(int);

	friend Queue getRecordsYearsBefore(Queue checkedQueue, int beforeYear);
	friend void printQueue(Queue& queueForPrinting);
	//
	friend ostream& operator << (ostream& os, Queue& outQueue);
	friend istream& operator >> (std::istream& in, Queue& inQueue);

	void readFromBinary(string fname);
	void writeToBinary(string fname);
	void changeStringBinary(int index, T changedRecord, string fname);
	void deleteStringFromBinary(int index, string fname);

	int findFirstGameYearBinary(string fname);

private:
	List queueElems;
};

