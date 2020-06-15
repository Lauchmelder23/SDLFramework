#pragma once

#include "SDL.h"

namespace sf
{
	class IWindow
	{
	public:
		IWindow();

	private:
		SDL_Window* m_pWindow;
		SDL_Renderer* m_pRenderer;
	};
}