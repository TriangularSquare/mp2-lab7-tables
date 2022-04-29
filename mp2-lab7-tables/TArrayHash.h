#pragma once
#include "THashTable.h"

class TArrayHash : public THashTable {
protected:
	TRecord free;
	TRecord del;

	TRecord* arr;

	int size;
	int step;

	int curr;
public:
	TArrayHash(int _size = 10, int _step = 1);

	bool Find(TKey key);

	bool Insert(TRecord trec);
	bool Delete(TKey key);

	void Reset();
	void GoNext();
	bool IsEnd();
};
