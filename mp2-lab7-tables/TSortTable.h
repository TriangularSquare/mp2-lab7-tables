#pragma once
#include <iostream>
#include "TScanTable.h"

class TSortTable : public TScanTable {
public:
	TSortTable(int _size = 10);
	
	TSortTable(TScanTable& st);

	bool Find(TKey key);
	bool Insert(TRecord rec);
	bool Delete(TKey key);

	void QuickSort(int first, int last);
	void SelectionSort();
	void Sort(int flag = 0);
};

inline TSortTable::TSortTable(int _size) : TScanTable(_size) {}

inline TSortTable::TSortTable(TScanTable& st) : TScanTable(st.GetSize()) {
	int i;
	for (i = 0, st.Reset(); i < DataCount && !st.IsEnd(); i++, st.GoNext()) {
		arr[i].key = st.GetCurrentKey();
		arr[i].val = st.GetCurrentValue();
	}

	Sort();
}

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

inline void TSortTable::QuickSort(int first, int last) {
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
		QuickSort(first, end);
	if (begin < last)
		QuickSort(begin, last);
}

inline void TSortTable::SelectionSort()
{
	int pos;

	for (int i = 0; i < DataCount; i++)
	{
		pos = i;
		
		for (int j = i; j < DataCount; j++)
		{
			Eff++;
			if (arr[j].key < arr[pos].key)
				pos = j;
		}
		
		std::swap(arr[pos], arr[i]);
		Eff++;
	}
}

inline void TSortTable::Sort(int flag)
{
	if (flag) {
		SelectionSort();
	}
	else {
		QuickSort(0, DataCount - 1);
	}
}
