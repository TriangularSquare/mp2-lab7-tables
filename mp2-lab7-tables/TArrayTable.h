#pragma once
#include "TTable.h"

class TArrayTable : public TTable {
protected:
	TRecord* arr;
	int size, curr;
public:
	TArrayTable(int _size = 10);
	~TArrayTable();

	int GetSize() const;
	bool IsFull() const override;

	TKey GetCurrentKey() const override;
	TValue GetCurrentValue() const override;

	void Reset() override;
	void GoNext() override;
	bool IsEnd() override;
};

inline TArrayTable::TArrayTable(int _size) 
{
	size = _size;
	arr = new TRecord[size];
	curr = -1;
}

inline TArrayTable::~TArrayTable() 
{
	delete[] arr;
}

inline int TArrayTable::GetSize() const
{
	return size;
}

inline bool TArrayTable::IsFull() const
{
	return DataCount == size;
}

inline TKey TArrayTable::GetCurrentKey() const
{
	return arr[curr].key;
}

inline TValue TArrayTable::GetCurrentValue() const
{
	return arr[curr].val;
}

inline void TArrayTable::Reset() 
{
	curr = 0;
}

inline void TArrayTable::GoNext() 
{
	curr++;
}

inline bool TArrayTable::IsEnd() 
{
	return curr == DataCount;
}
