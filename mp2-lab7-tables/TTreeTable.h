#pragma once
#include "TTable.h"
#include "Stack.h"

struct TTreeNode
{
	TRecord rec;
	TTreeNode* pLeft, * pRight;

	TTreeNode(TRecord _rec, TTreeNode* _pLeft = nullptr, TTreeNode* _pRight = nullptr);
};

TTreeNode::TTreeNode(
	TRecord _rec,
	TTreeNode* _pLeft,
	TTreeNode* _pRight)
{
	rec = _rec;
	pLeft = _pLeft;
	pRight = _pRight;
}

class TTreeTable : public TTable
{
protected:
	TTreeNode* pRoot;
	TTreeNode* pPrev, * pCurr;

	TStack<TTreeNode*> st;

	int pos;
	int level;

	void Del(TTreeNode* pDel);
	void PrintKeys(std::ostream& os, TTreeNode* tn);

public:
	TTreeTable() : TTable()
	{
		pRoot = pPrev = pCurr = nullptr;
	}
	~TTreeTable();

	bool IsFull() const;

	bool Find(TKey key);
	bool Insert(TRecord rec);
	bool Delete(TKey key);

	void Reset();
	void GoNext();
	bool IsEnd();

	TKey GetCurrentKey();
	TValue GetCurrentVal();

	void Print(std::ostream& os);
};

inline void TTreeTable::Del(TTreeNode* pDel)
{
	if (pDel != nullptr) 
	{
		Del(pDel->pRight);
		Del(pDel->pLeft);
		delete pDel;
	}
}

inline void TTreeTable::PrintKeys(std::ostream& os, TTreeNode* tn)
{
	if (tn != nullptr)
	{
		for (int i = 0; i < level; i++)
		{
			os << ' ';
		}
		os << tn->rec.key << '/n';
		level++;
		PrintKeys(os, tn->pLeft);
		PrintKeys(os, tn->pRight);
		level--;
	}
}

inline TTreeTable::~TTreeTable()
{
	Del(pRoot);
}

inline bool TTreeTable::IsFull() const
{
	try
	{
		TTreeNode* newNode = new TTreeNode(TRecord());
		delete newNode;
		return false;
	}
	catch (...)
	{
		return true;
	}
}

inline bool TTreeTable::Find(TKey key)
{
	pPrev = nullptr;
	pCurr = pRoot;

	while (pCurr != nullptr)
	{
		Eff++;
		if (pCurr->rec.key == key)
			return true;
		else if (key > pCurr->rec.key)
		{
			pPrev = pCurr;
			pCurr = pCurr->pRight;
		}
		else
		{
			pPrev = pCurr;
			pCurr = pCurr->pLeft;
		}
	}

	pCurr = pPrev;
}

inline bool TTreeTable::Insert(TRecord rec)
{
	if (IsFull()) throw "Table is already full";
	if (Find(rec.key)) return false;

	TTreeNode* newNode = new TTreeNode(rec);

	if (rec.key > pCurr->rec.key)
		pCurr->pRight = newNode;
	else
		pCurr->pLeft = newNode;

	Eff++;
	DataCount++;
	return true;
}

inline bool TTreeTable::Delete(TKey key)
{
	if (!Find(key)) return false;

	TTreeNode* pDel = pCurr;

	if (pCurr->pRight == nullptr)
	{
		Eff++;
		if (pPrev == nullptr)
			pRoot = pRoot->pLeft;
		else
		{
			if (pCurr->rec.key > pPrev->rec.key)
				pPrev->pRight = pCurr->pLeft;
			else
				pPrev->pLeft = pCurr->pLeft;
		}
	}
	else if (pCurr->pLeft == nullptr)
	{
		Eff++;
		if (pPrev == nullptr)
			pRoot = pRoot->pRight;
		else
		{
			if (pCurr->rec.key > pPrev->rec.key)
				pPrev->pRight = pCurr->pRight;
			else
				pPrev->pLeft = pCurr->pRight;
		}
	}
	else
	{
		TTreeNode* tmp = pCurr->pLeft;
		pPrev = pCurr;

		while (tmp->pRight != nullptr)
		{
			Eff++;
			pPrev = tmp;
			tmp = tmp->pRight;
		}
		Eff++;

		pCurr->rec = tmp->rec;

		if (pPrev != pCurr)
			pPrev->pRight = tmp->pLeft;
		else
			pPrev->pLeft = tmp->pLeft;

		pDel = tmp;
	}

	delete pDel;
	DataCount--;
	return true;
}

inline void TTreeTable::Reset()
{
	st.Clear();
	pCurr = pRoot;

	while (pCurr != nullptr)
	{
		st.Push(pCurr);
		pCurr = pCurr->pLeft;
	}

	if (!st.IsEmpty())
	{
		pCurr = st.Top();
	}
	pos = 0;
}

inline void TTreeTable::GoNext()
{
	if (pCurr->pRight != nullptr)
	{
		pCurr = pCurr->pRight;
		while (pCurr != nullptr)
		{
			st.Push(pCurr);
			pCurr = pCurr->pLeft;
		}
		pCurr = st.Top();
	}
	else if (st.IsEmpty())
	{
		pCurr = st.Pop()->pRight;
	}
	else
	{
		pCurr = st.Top();
	}
}

inline bool TTreeTable::IsEnd()
{
	return pos == DataCount;
}

inline TKey TTreeTable::GetCurrentKey()
{
	return pCurr->rec.key;
}

inline TValue TTreeTable::GetCurrentVal()
{
	return pCurr->rec.val;
}

inline void TTreeTable::Print(std::ostream& os)
{
	PrintKeys(os, pRoot);
}
