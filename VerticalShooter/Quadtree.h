#ifndef VS_QUADTREE_HPP
#define VS_QUADTREE_HPP

#include <vector>
#include "Transform2d.h"

using namespace std;

namespace vs {
	class quadtree {
	private:
		float									_x;
		float									_y;
		float									_width;
		float									_height;
		int										_level;
		int										_max_level;
		vector<transform_2d*>					_objects;

		quadtree *								_parent;
		quadtree *								_nw;
		quadtree *								_ne;
		quadtree *								_sw;
		quadtree *								_se;

		bool									contains			(quadtree* child, transform_2d* object);

	public:
		quadtree													(float x, float y,
																	float width, float height,
																	int level, int maxLevel, quadtree* parent);

		~quadtree													();

		void									add_object			(transform_2d *object);
		vector<transform_2d*>					get_objects_at		(float x, float y) const;
		vector<transform_2d*>					get_all_objects		() const;
		void									clear				();
		void									update				();
		void									render				(ID2D1HwndRenderTarget* render_target, ID2D1SolidColorBrush* brush);
	};
}
#endif //VS_QUADTREE_HPP
