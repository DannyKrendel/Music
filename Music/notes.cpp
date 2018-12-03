#include "stdafx.h"
#include "notes.h"

using std::cout;
using std::endl;

vector<Note> createNotes(int count, int startOctave)
{
	vector<Note> notes(count);

	if (startOctave < 1 || startOctave > CFreq.size())
	{
		cout << "Октава должна быть в диапазоне 1-11" << endl;
		return notes;
	}

	if (count < 1 || (startOctave - 1) * 12 + count > 11 * 12)
	{
		cout << "Количество нот вне диапазона" << endl;
		return notes;
	}

	for (int i = 0, noteName = 'C', noteOct = '0' + startOctave; i < count; i++)
	{
		bool sign = false;
		if (i == 0)
		{
			notes[0] = { string() + (char)noteName + (char)noteOct, CFreq[startOctave - 1] };
			continue;
		}

		notes[i].freq = notes[i - 1].freq * factor;

		if (i % 12 == 0 || i % 12 == 2 || i % 12 == 4 || i % 12 == 5 || i % 12 == 7 || i % 12 == 9 || i % 12 == 11)
			noteName++;
		else
			sign = true;

		if (i % 12 == 0)
			noteOct++;

		if (i % 12 == 9)
			noteName = 'A';

		notes[i].name += noteName;
		if (sign) notes[i].name += '#';
		notes[i].name += noteOct;
	}

	return notes;
}

void Note::play(int duration)
{
	Beep(freq, duration);
}
