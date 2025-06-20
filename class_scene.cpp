#include "class_scene.h"
#include "graphics.h"
#include <iostream>

using std::cout;
using std::endl;

Scene_T::Scene_T(SceneID_T ident, const char* scene_bitmap)
{
	id         = ident;
	background = scene_bitmap;
	item_count = 0;
	item       = NULL;
}

/* TODO: Zeby adept na <TEMPLATE> ?? */
void Scene_T::AddItem(Item_T *new_item)
{
	if (NULL == item)
	{
		item_count++;
		item = new Item_T* [item_count];
		item[item_count - 1] = new_item;
	}
	else
	{
		/* Check if an item which we want to add already exists in the item array. */
		bool item_already_exists = false;
		for (int i = 0; i < item_count; i++)
		{
			if (item[i]->id == new_item->id)
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

			item[item_count - 1] = new_item;
		}
		else
		{
			// TODO: output ID names instead of ID numbers.
			cout << "WARNING (Scene_T::AddItem()): Item with ID=" << new_item->id << " already exists in a scene with ID=" << this->id << endl;
		}
	}
}

Item_T* Scene_T::RemoveItem(const Item_T::Id_T item_id)
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
			cout << "WARNING (Scene_T::RemoveItem()): Item with ID=" << item_id << " does not exist in a scene with ID=" << this->id << endl;
		}
	}

	return retval;
}

// TODO: Kandidat na <TEMPLATE>?
Item_T::Id_T Scene_T::getItemUnderCursor(const int cursor_x, const int cursor_y) const
{
	Item_T::Id_T item_under_cursor = Item_T::NONE;

	for (int i = 0; i < item_count; i++)
	{
		if (true == item[i]->isCursorAbove(cursor_x, cursor_y))
		{
			item_under_cursor = (Item_T::Id_T)i;
			break;
		}
	}

	return item_under_cursor;
}

void Scene_T::Draw(void) const
{
	/* Print background image. */
	readimagefile(background, 0, 0, RIGHT, BOTTOM);

	/* Print items. */
	for (int i = 0; i < item_count; i++)
	{
		item[i]->Draw();
	}
}
