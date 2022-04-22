#pragma once
#include <iostream>
#include "TScanTable.h"

class TSortTable : public TScanTable {
public:
	TSortTable(int _size = 10) : TScanTable(_size) {};
	
	TSortTable(const TScanTable& st) : TScanTable(GetSize()) { //maybe incorrect

	}

	bool Find(TKey key);
	bool Insert(TRecord rec);
	bool Delete(TKey key);

	void Sort(int first, int last);
};

inline bool TSortTable::Find(TKey key) {
	int begin = 0, end = DataCount - 1, mid;
	while (begin <= end) {
		Eff++;
		mid = (begin + end) / 2;
		if (key < arr[mid].key) {
			end = mid - 1;
		}
		else if (key > arr[mid].key) {
			begin = end + 1;
		}
		else {
			cur = mid;
			return true;
		}
	}
	cur = begin;
	return false;
}

bool TSortTable::Insert(TRecord rec) {
	if (IsFull()) {
		return false;
	}
	if (Find(rec.key)) {
		return false;
	}

	for (int i = DataCount - 1; i >= cur; i--) {
		arr[i + 1] = arr[i];
		Eff++;
	}

	arr[cur] = rec;
	DataCount++;
	Eff++;
	return true;
}

bool TSortTable::Delete(TKey key) {
	if (!Find(key)) {
		return false;
	}

	for (int i = cur; i < DataCount - 1; i++) {
		arr[i] = arr[i + 1];
		Eff++;
	}

	DataCount--;
	Eff++;
	return true;
}

inline void TSortTable::Sort(int first, int last) {
	TRecord mid = arr[(first + last) / 2];
	int begin = first;
	int end = last;

	while (begin < end) {
		while (arr[begin] < mid) {
			begin++;
			Eff++;
		}
		while (arr[end] > mid) {
			end--;
			Eff++;
		}
		if (begin < end) {
			std::swap(arr[begin], arr[end]);
			begin++;
			end--;
			Eff++;
		}
	}

	if (first < end)
		Sort(first, end);
	if (begin < last)
		Sort(begin, last);
}
