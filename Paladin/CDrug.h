#pragma once
#include "CItem.h"
class CDrug :  public CItem
{
public:
    CDrug();
    ~CDrug();

    int hp;
    int mp;
};

