#include "class_node.h"
#include "graphics.h"
#include "definitions.h"

Node_T::Node_T(const char* const text,
			   const int         id,
			   const int         x,
	           const int         y,
			   const char* const bitmap,
		       const bool        frame,
			   const SceneID_T   go_to_scene) : Element_T(text, id, x, y, 2 * RADIUS, 2 * RADIUS, bitmap, frame, go_to_scene)
{
	enabled         = false;
	newly_created   = true;
	neighbour_count = 0;
	neighbour_node  = NULL;
}

/* Draw lines connecting two neighbour nodes. */
void Node_T::DrawConnection(void) const
{
	if (true == visible)
	{
		setcolor(Color_T::EDGE);
		for (int i = 0; i < neighbour_count; i++)
		{
			if (true == neighbour_node[i]->visible)
			{
				line(pos_x, pos_y, neighbour_node[i]->pos_x, neighbour_node[i]->pos_y);
			}
		}
	}
}

/* Draw marks on connecting lines next to neighbour nodes (to symbolize direction to the node). */
void Node_T::DrawDirection(void) const
{
	if (true == visible)
	{
		for (int i = 0; i < neighbour_count; i++)
		{
			if (true == neighbour_node[i]->visible)
			{
				int vx = neighbour_node[i]->pos_x - pos_x;
				int vy = neighbour_node[i]->pos_y - pos_y;

				double len = sqrt(vx * vx + vy * vy);
				int x = (int) (pos_x + (len - RADIUS) / len * vx);
				int y = (int) (pos_y + (len - RADIUS) / len * vy);

				setfillstyle(SOLID_FILL, GREEN);
				setcolor(GREEN);
				fillellipse(x, y, RADIUS / 4, RADIUS / 4);
			}
		}
	}
}

void Node_T::Draw(void) const
{
	if (true == visible)
	{
		const int color_edge   = false == enabled ? Color_T::DISABLED : true == highlighted ? Color_T::HIGHLIGHTED : Color_T::BACKGROUND;
		const int color_inside = false == enabled ? Color_T::DISABLED : true == selected    ? Color_T::SELECTED    : Color_T::BACKGROUND;

		/* Draw a circle representing a node. */
		setcolor(color_edge);
		setlinestyle(SOLID_LINE, 0, FRAME_THICKNESS);
		setfillstyle(SOLID_FILL, /*true == newly_created ? blink_color :*/ color_inside);
		fillellipse(pos_x, pos_y, RADIUS, RADIUS);

		/* Print text. */
		setcolor(Color_T::TEXT);
		setbkcolor(color_inside);
		settextstyle(DEFAULT_FONT, 0, 0);
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		outtextxy(pos_x, pos_y, (char *) text);
	}
}

void Node_T::DrawAvailablePath(void) const
{
	static int blink_color = Color_T::BACKGROUND;
	blink_color = (Color_T::BACKGROUND == blink_color) ? WHITE : Color_T::BACKGROUND;

	for (int i = 0; i < neighbour_count; i++)
	{
		if (true == neighbour_node[i]->visible)
		{
			setcolor(blink_color);
			setlinestyle(DASHED_LINE, 0, NORM_WIDTH);
			circle(neighbour_node[i]->pos_x, neighbour_node[i]->pos_y, RADIUS);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		}
	}
}

/* TODO: Zeby adept na <TEMPLATE> ?? */
void Node_T::Connect(Node_T &new_node)
{
	if (NULL == neighbour_node)
	{
		neighbour_count++;
		neighbour_node = new Node_T* [neighbour_count];
	}
	else
	{
		/* Save the item pointer array to temp. */
		Node_T **temp = new Node_T* [neighbour_count];
		for (int i = 0; i < neighbour_count; i++)
		{
			temp[i] = neighbour_node[i];
		}

		delete[] neighbour_node;
		neighbour_count++;

		/* Load the item pointer array from temp. */
		neighbour_node = new Node_T* [neighbour_count];
		for (int i = 0; i < neighbour_count - 1; i++)
		{
			neighbour_node[i] = temp[i];
		}
	}

	neighbour_node[neighbour_count - 1] = &new_node;
}

void Node_T::Disconnect(Node_T &node)
{

}

bool Node_T::IsConnectedTo(const Node_T &node) const
{
	bool connected = false;

	for (int i = 0; i < neighbour_count; i++)
	{
		if (neighbour_node[i]->id == node.id)
		{
			connected = true;
			break;
		}
	}

	return connected;
}

const ostream& operator<<(const ostream& os, Node_T& node)
{
	Element_T& element = node;

	cout << element;
	cout << "Node_T class properties:" << endl;
	cout << "ID              = " << node.id              << endl;
	cout << "VISIBLE         = " << node.visible         << endl;
	cout << "ENABLED         = " << node.enabled         << endl;
	cout << "NEWLY_CREATED   = " << node.newly_created   << endl;
	cout << "NEIGHBOUR_COUNT = " << node.neighbour_count << endl;
	cout << endl;

	return os;
}
