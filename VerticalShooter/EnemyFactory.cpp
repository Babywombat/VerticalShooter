#include "EnemyFactory.h"
#include "Bullet.h"

using namespace vs;

/// <summary>
/// Constructor
/// </summary>
enemy_factory::enemy_factory() = default;

/// <summary>
/// Destructor
/// </summary>
enemy_factory::~enemy_factory() = default;

/// <summary>
/// Creates a new enemy of the specified type
/// </summary>
/// <param name="type">Type of enemy</param>
/// <param name="x">x Position</param>
/// <param name="y">y Position</param>
/// <returns></returns>
vs::enemy* vs::enemy_factory::make_enemy(const E_ENEMY_TYPE type, const float x, const float y) const {
	enemy* new_enemy = nullptr;
	switch (type) {
	case normal: {
		new_enemy = new enemy();
		break;
	}
	default: {
		return new_enemy;
	};
	}
	if (new_enemy) {
		new_enemy->initialize();
		new_enemy->set_position(x, y);
	}
	return new_enemy;
}
