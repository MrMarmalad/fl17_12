#include "GameRecord.h"

#include <iostream>
#include <regex>

bool GameRecord::equal(GameRecord testRecord, bool strictEq) const {
	if (strictEq == true) {
		return (
			this->genre == testRecord.genre &&
			this->name == testRecord.name &&
			this->year == testRecord.year
			);
	}
	else {
		return (
			(this->genre == testRecord.genre || this->genre.empty() || testRecord.genre.empty()) &&
			(this->name == testRecord.name || this->name.empty() || testRecord.name.empty()) &&
			(this->year == testRecord.year || this->year == 0 || testRecord.year == 0)
			);
	}
}

bool GameRecord::empty() const {
	if (this->genre.empty() && this->name.empty() && this->year == 0) {
		return true;
	}
	return false;
}

void GameRecord::printRecord() const {
	cout << this->name << "\t" << this->genre << "\t" << this->year << endl;
}

bool GameRecord::operator > (const GameRecord& comparedRec) const
{
	return this->year > comparedRec.year;
}

bool GameRecord::operator < (const GameRecord& comparedRec) const
{
	return this->year < comparedRec.year;
}

ostream& operator << (ostream& os, const GameRecord& gr) {
	os << gr.name << endl;
	os << gr.genre << endl;
	os << gr.year;
	return os;
}

std::istream& operator >> (std::istream& in, GameRecord& gm)
{
	string name, genre, strYear;
	int year;

	getline(in, name);
	getline(in, genre);
	getline(in, strYear);



	name = regex_replace(name, regex("^ +| +$|( ) +"), "$1");
	genre = regex_replace(genre, regex("^ +| +$|( ) +"), "$1");
	strYear = regex_replace(strYear, regex("^ +| +$|( ) +"), "$1");

	if ((name == " ") || (genre == " ") || (strYear == " ")) return in;

	//cout << name << "\t" << genre << "\t" << strYear << endl;

	try
	{
		year = stoi(strYear);
	}
	catch (const std::invalid_argument& E)
	{
		return in;
	}

	gm.year = year;
	gm.genre = genre;
	gm.name = name;

	return in;
}