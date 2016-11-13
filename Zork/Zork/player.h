#ifndef PLAYER_H
#define PLAYER_H
#include "creature.h"

class Player : public Creature
{
public:

	Player(ptrRoom loc, Type type, std::string name, std::string desc, std::list<ptrEntity> list);
};



#endif
