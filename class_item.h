#ifndef CLASS_ITEM_T
#define CLASS_ITEM_T

#include "datatype.h"
#include "class_element.h"

class Item_T : public Element_T
{
	private:
		const char* bitmap;

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

		Id_T id;
		Type_T type;

		Item_T(const Id_T init_id               = NONE,
			   const int init_x                 = 0,
			   const int init_y                 = 0,
			   const bool init_frame            = false,
			   const Type_T init_type           = STATIC,
			   const SceneID_T init_go_to_scene = SCENE_NONE,
			   const int init_width             = 50,
			   const int init_height            = 50,
			   const char* const init_bitmap    = "N/A",
			   const char* const init_text      = "N/A");
		void Draw(void) const;

		friend const ostream& operator<<(const ostream& os, Item_T & item);
};

#endif
