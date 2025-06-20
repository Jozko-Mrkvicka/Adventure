#include "class_scene.h"
#include "graphics.h"
#include <iostream>

using std::cout;
using std::endl;

Scene_T::Scene_T(const char* const text,
				 const int         id,
				 const int         pos_x,
				 const int         pos_y,
				 const int         width,
				 const int         height,
				 const char* const bitmap) : Collection_T(text, id, pos_x, pos_y, width, height, bitmap)
{
}

ostream& operator<<(ostream& os, Scene_T scene)
{
	cout << "Scene = " << (Collection_T) scene;
	return os;
}
