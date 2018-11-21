#pragma once

#include"../constants.h"

#include<vector>
#include<map>

#include"../../../engine/include/entity.h"
#include"../../../engine/include/level.h"

// Include enemies and such
#include"../enemies/skeleton.h"

using namespace bear;

// Used for simplifly the task of converting a list of integers to a list of entities that can be rendered 
static void levelUtility_ConvertToLevelContent(LevelContent& level_content) {
	
	bool ground_toggle = false;

	level_content.enemies.clear();
	level_content.items.clear();

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
					std::string temp;
					switch (tile_value) {
					case FLOOR1:
						entity.renderable.m_TextureName = "floor" + std::to_string(ground_toggle);
						ground_toggle = !ground_toggle;
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
				// Toggle between the two floor types
				entity.renderable.m_TextureName = "floor" + std::to_string(ground_toggle);
				ground_toggle = !ground_toggle;
				entity.renderable.m_Transform.m_Position = realPosition;
				entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);

				// Place the enemy with key "key" at correct position with correct enemy object
				core::Vector2i tile_position(x, y);
				std::string key = (std::string)tile_position;
				switch (tile_value) {
				case SKE:
					level_content.enemies.insert(std::pair<std::string, EnemyBase>(key, Skeleton())); // Add enemy to the list
					level_content.enemies.at(key).entity.renderable.m_Transform.m_Position = core::Vector2f((tile_position.x*TILE_SIZE) + SKELETON_OFFSET_X, (tile_position.y*TILE_SIZE) + SKELETON_OFFSET_Y);
					level_content.enemies.at(key).entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE*SKELETON_SIZE_X, TILE_SIZE*SKELETON_SIZE_Y);
					break;
				}

				// Set correct layer according to y
				level_content.enemies.at(key).entity.renderable.m_Layer = LAYER3 + y;
			}
			else if (is_item(tile_value)) {
				// Place ground tile under the item
				level_content.walls_floors.push_back(Entity());
				Entity& entity = level_content.walls_floors.back();
				// Toggle between the two floor types
				entity.renderable.m_TextureName = "floor" + std::to_string(ground_toggle);
				ground_toggle = !ground_toggle;
				entity.renderable.m_Transform.m_Position = realPosition;
				entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);

				// Item entity position & size
				Item item;
				item.entity.renderable.m_Transform.m_Position = realPosition;
				item.entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE,TILE_SIZE);
				item.state = ItemState::ON_MAP;

				// Place the item with correct key at correct position
				core::Vector2i tile_position(x, y);
				std::string key = (std::string)tile_position;
				switch (tile_value) {
				case WI:
					// Weapon item! set correct sprite & shit
					// Item name, type & value
					item.entity.renderable.m_TextureName = "sword";
					item.type = ItemType::WEAPON;
					item.name = "Weapon";
					item.value = 2; 
					break;
				case HI:
					// Healing item! set correct sprite & shit
					// Item name, type & value
					item.entity.renderable.m_TextureName = "food";
					item.type = ItemType::HEALTH;
					item.name = "Health";
					item.value = 1; 
					break;
				case SI:
					item.entity.renderable.m_TextureName = "shield";
					item.type = ItemType::SHIELD;
					item.name = "Armor";
					item.value = 1;
					break;
				case KI:
					item.entity.renderable.m_TextureName = "key";
					item.type = ItemType::KEY;
					item.name = "Key";
					item.value = 1;
					break;
				}

				item.entity.renderable.m_Layer = LAYER3 + y;
				// Insert into the level content!
				level_content.items.insert(std::pair<std::string, Item>(key, item));
			}
		}
	}
}