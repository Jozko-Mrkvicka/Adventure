#ifndef CLASS_BASE_T
#define CLASS_BASE_T

#include <iostream>

using std::ostream;
using std::cout;
using std::endl;

class Base_T
{
	private:

	protected:
		const char* const text;
		const char* const bitmap;

		int pos_x;
		int pos_y;
		int width;
		int height;

		int id;

	public:
		Base_T(const char* const init_text,
			   const int         init_id,
			   const int         init_pos_x,
			   const int         init_pos_y,
			   const int         init_width,
			   const int         init_height,
			   const char* const init_bitmap);

		void SetPosition(const int init_pos_x, const int init_pos_y) { pos_x = init_pos_x; pos_y = init_pos_y;   };
		void SetSize(const int init_width, const int init_height)    { width = init_width; height = init_height; };
		int GetPosX(void) const { return pos_x; };
		int GetPosY(void) const { return pos_y; };
		int GetId(void) const   { return id;    };
		virtual const char* const GetText(void) const { return text; };
		virtual void Draw(void) const = 0;

		friend const ostream& operator<<(const ostream& os, Base_T& base);
};

#endif
