#ifndef CLASS_BUTTON_T
#define CLASS_BUTTON_T

#include "class_element.h"

class Button_T : public Element_T
{
	private:
		bool clicable;

	public:
		enum Id_T
		{
			NONE        = -1,
			ARROW_LEFT  =  0,
			ARROW_RIGHT =  1,
			MAP         =  2,
			MENU        =  3,
			NEW_GAME    =  4,

			SAVE,
			LOAD,
			SETTINGS,
			CREDITS,
			EXIT,
		};

		Id_T id;
		bool header;

		Button_T(const Id_T init_id          = NONE,
				 const int pos_x             = 0,
				 const int pos_y             = 0,
				 const int width             = 50,
				 const int height            = 50,
				 const bool frame            = false,
				 const bool init_click       = false,
				 const SceneID_T go_to_scene = SCENE_NONE,
				 const char* const text      = "N/A");
		
		void Draw(const int offset_x = 0, const int offset_y = 0) const;
};

#endif
