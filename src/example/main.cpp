#include "SDLF.hpp"

#include <iostream>

using namespace sf;

int Callback(void* userdata, SDL_Event* event)
{
	std::cout << event->type << std::endl;
	return 0;
}

class MyWindow : public IWindow
{
public:
	MyWindow() :
		IWindow(Vec2u(800, 800), Vec2i(100, 100), "MyWindow")
	{

	}

private:
	virtual bool OnCreate() override
	{
		printf("On Create\n");
		return true;
	}

	virtual void OnClose() override
	{
		printf("On Close\n");
	}

	virtual bool OnUpdate(double frametime) override
	{
		SDL_SetWindowTitle(m_pWindow, std::to_string(frametime).c_str());
		return true;
	}
};

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	MyWindow window;
	window.AddEventCallback(Callback, nullptr);

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