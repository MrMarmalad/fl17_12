#include "List.h"

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

template <typename T>
List::List()
	: size{ 0 }, back{ nullptr }, front{ nullptr }, lastReadedElement{ nullptr }, lastReadedIndex{ -1 }
{
}

List::List(T firstRecord) :
	size{ 1 }, lastReadedElement{ nullptr }, lastReadedIndex{ -1 }
{
	listElem* newElem = new(listElem);
	newElem->Data = firstRecord;

	this->back = newElem;
	this->front = newElem;
}

List::~List()
{
}

int List::length() const {
	return this->size;
}

bool List::empty() const {
	return this->length() == 0;
}

List* List::insertBefore(T newRecord, int insPlace) {
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

List* List::deleteFrom(int elemIndexToDelete) {
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

bool List::changeElem(int index, T changedRecord)
{
	this->insertBefore(changedRecord, index);
	this->deleteFrom(index + 1);
	return true;
}

bool List::clearList()
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

T List::getElement(int index)
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

T List::getElement()
{
	return this->getElement(0);
}

T List::getNext()
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

T List::getPrev()
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

void List::operator -=(int elemIndexToDelete) {
	this->deleteFrom(elemIndexToDelete);
}

void List::operator +=(T newElem) {
	this->insertBefore(newElem, this->length());
}

int List::findElemByGenre(string genre) {
	listElem* tmpElem = this->back;
	for (int currentIndex = 0; currentIndex < this->length(); currentIndex++) {
		if (tmpElem->Data.genre == genre) {
			return currentIndex;
		}
		tmpElem = tmpElem->next;
	}

	return -1;
}

List getRecordsYearsBefore(List checkedList, int beforeYear) {
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

void printList(List& listForPrinting)
{
	if (listForPrinting.empty()) {
		cout << "Структура данных пуста" << endl << endl;
		return;
	}
	int index = 0;
	List::listElem* tmpElem = listForPrinting.back;
	while (tmpElem->next != nullptr) {
		tmpElem->Data.printRecord();
		tmpElem = tmpElem->next;
		index++;
	}

	tmpElem->Data.printRecord();
	cout << endl;
}

ostream& setup(ostream& stream)
{
	stream.setf(ios::left);
	stream << setw(50);
	return stream;
}

ostream& operator<<(ostream& os, List& outList)
{
	outList.getElement(0);
	T tmpRecord = outList.getElement(0);
	//setup(os);
	while (!tmpRecord.empty()) {
		setup(os) << tmpRecord.name;
		setup(os) << tmpRecord.genre;
		setup(os) << tmpRecord.year;
		tmpRecord = outList.getNext();
	}
	return os;
}

istream& operator>>(std::istream& in, List& inList)
{
	string genre, name;
	int year;
	while (in >> name >> genre >> year) {
		inList.insertBefore({ name, genre, year }, inList.length());
	}
	return in;
}

void List::writeToBinary(string fname)
{
	std::fstream outStream;
	outStream.open(fname, fstream::out | fstream::binary | fstream::trunc);
	if (!outStream) {
		cout << "Ошибка открытия файла:" + fname << endl;
		return;
	}
	T tmpRecord = this->getElement(0);
	string writeString;
	while (!tmpRecord.empty()) {
		writeString = tmpRecord.name + " " + tmpRecord.genre + " " + to_string(tmpRecord.year) + "\n";
		writeString = to_string(writeString.size()) + " " + writeString;
		outStream.write(writeString.c_str(), writeString.size());
		//outStream << tmpRecord.name << " " << tmpRecord.genre << " " << tmpRecord.year << "фхфххфхф" << endl;
		tmpRecord = this->getNext();
	}
	outStream.close();
}

void List::readFromBinary(string fname)
{
	std::fstream in;
	in.open(fname, fstream::in | fstream::binary);

	if (!in) {
		cout << "Ошибка открытия файла:" + fname << endl;
		return;
	}

	string genre, name;
	int year, len;

	while (in >> len >> name >> genre >> year) {
		this->insertBefore({ name, genre, year }, this->length());
	}
}

void List::changeStringBinary(int index, T changedRecord, string fname)
{
	this->changeElem(index, changedRecord);
	this->writeToBinary(fname);
}

void List::deleteStringFromBinary(int index, string fname)
{
	this->deleteFrom(index);
	this->writeToBinary(fname);
}

int List::findFirstGameYearBinary(string fname)
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
