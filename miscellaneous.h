#ifndef MISCELLANEOUS
#define MISCELLANEOUS

#include "graphics.h"

void Frame(const int left, const int top, const int right, const int bottom, const int thickness = 3, const int linestyle = SOLID_LINE);

#endif

//class Collection_T
//{
//	private:
//		//SceneID_T id;
//		const char* background;
//		int item_count;
//		Item_T** item;
//
//	public:
//		Collection_T();
//		void Add(Item_T* new_item);
//		Item_T* Remove(ItemId_T item_id);
//		void Draw(void);
//};
//
//Collection_T::Collection_T()
//{
//	background = NULL;
//	item_count = 0;
//	item       = NULL;
//}
//
//void Collection_T::Add(Item_T *new_item)
//{
//	if (NULL == item)
//	{
//		item_count++;
//		item = new Item_T* [item_count];
//		item[item_count - 1] = new_item;
//	}
//	else
//	{
//		/* Check if an item which we want to add already exists in the item array. */
//		bool item_already_exists = false;
//		for (int i = 0; i < item_count; i++)
//		{
//			if (item[i]->id == new_item->id)
//			{
//				item_already_exists = true;
//				break;
//			}
//		}
//
//		if (false == item_already_exists)
//		{
//			/* Save the item pointer array to temp. */
//			Item_T** temp = new Item_T* [item_count];
//			for (int i = 0; i < item_count; i++)
//			{
//				temp[i] = item[i];
//			}
//
//			delete[] item;
//			item_count++;
//
//			/* Load the item pointer array from temp. */
//			item = new Item_T* [item_count];
//			for (int i = 0; i < item_count - 1; i++)
//			{
//				item[i] = temp[i];
//			}
//
//			item[item_count - 1] = new_item;
//		}
//		else
//		{
//			// TODO: output ID names instead of ID numbers.
//			//cout << "WARNING (Scene_T::AddItem()): Item with ID=" << new_item->id << " already exists in a scene with ID=" << this->id << endl;
//		}
//	}
//}
//
//Item_T* Collection_T::Remove(ItemId_T item_id)
//{
//	Item_T* retval = NULL;
//
//	if (NULL != item)
//	{
//		/* Check if an item which we want to remove exists in the item array. */
//		bool item_exists = false;
//		for (int i = 0; i < item_count; i++)
//		{
//			if (item[i]->id == item_id)
//			{
//				item_exists = true;
//				break;
//			}
//		}
//
//		if (true == item_exists)
//		{
//			if (1 == item_count)
//			{
//				retval = item[0];
//				delete[] item;
//				item = NULL;
//				item_count = 0;
//			}
//			else
//			{
//				/* Find the item which we want to remove and copy all other items to a temp array. */
//				Item_T** temp = new Item_T* [item_count - 1];
//				int j = 0;
//				for (int i = 0; i < item_count; i++)
//				{
//					if (item[i]->id == item_id)
//					{
//						retval = item[i];
//					}
//					else
//					{
//						temp[j] = item[i];
//						j++;
//					}
//				}
//				delete[] item;
//
//				item_count--;
//
//				/* Copy the temp array back to the item array. */
//				item = new Item_T* [item_count];
//				for (int i = 0; i < item_count; i++)
//				{
//					item[i] = temp[i];
//				}
//				delete[] temp;
//			}
//		}
//		else
//		{
//			// TODO: output ID names instead of ID numbers.
//			//cout << "WARNING (Scene_T::RemoveItem()): Item with ID=" << item_id << " does not exist in a scene with ID=" << this->id << endl;
//		}
//	}
//
//	return retval;
//}
//
//void Collection_T::Draw(void)
//{
//	/* Print background image. */
//	readimagefile(background, 0, 0, getmaxx(), getmaxy());
//
//	for (int i = 0; i < item_count; i++)
//	{
//		item[i]->Draw();
//	}
//}
