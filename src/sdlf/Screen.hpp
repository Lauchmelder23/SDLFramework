#pragma once

#include "SDL.h"

namespace sf
{
	class IScreen
	{
	public:

	protected:
		IScreen();

		virtual void OnFocus() = 0;							// Called when the screen is being switched to
		virtual void OnDefocus() = 0;						// Called when the screen is being switched from
		virtual void OnUpdate(double frametime) = 0;		// Called every frame
		virtual void OnEvent(const SDL_Event& event) = 0;	// Called after an event occurs
	
	private:
	};
}