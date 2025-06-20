#include "class_map.h"
#include "graphics.h"

Map_T::Map_T()
{
	prev_highlighted_node = Node_T::NONE;
	selected_node = Node_T::HOME;
	node[selected_node].Select();
}

void Map_T::Draw(const MapDrawOption_T op) const
{
	//const int CALL_COUNT_MAX = 10;
	//static int call_count = 0;
	//static int blink_color = GREEN/*NODE_COLOR_BACKGROUND*/;

	//if (call_count < CALL_COUNT_MAX)
	//{
	//	call_count++;
	//}
	//else
	//{
	//	call_count = 0;
	//	blink_color = (/*NODE_COLOR_BACKGROUND*/GREEN == blink_color) ? LIGHTGREEN/*NODE_COLOR_HIGHLIGHTED*/ : GREEN/*NODE_COLOR_BACKGROUND*/;
	//}

	switch (op)
	{
		case ALL:
			readimagefile(bitmap, 0, 0, getmaxx(), getmaxy());
			//for (int i = 0; i < NODE_COUNT; i++) { node[i].DrawConnection(); }
			//for (int i = 0; i < NODE_COUNT; i++) { node[i].DrawDirection();  }
			for (int i = 0; i < NODE_COUNT; i++) { node[i].DrawNode();       }
			break;

		case NODE:
			//for (int i = 0; i < NODE_COUNT; i++) { node[i].DrawConnection(); }
			//for (int i = 0; i < NODE_COUNT; i++) { node[i].DrawDirection();  }
			for (int i = 0; i < NODE_COUNT; i++) { node[i].DrawNode();       }
			break;

		case CONNECTION:
			for (int i = 0; i < NODE_COUNT; i++) { node[i].DrawConnection(); }
			break;

		case DIRECTION:
			for (int i = 0; i < NODE_COUNT; i++) { node[i].DrawDirection();  }
			break;
		
		case BACKGROUND:
			readimagefile(bitmap, 0, 0, getmaxx(), getmaxy());
			break;
	}
}

void Map_T::Select(const Node_T::Id_T idx)
{
	if (true == node[idx].isVisible())
	{
		if (true == node[selected_node].isConnectedTo(node[idx]))
		{
			node[selected_node].Unselect();
			node[idx].Select();
			selected_node = idx;
		}
	}
}

Node_T::Id_T Map_T::getNodeUnderCursor(const int cursor_x, const int cursor_y) const
{
	Node_T::Id_T node_under_cursor = Node_T::NONE;

	for (int i = 0; i < NODE_COUNT; i++)
	{
		if (true == node[i].isCursorAbove(cursor_x + Node_T::RADIUS, cursor_y + Node_T::RADIUS))
		{
			node_under_cursor = (Node_T::Id_T) i;
			break;
		}
	}

	return node_under_cursor;
}

void Map_T::LightOff(void)
{
	for (int i = 0; i < NODE_COUNT; i++)
	{
		node[i].LightOff();
	}
}
