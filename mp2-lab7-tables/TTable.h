#pragma once
#include <string>
#include <ostream>


typedef int TKey;
typedef std::string TValue;

struct TRecord {
	TKey key;
	TValue val;
};

class TTable {
protected:
	int DataCount;
	int Eff;
public:
	virtual bool Find(TKey key) = 0;
	virtual bool Insert(TRecord tr) = 0;
	virtual bool Delete(TKey key) = 0;

	virtual bool ISFull() const = 0;
	virtual TKey GetKey() = 0;
	virtual TValue GetValue() = 0;

	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;

	const int GetDataCount();
	const int GetEff();
	void ClearEff();
	bool IsEmpty();

	friend std::ostream& operator<<(std::ostream& os, TTable& tt) {
		for (tt.Reset(); !tt.IsEnd(); tt.GoNext())
			os << tt.GetKey();
		return os;
	}
};
