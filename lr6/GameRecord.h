#pragma once

#include <string>
using namespace std;

struct GameRecord
{
	string name = "";
	string genre = "";
	int year = 0;

	// если strict == false, то пустые поля будут учитываться как успешно прошедшие проверку
	bool equal(GameRecord testRecord, bool strictEq) const;

	bool empty() const;

	void printRecord() const;

	friend ostream& operator <<(ostream& os, GameRecord& outRec);
	friend istream& operator >> (std::istream& in, GameRecord& inRec);
};