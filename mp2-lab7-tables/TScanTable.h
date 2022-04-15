#pragma once
#include "TArrayTable.h"

class TScanTable : TArrayTable {
public:
	TScanTable(int _size = 10) : TArrayTable(_size) { };

	bool Find(TKey key);
	bool Insert(TRecord rec);
};

inline bool TScanTable::Find(TKey key)
{
	for (int i = 0; i < DataCount; i++) {
		Eff++;
		if (arr[i].key == key) {
			cur = i;
			return true;
		}
	}
	cur = DataCount;
	return false;
}

inline bool TScanTable::Insert(TRecord rec)
{

}
