#include "Window.hpp"

#include <sstream>
#include "util/util.hpp"

namespace sf
{

	void IWindow::Create(Vector2u size, Vector2i position, std::string title, Uint32 flags /*= SDL_WINDOW_RESIZABLE*/)
	{
		// Check if SDL was initialized
		Uint32 mask = SDL_WasInit(0);
		if ((mask & SDLF_REQUIRED_SUBSYSTEMS) != SDLF_REQUIRED_SUBSYSTEMS)
		{
			std::ostringstream errorStream;
			errorStream << "One or more required subsystems were not initialized. (Expected " <<
				SDLF_REQUIRED_SUBSYSTEMS << " but got " << mask << " instead). \n" <<
				"Make sure to call SDL_Init(" << SDLF_REQUIRED_SUBSYSTEMS << ") before instantiating sf::IWindow.";
			throw errorStream.str();
		}

		// Create SDL_Window
		if (m_pWindow == nullptr)
		{
			m_pWindow = SDL_CreateWindow(title.c_str(), position.x, position.y, size.x, size.y, flags);
			THROW_IF_NULLPTR(m_pWindow);
		}

		// Create SDL_Renderer
		if (m_pRenderer == nullptr)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
			THROW_IF_NULLPTR(m_pRenderer);
		}

	}

	void IWindow::Destroy()
	{
		SDL_DestroyRenderer(m_pRenderer);
		SDL_DestroyWindow(m_pWindow);
	}

	void IWindow::Launch(bool threaded /*= false*/)
	{
		m_atomWindowOpen = true;
		if (threaded)
		{
			m_oMsgLoopThread = std::thread(&IWindow::MessageLoop, this);
		}
		else {
			MessageLoop();
		}
	}

	void IWindow::Stop()
	{
		m_atomWindowOpen = false;

		if(m_oMsgLoopThread.joinable())
			m_oMsgLoopThread.join();

	}

	IWindow::IWindow(Vector2u size, Vector2i position, std::string title,
		Uint32 flags /*= SDL_WINDOW_RESIZABLE*/) :
		m_pWindow(nullptr), m_pRenderer(nullptr), m_oEvent(),
		m_oSize(size), m_oPosition(position), m_strTitle(title), m_uFlags(flags)
	{
		
	}

	void IWindow::MessageLoop()
	{
		Create(m_oSize, m_oPosition, m_strTitle, m_uFlags);

		// Test if the user instance's creation succeeded
		if (!OnCreate()) 
			m_atomWindowOpen = false;

		std::chrono::steady_clock::time_point pastTime = std::chrono::steady_clock::now();
		while (m_atomWindowOpen)
		{
			while (SDL_PollEvent(&m_oEvent))
			{
				if (m_oEvent.type == SDL_QUIT)
				{
					m_atomWindowOpen = false;
				}
			}

			double frametime = std::chrono::duration_cast<std::chrono::duration<double>>(
				std::chrono::steady_clock::now() - pastTime
				).count();
			pastTime = std::chrono::steady_clock::now();
			if (!OnUpdate(frametime))
				m_atomWindowOpen = false;

			SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			SDL_RenderClear(m_pRenderer);

			SDL_RenderPresent(m_pRenderer);
		}

		OnClose();
		Destroy();
	}

}