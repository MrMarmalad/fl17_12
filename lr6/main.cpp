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
		cout << "Невозможно открыть файл: " << ex2TextFname << endl;
		printf("Текущая директория:  %s", dir);
	}
	else {
		inOut >> testList;
		testList.sort();
		printList(testList, false);
		inOut.close();
	}

	testList.sort();

	cout << "Запись в бинарь" << endl;
	testList.writeToBinary(ex2BinFname);
	printList(testList, false);
	testList.clearList();
	printList(testList, false);
	testList.readFromBinary(ex2BinFname);

	testList.sort();
	printList(testList, false);

	cout << "Изменение строк" << endl;
	testList.changeStringBinary(0, { "The Legend Of Zelda: Ocarina of Time", "Action-adventure", 1998 }, ex2BinFname);
	printList(testList, false);

	cout << "Удаление строки" << endl;
	testList.deleteStringFromBinary(0, ex2BinFname);
	printList(testList, false);

	cout << "Поиск по жанру" << endl;
	auto testList2 = testList.findElemsByGenre("Action");
	printList(testList2, false);
	cout << endl;

	cout << "Поиск игры самого раннего года выпуска" << endl;
	cout << "Самая ранняя игра: " << testList.findFirstGameYearBinary(ex2BinFname) << endl;
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
		cout << "Невозможно открыть файл: " << ex2TextFname << endl;
		printf("Текущая директория:  %s", dir);
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

	cout << "Изменение строк" << endl;
	testQueue.changeStringBinary(0, { "The Legend Of Zelda: Ocarina of Time", "Action-adventure", 1998 }, ex2BinFname);
	printQueue(testQueue);

	cout << "Удаление строки" << endl;
	testQueue.deleteStringFromBinary(0, ex2BinFname);
	printQueue(testQueue);

	cout << "Поиск игры самого раннего года выпуска" << endl;
	cout << "Самая ранняя игра: " << testQueue.findFirstGameYearBinary(ex2BinFname) << endl;
}

int main() {
	setlocale(LC_ALL, "rus");

	listTesting();
	cout << endl << "======================================" << endl
		<< "Тест очереди" << endl
		<< "======================================" << endl;

	queueTesting();

}