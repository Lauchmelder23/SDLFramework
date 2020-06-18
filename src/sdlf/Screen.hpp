#pragma once

#include "SDL.h"

namespace sf
{
	class IScreen
	{
	public:
		virtual void OnFocus() {}							// Called when the screen is being switched to
		virtual void OnDefocus() {}							// Called when the screen is being switched from
		virtual bool OnUpdate(double frametime) { return true; }			// Called every frame
		virtual void OnEvent(const SDL_Event& event) {}		// Called after an event occurs
		virtual void OnRender(SDL_Renderer* renderer) {}	// Called for rendering

	protected:
		IScreen() = default;

	private:
	};
}