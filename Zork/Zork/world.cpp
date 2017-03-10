#include "world.h"
#include <iostream>
#include "room.h"
#include "exit.h"
#include "item.h"
#include "player.h"
#include "enemy.h"
#include <list>

void World::Init()
{
	//Create game entities
	//--------------------------------------ROOMS-----------------------------------------
	cell = new Room(ROOM, "cell", "cold dirty cell.", cel_inv);
	world.push_back(cell);
	corridor = new Room(ROOM, "corridor", "prison corridor. To the north the main hall is visible. To the east, a door.", cor_inv);
	world.push_back(corridor);
	wardrobe = new Room(ROOM, "wardrobe", "guards wardrobe. There is a closet here.", war_inv);
	world.push_back(wardrobe);
	main_hall = new Room(ROOM, "main hall", "main hall entrance. A door leads to the street.", mh_inv);
	world.push_back(main_hall);
	//---------------------------------------EXITS----------------------------------------------
	//cell <-> corridor
	door_clc = new Exit(NORTH, cell, corridor, false, EXIT, "cell door", "metallic cell door with a hole to the north.", clc_inv);
	world.push_back(door_clc);
	door_ccl = new Exit(SOUTH, corridor, cell, false, EXIT, "cell door", "metallic cell door with a hole to the south.", clc_inv);
	world.push_back(door_ccl);
	//corridor <-> wardrobe
	door_cw = new Exit(EAST, corridor, wardrobe, false, EXIT, "wardrobe door", "wooden door to the east.", common_inv);
	world.push_back(door_cw);
	door_wc = new Exit(WEST, wardrobe, corridor, true, EXIT, "wardrobe door", "wooden door to the west.", common_inv);
	world.push_back(door_wc);
	//main_hall -> stret
	door_hs = new Exit(NORTH, main_hall, nullptr, false, EXIT, "street exit", "door leading to the street to the north.", common_inv);
	world.push_back(door_hs);
	 //---------------------------------------ITEMS CELL-----------------------------------------
	window = new Item(cell, MEDIUM, true, true, false, ITEM, "window", "barred window leading to the forest with a loose bar. You can hear doves singing nearby.", win_inv);
	world.push_back(window);
	breadcrumbs = new Item(cell, SMALL, false, false, false, ITEM, "bread crumbs", "bread crumbs. Someone enjoy his last meal here.", common_inv);
	world.push_back(breadcrumbs);
	door_hole = new Item(cell, SMALL, true, true, false, ITEM, "door hole", "through this hole prisoners are given food.", doh_inv);
	world.push_back(door_hole);
	pigeon = new Item(nullptr, SMALL, false, false, false, ITEM, "pigeon", "young pigeon.", common_inv);
	world.push_back(pigeon);
	bar = new Item(cell, SMALL, false, false, false, ITEM, "bar", "metallic bar.", common_inv);
	world.push_back(bar);
	//---------------------------------------ITEMS CORRIDOR-------------------------------------
	table = new Item(corridor, MEDIUM, false, false, false, ITEM, "table", "wood table", common_inv);
	world.push_back(table);
	closet_key = new Item(corridor, SMALL, false, false, false, ITEM, "closet key", "key with a tag attached: closet.", common_inv);
	world.push_back(closet_key);
	//---------------------------------------ITEMS WARDROBE-------------------------------------
	closet = new Item(wardrobe, LARGE, false, true, true, ITEM, "clothes closet", "clothes closet used by the guards.", clo_inv);
	world.push_back(closet);
	guard_outfit = new Item(wardrobe, SMALL, false, false, false, ITEM, "guard outfit", "guard outfit clean and ready to wear", common_inv);
	world.push_back(guard_outfit);
	//--------------------------------------PLAYER & ENEMIES------------------------------
	player = new Player(cell, PLAYER, "Daniel", "It's me", pla_inv);
	world.push_back(player);
	enemy = new Enemy(corridor, ENEMY, "guard", "a cell guard wearing it's outfit", common_inv);
	world.push_back(enemy);

	//Fill inventories
	//CELL
	win_inv.push_back(bar);
	cel_inv.push_back(window);
	cel_inv.push_back(breadcrumbs);
	cel_inv.push_back(door_hole);
	cel_inv.push_back(door_clc);

	//CORRIDOR
	cor_inv.push_back(table);
	cor_inv.push_back(closet_key);
	cor_inv.push_back(door_ccl);
	cor_inv.push_back(door_cw);

	//WARDROBE
	clo_inv.push_back(guard_outfit);
	war_inv.push_back(closet);
	war_inv.push_back(door_wc);

	//MAIN HALL
	mh_inv.push_back(door_hs);

}

void World::Start()
{
	//Initial message
	printf("*****Wellcome to Dan Zork*****\n");
}

ReturnState World::Update()
{
	ReturnState ret = ReturnState::CONTINUE;
	//Receive Input and make player execute actions
	memset(raw_input, '\0', sizeof(raw_input)/sizeof(char));
	memset(command, '\0', sizeof(command) / sizeof(char));
	printf(">");
	int i = 0;
	char c = ' ';

	while ('\n' != (c = getchar()))
	{
		raw_input[i] = c;
		i++;
	}

	ParseInput(raw_input, command);
	ToUpper(command, raw_input);

	//Quit game
	if (!strcmp(raw_input, "Q"))
		return QUIT;


	return ret;
}

void World::CleanUp()
{
	for (std::list<Entity*>::iterator it = world.begin(); it != world.end(); it++)
	{
		RELEASE(*it);
	}
}