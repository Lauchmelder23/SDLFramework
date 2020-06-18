#pragma once

#include <string>
#include <thread>
#include <atomic>
#include <functional>

#include "SDL.h"
#include "util/Vector2.hpp"
#include "Screen.hpp"

#define SDLF_REQUIRED_SUBSYSTEMS SDL_INIT_VIDEO

namespace sf
{
	typedef std::function<int(void*, SDL_Event*)> EventCallback;

	class IWindow
	{
	public:
		void Create(Vector2u size, Vector2i position, std::string title, Uint32 flags = SDL_WINDOW_RESIZABLE);

		void Launch(bool threaded = false);
		void Stop();

		bool IsOpen() { return m_atomWindowOpen; }

		void AddEventCallback(EventCallback callback, void* userdata);

		void SwitchScreen(IScreen* screen);

	protected:
		IWindow(Vector2u size, Vector2i position, std::string title, Uint32 flags = SDL_WINDOW_RESIZABLE);

		virtual bool OnCreate() { return true; }
		virtual void OnClose() { }
		virtual void OnEvent(const SDL_Event& event) { }
		virtual bool OnUpdate(double frametime) { return true; }
		virtual void OnRender(SDL_Renderer* renderer) { }

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

		std::function<void( SDL_Event& )> m_oEventFunction;
		std::function<bool( double )>			m_oUpdateFunction;
		std::function<void( SDL_Renderer* )>	m_oRenderFunction;
	};
}