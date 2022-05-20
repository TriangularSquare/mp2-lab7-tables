#pragma once
#include "TTreeTable.h"

const int H_Ok = 0;
const int H_Inc = 1;
const int H_Del = -1;

class TBalancedTree : public TTreeTable {
public:
	bool Insert(TRecord rec);

	int LeftBalance(TTreeNode*& tn);
	int RightBalance(TTreeNode*& tn);
	int InsBalance(TTreeNode*& tn, TRecord rec);
};

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
