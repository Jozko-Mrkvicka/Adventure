#ifndef CLASS_NODE_T
#define CLASS_NODE_T

#include "class_scene.h"
#include "graphics.h"

class Node_T : public Element_T
{
	private:

		enum Color_T
		{
			TEXT        = WHITE,
			EDGE        = GREEN,
			HIGHLIGHTED = LIGHTGREEN,
			SELECTED    = RED,
			DISABLED    = LIGHTGRAY,
			BACKGROUND  = GREEN,
		};

		bool visible;
		bool enabled;

		int neighbour_count;
		Node_T **neighbour_node;

	public:
		static const int RADIUS = 30;

		enum Id_T
		{
			NONE     = -1,
			HOME     =  0,
			BRIDGE   =  1,
			PUB      =  2,
			FOREST   =  3,
			SHOP     =  4,
			DOWNTOWN =  5,
		};

		bool newly_created;  // TODO: Move it to private section after debugging is finished.
		Id_T id;

		Node_T(const Id_T init_id, 
			   const int x,
			   const int y,
			   const bool frame,
			   const SceneID_T go_to_scene,
			   const char* const text);

		void DrawConnection(void) const;     // TODO: delete if not needed
		void DrawDirection(void) const;      // TODO: delete if not needed
		void DrawNode(void) const;       
		void DrawAvailablePath(void) const;  // TODO: delete if not needed
		void Connect(Node_T &new_node);
		void Disconnect(Node_T &node);
		bool isConnectedTo(const Node_T &node) const;
		void Select(void)              { selected    = true;  };
		void Unselect(void)            { selected    = false; };
		void Show(void)                { visible     = true;  };
		void Hide(void)                { visible     = false; };
		void Enable(void)              { enabled     = true;  };
		void Disable(void)             { enabled     = false; };
		int GetRadius(void)      const { return RADIUS;       };
		bool isVisible(void)     const { return visible;      };
		bool isEnabled(void)     const { return enabled;      };
		bool isHighlighted(void) const { return highlighted;  };
		bool isSelected(void)    const { return selected;     };
};

#endif
