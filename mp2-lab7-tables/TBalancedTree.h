#pragma once
#include "TTreeTable.h"

const int H_Ok = 0;
const int H_Inc = 1;
const int H_Dec = -1;

class TBalancedTree : public TTreeTable {
	int LeftBalance(TTreeNode*& tn);
	int RightBalance(TTreeNode*& tn);
    int InsBalance(TTreeNode*& tn, TRecord rec);
	
	int LeftBalanceDel(TTreeNode*& tn);
	int RightBalanceDel(TTreeNode*& tn);
	int DelBalance(TTreeNode*& tn, TKey key);

	TTreeNode* FindMax(TTreeNode* tn);
	int DelMax(TTreeNode* tn);
public:
	bool Insert(TRecord rec);
	bool Delete(TKey key);
};

inline bool TBalancedTree::Insert(TRecord rec)
{
	if (IsFull()) throw "Can't insert: no more space in table";
	if (Find(rec.key)) return false;
	InsBalance(pRoot, rec);
	return true;

}

inline bool TBalancedTree::Delete(TKey key)
{
	if (!Find(key)) return false;
	DelBalance(pRoot, key);
	return true;

}

inline int TBalancedTree::LeftBalance(TTreeNode*& tn)
{
	int result = H_Ok;

	if (tn->Bal == 1)
	{
		tn->Bal = 0;
		result = H_Ok;
	}

	else if (tn->Bal == 0)
	{
		tn->Bal = -1;
		result = H_Inc;
	}
	
	else
	{
		TTreeNode* ttn = tn->pLeft;

		if (ttn->Bal == -1)
		{
			tn->pLeft = ttn->pRight;
			ttn->pRight = tn;
			ttn->Bal = 0;
			tn->Bal = 0;

			tn = ttn;
			result = H_Ok;
		}
		
		else if (ttn->Bal == 1)
		{
			TTreeNode* ttnr = ttn->pRight;

			ttn->pRight = ttnr->pLeft;
			ttnr->pLeft = ttn;
			tn->pLeft = ttnr->pRight;
			ttnr->pRight = tn;
			if (ttnr->Bal == -1)
				tn->Bal = 1;
			else
				tn->Bal = 0;
			if (ttnr->Bal == 1)
				ttn->Bal = -1;
			else
				ttn->Bal = 0;
			tn = ttnr;
			tn->Bal = 0;
			result = H_Ok;
		}
	}
	return result;

}

inline int TBalancedTree::RightBalance(TTreeNode*& tn)
{
	int result = H_Ok;

	if (tn->Bal == -1)
	{
		tn->Bal = 0;
		result = H_Ok;
	}
	
	else if (tn->Bal == 0)
	{
		tn->Bal = 1;
		result = H_Inc;
	}
	
	else
	{
		TTreeNode* ttn = tn->pRight;

		if (ttn->Bal == 1)
		{
			tn->pRight = ttn->pLeft;
			ttn->pLeft = tn;

			ttn->Bal = 0;
			tn->Bal = 0;

			tn = ttn;
			result = H_Ok;
		}

		else if (ttn->Bal == -1)
		{
			TTreeNode* ttnl = ttn->pLeft;

			ttn->pLeft = ttnl->pRight;
			ttnl->pRight = ttn;
			tn->pRight = ttnl->pLeft;
			ttnl->pLeft = tn;
			if (ttnl->Bal == 1)
				tn->Bal = -1;
			else
				tn->Bal = 0;
			if (ttnl->Bal == -1)
				ttn->Bal = 1;
			else
				ttn->Bal = 0;
			tn = ttnl;
			tn->Bal = 0;
			result = H_Ok;
		}
	}
	return result;

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

inline int TBalancedTree::LeftBalanceDel(TTreeNode*& tn)
{
	int result = H_Ok;

	if (tn->Bal == 1)
	{
		tn->Bal = 0;
		result = H_Dec;
	}
	
	else if (tn->Bal == 0)
	{
		tn->Bal = -1;
		result = H_Ok;
	}
	
	else
	{
		TTreeNode* ttn = tn->pLeft;

		if (ttn->Bal == -1)
		{
			tn->pLeft = ttn->pRight;
			ttn->pRight = tn;

			ttn->Bal = 0;
			ttn->Bal = 0;

			tn = ttn;
			result = H_Dec;
		}
		
		else if (ttn->Bal == 1)
		{
			TTreeNode* ttnr = ttn->pRight;

			ttn->pRight = ttnr->pLeft;
			ttnr->pLeft = ttn;
			tn->pLeft = ttnr->pRight;
			ttnr->pRight = tn;
			if (ttnr->Bal == -1)
				tn->Bal = 1;
			else
				tn->Bal = 0;
			if (ttnr->Bal == 1)
				ttn->Bal = -1;
			else
				ttn->Bal = 0;
			tn = ttnr;
			tn->Bal = 0;
			result = H_Dec;
		}
		
		else
		{
			TTreeNode* tmp = tn;
			TTreeNode* ttnl = ttn->pLeft;
			TTreeNode* ttnr = ttn->pRight;

			tn = ttn;
			tn->pLeft = ttnl;
			tn->pRight = tmp;
			tmp->pLeft = ttnr;
			ttn->Bal = 1;
			return H_Ok;
		}
	}
	return result;

}

inline int TBalancedTree::RightBalanceDel(TTreeNode*& tn)
{
	int result = H_Ok;

	
	if (tn->Bal == -1)
	{
		tn->Bal = 0;
		result = H_Dec;
	}
	
	else if (tn->Bal == 0)
	{
		tn->Bal = 1;
		result = H_Ok;
	}
	
	else
	{
		TTreeNode* ttn = tn->pRight;

		if (ttn->Bal == 1)
		{
			tn->pRight = ttn->pLeft;
			ttn->pLeft = tn;

			ttn->Bal = 0;
			tn->Bal = 0;

			tn = ttn;
			result = H_Dec;
		}

		else if (ttn->Bal == -1)
		{
			TTreeNode* ttnl = ttn->pLeft;

			ttn->pLeft = ttnl->pRight;
			ttnl->pRight = ttn;
			tn->pRight = ttnl->pLeft;
			ttnl->pLeft = tn;
			if (ttnl->Bal == 1)
				tn->Bal = -1;
			else
				tn->Bal = 0;
			if (ttnl->Bal == -1)
				ttn->Bal = 1;
			else
				ttn->Bal = 0;
			tn = ttnl;
			tn->Bal = 0;
			result = H_Dec;
		}
		
		else
		{
			TTreeNode* tmp = tn;
			TTreeNode* ttnl = ttn->pLeft;
			TTreeNode* ttnr = ttn->pRight;

			tn = ttn;
			tn->pLeft = tmp;
			tn->pRight = ttnr;
			tmp->pRight = ttnl;
			ttn->Bal = -1;
			return H_Ok;
		}
	}
	return result;

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
			TTreeNode* ttn = tn->pLeft;
			TTreeNode* pMax = FindMax(tn->pLeft);
			tmp = DelMax(ttn);
			tn->rec = pMax->rec;
			delete pMax;
			pMax = nullptr;

			tn->pLeft = ttn;

			if (tmp != H_Ok)
				res = RightBalanceDel(tn);

		}
		DataCount--;
	}

	return res;
}

inline TTreeNode* TBalancedTree::FindMax(TTreeNode* tn)
{
	while (tn->pRight != nullptr)
		tn = tn->pRight;
	return tn;
}

inline int TBalancedTree::DelMax(TTreeNode* tn)
{
	Eff++;
	int result;
	if (tn->pRight == nullptr)
	{
		tn = tn->pLeft;
		result = H_Dec;
	}
	else
	{
		result = DelMax(tn->pRight);
		if (result == H_Dec)
			result = LeftBalanceDel(tn);
	}
	return result;

}
