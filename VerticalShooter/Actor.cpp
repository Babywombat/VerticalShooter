#include "Actor.h"

/// <summary>
/// Constructor
/// </summary>
actor::actor() : 
	_brush(nullptr), 
	_color(0.0f, 0.0f, 0.0f, 1.0f) {}

/// <summary>
/// Destructor
/// </summary>
actor::~actor() = default;
