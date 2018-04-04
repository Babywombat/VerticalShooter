#include "Quadtree.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace vs;

/// <summary>
/// Constructor
/// </summary>
/// <param name="x">Position on the x axis</param>
/// <param name="y">Position on the y axis</param>
/// <param name="width">Width of the tree</param>
/// <param name="height">Height of the tree</param>
/// <param name="level">Level of the tree</param>
/// <param name="maxLevel">Maximum level of the tree</param>
quadtree::quadtree(float x, float y, float width, float height, int level, int maxLevel, quadtree* parent) :
	_x			(x),
	_y			(y),
	_width		(width),
	_height		(height),
	_level		(level),
	_max_level	(maxLevel),
	_parent		(parent)
{
	if (level == maxLevel) {
		return;
	}

	_nw = new quadtree(x, y, width / 2.0f, height / 2.0f, level+1, maxLevel, this);
	_ne = new quadtree(x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, maxLevel, this);
	_sw = new quadtree(x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel, this);
	_se = new quadtree(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel, this);
}

/// <summary>
/// Destructor
/// </summary>
quadtree::~quadtree() {
	if (_level == _max_level)
		return;

	delete _nw;
	delete _ne;
	delete _sw;
	delete _se;
}

/// <summary>
/// Adds a new object to the tree
/// </summary>
/// <param name="object">Object to add</param>
void quadtree::add_object(transform_2d* object) {
	if (_level == _max_level) {
		_objects.push_back(object);
		return;
	}
	if (contains(_nw, object)) {
		_nw->add_object(object); return;
	} else if (contains(_ne, object)) {
		_ne->add_object(object); return;
	} else if (contains(_sw, object)) {
		_sw->add_object(object); return;
	} else if (contains(_se, object)) {
		_se->add_object(object); return;
	}
	if (contains(this, object)) {
		_objects.push_back(object);
	}
}

/// <summary>
/// Returns the objects in the quadtree that are inside the area with the given point
/// </summary>
/// <param name="x">Position on the x axis</param>
/// <param name="y">Position on the y axis</param>
/// <returns>List of collision objects</returns>
vector<transform_2d*> quadtree::get_objects_at(float x, float y) const {
	if (_level == _max_level) {
		return _objects;
	}
	
	vector<transform_2d*> return_objects, child_return_objects;
	if (!_objects.empty()) {
		return_objects = _objects;
	}

	//Check each subtree and add results
	if (_x > x + _width / 2.0f && _x < x + _width) {
		if (_y > y + _height / 2.0f && _y < y + _height) {
			child_return_objects = _se->get_objects_at(_x, _y);
			return_objects.insert(return_objects.end(), child_return_objects.begin(), child_return_objects.end());
			return return_objects;
		}
		if (_y > y && _y <= y + _height / 2.0f) {
			child_return_objects = _ne->get_objects_at(_x, _y);
			return_objects.insert(return_objects.end(), child_return_objects.begin(), child_return_objects.end());
			return return_objects;
		}
	} else if (_x > x && _x <= x + _width / 2.0f) {
		if (_y > y + _height / 2.0f && _y < y + _height) {
			child_return_objects = _sw->get_objects_at(_x, _y);
			return_objects.insert(return_objects.end(), child_return_objects.begin(), child_return_objects.end());
			return return_objects;
		}
		if (_y > y && _y <= y + _height / 2.0f) {
			child_return_objects = _nw->get_objects_at(_x, _y);
			return_objects.insert(return_objects.end(), child_return_objects.begin(), child_return_objects.end());
			return return_objects;
		}
	}
	return return_objects;
}

/// <summary>
/// Returns all the objects in the tree
/// </summary>
/// <returns></returns>
vector<transform_2d*> quadtree::get_all_objects() const {
	if (_level == _max_level) {
		return _objects;
	}

	vector<transform_2d*> return_objects;
	if (!_objects.empty()) {
		return_objects = _objects;
	}

	auto child_return_objects = _se->get_all_objects();
	return_objects.insert(return_objects.end(), child_return_objects.begin(), child_return_objects.end());
	
	child_return_objects = _ne->get_all_objects();
	return_objects.insert(return_objects.end(), child_return_objects.begin(), child_return_objects.end());
	
	child_return_objects = _sw->get_all_objects();
	return_objects.insert(return_objects.end(), child_return_objects.begin(), child_return_objects.end());

	child_return_objects = _nw->get_all_objects();
	return_objects.insert(return_objects.end(), child_return_objects.begin(), child_return_objects.end());

	return return_objects;
}

/// <summary>
/// Clears the tree
/// </summary>
void quadtree::clear() {
	if (_level == _max_level) {
		_objects.clear();
		return;
	}
	_nw->clear();
	_ne->clear();
	_sw->clear();
	_se->clear();

	if (!_objects.empty()) {
		_objects.clear();
	}
}

/// <summary>
/// Updates the quadtree, so that moved objects are sorted correctly
/// </summary>
void quadtree::update() {
	//Only allow calling on the root
	if (_parent != nullptr) return;
	auto objects = get_all_objects();
	
	//Rebuild the tree
	clear();
	for (auto* object : objects) {
		add_object(object);
	}
}

/// <summary>
/// Renders the quadtree
/// </summary>
/// <param name="render_target">Target to render to</param>
void quadtree::render(ID2D1HwndRenderTarget* render_target, ID2D1SolidColorBrush* brush) {
	if(brush == nullptr) {
		render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::AntiqueWhite), &brush);
	}
	if(_level == _max_level) {
		render_target->DrawRectangle(D2D1::RectF(_x, _y, _x + _width, _y + _height), brush);
		return;
	}
	_se->render(render_target, brush);
	_ne->render(render_target, brush);
	_nw->render(render_target, brush);
	_sw->render(render_target, brush);

	if (_parent == nullptr) {
		brush->Release();
	}
}

/// <summary>
/// Returns true if the tree contains the given object, false if not
/// </summary>
/// <param name="child">Tree to check</param>
/// <param name="object">Object to check</param>
/// <returns></returns>
bool quadtree::contains(quadtree *child, transform_2d *object) {
	//Classic aabb collision check
	return	 !(object->get_x() < child->_x ||
				object->get_y() < child->_y ||
				object->get_x() > child->_x + child->_width  ||
				object->get_y() > child->_y + child->_height ||
				object->get_x() + object->get_width() < child->_x ||
				object->get_y() + object->get_height() < child->_y ||
				object->get_x() + object->get_width() > child->_x + child->_width ||
				object->get_y() + object->get_height() > child->_y + child->_height);
}
