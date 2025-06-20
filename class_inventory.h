#ifndef CLASS_INVENTORY_T
#define CLASS_INVENTORY_T

#include "class_item.h"
#include "class_collection.h"
#include "graphics.h"

class Inventory_T : public Collection_T
{
	private:
		enum Color_T
		{
			BACKGROUND = LIGHTGREEN,
			FRAME      = GREEN,
			TEXT       = GREEN,
		};

		static const int SLOT_SIZE = 100;
		static const int VISIBLE_ITEMS_COUNT = 5;
		static const int FRAME_THICKNESS = 6;
		int view_index;

	public:
		enum Direction_T
		{
			SCROLL_LEFT  = -1,
			SCROLL_RIGHT = 1
		};

		Inventory_T(const char* const text,
					const int         pos_x,
					const int         pos_y,
					const char* const bitmap);

		void ShiftView(const Direction_T dir);
		void Draw(void) const;
};

#endif
