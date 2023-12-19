#pragma once


template <typename T>

class List
{

private:
	struct listElem {
		T Data;
		listElem* prev = nullptr;
		listElem* next = nullptr;
	};
	int size;
	listElem* back;
	listElem* front;

	listElem* lastReadedElement;
	int lastReadedIndex;

public:
	List();
	List(T firstRecord);
	~List();

	//add new element to end
	void operator +=(T newElem);
	//delete element with index
	void operator -=(int elemIndexToDelete);

	int length() const;
	bool empty() const;
	int findElemByGenre(string genre);
	List* insertBefore(T newRecord, int insPlace);
	List* deleteFrom(int elemIndexToDelete);
	bool changeElem(int index, T changedRecord);
	bool clearList();



	T getElement(int index);
	T getElement();
	T getNext();
	T getPrev();

	friend void printList(List& listForPrinting);
	//
	friend ostream& operator <<(ostream& os, List& outList);
	friend istream& operator >> (std::istream& in, List& inList);

	void readFromBinary(string fname);
	void writeToBinary(string fname);
	void changeStringBinary(int index, T changedRecord, string fname);
	void deleteStringFromBinary(int index, string fname);
	int findFirstGameYearBinary(string fname);

};

List getRecordsYearsBefore(List checkedList, int beforeYear);
ostream& setup(ostream& stream);
