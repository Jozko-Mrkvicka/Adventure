#include "class_control.h"

Control_T::Control_T()
{
	prev_highlighted_button = -1;
}

Button_T::Id_T Control_T::getButtonUnderCursor(const int cursor_x, const int cursor_y) const
{
	Button_T::Id_T button_under_cursor = Button_T::NONE;

	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		if (true == button[i].isCursorAbove(cursor_x, cursor_y))
		{
			button_under_cursor = (Button_T::Id_T)i;
			break;
		}
	}

	return button_under_cursor;
}

void Control_T::Draw(void) const
{
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		button[i].Draw();
	}
}
