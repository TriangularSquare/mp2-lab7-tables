#pragma once
#include "THashTable.h"

class TArrayHash : public THashTable {
protected:
	TRecord free;
	TRecord* arr;
	int size;
	int step;
public:
	TArrayHash(int _size = 10, int _step = 1);
};

inline TArrayHash::TArrayHash(int _size = 10, int _step = 1) {
	size = _size;
	step = _step;
	arr = new TRecord[size];

	free.key = -1;

	for (int i = 0; i < size; i++)
		arr[i] = free;
}
