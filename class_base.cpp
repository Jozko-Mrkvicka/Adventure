#include "class_base.h"

Base_T::Base_T(const char* const init_text,
			   const int         init_id,
			   const int         init_pos_x,
			   const int         init_pos_y,
			   const int         init_width,
			   const int         init_height,
			   const char* const init_bitmap) : bitmap(init_bitmap), text(init_text), id(init_id)
{
	pos_x  = init_pos_x;
	pos_y  = init_pos_y;
	width  = init_width;
	height = init_height;
}

const ostream& operator<<(const ostream& os, Base_T& base)
{
	cout << endl;
	cout << "------------------------" << endl;
	cout << "Base_T class properties:" << endl;
	cout << "TEXT   = " << (NULL == base.text ? "NULL" : base.text) << endl;
	cout << "ID     = " << base.id     << endl;
	cout << "POS_X  = " << base.pos_x  << endl;
	cout << "POS_Y  = " << base.pos_y  << endl;
	cout << "WIDTH  = " << base.pos_y  << endl;
	cout << "HEIGHT = " << base.pos_y  << endl;
	cout << "BITMAP = " << (NULL == base.bitmap ? "NULL" : base.bitmap) << endl;
	cout << endl;

	return os;
}
