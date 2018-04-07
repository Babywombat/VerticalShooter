#ifndef VS_BULLET_HPP
#define VS_BULLET_HPP

#include "GameObject.h"

namespace vs {
	class bullet : public game_object {
	private:
		int				_direction;
	public:
		enum E_BULLET_TYPE {
			normal = 0,
			multi = 1
		};

		bullet();
		~bullet();

		void			on_update(double delta_time) override;
		void			on_render(ID2D1HwndRenderTarget* render_target) override;
		void			initialize() override;
		void			handle_collision(transform_2d* collided_object) override;

		void			set_direction(const int direction);
	};
}

#endif //VS_BULLET_HPP