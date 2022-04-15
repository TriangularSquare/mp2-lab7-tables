#pragma once
#include "TTable.h"

class TArrayTable : TTable {
protected:
	TRecord* arr;
	int size;
	int cur;
public:
	TArrayTable(int _size = 10);

	bool ISFull() const;
	TKey GetKey();
	TValue GetValue();

	void Reset();
	void GoNext();
	bool IsEnd();
};

inline TArrayTable::TArrayTable(int _size)
{
	arr = new TRecord[_size];
	size = _size;
	cur = -1;
}

inline bool TArrayTable::ISFull() const
{
	return (DataCount == size);
}

inline TKey TArrayTable::GetKey()
{
	return arr[cur].key;
}

inline TValue TArrayTable::GetValue()
{
	return arr[cur].val;
}

inline void TArrayTable::Reset()
{
	cur = 0;
}

inline void TArrayTable::GoNext()
{
	cur++;
}

inline bool TArrayTable::IsEnd()
{
	return cur == DataCount;
}
