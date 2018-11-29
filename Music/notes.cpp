#include "stdafx.h"
#include "notes.h"

vector<Note> createNotes(int count, string start)
{
	vector<Note> notes(count);

	for (int i = 0, note, oct; i < count; i++)
	{
		bool sign = false;
		if (i == 0)
		{
			notes[0] = { "A3", 220 };
			note = notes[0].name[0];
			oct = notes[0].name[1];
			continue;
		}

		notes[i].freq = notes[i - 1].freq * factor;

		if (i % 12 == 2 || i % 12 == 3 || i % 12 == 5 || i % 12 == 7 || i % 12 == 8 || i % 12 == 10)
			note++;
		else
			sign = true;

		if (i % 12 == 0)
		{
			note = 'A';
			oct++;
		}

		notes[i].name += note;
		if (sign)
			notes[i].name += '#';
		notes[i].name += oct;
	}

	return notes;
}
