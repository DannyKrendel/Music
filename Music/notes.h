#pragma once
#include "stdafx.h"

const double factor = 1.059454545;
const vector<double> CFreq = { 16.35, 32.70, 65.41, 130.82, 261.63, 523.25, 1046.5, 2093, 4186 };

struct Note
{
	string name;
	double freq;

	void play(int duration);
};

vector<Note> createNotes(int count, int startOctave);