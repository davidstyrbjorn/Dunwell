#pragma once

#include"../constants.h"

#include<vector>
#include<map>

#include"../../../engine/include/entity.h"
#include"../../../engine/include/level.h"

// Include enemies and such
#include"../enemies/bat.h"

using namespace bear;

// Used for simplifly the task of converting a list of integers to a list of entities that can be rendered 
static void levelUtility_ConvertToLevelContent(LevelContent& level_content) {

	level_content.enemies.clear();

	level_list _level_list = level_content.tile_map;
	for (int y = 0; y < _level_list.size(); y++) 
	{ 
		for (int x = 0; x < _level_list.at(y).size(); ++x) 
		{
			core::Vector2f realPosition = core::Vector2f(x*TILE_SIZE, y*TILE_SIZE);
			
			int tile_value = _level_list.at(y).at(x);
			if (is_floor_or_wall(tile_value)) {
				level_content.walls_floors.push_back(Entity());
				Entity& entity = level_content.walls_floors.back();
				entity.renderable.m_Transform.m_Position = realPosition;
				entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);
				entity.renderable.m_Layer = LAYER1;

				// Set texture name based on tile value
				{
					// Big switch setting the correct texture for the tile
					switch (tile_value) {
					case FLOOR1:
						entity.renderable.m_TextureName = "ground";
						break;
					case WALL_TOP:
						entity.renderable.m_TextureName = "wallTop";
						break;
					case PIT:
						entity.renderable.m_TextureName = "pit";
						break;
					case WALL_LEFT:
						entity.renderable.m_TextureName = "wallLeft";
						break;
					case WALL_RIGHT:
						entity.renderable.m_TextureName = "wallRight";
						break;
					case BOTTOM_LEFT_WALL:
						entity.renderable.m_TextureName = "bottomLeftWall";
						break;
					case BOTTOM_RIGHT_WALL:
						entity.renderable.m_TextureName = "bottomRightWall";
						break;
					case GOAL:

						break;
					}
				}
			}
			else if (is_enemy(tile_value)) {

				// Place ground tile under the enemy
				level_content.walls_floors.push_back(Entity());
				Entity& entity = level_content.walls_floors.back();
				entity.renderable.m_TextureName = "ground";
				entity.renderable.m_Transform.m_Position = realPosition;
				entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);

				// Place the enemy with key "key" at correct position with correct enemy object
				core::Vector2i tile_position(x, y);
				std::string key = (std::string)tile_position;
				switch (tile_value) {
				case BAT:
					level_content.enemies.insert(std::pair<std::string, EnemyBase>(key, Bat())); // Add enemy to the list
					level_content.enemies.at(key).entity.renderable.m_TextureName = "test_enemy";
					level_content.enemies.at(key).entity.renderable.m_Transform.m_Position = core::Vector2f((tile_position.x*TILE_SIZE) + BAT_OFFSET_X, (tile_position.y*TILE_SIZE) + BAT_OFFSET_Y);
					level_content.enemies.at(key).entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE*BAT_SIZE_X, TILE_SIZE*BAT_SIZE_Y);
					break;
				}

				// Set correct layer according to y
				level_content.enemies.at(key).entity.renderable.m_Layer = LAYER3 + y;
			}
			else if (is_item(tile_value)) {
				// Place ground tile under the item
				level_content.walls_floors.push_back(Entity());
				Entity& entity = level_content.walls_floors.back();
				entity.renderable.m_TextureName = "ground";
				entity.renderable.m_Transform.m_Position = realPosition;
				entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);

				Item item;
				item.entity

				// Place the item with correct key at correct position
				core::Vector2i tile_position(x, y);
				std::string key = (std::string)tile_position;
				switch (tile_value) {
				case WI:
					break;
				case HI:
					break;
				}
			}
		}
	}
}