#include "class_item.h"
#include "graphics.h"
#include "definitions.h"
#include "miscellaneous.h"

Item_T::Item_T(const Id_T init_id,
			   const int init_x,
			   const int init_y,
			   const bool init_frame,
			   const Type_T init_type,
			   const SceneID_T init_go_to_scene,
			   const int init_width,
			   const int init_height,
			   const char* const init_bitmap,
			   const char* const init_text) : Element_T(init_x, init_y, init_width, init_height, init_frame, init_go_to_scene, init_text)
{
	id          = init_id;
	type        = init_type;
	bitmap      = init_bitmap;
}

//bool Item_T::isCursorAbove(const int cursor_x, const int cursor_y) const
//{
//	bool retval = false;
//
//	if ((cursor_x < pos_x + width) &&
//		(cursor_x > pos_x) &&
//		(cursor_y < pos_y + height) &&
//		(cursor_y > pos_y))
//	{
//		retval = true;
//	}
//
//	return retval;
//}

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

const ostream& operator<<(const ostream& os, Item_T & item)
{
	Element_T &element = item;

	cout << element;
	cout << "WIDTH       = " << item.width       << endl;
	cout << "HEIGHT      = " << item.height      << endl;
	cout << "BITMAP      = " << item.bitmap      << endl;
	cout << "ID          = " << item.id          << endl;
	cout << "TYPE        = " << item.type        << endl;
	cout << "GOTO        = " << item.go_to_scene << endl;

	return os;
}
