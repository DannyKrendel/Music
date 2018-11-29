#pragma once

#include "stdafx.h"

using std::string;
using std::vector;

const double factor = 1.059454545;

struct Note
{
	string name;
	double freq;
};

vector<Note> createNotes(int count, string start);