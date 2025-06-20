#ifndef CLASS_BUTTON_T
#define CLASS_BUTTON_T

#include "class_element.h"

class Button_T : public Element_T
{
	private:
		static const int LETTER_HEIGHT = 23;
		static const int LETTER_WIDTH  = 24;

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

		bool header;

		Button_T(const char* const text,
				 const int         id,
				 const int         pos_x,
				 const int         pos_y,
				 const char* const bitmap,
				 const bool        frame,
				 const SceneID_T   go_to_scene,
				 const bool        init_click);
		
		const char* const Button_T::GetText(void) const;
		void Draw(void) const;
};

#endif
