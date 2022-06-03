#pragma once
#include <string>
#include <iostream>

typedef int TKey;
typedef std::string TValue;

struct TRecord {
	TKey key;
	TValue val;

	TRecord(TKey _key = -1, TValue _val = "value-1")
	{
		key = _key;
		val = _val;
	}

	bool operator==(const TRecord& other) const {
		return (key == other.key);
	}

	bool operator!=(const TRecord& other) const {
		return (key != other.key);
	}

	bool operator>(const TRecord& other) const {
		return (key > other.key);
	}

	bool operator<(const TRecord& other) const {
		return (key < other.key);
	}

	bool operator>=(const TRecord& other) const {
		return (key >= other.key);
	}

	bool operator<=(const TRecord& other) const {
		return key <= other.key;
	}
};

class TTable {
protected:
	int DataCount;
	int Eff;
public:
	TTable();
	virtual ~TTable();

	int GetDataCount() const;
	int GetEff() const;

	void ClearEff();

	bool IsEmpty();
	virtual bool IsFull() const = 0;

	virtual bool Find(TKey key) = 0;
	virtual bool Insert(TRecord rec) = 0;
	virtual bool Delete(TKey key) = 0;

	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;

	virtual TKey GetCurrentKey() const = 0;
	virtual TValue GetCurrentValue() const = 0;

	friend std::ostream& operator<<(std::ostream& os, TTable& t) {
		for (t.Reset(); !t.IsEnd(); t.GoNext()) {
			os << t.GetCurrentKey() << " " << t.GetCurrentValue() << '\n';
		}
		return os;
	}
};

inline TTable::TTable() {
	DataCount = Eff = 0;
}

inline TTable::~TTable() { }

inline int TTable::GetDataCount() const {
	return DataCount;
}

inline int TTable::GetEff() const {
	return Eff;
}

inline void TTable::ClearEff() {
	Eff = 0;
}

inline bool TTable::IsEmpty() {
	return DataCount == 0;
}
