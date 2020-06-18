#pragma once

#include "util/Callback.hpp"

namespace sf
{
	class IWindow;

	class IScreen : public ICallback
	{
	public:
		virtual void OnFocus(IWindow* parent) { }
		virtual void OnDefocus() { }
		virtual bool OnUpdate(double frametime) override { return true; }
		virtual bool OnEvent(const SDL_Event& event) override { return true; }
		virtual void OnRender(SDL_Renderer* renderer) override {}	

	protected:
		IScreen() = default;
	private:
	};
}