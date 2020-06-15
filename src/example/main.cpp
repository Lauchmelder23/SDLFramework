#include "SDLF.hpp"

#include <iostream>

using namespace sf;

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
		printf("Frame took %f seconds\n", frametime);
		return true;
	}
};

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