#ifndef CLASS_CONTROL_T
#define CLASS_CONTROL_T

#include "class_button.h"

class Control_T
{
	private:
		static const int HEIGHT = 30;
		static const int WIDTH  = 90;
		static const int BUTTON_COUNT = 4;

	public:
		int prev_highlighted_button;
		Button_T button[BUTTON_COUNT] =
		{
			/* For the arrow buttons, the height and width dimensions are intentionally set vice versa. */
			/*       Id                     X    Y    W             H             Frame  Click  GoToScene   Text         */
			Button_T(Button_T::ARROW_LEFT,    0, 379,       HEIGHT, 379 + WIDTH,  false, false, SCENE_NONE, "Arrow Left" ),
			Button_T(Button_T::ARROW_RIGHT, 451, 379, 451 + HEIGHT, 379 + WIDTH,  false, false, SCENE_NONE, "Arrow Right"),
			Button_T(Button_T::MAP,         476, 379, 476 + WIDTH,  379 + HEIGHT, false, false, SCENE_NONE, "Map"        ),
			Button_T(Button_T::MENU,        476, 405, 476 + WIDTH,  405 + HEIGHT, false, false, SCENE_NONE, "Menu"       ),
		};

		Control_T();
		Button_T::Id_T getButtonUnderCursor(const int cursor_x, const int cursor_y) const;
		void Draw(void) const;
};

#endif
