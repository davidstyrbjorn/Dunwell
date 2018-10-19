#include"include/game.h"

#include"include/levels/level1.h"
#include"include/levels/level2.h"

void Game::init()
{
	level_manager->registerLevel("level1", new Level1);
	level_manager->registerLevel("level2", new Level2);

	level_manager->setCurrentLevel("level1");
}

void Game::update(float dt) {
	graphics_singleton->update(dt);
	level_manager->update_current_level(dt);
	player->update(dt);
}

void Game::render() {
	level_manager->render_current_level();
	player->render();
}

void Game::on_event(Event& event) {
	level_manager->on_event_current_level(event);
	player->on_event(event);
}

void Game::exit()
{

}