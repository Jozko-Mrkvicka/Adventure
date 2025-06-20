#include "class_element.h"

Element_T::Element_T(const char* const text,
					 const int         id,
					 const int         pos_x,
					 const int         pos_y,
					 const int         width,
					 const int         height,
					 const char*       bitmap,
					 bool              init_frame,
					 SceneID_T         init_go_to_scene) : Base_T(text, id, pos_x, pos_y, width, height, bitmap)
{
	highlighted = false;
	selected    = false;
	visible     = false;
	frame       = init_frame;
	go_to_scene = init_go_to_scene;
}

bool Element_T::IsCursorAbove(const int cursor_x, const int cursor_y) const
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

const ostream& operator<<(const ostream &os, Element_T &element)
{
	Base_T &base = element;

	cout << base;
	cout << "Element_T class properties:"            << endl;
	cout << "HIGHLIGHTED = " << element.highlighted  << endl;
	cout << "SELECTED    = " << element.selected     << endl;
	cout << "VISIBLE     = " << element.visible      << endl;
	cout << "FRAME       = " << element.frame        << endl;
	cout << "GOTO_SCENE  = " << element.go_to_scene  << endl;
	cout << endl;

	return os;
}
