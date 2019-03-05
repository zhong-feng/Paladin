#include "CWeapon.h"


CWeapon::~CWeapon()
{

}

CWeapon::CWeapon()
{
    type = IT_Weapon;
    count = 1;

    attack = 0;

    strength = 0;
    intelligence = 0;
}
