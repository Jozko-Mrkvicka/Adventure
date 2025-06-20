#ifndef CLASS_SCENE_T
#define CLASS_SCENE_T

#include <iostream>      /* Definition of NULL. */
#include "datatype.h"
#include "class_item.h"

class Scene_T
{
	private:
		static const int TOP    = 0; 
		static const int LEFT   = 0;
		static const int BOTTOM = 378; // TODO: Bind it somehow with constant Inventory_T->TOP!!
		static const int RIGHT  = 639 - 10; /* There must be some bug in the WinBGIm library. */

		SceneID_T id;
		const char* background;

	public:
		int item_count;
		Item_T** item;

		Scene_T(SceneID_T ident, const char* scene_bitmap);
		void AddItem(Item_T *new_item);
		Item_T* RemoveItem(const Item_T::Id_T item_id);
		Item_T::Id_T getItemUnderCursor(const int cursor_x, const int cursor_y) const;
		void Draw(void) const;
};

#endif
