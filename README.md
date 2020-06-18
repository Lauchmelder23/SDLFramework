# SDL Framework

A small wrapper around SDL2 that makes development of non-demanding small projects easier.

## Installation

Add this project as a git submodule and include it in your CMake project. Alternatively you can clone the repository, build the binaries and use them like any other library.

## Usage

This library provides a window interface, that could be used directly, however it is better to derive from it and overload some (or all) of the callback functions.

```cpp
class MyWindow : public sf::IWindow
{
public:
  MyWindow() { /* Constructor Stuff */ }
  
private:
  virtual bool OnCreate() { return true; }
	virtual void OnClose() { }
	virtual bool OnEvent(const SDL_Event& event) { return true;}
	virtual bool OnUpdate(double frametime) { return true; }
	virtual void OnRender(SDL_Renderer* renderer) { }
};
```

Then simple instantiate your new window and call `IWindow::Launch(threaded)` on it. `threaded` controls wether the message loop of your window will be executed in the main thread, or in a worker thread to allow for multiple parallel windows.

### What do the callbacks do?
The callbacks in `sf::IWindow` can be overridden and are called at certain points in the windows lifecycle:

* `bool IWindow::OnCreate()` is called immediately after the SDL_Window and SDL_Renderer are created, and before the message loop starts. If this callback returns `false`, the message loop will not start and the windows life cycle ends here
* `void IWindow::OnClose()` is called immediately after exiting the message loop, and before any objects are destroyed
* `bool OnEvent(const SDL_Event& event)` gets called for each event that is polled from the message queue. If it returns `false`, then `sd::IWindow` will not process that same event again. (e.g. you can block `sf::IWindow` from closing on an `SDL_QUIT` event.
* `bool OnUpdate(double frametime)` gets called every frame right before the rendering step. It provides the callback with the current frametime. Returnung `false` will quit the message loop.
* `void OnRender(SDL_Renderer* renderer)` gets called every frame right after the update step. There is no need to call `SDL_RenderPresent` as the message loop does that. The message loop does not clear the screen however.

### What are screens?
If your program will always have the same content, then this isn't of interest to you. 
However if you plan on having different menus, different types of screens etc, then you might wanna read this.
A screen is basically a window without a message loop. It has (almost) the same callbacks as an `sf::IWindow`,
the only difference being `IScreen::OnFocus()` and `IScreen::OnDefocus()` which are called when a screen is switched to, or switched from.
A window holds a pointer to an `sf::IScreen`. If that pointer is `nullptr`, the above callbacks will be called. If it isn't `nullptr` then the callbacks from the `sf::IScreen` will be called instead.
You can switch screens via a the `IWindow::SwitchScreen()` function.

To use a screen, you simple derive from `sf::IScreen` and implement the callbacks. `IScreen::OnFocus()` receives the calling `sf::IWindow` as a parameter.