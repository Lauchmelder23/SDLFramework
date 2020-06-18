#pragma once

#include <string>
#include <thread>
#include <atomic>
#include <functional>

#include "util/Vector2.hpp"
#include "util/Callback.hpp"
#include "Screen.hpp"

#define SDLF_REQUIRED_SUBSYSTEMS SDL_INIT_VIDEO

namespace sf
{
	typedef std::function<int(void*, SDL_Event*)> EventCallback;

	class IWindow : public ICallback
	{
	public:
		void Create(Vector2u size, Vector2i position, std::string title, 
			Uint32 windowFlags = SDL_WINDOW_RESIZABLE, Uint32 rendererFlags = SDL_RENDERER_SOFTWARE);

		void Launch(bool threaded = false);
		void Stop();

		bool IsOpen() { return m_atomWindowOpen; }

		void AddEventCallback(EventCallback callback, void* userdata);

		void SwitchScreen(IScreen* screen);

	protected:
		IWindow(Vector2u size, Vector2i position, std::string title, Uint32 flags = SDL_WINDOW_RESIZABLE);

		virtual bool OnCreate() { return true; }
		virtual void OnClose() { }
		virtual bool OnEvent(const SDL_Event& event) override { return true; }
		virtual bool OnUpdate(double frametime) override { return true; }
		virtual void OnRender(SDL_Renderer* renderer) override { }

	protected:
		SDL_Window* m_pWindow;
		SDL_Renderer* m_pRenderer;
		SDL_Event m_oEvent;

	private:
		void MessageLoop();
		void Destroy();

	private:
		Vector2u m_oSize;
		Vector2i m_oPosition;
		std::string m_strTitle;
		Uint32 m_uFlags;

		IScreen* m_pCurrentScreen;

		std::thread m_oMsgLoopThread;
		std::atomic_bool m_atomWindowOpen;

		std::function<bool( SDL_Event& )> m_oEventFunction;
		std::function<bool( double )>			m_oUpdateFunction;
		std::function<void( SDL_Renderer* )>	m_oRenderFunction;
	};
}