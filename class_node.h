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

		Node_T(const char* const text,
			   const int         id,
			   const int         x,
			   const int         y,
			   const char* const bitmap,
			   const bool        frame,
			   const SceneID_T   go_to_scene);

		void DrawConnection(void) const;     // TODO: delete if not needed
		void DrawDirection(void) const;      // TODO: delete if not needed
		void Draw(void) const;       
		void DrawAvailablePath(void) const;  // TODO: delete if not needed
		void Connect(Node_T &new_node);
		void Disconnect(Node_T &node);
		bool IsConnectedTo(const Node_T &node) const;
		int  GetRadius(void)     const { return RADIUS;      };

		friend const ostream& operator<<(const ostream& os, Node_T& node);
};

#endif
