#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "GameRecord.h"

using namespace std;

template <typename T=GameRecord>

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

	template <typename V>
		friend void printList(List<V>& listForPrinting);
	//
	template <typename V>
		friend ostream& operator <<(ostream& os, List<V>& outList);

	template <typename V>
		friend istream& operator >> (std::istream& in, List<V>& inList);

	void readFromBinary(string fname);
	void writeToBinary(string fname);
	void changeStringBinary(int index, T changedRecord, string fname);
	void deleteStringFromBinary(int index, string fname);
	int findFirstGameYearBinary(string fname);

};

template <typename T>
List<T> getRecordsYearsBefore(List<T> checkedList, int beforeYear);
ostream& setup(ostream& stream);







template <typename T>
List<T>::List()
	: size{ 0 }, back{ nullptr }, front{ nullptr }, lastReadedElement{ nullptr }, lastReadedIndex{ -1 }
{
}

template <typename T>
List<T>::List(T firstRecord) :
	size{ 1 }, lastReadedElement{ nullptr }, lastReadedIndex{ -1 }
{
	listElem* newElem = new(listElem);
	newElem->Data = firstRecord;

	this->back = newElem;
	this->front = newElem;
}

template <typename T>
List<T>::~List()
{
}

template <typename T>
int List<T>::length() const {
	return this->size;
}

template <typename T>
bool List<T>::empty() const {
	return this->length() == 0;
}

template <typename T>
List<T>* List<T>::insertBefore(T newRecord, int insPlace) {
	listElem* newElem;
	listElem* tmpElem;

	int elemCounter = 0;

	newElem = new(listElem);
	newElem->Data = newRecord;

	if (this->empty()) {
		this->back = newElem;
		this->front = newElem;
	}
	else {
		if (insPlace >= this->length()) {
			tmpElem = this->front;
			tmpElem->next = newElem;
			newElem->prev = tmpElem;
			this->front = newElem;
		}
		else if (insPlace <= 0) {
			tmpElem = this->back;
			tmpElem->prev = newElem;
			newElem->next = this->back;
			this->back = newElem;
		}
		else {
			tmpElem = this->back;
			while (elemCounter < insPlace) {
				tmpElem = tmpElem->next;
				elemCounter++;
			}
			newElem->next = tmpElem;
			newElem->prev = tmpElem->prev;
			tmpElem->prev->next = newElem;
			tmpElem->prev = newElem;

		}
	}
	this->size++;
	return this;
}

template <typename T>
List<T>* List<T>::deleteFrom(int elemIndexToDelete) {
	listElem* tmpElem;
	if (this->length() == 0) return this;

	if (elemIndexToDelete <= 0) {
		if (this->back->next != nullptr) {
			tmpElem = this->back->next;
			delete this->back;
			this->back = tmpElem;
			this->back->prev = nullptr;
		}
		else {
			delete this->back;
		}

	}
	else if (elemIndexToDelete >= this->length() - 1) {
		tmpElem = this->front->prev;
		delete this->front;
		this->front = tmpElem;
		this->front->next = nullptr;
	}
	else {
		tmpElem = this->back;
		for (int recordCounter = 0; recordCounter < elemIndexToDelete; recordCounter++) {
			tmpElem = tmpElem->next;
		}
		tmpElem->next->prev = tmpElem->prev;
		tmpElem->prev->next = tmpElem->next;

		delete tmpElem;

	}
	this->size--;
	return this;
}

template <typename T>
bool List<T>::changeElem(int index, T changedRecord)
{
	this->insertBefore(changedRecord, index);
	this->deleteFrom(index + 1);
	return true;
}

template <typename T>
bool List<T>::clearList()
{
	while (!this->empty()) {
		this->deleteFrom(0);
	}
	this->back = nullptr;
	this->front = nullptr;
	this->lastReadedElement = nullptr;
	this->lastReadedIndex = -1;
	return true;
}

template <typename T>
T List<T>::getElement(int index)
{
	if (index > this->length() - 1 || index < 0) return T();
	if (lastReadedIndex == index) return this->lastReadedElement->Data;

	listElem* tmpRecord = this->back;
	for (int i = 0; i < index; i++) {
		tmpRecord = tmpRecord->next;
		this->lastReadedIndex = i;
	}
	this->lastReadedElement = tmpRecord;
	this->lastReadedIndex++;
	return tmpRecord->Data;
}

template <typename T>
T List<T>::getElement()
{
	return this->getElement(0);
}

template <typename T>
T List<T>::getNext()
{
	T retVal = T();
	if (lastReadedElement != nullptr &&
		lastReadedIndex != -1 &&
		lastReadedElement->next != nullptr)
	{
		lastReadedElement = lastReadedElement->next;
		lastReadedIndex++;
		retVal = lastReadedElement->Data;
	}
	return retVal;
}

template <typename T>
T List<T>::getPrev()
{
	T retVal = T();
	if (lastReadedElement == nullptr || lastReadedIndex == -1) {
		cout << "Нет прочитанных ранее элементов" << endl;
	}
	else if (lastReadedElement->prev == nullptr) {
		cout << "Это самый первый элемент" << endl;
	}
	else {
		lastReadedElement = lastReadedElement->prev;
		lastReadedIndex--;
		retVal = lastReadedElement->Data;
	}
	return retVal;
}

template <typename T>
void List<T>::operator -=(int elemIndexToDelete) {
	this->deleteFrom(elemIndexToDelete);
}

template <typename T>
void List<T>::operator +=(T newElem) {
	this->insertBefore(newElem, this->length());
}

template <typename T>
int List<T>::findElemByGenre(string genre) {
	listElem* tmpElem = this->back;
	for (int currentIndex = 0; currentIndex < this->length(); currentIndex++) {
		if (tmpElem->Data.genre == genre) {
			return currentIndex;
		}
		tmpElem = tmpElem->next;
	}

	return -1;
}

template <typename T>
List<T> getRecordsYearsBefore(List<T> checkedList, int beforeYear) {
	List filteredList;
	T tmpRecord;

	if (checkedList.empty()) {
		cout << "Список пустой" << endl;
	}
	else {
		tmpRecord = checkedList.getElement();
		while (!tmpRecord.empty())
		{
			if (tmpRecord.year < beforeYear) {
				filteredList.insertBefore(tmpRecord, filteredList.length());
			}
			tmpRecord = checkedList.getNext();
		}
	}
	return filteredList;
}

template <typename V>
void printList(List<V>& listForPrinting)
{
	if (listForPrinting.empty()) {
		cout << "Структура данных пуста" << endl << endl;
		return;
	}
	int index = 0;
	auto tmpElem = listForPrinting.back;
	while (tmpElem->next != nullptr) {
		cout << tmpElem->Data << endl;
		tmpElem = tmpElem->next;
		index++;
	}

	cout << tmpElem->Data << endl;
}

ostream& setup(ostream& stream)
{
	stream.setf(ios::left);
	stream << setw(50);
	return stream;
}

/// <summary>
/// Переделать
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="os"></param>
/// <param name="outList"></param>
/// <returns></returns>
template <typename V>
ostream& operator<<(ostream& os, List<V>& outList)
{
	outList.getElement(0);
	V tmpRecord = outList.getElement(0);
	//setup(os);
	while (!tmpRecord.empty()) {
		setup(os) << tmpRecord;
		tmpRecord = outList.getNext();
	}
	return os;
}

template <typename V>
istream& operator>>(std::istream& in, List<V>& inList)
{
	V newRecord;
	while (in >> newRecord) {
		inList.insertBefore(newRecord, inList.length());
	}
	return in;
}

template <typename T>
void List<T>::writeToBinary(string fname)
{
	std::fstream outStream;
	std::ostringstream sstrm;
	outStream.open(fname, fstream::out | fstream::binary | fstream::trunc);
	if (!outStream) {
		cout << "Ошибка открытия файла: " + fname << endl;
		return;
	}
	T tmpRecord = this->getElement(0);
	while (!tmpRecord.empty()) {
		outStream << tmpRecord << "\n";
		tmpRecord = this->getNext();
	}
	outStream.close();
}

template <typename T>
void List<T>::readFromBinary(string fname)
{
	std::fstream in;
	in.open(fname, fstream::in | fstream::binary);

	if (!in) {
		cout << "Ошибка открытия файла:" + fname << endl;
		return;
	}

	//string genre, name;
	T inRec;
	int len;//, year;

	while (in >> inRec) {
		this->insertBefore(inRec, this->length());
	}
}

template <typename T>
void List<T>::changeStringBinary(int index, T changedRecord, string fname)
{
	this->changeElem(index, changedRecord);
	this->writeToBinary(fname);
}

template <typename T>
void List<T>::deleteStringFromBinary(int index, string fname)
{
	this->deleteFrom(index);
	this->writeToBinary(fname);
}

template <typename T>
int List<T>::findFirstGameYearBinary(string fname)
{
	this->clearList();
	this->readFromBinary(fname);

	T tmpRecord = this->getElement(0);
	int minYear = tmpRecord.year;

	while (!tmpRecord.empty()) {
		if (tmpRecord.year < minYear) {
			minYear = tmpRecord.year;
		}
		tmpRecord = this->getNext();
	}
	return minYear;
}

template <typename T>
vector<vector<T>> readElemsFromFile(int iLen, int jLen, string filename) {
	vector<vector<T>> retVal;
	vector<T> tmpVec;
	T tmpVal;

	fstream in;
	in.open(filename, fstream::read);
	if (!in) {
		cout << "Невозможно открыть файл " << filename;
		return retVal;
	}

	for (int i = 0; i < iLen; i++) {
		for (int j = 0; j < jLen; j++) {
			in >> tmpVal;
			tmpVec.push_back(tmpVal);
		}
		retVal.push_back(tmpVec);
	}
	return retVal;
}

template <typename T>
bool writeElemsFromFile(vector<vector<T>> inVec, string filename) {
	fstream out;
	out.open(filename, fstream::write);
	if (!out) {
		cout << "Невозможно открыть файл " << filename;
		return false;
	}

	for (int i = 0; i < inVec.size(); i++) {
		for (int j = 0; j < inVec[i].size(); j++) {
			out << inVec[i][j] << " ";
		}
		out << endl;
	}
	return true;
}

template <typename T>
vector<vector <T> > getEvenLines(vector<vector<T>> inVec) {
	vector<vector<T>> retVec;
	for (int i = 0; i < inVec.size(); i + 2) {
		retVec.push_back(inVec[i]);
	}
	return retVec;
}

template <typename T>
vector<T> getMinMaxElemsFromLines(vector<vector<T>> inVec) {
	T minElem;
	T maxElem;
	vector<T> retVal;

	for (int i = 0; i < inVec.size(); i++) {
		minElem = inVec[i][0];
		maxElem = inVec[i][0];
		for (int j = 1; j < inVec[i].size(); j++) {
			if (inVec[i][j] < minElem) {
				minElem = inVec[i][j];
			}
			if (inVec[i][j] > maxElem) {
				maxElem = inVec[i][j];
			}
		}
		retVal.push_back(minElem);
		retVal.push_back(maxElem);
	}
	return retVal;
}

template <typename T>
void printOddNegativeLines(vector<vector<T>> inVec) {
	T retVal;
	if (inVec.size() < 1) {
		cout << "Количество строк массива меньше 1" << endl;
		return retVal;
	}

	for (int i = 1; i < inVec; i + 2) {
		for (int j = 0; j < inVec[i].size(); j++) {
			if (inVec[i][j] < 0) {
				cout << inVec[i][j] << " ";
			}
		}
		cout << endl;
	}
}