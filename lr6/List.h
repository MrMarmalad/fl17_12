#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "GameRecord.h"

using namespace std;

template <typename T=GameRecord>
class List
{

private:

	vector<T> listElems;

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
	List<T> findElemsByGenre(string genre);
	List* insertBefore(T newRecord, int insPlace);
	List* deleteFrom(int elemIndexToDelete);
	bool changeElem(int index, T changedRecord);
	bool clearList();


	T getElement(int index);
	T getElement();

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
	T findFirstGameYearBinary(string fname);


	//
	void swap(int indexF, int indexS);
	void sortList(bool asc = true);

	////
	bool writeToFile(string fname);
	bool readFromFile(string fname);
};

template <typename T>
List<T> getRecordsYearsBefore(List<T> checkedList, int beforeYear);
ostream& setup(ostream& stream);


template <typename T>
List<T>::List(){}

template <typename T>
List<T>::List(T firstRecord)
{
	this->listElems.push_back(firstRecord);
}

template <typename T>
List<T>::~List() {}

template <typename T>
int List<T>::length() const {
	return this->listElems.size();
}

template <typename T>
bool List<T>::empty() const {
	return this->listElems.size() == 0;
}

template <typename T>
List<T>* List<T>::insertBefore(T newRecord, int insPlace) {
	auto it = this->listElems.begin();
	advance(it, insPlace);
	this->listElems.insert(it, newRecord);
	return this;
}

template <typename T>
List<T>* List<T>::deleteFrom(int elemIndexToDelete) {
	auto it = this->listElems.begin();
	advance(it, elemIndexToDelete);
	this->listElems.erase(it);
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
	this->listElems.clear();
	return true;
}

template <typename T>
T List<T>::getElement(int index)
{
	return this->listElems[index];
}

template <typename T>
T List<T>::getElement()
{
	return this->getElement(0);
}

template <typename T>
void List<T>::operator -=(int elemIndexToDelete) {
	this->deleteFrom(elemIndexToDelete);
}

template <typename T>
void List<T>::operator +=(T newElem) {
	this->listElems.push_back(newElem);
}

template <typename T>
List<T> List<T>::findElemsByGenre(string genre) {

	List<T> result;
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
List<T> getRecordsYearsBefore(List<T> checkedList, int beforeYear) {
	List<T> filteredList;
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
void printList(List<V>& listForPrinting)
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

ostream& setup(ostream& stream)
{
	stream.setf(ios::left);
	stream << setw(50);
	return stream;
}


template <typename V>
ostream& operator<<(ostream& os, List<V>& outList)
{
	outList.getElement(0);
	V tmpRecord = outList.getElement(0);
	for (int i = 0; i < outList.length(); i++) {
		setup(os) << outList.getElement(i);
	}

	return os;
}

template <typename V>
istream& operator>>(std::istream& in, List<V>& inList)
{
	V newRecord;
	while (!in.eof()) {
		in >> newRecord;
		inList.insertBefore(newRecord, inList.length());
	}
	return in;
}

template <typename T>
void List<T>::writeToBinary(string fname)
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
void List<T>::readFromBinary(string fname)
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
T List<T>::findFirstGameYearBinary(string fname)
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
inline void List<T>::swap(int indexF, int indexS)
{
	T tmpRecord = this->getElement(indexF);
	this->changeElem(indexF, this->getElement(indexS));
	this->changeElem(indexS, tmpRecord);
}

template<typename T>
inline void List<T>::sortList(bool asc)
{
	sort(this->listElems.begin(), this->listElems.end());
	if (!asc) {
		reverse(this->listElems.begin(), this->listElems.end());
	}
}

template<typename T>
inline bool List<T>::writeToFile(string fname)
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
inline bool List<T>::readFromFile(string fname)
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
bool writeElemsToFile(vector<vector<T>> inVec, string filename) {
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