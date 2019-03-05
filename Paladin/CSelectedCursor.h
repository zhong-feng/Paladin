#pragma once
#include "bagData.h"
class CSelectedCursor
{
public:
    CSelectedCursor();
    ~CSelectedCursor();

    void render(CPosition _pos);


public:
    CPosition pos;
};

