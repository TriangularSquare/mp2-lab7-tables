#pragma once
#include "TArrayTable.h"

class TScanTable : public TArrayTable {
public:
	TScanTable(int _size = 10);

	bool Find(TKey key);
	bool Insert(TRecord rec);
	bool Delete(TKey key);
};

inline TScanTable::TScanTable(int _size) : TArrayTable(_size) { }

inline bool TScanTable::Find(TKey key)
{
	for (int i = 0; i < DataCount; i++) {
		Eff++;
		if (arr[i].key == key) {
			curr = i;
			return true;
		}
	}
	curr = DataCount;
	return false;
}

inline bool TScanTable::Insert(TRecord rec)
{
	if (IsFull()) {
		return false;
	}
	if (Find(rec.key)) {
		return false;
	}

	arr[curr] = rec;
	DataCount++;
	Eff++;
	return true;
}

inline bool TScanTable::Delete(TKey key)
{
	if (!Find(key)) {
		return false;
	}

	arr[curr] = arr[DataCount - 1];
	DataCount--;
	Eff++;
	return true;
}
