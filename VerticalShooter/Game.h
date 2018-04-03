#ifndef VS_GAME_HPP
#define VS_GAME_HPP

#include <windows.h>
#include <d2d1.h>
#include "StepTimer.h"
#include "Player.h"

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

template<class i>
inline void safe_release(i **interface_to_release) {
	if (*interface_to_release != nullptr) {
		(*interface_to_release)->Release();
		(*interface_to_release) = nullptr;
	}
}

class game {
private:
	//Variables
	HWND _hwnd;
	ID2D1Factory* _direct2d_factory;
	ID2D1HwndRenderTarget* _render_target;
	DX::StepTimer _timer;
	player _player;

	const int _window_width = 1024;
	const int _window_height = 768;

	//Functions
	HRESULT create_device_independant_resources();
	HRESULT create_device_resources();
	void discard_device_resources();

	HRESULT on_render();
	void on_update(const DX::StepTimer& timer);

	void on_resize(
		UINT width,
		UINT height
	);

	static LRESULT CALLBACK wnd_proc(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

public:
	game();
	~game();

	HRESULT initialize();

	void run_game_loop();
};

#endif //VS_GAME_HPP