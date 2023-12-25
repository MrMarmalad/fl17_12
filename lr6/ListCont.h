#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "GameRecord.h"
#include "Utils.h"

using namespace std;

template <typename T=GameRecord>
class ListCont
{

private:

	vector<T> listElems;

public:
	ListCont();
	ListCont(T firstRecord);
	~ListCont();

	//add new element to end
	void operator +=(T newElem);
	//delete element with index
	void operator -=(int elemIndexToDelete);

	int length() const;
	bool empty() const;
	ListCont<T> findElemsByGenre(string genre);
	ListCont* insertBefore(T newRecord, int insPlace);
	ListCont* deleteFrom(int elemIndexToDelete);
	bool changeElem(int index, T changedRecord);
	bool clearList();


	T getElement(int index);
	T getElement();

	template <typename V>
		friend void printList(ListCont<V>& listForPrinting);
	//
	template <typename V>
		friend ostream& operator <<(ostream& os, ListCont<V>& outList);

	template <typename V>
		friend istream& operator >> (std::istream& in, ListCont<V>& inList);

	void readFromBinary(string fname);
	void writeToBinary(string fname);
	void changeStringBinary(int index, T changedRecord, string fname);
	void deleteStringFromBinary(int index, string fname);
	T findFirstGameYearBinary(string fname);


	//
	void swap(int indexF, int indexS);
	void sortList(bool asc = true);

	////
	bool writeToFile(string fname);
	bool readFromFile(string fname);
};

template <typename T>
ListCont<T> getRecordsYearsBefore(ListCont<T> checkedList, int beforeYear);

ostream& setup(ostream& stream);


template <typename T>
ListCont<T>::ListCont(){}

template <typename T>
ListCont<T>::ListCont(T firstRecord)
{
	this->listElems.push_back(firstRecord);
}

template <typename T>
ListCont<T>::~ListCont() {}

template <typename T>
int ListCont<T>::length() const {
	return this->listElems.size();
}

template <typename T>
bool ListCont<T>::empty() const {
	return this->listElems.size() == 0;
}

template <typename T>
ListCont<T>* ListCont<T>::insertBefore(T newRecord, int insPlace) {
	auto it = this->listElems.begin();
	advance(it, insPlace);
	this->listElems.insert(it, newRecord);
	return this;
}

template <typename T>
ListCont<T>* ListCont<T>::deleteFrom(int elemIndexToDelete) {
	auto it = this->listElems.begin();
	advance(it, elemIndexToDelete);
	this->listElems.erase(it);
	return this;
}

template <typename T>
bool ListCont<T>::changeElem(int index, T changedRecord)
{
	this->insertBefore(changedRecord, index);
	this->deleteFrom(index + 1);
	return true;
}

template <typename T>
bool ListCont<T>::clearList()
{
	this->listElems.clear();
	return true;
}

template <typename T>
T ListCont<T>::getElement(int index)
{
	return this->listElems[index];
}

template <typename T>
T ListCont<T>::getElement()
{
	return this->getElement(0);
}

template <typename T>
void ListCont<T>::operator -=(int elemIndexToDelete) {
	this->deleteFrom(elemIndexToDelete);
}

template <typename T>
void ListCont<T>::operator +=(T newElem) {
	this->listElems.push_back(newElem);
}

template <typename T>
ListCont<T> ListCont<T>::findElemsByGenre(string genre) {

	ListCont<T> result;
	if (typeid(T) == typeid(GameRecord)) {
		for (int currentIndex = 0; currentIndex < this->listElems.size(); currentIndex++) {
			if (this->listElems[currentIndex].genre == genre) {
				result += this->listElems[currentIndex];
			}
		}
	}
	return result;
}

template <typename T>
ListCont<T> getRecordsYearsBefore(ListCont<T> checkedList, int beforeYear) {
	ListCont<T> filteredList;
	T tmpRecord;

	if (checkedList.empty()) {
		cout << "Список пустой" << endl;
	}
	else {
		tmpRecord = checkedList.getElement(0);
		for (int i = 1; i < checkedList.length(); i++) {
			if (checkedList.getElement(i) < tmpRecord) {
				filteredList += checkedList.getElement(i);
			}
		}
	}
	return filteredList;
}

template <typename V>
void printList(ListCont<V>& listForPrinting)
{
	if (listForPrinting.empty()) {
		cout << "Структура данных пуста" << endl << endl;
		return;
	}
	int index = 0;
	V tmpElem;


	for (int i = 0; i < listForPrinting.length(); i++) {
		cout << listForPrinting.getElement(i);
		if (i < listForPrinting.length() - 1) cout << endl << endl;
	}
	cout << endl;
}


template <typename V>
ostream& operator<<(ostream& os, ListCont<V>& outList)
{
	outList.getElement(0);
	V tmpRecord = outList.getElement(0);
	for (int i = 0; i < outList.length(); i++) {
		setup(os) << outList.getElement(i);
	}

	return os;
}

template <typename V>
istream& operator>>(std::istream& in, ListCont<V>& inList)
{
	V newRecord;
	while (!in.eof()) {
		in >> newRecord;
		inList.insertBefore(newRecord, inList.length());
	}
	return in;
}

template <typename T>
void ListCont<T>::writeToBinary(string fname)
{
	fstream outStream;
	stringstream ss;

	outStream.open(fname, ios::out | ios::binary | ios::trunc);
	if (!outStream) {
		cout << "Ошибка открытия файла:" + fname << endl;
		return;
	}

	T tmpRecord = this->getElement(0);
	string writeString;

	for (int i = 0; i < this->length(); i++) {
		tmpRecord = this->getElement(i);
		ss << tmpRecord;
		if (i < this->length() - 1) {
			ss << endl;
		}
	}
	writeString = ss.str();
	outStream.write(writeString.c_str(), writeString.size());
	outStream.close();
}

template <typename T>
void ListCont<T>::readFromBinary(string fname)
{
	std::fstream in;
	in.open(fname, ios::in | ios::binary);

	if (!in) {
		cout << "Ошибка открытия файла:" + fname << endl;
		return;
	}

	T tmpRec;
	while (!in.eof()) {
		in >> tmpRec;
		this->insertBefore(tmpRec, this->length());
	}
	in.close();
}

template <typename T>
void ListCont<T>::changeStringBinary(int index, T changedRecord, string fname)
{
	this->changeElem(index, changedRecord);
	this->writeToBinary(fname);
}

template <typename T>
void ListCont<T>::deleteStringFromBinary(int index, string fname)
{
	this->deleteFrom(index);
	this->writeToBinary(fname);
}

template <typename T>
T ListCont<T>::findFirstGameYearBinary(string fname)
{
	this->clearList();
	this->readFromBinary(fname);

	T tmpRecord = this->getElement(0);
	T retVal = this->getElement(0);

	for (int i = 0; i < this->listElems.size(); i++) {
		if (tmpRecord < retVal) {
			retVal = tmpRecord;
		}
	}
	return retVal;
}

template<typename T>
inline void ListCont<T>::swap(int indexF, int indexS)
{
	T tmpRecord = this->getElement(indexF);
	this->changeElem(indexF, this->getElement(indexS));
	this->changeElem(indexS, tmpRecord);
}

template<typename T>
inline void ListCont<T>::sortList(bool asc)
{
	sort(this->listElems.begin(), this->listElems.end());
	if (!asc) {
		reverse(this->listElems.begin(), this->listElems.end());
	}
}

template<typename T>
inline bool ListCont<T>::writeToFile(string fname)
{
	fstream out;
	stringstream ss;
	T tmpRecord;

	out.open(fname, ios::out);
	if (!out.is_open()) {
		cout << "Невозможно открыть файл " << fname << endl;
		return false;
	}

	for (int i = 0; i < this->length(); i++) {
		tmpRecord = this->getElement(i);
		ss << tmpRecord;
	}
	out << ss.str();
	return true;
}

template<typename T>
inline bool ListCont<T>::readFromFile(string fname)
{
	fstream in;
	T tmpRecord;


	in.open(fname, ios::in);
	if (!in.is_open()) {
		cout << "Невозможно открыть файл " << fname << endl;
		return false;
	}

	while (!in.eof()) {
		in >> tmpRecord;
		*this += tmpRecord;
	}

	return true;
}
