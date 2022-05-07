#pragma once
#include "TTable.h"

class TArrayTable : public TTable {
protected:
	TRecord* arr;
	int size, cur;
public:
	TArrayTable(int _size = 10);
	~TArrayTable();

	int GetSize();
	bool IsFull();

	TKey GetCurrentKey();
	TValue GetCurrentValue();

	void Reset();
	void GoNext();
	bool IsEnd();
};

inline TArrayTable::TArrayTable(int _size) {
	size = _size;
	arr = new TRecord[size];
	cur = -1;
}

inline TArrayTable::~TArrayTable() {
	delete[] arr;
}

inline int TArrayTable::GetSize()
{
	return size;
}

inline bool TArrayTable::IsFull() {
	return DataCount == size;
}

inline TKey TArrayTable::GetCurrentKey() {
	return arr[cur].key;
}

inline TValue TArrayTable::GetCurrentValue() {
	return arr[cur].val;
}

inline void TArrayTable::Reset() {
	cur = 0;
}

inline void TArrayTable::GoNext() {
	cur++;
}

inline bool TArrayTable::IsEnd() {
	return cur == DataCount;
}
