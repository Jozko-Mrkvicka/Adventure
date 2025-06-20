#ifndef CLASS_ITEM_T
#define CLASS_ITEM_T

#include "datatype.h"
#include "class_element.h"

class Item_T : public Element_T
{
	private:

	public:
		enum Type_T
		{
			STATIC      = 0,
			INTERACTIVE = 1,
			COLLECTIBLE = 2,
			LINK        = 3,
		};

		/* By design, order of items in the gItem array must be the same as order of enums in the ItemId_T type. */
		enum Id_T
		{
			NONE         = -1,
			KOFOLA       =  0,
			RUM          =  1,
			GUITAR       =  2,
			NOTEBOOK     =  3,
			FRIDGE       =  4,
			OVEN         =  5,
			BOOTS        =  6,
			PICTURE      =  7,
			TV           =  8,
			DOOR         =  9,
			CAR          = 10,
			STUDIO_ENTRY = 11,
		};

		Type_T type;

		Item_T(const char* const text,
			   const int         id,
			   const int         x,
			   const int         y,
			   const int         width,
			   const int         height,
			   const char* const bitmap,
			   const bool        frame,
			   const SceneID_T   go_to_scene,
			   const Type_T      init_type);

		void Draw(void) const;

		friend const ostream& operator<<(const ostream& os, Item_T & item);
};

#endif
