#pragma once
#include "TTreeTable.h"

const int H_Ok = 0;
const int H_Inc = 1;
const int H_Dec = -1;

class TBalancedTree : public TTreeTable {
public:
	bool Insert(TRecord rec);
	bool Delete(TKey key);

	int InsBalance(TTreeNode*& tn, TRecord rec);
	int DelBalance(TTreeNode*& tn, TKey key);

	int LeftBalance(TTreeNode*& tn);
	int RightBalance(TTreeNode*& tn);
	int RightBalanceDel(TTreeNode*& tn);

	TTreeNode* FindMax(TTreeNode* tn);
	int DelMax(TTreeNode* tn);
};

inline bool TBalancedTree::Insert(TRecord rec)
{
	if (Find(rec.key))
		throw "There is the same record";
	InsBalance(pRoot, rec);
}

inline bool TBalancedTree::Delete(TKey key)
{
	if (!Find(key))
		throw "There isn't such record";
	DelBalance(pRoot, key);
}

inline int TBalancedTree::InsBalance(TTreeNode*& tn, TRecord rec)
{
	int tmp;
	int res = H_Ok;
	Eff++;

	if (tn == nullptr)
	{
		tn = new TTreeNode(rec);
		res = H_Inc;
		DataCount++;
	}
	else if (rec < tn->rec)
	{
		tmp = InsBalance(tn->pLeft, rec);
		if (tmp == H_Inc)
		{
			res = LeftBalance(tn);
		}
	}
	else
	{
		tmp = InsBalance(tn->pRight, rec);
		if (tmp = H_Inc)
		{
			res = RightBalance(tn);
		}
	}

	return res;
}

inline int TBalancedTree::DelBalance(TTreeNode*& tn, TKey key)
{
	int res = H_Ok;
	int tmp;

	if (tn == nullptr)
		return res;

	else if (key < tn->rec.key)
	{
		tmp = DelBalance(tn->pLeft, key);
		if (tmp != H_Ok)
			res = RightBalance(tn);
	}
	else if (key > tn->rec.key)
	{
		tmp = DelBalance(tn->pRight, key);
		if (tmp != H_Ok)
			res = LeftBalance(tn);
	}

	else
	{
		if (tn->pLeft == nullptr && tn->pRight == nullptr)
		{
			delete tn;
			tn = nullptr;
			res = H_Dec;
		}

		else if (tn->pLeft != nullptr && tn->pRight == nullptr)
		{
			tn->rec = tn->pLeft->rec;
			delete tn->pLeft;
			tn->pLeft = nullptr;
			res = H_Dec;
			tn->Bal = H_Ok;
		}
		else if (tn->pLeft == nullptr && tn->pRight != nullptr)
		{
			tn->rec = tn->pRight->rec;
			delete tn->pRight;
			tn->pRight = nullptr;
			res = H_Dec;
			tn->Bal = H_Ok;
		}

		else
		{
			TTreeNode* tn1;
			TTreeNode* tn2;
			TTreeNode* pMax = FindMax(tn1);
			tmp = DelMax(tn1);
			tn->rec = pMax->rec;
			delete pMax;
			tn->pLeft = tn1;
			tn->pRight = tn2;
			if (tmp != H_Ok)
				res = RightBalanceDel(tn);
		}
	}

	return res;
}

inline TTreeNode* TBalancedTree::FindMax(TTreeNode* tn)
{
	while (tn->pRight != nullptr)
		tn = tn->pRight;
	return tn;
}
