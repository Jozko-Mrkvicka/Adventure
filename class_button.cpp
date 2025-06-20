#include "class_button.h"
#include "graphics.h"
#include "miscellaneous.h"

Button_T::Button_T(const Id_T init_id,
				   const int pos_x,
				   const int pos_y,
				   const int width,
				   const int height,
				   const bool frame,
				   const bool init_click,
				   const SceneID_T go_to_scene,
				   const char* const text) : Element_T(pos_x, pos_y, width, height, frame, go_to_scene, text)
{
	id          = init_id;
	clicable    = init_click;
	header      = false;
}
void Button_T::Draw(const int offset_x, const int offset_y) const
{
	setcolor(GREEN);
	setfillstyle(SOLID_FILL, GREEN);

	int n_points = 4;

- Nahradit vykreslovanie sipiek pomocou obrazku.
	if (ARROW_LEFT == id)
	{
		int points[] =
		{
			pos_x + width, pos_y,
			pos_x + width, pos_y + height,
			pos_x,  pos_y + (pos_y + height - pos_y) / 2,
			pos_x + width, pos_y
		};

		fillpoly(n_points, points);
		Frame(pos_x, pos_y, pos_x + width, pos_y + height, 6 /* TODO: Somehow bind thickness to Inventory_T::FRAME_THICKNESS */);
	}
	else if (ARROW_RIGHT == id)
	{
		int points[] =
		{
			pos_x,  pos_y,
			pos_x,  pos_y + height,
			pos_x + width, pos_y + (pos_y + height - pos_y) / 2,
			pos_x,  pos_y
		};

		fillpoly(n_points, points);
		Frame(pos_x, pos_y, pos_x + width, pos_y + height, 6 /* TODO: Somehow bind thickness to Inventory_T::FRAME_THICKNESS */);
	}
	else
	{
		//const int OFFSET_X = 0;
		//const int OFFSET_Y = 5;
		const int x = /*OFFSET_X*/ /*offset_x + */ pos_x /* + (pos_x + width - pos_x) / 2 */;
		const int y = /*OFFSET_Y*/ /*offset_y + */ pos_y  /* + (pos_y + height - pos_y) / 2 */;
		
		setbkcolor(true == header ? GREEN : true == highlighted ? RED : LIGHTGREEN);
		setcolor(true == header ? LIGHTGREEN : GREEN);
		settextjustify(LEFT_TEXT/*CENTER_TEXT*/, TOP_TEXT/*VCENTER_TEXT*/);
		settextstyle(DEFAULT_FONT, 0, 3);
		outtextxy(x, y, (char*)text);


		//const int FRAME_THICKNESS = 6;
		//static const int LETTER_HEIGHT = 23;
		//static const int LETTER_WIDTH = 24;

		//const int FRAME_WIDTH  = 2 * FRAME_THICKNESS + strlen(name) * LETTER_WIDTH;
		//const int FRAME_HEIGHT = 1 * FRAME_THICKNESS + LETTER_HEIGHT;

		//const int FRAME_OFFSET_X = x;//pos_x - FRAME_THICKNESS;
		//const int FRAME_OFFSET_Y = y;// pos_y /*- FRAME_THICKNESS*/;

		//setcolor(GREEN);
		//Frame(FRAME_OFFSET_X,
		//	  FRAME_OFFSET_Y,
		//	  FRAME_OFFSET_X + FRAME_WIDTH,
		//	  FRAME_OFFSET_Y + FRAME_HEIGHT,
		//	  FRAME_THICKNESS);
	}
}
