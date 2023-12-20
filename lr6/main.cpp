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
	//

	inOut.open(ex2TextFname);
	if (!inOut) {
		cout << "Невозможно открыть файл: " << ex2TextFname << endl;
		printf("Текущая директория:  %s", dir);
	}
	else {
		inOut >> testList;
		printList(testList);
		cout << endl;
		inOut.close();
	}

	cout << "Запись и чтение из бинарного файла" << endl;
	testList.writeToBinary(ex2BinFname);
	printList(testList);
	cout << endl;
	testList.clearList();
	printList(testList);
	cout << endl;
	testList.readFromBinary(ex2BinFname);
	printList(testList);

	cout << endl << "Изменение строк" << endl;
	testList.changeStringBinary(0, { "Game1", "Genre1", 1999 }, ex2BinFname);
	printList(testList);

	cout << endl << "Удаление строки" << endl;
	testList.deleteStringFromBinary(0, ex2BinFname);
	printList(testList);

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
	cout << endl << "Тестирование очереди" << endl;
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

	cout << "Запись и чтение из бинарного файла" << endl;
	testQueue.writeToBinary(ex2BinFname);
	printQueue(testQueue);
	cout << endl;
	testQueue.clearQueue();
	printQueue(testQueue);
	cout << endl;
	testQueue.readFromBinary(ex2BinFname);
	printQueue(testQueue);

	cout << endl << "Изменение строк" << endl;
	testQueue.changeStringBinary(0, { "Game1", "Genre1", 1999 }, ex2BinFname);
	printQueue(testQueue);

	cout << endl << "Удаление строки" << endl;
	testQueue.deleteStringFromBinary(0, ex2BinFname);
	printQueue(testQueue);

	cout << "Поиск игры самого раннего года выпуска" << endl;
	cout << "Самая ранняя игра: " << testQueue.findFirstGameYearBinary(ex2BinFname) << endl;
}

int main() {
	setlocale(LC_ALL, "rus");
	
	listTesting();

	queueTesting();

}