#include "class_element.h"

Element_T::Element_T(const int init_pos_x, 
					 const int init_pos_y,
					 const int init_width,
					 const int init_height,
					 bool init_frame,
					 SceneID_T init_go_to_scene,
					 const char* const init_text) : text(init_text)
{
	pos_x       = init_pos_x;
	pos_y       = init_pos_y;
	width       = init_width;
	height      = init_height;
	highlighted = false;
	selected    = false;
	frame       = init_frame;
	go_to_scene = init_go_to_scene;
}

bool Element_T::isCursorAbove(const int cursor_x, const int cursor_y) const
{
	bool retval = false;

	if ((cursor_x < pos_x + width) &&
		(cursor_x > pos_x) &&
		(cursor_y < pos_y + height) &&
		(cursor_y > pos_y))
	{
		retval = true;
	}

	return retval;
}

const ostream& operator<<(const ostream& os, Element_T & element)
{
	cout << endl;
	cout << "TEXT        = \"" << element.text << "\"" << endl;
	cout << "POSITION_X  = " << element.pos_x          << endl;
	cout << "POSITION_Y  = " << element.pos_y          << endl;
	cout << "HIGHLIGHTED = " << element.highlighted    << endl;
	cout << "SELECTED    = " << element.selected       << endl;
	cout << "FRAME       = " << element.frame          << endl;

	return os;
}
