#ifndef CLASS_SCENE_T
#define CLASS_SCENE_T

#include <iostream>      /* Definition of NULL. */
#include "datatype.h"
#include "class_item.h"
#include "class_collection.h"

class Scene_T : public Collection_T
{
	private:

	public:
		Scene_T(const char* const text, 
				const int         id,
				const int         pos_x,
				const int         pos_y,
				const int         width,
				const int         height,
				const char* const bitmap);

		friend ostream& operator<<(ostream& os, Scene_T scene);
};

#endif
