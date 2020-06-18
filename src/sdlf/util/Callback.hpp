#pragma once

namespace sf
{
	#include <SDL.h>

	class ICallback
	{
	protected:
		virtual bool OnEvent(const SDL_Event& event) = 0;
		virtual bool OnUpdate(double frametime) = 0;
		virtual void OnRender(SDL_Renderer* renderer) = 0;

	protected:
		ICallback() = default;
		ICallback(const ICallback& other) = delete;
		ICallback& operator=(const ICallback& other) = delete;
	};
}