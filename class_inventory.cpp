#include "class_inventory.h"
#include "graphics.h"
#include "miscellaneous.h"
#include <iostream>

using std::cout;
using std::endl;

Inventory_T::Inventory_T()
{
	background = NULL;
	item_count = 0;
	item       = NULL;
	view_index = 0;
}

void Inventory_T::Add(Item_T &new_item)
{
	if (NULL == item)
	{
		item_count++;
		item = new Item_T* [item_count];
		item[item_count - 1] = &new_item;
	}
	else
	{
		/* Check if an item which we want to add already exists in the item array. */
		bool item_already_exists = false;
		for (int i = 0; i < item_count; i++)
		{
			if (item[i]->id == new_item.id)
			{
				item_already_exists = true;
				break;
			}
		}

		if (false == item_already_exists)
		{
			/* Save the item pointer array to temp. */
			Item_T** temp = new Item_T* [item_count];
			for (int i = 0; i < item_count; i++)
			{
				temp[i] = item[i];
			}

			delete[] item;
			item_count++;

			/* Load the item pointer array from temp. */
			item = new Item_T* [item_count];
			for (int i = 0; i < item_count - 1; i++)
			{
				item[i] = temp[i];
			}

			item[item_count - 1] = &new_item;
		}
		else
		{
			// TODO: output ID names instead of ID numbers.
			cout << "WARNING (Inventory_T::Add()): Item with ID=" << new_item.id << " already exists in inventory" << endl;
		}
	}
}

Item_T & Inventory_T::Remove(const Item_T::Id_T item_id)
{
	Item_T* retval = NULL;

	if (NULL != item)
	{
		/* Check if an item which we want to remove exists in the item array. */
		bool item_exists = false;
		for (int i = 0; i < item_count; i++)
		{
			if (item[i]->id == item_id)
			{
				item_exists = true;
				break;
			}
		}

		if (true == item_exists)
		{
			if (1 == item_count)
			{
				retval = item[0];
				delete[] item;
				item = NULL;
				item_count = 0;
			}
			else
			{
				/* Find the item which we want to remove and copy all other items to a temp array. */
				Item_T** temp = new Item_T* [item_count - 1];
				int j = 0;
				for (int i = 0; i < item_count; i++)
				{
					if (item[i]->id == item_id)
					{
						retval = item[i];
					}
					else
					{
						temp[j] = item[i];
						j++;
					}
				}
				delete[] item;

				item_count--;

				/* Copy the temp array back to the item array. */
				item = new Item_T* [item_count];
				for (int i = 0; i < item_count; i++)
				{
					item[i] = temp[i];
				}
				delete[] temp;
			}
		}
		else
		{
			// TODO: output ID names instead of ID numbers.
			//cout << "WARNING (Scene_T::RemoveItem()): Item with ID=" << item_id << " does not exist in a scene with ID=" << this->id << endl;
		}
	}

	return *retval;
}

void Inventory_T::ShiftView(const Direction_T dir)
{
	if ((view_index + dir >= 0) && (view_index + VISIBLE_ITEMS_COUNT + dir <= item_count))
	{
		view_index += dir;
	}
}

void Inventory_T::Draw(void) const
{
	/* Print background. */
	viewporttype viewport;
	setviewport(LEFT, TOP, RIGHT, BOTTOM, 0);
	getviewsettings(&viewport);
	setbkcolor(LIGHTGREEN);
	clearviewport();

	/* Print frame around the inventory window. */
	//setcolor(GREEN);
	//Frame(0, 0 , GetMaxX(viewport), GetMaxY(viewport), FRAME_THICKNESS);

	/* Print slot frames. */
	setcolor(GREEN);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	int OFFSET_X = SPACE_FOR_ARROW;
	int OFFSET_Y = 0;
	for (int i = 0; i < VISIBLE_ITEMS_COUNT; i++)
	{
		Frame(OFFSET_X + i * (SLOT_SIZE - FRAME_THICKNESS)            , OFFSET_Y + 0,
			OFFSET_X + i * (SLOT_SIZE - FRAME_THICKNESS) + SLOT_SIZE, OFFSET_Y + SLOT_SIZE,
			FRAME_THICKNESS);
	}

	/* Print inventory items. */
	for (int i = view_index, j = 0; i < view_index + VISIBLE_ITEMS_COUNT; i++, j++)
	{
		if ((i >= 0) && (i < item_count))
		{
			/* Print item. */
			OFFSET_X = FRAME_THICKNESS + SPACE_FOR_ARROW;
			OFFSET_Y = FRAME_THICKNESS;
			item[i]->SetPosition(OFFSET_X + j * (SLOT_SIZE - FRAME_THICKNESS), OFFSET_Y);
			item[i]->SetSize(ITEM_SIZE, ITEM_SIZE);
			item[i]->Draw();
		}
		else
		{
			/* Print "Empty". */
			OFFSET_X = SPACE_FOR_ARROW + (SLOT_SIZE / 2);
			OFFSET_Y = FRAME_THICKNESS;
			int x = OFFSET_X + j * (SLOT_SIZE - FRAME_THICKNESS);
			int y = OFFSET_Y + SLOT_SIZE / 2;
			setcolor(GREEN);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			outtextxy(x, y, "Empty");
		}
	}

	/* Print selection frame. */
	//setcolor(YELLOW);
	//const int SELECT = 2;
	//OFFSET_X = 2 * FRAME_THICKNESS;
	//OFFSET_Y = 2 * FRAME_THICKNESS;
	//Frame(SELECT * (SLOT_SIZE - FRAME_THICKNESS) + OFFSET_X , OFFSET_Y + 0,
	//	SELECT * (SLOT_SIZE - FRAME_THICKNESS) + SLOT_SIZE, SLOT_SIZE,
	//	  FRAME_THICKNESS);

	setviewport(0, 0, getmaxx(), getmaxy(), 0);
}
