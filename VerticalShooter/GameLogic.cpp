#include <algorithm>

#include "GameLogic.h"
#include "Game.h"
#include "Defines.h"
#include "Enemy.h"
#include <sstream>
#include "Utils.h"

using namespace vs;

/// <summary>
/// Constructor
/// </summary>
game_logic::game_logic(game* game):
	_player					(this),
	_quadtree				(0.0f, 0.0f, RESOLUTION_X, RESOLUTION_Y, 0, 3, nullptr), 
	_enemy_factory			(this),
	_game					(game),
	_time_since_spawn		(0.0f),
	_spawn_speed			(3.0f),
	_points					(0),
	_killed_enemies			(0) { }

/// <summary>
/// Destructor
/// </summary>
game_logic::~game_logic() = default;

/// <summary>
/// Initializes the game
/// </summary>
void game_logic::initialize() {
	_player.initialize();
	_player.set_position(RESOLUTION_X / 2.0f, RESOLUTION_Y - 100);

	_quadtree.add_object(&_player);

	_enemy_factory.initialize();

	/*for (size_t i = 0; i < 5; i++) {
		enemy enem;
		enem.initialize();
		enem.set_position((i + 1) * 50, 50);
		enem.set_player(&_player);
		_enemies.push_back(enem);
		_quadtree.add_object(&enem);
	}*/
}

/// <summary>
/// Renders all the game's visuals
/// </summary>
/// <param name="render_target">Target to render to</param>
/// <param name="text_format">Format for writing texts</param>
void game_logic::on_render(ID2D1HwndRenderTarget* render_target, IDWriteTextFormat* text_format) {
	//_quadtree.render(render_target, nullptr);
	//Render the player
	_player.on_render(render_target);

	//Render objects
	for (auto& obj : _objects) {
		obj->on_render(render_target);
	}

	//Render player health
	ID2D1SolidColorBrush* brush;
	render_target->CreateSolidColorBrush(D2D1::ColorF(1.0f, 69.0f / 255.0f, 0.0f, 1.0f), &brush);
	for (size_t i = 0; static_cast<int>(i) < _player.get_health(); i++) {
		render_target->FillRoundedRectangle(D2D1::RoundedRect(
			D2D1::RectF(
				RESOLUTION_X - (static_cast<int>(i) + 1) * 30,
				RESOLUTION_Y - 30,
				RESOLUTION_X - ((static_cast<int>(i) + 1) * 30) + 25,
				RESOLUTION_Y - 5), 5, 5), brush);
	}

	//Create string to display
	std::stringstream ss;
	ss << "Score: ";
	ss << _points;

	wstring widestr;
	for (auto i = 0; static_cast<int>(i) < static_cast<int>(ss.str().length()); ++i) {
		widestr += wchar_t(ss.str()[i]);
	}

	const auto str = widestr.c_str();

	//Render kills
	render_target->DrawText(
		str,
		ss.str().length(),
		text_format,
		D2D1::RectF(0, 0, 100, 50),
		brush
	);

	utils::safe_release(&brush);
}

/// <summary>
/// Updates all the game's states and logic
/// </summary>
/// <param name="delta">Time since last frame in seconds</param>
/// <returns>True if game has ended</returns>
bool game_logic::on_update(const double delta) {
	on_update_spawn(delta);

	_quadtree.update(_objects);
	_quadtree.add_object(&_player);

	_player.on_update(delta);

	//Update enemies
	for (size_t i = 0; i < _objects.size(); i++) {
		_objects[i]->on_update(delta);
	}

	check_collisions();

	if(_player.is_dead()) {
		//Player is dead, game ended
		return true;
	}

	cleanup();
	return false;
}


/// <summary>
/// Checks for collisions and handles them
/// </summary>
void game_logic::check_collisions() {
	for (auto& obj : _objects) {
		//Check if the object can collide at all
		if(obj->get_layer() != 0) {
			auto near_objects = _quadtree.get_objects_at(obj->get_x(), obj->get_y());
			for (auto& near_object : near_objects) {
				if(near_object != obj && near_object->is_colliding(obj)) {
					//Objects are colliding, so let them handle it
					//Ignore double collisions for now because there only is one health and the player doesnt check himself
					obj->on_collision(near_object);
					near_object->on_collision(obj);
				}
			}
		}
	}
}

/// <summary>
/// Cleans up dead objects
/// </summary>
/// <param name="end">True if game ended, false if not</param>
void game_logic::cleanup(bool end) {
	if(end) {
		for (auto& _object : _objects) {
			delete _object;
		}
		return;
	}
	//Delete dead objects
	_objects.erase(std::remove_if(_objects.begin(), _objects.end(), [this](game_object* obj) {
		if(obj->is_dead()) {
			auto e = dynamic_cast<enemy*>(obj);
			if(e != nullptr) {
				switch(e->get_type()) {
					case enemy::E_ENEMY_TYPE::normal: {
						_points += 10;
						break;
					}
					case enemy::E_ENEMY_TYPE::fast: {
						_points += 20;
						break;
					}
					case enemy::E_ENEMY_TYPE::shooting: {
						_points += 50;
						break;
					}
				}
				++_killed_enemies;
				//Adjust spawn speed based on kills
				_spawn_speed = max(3.0f - _killed_enemies * 0.05f, 0.5f);
			}

			delete obj;
			obj = nullptr;
			return true;
		};
		return false;
	}), _objects.end());
}

/// <summary>
/// Creates a new enemy of the specified type
/// </summary>
/// <param name="type">Type of enemy</param>
/// <param name="x">x Position</param>
/// <param name="y">y Position</param>
/// <returns></returns>
void game_logic::create_enemy(const enemy::E_ENEMY_TYPE type, const float x, const float y) {
	const auto enemy = _enemy_factory.make_enemy(type, x, y);
	_objects.push_back(enemy);
}

/// <summary>
/// Updates the spawning process
/// </summary>
/// <param name="delta">Time since last frame</param>
void game_logic::on_update_spawn(const float delta) {
	//Try to spawn new enemies
	if (_time_since_spawn > 0.0f) {
		_time_since_spawn -= delta;
	}

	//Spawn enemies
	if (_time_since_spawn <= 0.0f) {
		_time_since_spawn = _spawn_speed;

		//Enemies spawn with different probabilities
		//70% Normal
		//20% Fast
		//10% Shooting
		enemy::E_ENEMY_TYPE type = enemy::normal;
		const int percent = (rand() % 99) + 1;
		if (percent > 70 && percent <= 90) {
			type = enemy::fast;
		} else if(percent > 90) {
			type = enemy::shooting;
		}

		create_enemy(type, rand() % (RESOLUTION_X - 400 + 1) + 200, 50);
	}
}

/// <summary>
/// Creates new bullets of the specified type
/// </summary>
/// <param name="type">Type of bullet</param>
/// <param name="x">x Position</param>
/// <param name="y">y Position</param>
/// <param name="layer">Layer of the bullet</param>
/// <returns></returns>
void game_logic::create_bullets(const bullet::E_BULLET_TYPE type, const float x, const float y, transform_2d::E_LAYER layer) {
	const auto bullets = _bullet_factory.make_bullets(type, x, y, layer);

	//Add the bullets to the list of objects
	/*for (size_t i = 0; i < bullets.size(); i++) {
		_objects.push_back(bullets[i]);
	}*/

	_objects.insert(_objects.end(), bullets.begin(), bullets.end());
}

/// <summary>
/// Returns the game instance
/// </summary>
/// <returns>Game pointer</returns>
game* game_logic::get_game() const {
	return _game;
}
