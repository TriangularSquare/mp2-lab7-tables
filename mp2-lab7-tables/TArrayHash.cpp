#include "TArrayHash.h"

TArrayHash::TArrayHash(int _size = 10, int _step = 1) {
	size = _size;
	step = _step;
	arr = new TRecord[size];

	free.key = -1;

	for (int i = 0; i < size; i++)
		arr[i] = free;
}

bool TArrayHash::Find(TKey key)
{
	int flag = -1;
	int pos = HashFunc(key) % size;

	for (int i = 0; i < size; i++) {
		Eff++;

		if (arr[pos].key == key) {
			curr = pos;
			return true;
		}

		if (arr[pos] == del && flag == -1) {
			curr = pos;
			flag = 1;
		}

		if (arr[pos] == free) {
			if (flag == -1)
				curr = pos;
			break;
		}

		pos = (pos + step) % size;
	}

	return false;
}

bool TArrayHash::Insert(TRecord trec)
{
	if (IsFull())
		return false;

	bool found = Find(trec.key);
	if (found)
		return false;

	arr[curr] = trec;
	DataCount++;

	return true;
}

bool TArrayHash::Delete(TKey key)
{
	if (Find(key)) {
		arr[curr] = del;
		return true;
	}
	else
		return false;
}

void TArrayHash::Reset()
{
	for (curr = 0; curr < size; curr++)
		if (arr[curr] != del && arr[curr] != free)
			return;
}

void TArrayHash::GoNext()
{
	for (curr++; curr < size; curr++)
		if (arr[curr] != del && arr[curr] != free)
			return;
}

bool TArrayHash::IsEnd()
{
	return curr == size;
}