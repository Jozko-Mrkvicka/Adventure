#include "class_inventory.h"
#include "graphics.h"
#include "miscellaneous.h"
#include <iostream>

using std::cout;
using std::endl;

Inventory_T::Inventory_T(const char* const text, 
						 const int         pos_x,
						 const int         pos_y,
						 const char* const bitmap) : Collection_T(text, -1, pos_x, pos_y, 0, 0, bitmap)
{
	view_index = 0;
}

void Inventory_T::ShiftView(const Direction_T dir)
{
	if ((view_index + dir >= 0) && (view_index + VISIBLE_ITEMS_COUNT + dir <= count))
	{
		view_index += dir;
	}
}

void Inventory_T::Draw(void) const
{
	/* Print inventory items. */
	for (int i = view_index, j = 0; i < view_index + VISIBLE_ITEMS_COUNT; i++, j++)
	{
		const int X = pos_x + j * (SLOT_SIZE - FRAME_THICKNESS);
		const int Y = pos_y;

		/* Print item background. */
		setfillstyle(SOLID_FILL, Color_T::BACKGROUND);
		bar(X, Y, X + SLOT_SIZE, Y + SLOT_SIZE);

		/* Print slot frames. */
		setcolor(Color_T::FRAME);
		Frame(X, Y, X + SLOT_SIZE, Y + SLOT_SIZE, FRAME_THICKNESS);

		if ((i >= 0) && (i < count))
		{
			/* Print item. */
			element[i]->SetPosition(X + FRAME_THICKNESS , Y + FRAME_THICKNESS);
			element[i]->SetSize(SLOT_SIZE - 2 * FRAME_THICKNESS, SLOT_SIZE - 2 * FRAME_THICKNESS);
			element[i]->Draw();
		}
		else
		{
			/* Print "Empty". */
			setcolor(Color_T::TEXT);
			setbkcolor(Color_T::BACKGROUND);
			settextstyle(DEFAULT_FONT, 0, 0);
			settextjustify(CENTER_TEXT, VCENTER_TEXT);
			outtextxy(X + SLOT_SIZE / 2, Y + SLOT_SIZE / 2, "Empty");
		}
	}
}
