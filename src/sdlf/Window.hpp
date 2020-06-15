#pragma once

#include <string>
#include <thread>
#include <atomic>

#include "SDL.h"
#include "util/Vector2.hpp"

#define SDLF_REQUIRED_SUBSYSTEMS SDL_INIT_VIDEO

namespace sf
{
	class IWindow
	{
	public:
		void Create(Vector2u size, Vector2i position, std::string title, Uint32 flags = SDL_WINDOW_RESIZABLE);

		void Launch(bool threaded = false);
		void Stop();

		bool IsOpen() { return m_atomWindowOpen; }

	protected:
		IWindow(Vector2u size, Vector2i position, std::string title, Uint32 flags = SDL_WINDOW_RESIZABLE);

		virtual bool OnCreate() { return true; }
		virtual void OnClose() { }
		virtual bool OnUpdate(double frametime) { return true; }

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

		std::thread m_oMsgLoopThread;
		std::atomic_bool m_atomWindowOpen;
	};
}