#ifndef VS_TRANSFORMTWOD_HPP
#define VS_TRANSFORMTWOD_HPP
#include <d2d1.h>

namespace vs {
	class transform_2d {
	protected:
		float			_x;
		float			_y;
		float			_width;
		float			_height;
	public:
		transform_2d(float x, float y, float width, float height);
		virtual ~transform_2d();

		float			get_x()				const;
		float			get_y()				const;
		float			get_width()			const;
		float			get_height()		const;
		D2D1_RECT_F		get_aabb()			const;

		void			set_position(float x, float y);
		bool			is_colliding(transform_2d* other) const;
	};
}

#endif //VS_TRANSFORMTWOD_HPP