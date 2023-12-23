#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <direct.h>

#include "Queue.h"
#include "List.h"

using namespace std;

string ex1Fname = "Ex1.txt",
ex2TextFname = "Ex2_3.txt",

ex2BinFname = "Ex2Bin.txt",
ex2BinFnameIn = "Ex2BinIn.txt",
ex2BinFnameOut = "Ex2BinOut.txt";

void listTesting() {
	List<GameRecord> testList;
	fstream inOut;
	//
	char dir[255];
	_getcwd(dir, 255);

	inOut.open(ex2TextFname);
	if (!inOut) {
		cout << "���������� ������� ����: " << ex2TextFname << endl;
		printf("������� ����������:  %s", dir);
	}
	else {
		inOut >> testList;
		testList.sort();
		printList(testList, false);
		inOut.close();
	}

	testList.sort();

	cout << "������ � ������" << endl;
	testList.writeToBinary(ex2BinFname);
	printList(testList, false);
	testList.clearList();
	printList(testList, false);
	testList.readFromBinary(ex2BinFname);

	testList.sort();
	printList(testList, false);

	cout << "��������� �����" << endl;
	testList.changeStringBinary(0, { "The Legend Of Zelda: Ocarina of Time", "Action-adventure", 1998 }, ex2BinFname);
	printList(testList, false);

	cout << "�������� ������" << endl;
	testList.deleteStringFromBinary(0, ex2BinFname);
	printList(testList, false);

	cout << "����� �� �����" << endl;
	auto testList2 = testList.findElemsByGenre("Action");
	printList(testList2, false);
	cout << endl;

	cout << "����� ���� ������ ������� ���� �������" << endl;
	cout << "����� ������ ����: " << testList.findFirstGameYearBinary(ex2BinFname) << endl;
}

void queueTesting() {
	Queue<GameRecord> testQueue;
	fstream inOut;
	//
	char dir[255];
	_getcwd(dir, 255);
	//
	inOut.open(ex2TextFname);
	if (!inOut) {
		cout << "���������� ������� ����: " << ex2TextFname << endl;
		printf("������� ����������:  %s", dir);
	}
	else {
		inOut >> testQueue;
		printQueue(testQueue);
		inOut.close();
	}

	testQueue.sort();

	testQueue.writeToBinary(ex2BinFname);
	printQueue(testQueue);
	testQueue.clearQueue();
	printQueue(testQueue);
	testQueue.readFromBinary(ex2BinFname);
	printQueue(testQueue);

	testQueue.sort();

	cout << "��������� �����" << endl;
	testQueue.changeStringBinary(0, { "The Legend Of Zelda: Ocarina of Time", "Action-adventure", 1998 }, ex2BinFname);
	printQueue(testQueue);

	cout << "�������� ������" << endl;
	testQueue.deleteStringFromBinary(0, ex2BinFname);
	printQueue(testQueue);

	cout << "����� ���� ������ ������� ���� �������" << endl;
	cout << "����� ������ ����: " << testQueue.findFirstGameYearBinary(ex2BinFname) << endl;
}

int main() {
	setlocale(LC_ALL, "rus");

	listTesting();
	cout << endl << "======================================" << endl
		<< "���� �������" << endl
		<< "======================================" << endl;

	queueTesting();

}