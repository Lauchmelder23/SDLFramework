#include "SDLF.hpp"

#include <iostream>

using namespace sf;

class MyScreen : public IScreen
{
public:
	void OnFocus(IWindow* parent) override
	{
		printf("Received Focus\n");
	}

	void OnDefocus() override
	{
		printf("Lost Focus\n");
	}

	void OnRender(SDL_Renderer* renderer) override
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);
	}

	static MyScreen* Get() 
	{
		static MyScreen* instance = new MyScreen;
		return instance;
	}
private:
	MyScreen() = default;
};



class MyWindow : public IWindow
{
public:
	MyWindow() :
		IWindow(Vec2u(800, 800), Vec2i(100, 100), "MyWindow")
	{
	}

private:
	bool OnCreate() override
	{
		SwitchScreen(MyScreen::Get());
		printf("On Create\n");
		return true;
	}

	void OnClose() override
	{
		printf("On Close\n");
	}

	bool OnUpdate(double frametime) override
	{
		SDL_SetWindowTitle(m_pWindow, std::to_string(frametime).c_str());
		return true;
	}
};

#undef main

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	MyWindow window;

	try
	{
		window.Launch(true);
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	while (window.IsOpen())
		true;

	window.Stop();

	return 0;
}