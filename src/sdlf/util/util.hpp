#include "Vector2.hpp"

#define THROW_IF_NULLPTR(x) { if(x == nullptr) throw SDL_GetError(); }
#define IS_NULLPTR(x) ( x == nullptr ? true : false )
#define IS_NOT_NULLPTR(x) !IS_NULLPTR(x)