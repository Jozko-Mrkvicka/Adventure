#include "graphics.h"
#include "miscellaneous.h"
#include "class_button.h"

static const int RAKUSKA_KONSTANTA = 2;

Button_T::Button_T(const char* const text,
				   const int         id,
				   const int         pos_x,
				   const int         pos_y,
				   const char* const bitmap,
				   const bool        frame,
				   const SceneID_T   go_to_scene,
				   const bool        init_click) : Element_T(text,
															 id,
															 pos_x,
															 pos_y,
															 (ARROW_LEFT == id) || (ARROW_RIGHT == id) ?     LETTER_WIDTH                      : LETTER_WIDTH * strlen(text),
															 (ARROW_LEFT == id) || (ARROW_RIGHT == id) ? 3 * LETTER_HEIGHT + RAKUSKA_KONSTANTA : LETTER_HEIGHT,
															 bitmap,
															 frame,
															 go_to_scene)
{
	clicable    = init_click;
	header      = false;
}

void Button_T::Draw(void) const
{
	setbkcolor(true == header ? GREEN : true == highlighted ? RED : LIGHTGREEN);
	setcolor(true == header ? LIGHTGREEN : GREEN);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(DEFAULT_FONT, 0, 3);
	bgiout << text;
	outstreamxy(pos_x, pos_y);

	if (true == frame)
	{
		setcolor(GREEN);
		Frame(pos_x          - FRAME_THICKNESS,
			  pos_y          - FRAME_THICKNESS,
			  pos_x + width  + FRAME_THICKNESS,
			  pos_y + height + FRAME_THICKNESS,
			  FRAME_THICKNESS);
	}
}

const char* const Button_T::GetText(void) const
{
	return ARROW_LEFT == id ? " <<<  " : ARROW_RIGHT == id ? "  >>> " : Element_T::GetText();
}
