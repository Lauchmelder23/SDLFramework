#include "Window.hpp"

#include <sstream>
#include <iostream>
#include "util/util.hpp"

namespace sf
{

	void IWindow::Create(Vector2u size, Vector2i position, std::string title, 
		Uint32 windowFlags /*= SDL_WINDOW_RESIZABLE*/, Uint32 renderFlags /*= SDL_RENDERER_SOFTWARE*/)
	{
		m_pCurrentException = "";

		// Check if SDL was initialized
		Uint32 mask = SDL_WasInit(0);
		if ((mask & SDLF_REQUIRED_SUBSYSTEMS) != SDLF_REQUIRED_SUBSYSTEMS)
		{
			std::ostringstream errorStream;
			errorStream << "One or more required subsystems were not initialized. (Expected " <<
				SDLF_REQUIRED_SUBSYSTEMS << " but got " << mask << " instead). \n" <<
				"Make sure to call SDL_Init(" << SDLF_REQUIRED_SUBSYSTEMS << ") before instantiating sf::IWindow.";
			m_pCurrentException = const_cast<char*>(errorStream.str().c_str());
			return;
		}

		// Create SDL_Window
		if (m_pWindow == nullptr)
		{
			m_pWindow = SDL_CreateWindow(title.c_str(), position.x, position.y, size.x, size.y, windowFlags);
			if (IS_NULLPTR(m_pWindow))
			{
				m_pCurrentException = const_cast<char*>(SDL_GetError());
				return;
			}
		}

		// Create SDL_Renderer
		if (m_pRenderer == nullptr)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, renderFlags);
			if (IS_NULLPTR(m_pRenderer))
			{
				m_pCurrentException = const_cast<char*>(SDL_GetError());
				return;
			}
		}

		m_oEventFunction = std::bind(&IWindow::OnEvent, this, std::placeholders::_1);
		m_oUpdateFunction = std::bind<bool>(&IWindow::OnUpdate, this, std::placeholders::_1);
		m_oRenderFunction = std::bind(&IWindow::OnRender, this, std::placeholders::_1);

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

	void IWindow::AddEventCallback(EventCallback callback, void* userdata)
	{
		SDL_AddEventWatch(*(callback.target<SDL_EventFilter>()), userdata);
	}

	void IWindow::SwitchScreen(IScreen* screen)
	{
		if (m_pCurrentScreen == screen)
			return;

		if (IS_NOT_NULLPTR(m_pCurrentScreen))
			m_pCurrentScreen->OnDefocus();
		
		m_pCurrentScreen = screen;

		if (IS_NOT_NULLPTR(m_pCurrentScreen))
		{
			m_oEventFunction = std::bind(&IScreen::OnEvent, m_pCurrentScreen, std::placeholders::_1);
			m_oUpdateFunction = std::bind<bool>(&IScreen::OnUpdate, m_pCurrentScreen, std::placeholders::_1);
			m_oRenderFunction = std::bind(&IScreen::OnRender, m_pCurrentScreen, std::placeholders::_1);

			m_pCurrentScreen->OnFocus(this);
		}
		else
		{
			m_oEventFunction = std::bind(&IWindow::OnEvent, this, std::placeholders::_1);
			m_oUpdateFunction = std::bind<bool>(&IWindow::OnUpdate, this, std::placeholders::_1);
			m_oRenderFunction = std::bind(&IWindow::OnRender, this, std::placeholders::_1);

		}
	}

	IWindow::IWindow(Vector2u size, Vector2i position, std::string title,
		Uint32 windowFlags /*= SDL_WINDOW_RESIZABLE*/, Uint32 renderFlags /*= SDL_RENDERER_SOFTWARE*/) :
		m_pWindow(nullptr), m_pRenderer(nullptr), m_oEvent(),
		m_oSize(size), m_oPosition(position), m_strTitle(title), m_uWindowFlags(windowFlags),
		m_uRenderFlags(renderFlags), m_pCurrentScreen(nullptr), m_pCurrentException("")
	{
		
	}

	void IWindow::MessageLoop()
	{
		Create(m_oSize, m_oPosition, m_strTitle, m_uWindowFlags, m_uRenderFlags);
		if (strcmp(m_pCurrentException, ""))
		{
			std::cerr << "ERROR: " << m_pCurrentException << std::endl;
			return;
		}

		// Test if the user instance's creation succeeded
		if (!OnCreate()) 
			m_atomWindowOpen = false;

		std::chrono::steady_clock::time_point pastTime = std::chrono::steady_clock::now();
		while (m_atomWindowOpen)
		{
			while (SDL_PollEvent(&m_oEvent))
			{
				if (m_oEventFunction(m_oEvent))
				{

					if (m_oEvent.type == SDL_QUIT)
					{
						m_atomWindowOpen = false;
					}
				}
			}

			double frametime = std::chrono::duration_cast<std::chrono::duration<double>>(
				std::chrono::steady_clock::now() - pastTime
				).count();
			pastTime = std::chrono::steady_clock::now();
			if (!m_oUpdateFunction(frametime))
				m_atomWindowOpen = false;

			m_oRenderFunction(m_pRenderer);

			SDL_RenderPresent(m_pRenderer);
		}

		OnClose();
		Destroy();
	}

}