#ifndef CLASS_INVENTORY_T
#define CLASS_INVENTORY_T

#include "class_item.h"

class Inventory_T
{
	private:
		static const int VISIBLE_ITEMS_COUNT = 5;
		static const int FRAME_THICKNESS = 6;
		static const int SPACE_FOR_ARROW = 31 - FRAME_THICKNESS;
		static const int LEFT      = 0;
		static const int TOP       = 379; // TODO: Bind somehow to the Scene dimensions.
		static const int BOTTOM    = 479 - 9; /* There must be some bug in the WinBGIm library. */
		static const int SLOT_SIZE = (BOTTOM - TOP);
		static const int ITEM_SIZE = (BOTTOM - TOP) - FRAME_THICKNESS * 2;
		static const int RIGHT = 639;//LEFT + (SLOT_SIZE - FRAME_THICKNESS) * VISIBLE_ITEMS_COUNT + FRAME_THICKNESS + 2 * SPACE_FOR_ARROW;

		const char* background;
		int view_index;

	public:
		enum Direction_T
		{
			SCROLL_LEFT  = -1,
			SCROLL_RIGHT = 1
		};

int item_count;
Item_T** item;
		Inventory_T();
		void Add(Item_T &new_item);
		Item_T & Remove(const Item_T::Id_T item_id);
		void ShiftView(const Direction_T dir);
		void Draw(void) const;
};

#endif
