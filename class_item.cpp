#include "class_item.h"
#include "graphics.h"
#include "definitions.h"
#include "miscellaneous.h"

Item_T::Item_T(const char* const text,
			   const int         id,
			   const int         x,
			   const int         y,
			   const int         width,
			   const int         height,
			   const char* const bitmap,
			   const bool        frame,
			   const SceneID_T   go_to_scene,
			   const Type_T      init_type) : Element_T(text, id, x, y, width, height, bitmap, frame, go_to_scene)
{
	type = init_type;
}

void Item_T::Draw(void) const
{
	if (NULL != bitmap)
	{
		readimagefile(bitmap, pos_x, pos_y, pos_x + width, pos_y + height);
	}

	if (true == frame)
	{
		setcolor(YELLOW);
		Frame(pos_x, pos_y, pos_x + width, pos_y + height, FRAME_THICKNESS);
	}
}

const ostream& operator<<(const ostream& os, Item_T& item)
{
	Element_T& element = item;
		
	cout << element;
	cout << "Item_T class properties:" << endl;
	cout << "ID   = " << item.id   << endl;
	cout << "TYPE = " << item.type << endl;
	cout << endl;

	return os;
}
