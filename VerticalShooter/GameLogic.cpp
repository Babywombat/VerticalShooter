#include <algorithm>

#include "GameLogic.h"
#include "Defines.h"

using namespace vs;

/// <summary>
/// Constructor
/// </summary>
game_logic::game_logic():
	_quadtree	(0.0f, 0.0f, RESOLUTION_X, RESOLUTION_Y, 0, 3, nullptr) {
	
}

/// <summary>
/// Destructor
/// </summary>
game_logic::~game_logic() = default;

/// <summary>
/// Initializes the game
/// </summary>
void game_logic::initialize() {
	_player.initialize();
	_player.set_position(RESOLUTION_X / 2, RESOLUTION_Y - 100);

	_quadtree.add_object(&_player);

	for (size_t i = 0; i < 5; i++) {
		enemy enem;
		enem.initialize();
		enem.set_position((i + 1) * 50, 50);
		enem.set_player(&_player);
		_enemies.push_back(enem);
		_quadtree.add_object(&enem);
	}
}

/// <summary>
/// Renders all the game's visuals
/// </summary>
/// <param name="render_target">Target to render to</param>
void game_logic::on_render(ID2D1HwndRenderTarget* render_target) {
	_quadtree.render(render_target, nullptr);
	//Render the player
	_player.on_render(render_target);

	//Render enemies
	for (auto& enemy : _enemies) {
		enemy.on_render(render_target);
	}

	//Render player health
	ID2D1SolidColorBrush* brush;
	render_target->CreateSolidColorBrush(D2D1::ColorF(1.0f, 69.0f / 255.0f, 0.0f, 1.0f), &brush);
	for (size_t i = 0; i < _player.get_health(); i++) {
		render_target->FillRoundedRectangle(D2D1::RoundedRect(
			D2D1::RectF(
				RESOLUTION_X - (i + 1) * 30,
				RESOLUTION_Y - 30,
				RESOLUTION_X - ((i + 1) * 30) + 25,
				RESOLUTION_Y - 5), 5, 5), brush);
	}
	brush->Release();
}

/// <summary>
/// Updates all the game's states and logic
/// </summary>
/// <param name="delta">Time since last frame in seconds</param>
/// <returns>True if game has ended</returns>
bool game_logic::on_update(const double delta) {
	_quadtree.update();

	_player.on_update(delta);

	//Update enemies
	for (auto& enemy : _enemies) {
		enemy.on_update(delta);
		if(enemy.is_colliding(&_player)) {
			enemy.inflict_damage(1);
			if(_player.inflict_damage(1)) {
				//Player is dead, game ended
				return true;
			}
		}
	}

	//Delete dead enemies
	_enemies.erase(std::remove_if(_enemies.begin(), _enemies.end(), [](enemy& enem) {
		return enem.is_dead();
	}), _enemies.end());
	return false;
}
