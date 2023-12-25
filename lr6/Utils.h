#pragma once
#include <fstream>
#include <iomanip>

using namespace std;

ostream& setup(ostream& stream)
{
	stream.setf(ios::left);
	stream << setw(50);
	return stream;
}