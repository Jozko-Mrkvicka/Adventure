#include "class_map.h"
#include "graphics.h"

Map_T::Map_T(const char* const text,
			 const int         pos_x,
			 const int         pos_y,
			 const int         width,
			 const int         height,
			 const char* const bitmap) : Collection_T(text, -1, pos_x, pos_y, width, height, bitmap)
{
	selected_element = Node_T::HOME;
}
