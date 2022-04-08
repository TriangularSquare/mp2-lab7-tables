#include "TTable.h"

const int TTable::GetDataCount()
{
    return DataCount;
}

const int TTable::GetEff()
{
    return Eff;
}

void TTable::ClearEff()
{
    Eff = 0;
}

bool TTable::IsEmpty()
{
    return DataCount == 0;
}
