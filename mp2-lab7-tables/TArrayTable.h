#pragma once
#include "TTable.h"

class TArrayTable : public TTable {
protected:
	TRecord* arr;
	int size, cur;
public:
	TArrayTable(int _size = 10);
	~TArrayTable();

	bool IsFull();

	TKey GetKey();
	TValue GetValue();

	void Reset();
	void GoNext();
	bool IsEnd();
};

TArrayTable::TArrayTable(int _size) {
	size = _size;
	arr = new TRecord[size];
	cur = -1;
}

TArrayTable::~TArrayTable() {
	delete[] arr;
}

bool TArrayTable::IsFull() {
	return DataCount == size;
}

TKey TArrayTable::GetKey() {
	return arr[cur].key;
}

TValue TArrayTable::GetValue() {
	return arr[cur].val;
}

void TArrayTable::Reset() {
	cur = 0;
}

void TArrayTable::GoNext() {
	cur++;
}

bool TArrayTable::IsEnd() {
	return cur == DataCount;
}
