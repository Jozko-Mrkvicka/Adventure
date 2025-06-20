#ifndef CLASS_ELEMENT_T
#define CLASS_ELEMENT_T

#include <iostream>
#include "datatype.h"
#include "class_base.h"

using std::ostream;
using std::cout;
using std::endl;

class Element_T : public Base_T
{
	private:

	protected:
		static const int FRAME_THICKNESS = 6;

		bool highlighted;
		bool selected;
		bool enabled;
		bool visible;
		bool frame;

	public:
		SceneID_T go_to_scene;

		Element_T(const char* const text,
				  const int         id,
				  const int         pos_x,
				  const int         pos_y,
				  const int         width,
				  const int         height,
				  const char*       bitmap,
				  const bool        init_frame,
				  const SceneID_T   init_go_to_scene);

		void Enable(void)              { enabled     = true;  };
		void Disable(void)             { enabled     = false; };
		void Select(void)              { selected    = true;  };
		void Unselect(void)            { selected    = false; };
		void Show(void)                { visible     = true;  };
		void Hide(void)                { visible     = false; };
		void LightOn(void)             { highlighted = true;  };
		void LightOff(void)            { highlighted = false; };
		bool IsEnabled(void)     const { return enabled;      };
		bool IsVisible(void)     const { return visible;      };
		bool IsHighlighted(void) const { return highlighted;  };
		bool IsSelected(void)    const { return selected;     };

		bool IsCursorAbove(const int cursor_x, const int cursor_y) const;

		friend const ostream & operator<<(const ostream & os, Element_T & element);
};

#endif
