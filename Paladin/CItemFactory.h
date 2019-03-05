#pragma once

#include "CHP.h"
#include "CMP.h"

#include "CSword.h"
#include "CWhips.h"

#include "CIoricae.h"
#include "CSackcloth.h"

#include "CApple.h"

class CItemFactory
{
public:
    static CItem* createItem(CItemID _itemID);

protected:
    static void initItemPropONxML(CItemID _itemID, CItem* _pItem);
};

