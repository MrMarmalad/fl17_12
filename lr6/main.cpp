
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


int main() {

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

	if (inVec.size() < 1) {
		cout << "Количество строк массива меньше 1" << endl;
		return retVal;
	}

	for (int i = 1; i < inVec; i + 2) {
		for (j = 0; j < inVec[i].size(); j++) {
			if (inVec[i][j] < 0) {
				cout << inVec[i][j] << " ";
			}
		}
		cout << endl;
	}
}