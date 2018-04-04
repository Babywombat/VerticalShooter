#ifndef VS_ACTOR_HPP
#define VS_ACTOR_HPP

#include <d2d1.h>
#include "Transform2d.h"

namespace vs {
	class actor : public transform_2d {
	protected:
		ID2D1SolidColorBrush *				_brush;
		D2D1::ColorF						_color;
		float								_speed;
		int									_health;

	public:
		actor(float x, float y, float width, float height);
		virtual ~actor();

		virtual void						on_update(double delta_time) = 0;
		virtual void						on_render(ID2D1HwndRenderTarget* render_target) = 0;
		virtual void						initialize() = 0;
		void								set_speed(float speed);
		bool								inflict_damage(int damage);
		bool								is_dead() const;
		int									get_health() const;
	};
}

#endif //VS_ACTOR_HPP