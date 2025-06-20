#ifndef CLASS_MAP_T
#define CLASS_MAP_T

#include "class_node.h"

class Map_T
{
	private:
		static const int NODE_COUNT = 6;
		const char *bitmap = "../map.jpg";

	public:
		enum MapDrawOption_T
		{
			ALL        = 0,
			NODE       = 1,
			CONNECTION = 2,
			DIRECTION  = 3,
			BACKGROUND = 4,
		};

		Node_T::Id_T prev_highlighted_node;
		Node_T::Id_T selected_node;

		Node_T node[NODE_COUNT] =
		{
			/*     Id                X    Y    Frame  GoToScene       Text      */
			Node_T(Node_T::HOME,     100, 300, false, SCENE_HOME,     "Home"    ),
			Node_T(Node_T::BRIDGE,   500, 400, false, SCENE_BRIDGE,   "Bridge"  ),
			Node_T(Node_T::PUB,      600, 250, false, SCENE_PUB,      "Pub"     ),
			Node_T(Node_T::FOREST,   100, 100, false, SCENE_FOREST,   "Forest"  ),
			Node_T(Node_T::SHOP,     460, 180, false, SCENE_SHOP,     "Shop"    ),
			Node_T(Node_T::DOWNTOWN, 340, 240, false, SCENE_DOWNTOWN, "Downtown"),
		};

		Map_T();
		void Draw(const MapDrawOption_T op) const;
		void Select(Node_T::Id_T node);
		Node_T::Id_T getNodeUnderCursor(const int cursor_x, const int cursor_y) const;
		void LightOff(void);
};

#endif
