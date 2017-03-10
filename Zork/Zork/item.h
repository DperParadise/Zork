#ifndef ITEM_H
#define ITEM_H

#include "entity.h"

class Item : public Entity
{
public:

	Item(Entity *parentEntity, ItemSize size, bool isOpen, bool isContainer, bool isLocked, Type type, const std::string &name, const std::string &desc, std::list<Entity*> &list);
	virtual ~Item();

	Entity *parent;
	ItemSize size;
	bool isOpen;
	bool isContainer;
	bool isLocked;
};



#endif // !ITEM_H