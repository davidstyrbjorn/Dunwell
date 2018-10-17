#pragma once

#include<core\vector2.h>
#include<window/event.h>
using namespace bear;

#include<vector>
typedef std::vector<std::vector<int>> level_list;

#include"enemy.h"

// Structure for data that every level has // @PROTOTYPE
struct LevelContent {
	core::Vector2i goal_pos;
	level_list tile_map;
	std::vector<Entity> walls_floors;
	//std::map<core::Vector2i, Item> items;
	std::map<std::string, EnemyBase> enemies;
};

struct ILevel {

	std::string next_level_name;

	virtual void init() = 0; // Called when a level is started
	virtual void on_event(Event& event) = 0; // Called every event
	virtual void update(float dt) = 0; // Called ones each frame used to update game logic
	virtual void render() = 0; // Do rendering here
	virtual void player_moved() = 0; // Called when the player moves!
	virtual LevelContent& get_level_content() = 0;
};