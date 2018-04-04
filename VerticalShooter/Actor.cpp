#include "Actor.h"

using namespace vs;

/// <summary>
/// Constructor
/// </summary>
/// <param name="x">Position on the x axis</param>
/// <param name="y">Position on the y axis</param>
/// <param name="width">Width of the object</param>
/// <param name="height">Height of the object</param>
actor::actor(const float x, const float y, const float width, const float height) : 
	transform_2d	(x, y, width, height),
	_brush				(nullptr), 
	_color				(0.0f, 0.0f, 0.0f, 1.0f) {}

/// <summary>
/// Destructor
/// </summary>
actor::~actor() = default;

/// <summary>
/// Sets the actor's speed
/// </summary>
/// <param name="speed">Speed to use</param>
void actor::set_speed(float speed) {
	_speed = speed;
}

/// <summary>
/// Inflicts damage on the actor and returns if it is dead
/// </summary>
/// <param name="damage">Damage to inflict</param>
/// <returns>True if actor died, false if not</returns>
bool actor::inflict_damage(int damage) {
	_health -= damage;
	return is_dead();
}

/// <summary>
/// Returns if the actor is dead
/// </summary>
/// <returns>True if actor is dead, false if not</returns>
bool actor::is_dead() const {
	return _health <= 0;
}

/// <summary>
/// Returns the actor's health
/// </summary>
/// <returns></returns>
int actor::get_health() const {
	return _health;
}


