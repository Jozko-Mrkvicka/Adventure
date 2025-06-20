#ifndef CLASS_ELEMENT_T
#define CLASS_ELEMENT_T

#include <iostream>
#include "datatype.h"

using std::ostream;
using std::cout;
using std::endl;

class Element_T
{
	private:

	protected:
		static const int FRAME_THICKNESS = 3;

		int pos_x;
		int pos_y;
		int width;
		int height;

		bool highlighted;
		bool selected;
		bool frame;

	public:
		const char * const text;
		SceneID_T go_to_scene;

		Element_T(const int init_pos_x = 0,
				  const int init_pos_y = 0,
				  const int init_width = 50,
				  const int init_height = 50,
				  const bool init_frame = false,
				  const SceneID_T init_go_to_scene = SCENE_NONE,
				  const char* const init_text = "N/A");

		void SetPosition(const int init_pos_x, const int init_pos_y) { pos_x = init_pos_x; pos_y  = init_pos_y;  };
		void SetSize(const int init_width, const int init_height)    { width = init_width; height = init_height; };
		int GetPosX(void) const                                      { return pos_x;                             };
		int GetPosY(void) const                                      { return pos_y;                             };
		void LightOn(void)                                           { highlighted = true;                       };
		void LightOff(void)                                          { highlighted = false;                      };
		bool isCursorAbove(const int cursor_x, const int cursor_y) const;
		virtual void Draw(void) const {};

		friend const ostream & operator<<(const ostream & os, Element_T & element);
};

#endif
