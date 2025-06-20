#include <iostream>
#include "graphics.h"

using std::cout;
using std::cin;
using std::endl;

// TODO: Add to namespace!
static const int _COLOR_BACKGROUND = BLACK;

static int GetMaxX(void)
{
	return getmaxx() - 10;
}

static int GetMaxY(void)
{
	return getmaxy() - 10;
}

enum ItemType_T
{
	STATIC      = 0,
	INTERACTIVE = 1,
	COLLECTIBLE = 2
};

enum ItemId_T
{
	KOFOLA   = 0,
	RUM      = 1,
	GUITAR   = 2,
	NOTEBOOK = 3,
	FRIDGE   = 4,
	OVEN     = 5,
	BOOTS    = 6,
	PICTURE  = 7,
	TV       = 8,
};

class Item_T
{
private:
	int pos_x;
	int pos_y;

	int width;
	int height;

	ItemType_T type;
	const char* bitmap;

	//description text to be shown when cursor is over the item.

public:
	ItemId_T id;

	Item_T(ItemId_T ident, int x, int y, ItemType_T ot, const char* fn, int item_width = 50, int item_height = 50);
	void SetPosition(int x, int y);
	void SetSize(int w, int h);
	void Draw(void);
};

Item_T::Item_T(ItemId_T ident, int x, int y, ItemType_T ot, const char* fn, int item_width, int item_height)
{
	id     = ident;
	pos_x  = x;
	pos_y  = y;
	type   = ot;
	bitmap = fn;
	width  = item_width;
	height = item_height;
}

void Item_T::SetPosition(int x, int y)
{
	pos_x = x;
	pos_y = y;
}

void Item_T::SetSize(int w, int h)
{
	width = w;
	height = h;
}

void Item_T::Draw(void)
{
	readimagefile(bitmap, pos_x, pos_y, pos_x + width, pos_y + height);
}

//class Collection_T
//{
//	private:
//		//SceneID_T id;
//		const char* background;
//		int item_count;
//		Item_T** item;
//
//	public:
//		Collection_T();
//		void Add(Item_T* new_item);
//		Item_T* Remove(ItemId_T item_id);
//		void Draw(void);
//};
//
//Collection_T::Collection_T()
//{
//	background = NULL;
//	item_count = 0;
//	item       = NULL;
//}
//
//void Collection_T::Add(Item_T *new_item)
//{
//	if (NULL == item)
//	{
//		item_count++;
//		item = new Item_T* [item_count];
//		item[item_count - 1] = new_item;
//	}
//	else
//	{
//		/* Check if an item which we want to add already exists in the item array. */
//		bool item_already_exists = false;
//		for (int i = 0; i < item_count; i++)
//		{
//			if (item[i]->id == new_item->id)
//			{
//				item_already_exists = true;
//				break;
//			}
//		}
//
//		if (false == item_already_exists)
//		{
//			/* Save the item pointer array to temp. */
//			Item_T** temp = new Item_T* [item_count];
//			for (int i = 0; i < item_count; i++)
//			{
//				temp[i] = item[i];
//			}
//
//			delete[] item;
//			item_count++;
//
//			/* Load the item pointer array from temp. */
//			item = new Item_T* [item_count];
//			for (int i = 0; i < item_count - 1; i++)
//			{
//				item[i] = temp[i];
//			}
//
//			item[item_count - 1] = new_item;
//		}
//		else
//		{
//			// TODO: output ID names instead of ID numbers.
//			//cout << "WARNING (Scene_T::AddItem()): Item with ID=" << new_item->id << " already exists in a scene with ID=" << this->id << endl;
//		}
//	}
//}
//
//Item_T* Collection_T::Remove(ItemId_T item_id)
//{
//	Item_T* retval = NULL;
//
//	if (NULL != item)
//	{
//		/* Check if an item which we want to remove exists in the item array. */
//		bool item_exists = false;
//		for (int i = 0; i < item_count; i++)
//		{
//			if (item[i]->id == item_id)
//			{
//				item_exists = true;
//				break;
//			}
//		}
//
//		if (true == item_exists)
//		{
//			if (1 == item_count)
//			{
//				retval = item[0];
//				delete[] item;
//				item = NULL;
//				item_count = 0;
//			}
//			else
//			{
//				/* Find the item which we want to remove and copy all other items to a temp array. */
//				Item_T** temp = new Item_T* [item_count - 1];
//				int j = 0;
//				for (int i = 0; i < item_count; i++)
//				{
//					if (item[i]->id == item_id)
//					{
//						retval = item[i];
//					}
//					else
//					{
//						temp[j] = item[i];
//						j++;
//					}
//				}
//				delete[] item;
//
//				item_count--;
//
//				/* Copy the temp array back to the item array. */
//				item = new Item_T* [item_count];
//				for (int i = 0; i < item_count; i++)
//				{
//					item[i] = temp[i];
//				}
//				delete[] temp;
//			}
//		}
//		else
//		{
//			// TODO: output ID names instead of ID numbers.
//			//cout << "WARNING (Scene_T::RemoveItem()): Item with ID=" << item_id << " does not exist in a scene with ID=" << this->id << endl;
//		}
//	}
//
//	return retval;
//}
//
//void Collection_T::Draw(void)
//{
//	/* Print background image. */
//	readimagefile(background, 0, 0, getmaxx(), getmaxy());
//
//	for (int i = 0; i < item_count; i++)
//	{
//		item[i]->Draw();
//	}
//}


enum NodeName_T
{
	HOME    = 0,
	PARKING = 1,
	PUB     = 2,
	FOREST  = 3,
	SHOP    = 4
};

enum NodeType_T
{
	DISTRICT = 0,
	SCENE    = 1
};

class Node_T
{
    private:
        const int RADIUS = 30;

		const char *name;
		NodeType_T type;

        int pos_x;
        int pos_y;
 
        int color;

		bool selected;
        bool visible;

        int neighbour_count;
        Node_T **neighbour_node;

    public:
		NodeName_T id;

        Node_T(int x, int y, NodeType_T node_type, NodeName_T id, const char* location_name);
        void DrawConnection(void);
        void DrawDirection(void);
        void DrawNode(void) const;
		void DrawAvailablePath(void);
        void Connect(Node_T * new_node);
        void Disconnect(Node_T* node);
		bool isConnectedTo(Node_T* node) const;
        void Select(void);
        void Unselect(void);
        void Show(void);
        void Hide(void);
		bool isVisible(void) const;
};

Node_T::Node_T(int x, int y, NodeType_T node_type, NodeName_T ident, const char *node_name)
{
	name = node_name;
	id = ident;
	type = node_type;

    pos_x = x;
    pos_y = y;

    color = WHITE;

	selected = false;
    visible = false;

    neighbour_count = 0;
	//neighbour_node = new Node_T* [0];
	neighbour_node = NULL;
}

/* Draw lines connecting two neighbour nodes. */
void Node_T::DrawConnection(void)
{
	if (true == visible)
	{
		setcolor(color);
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
void Node_T::DrawDirection(void)
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

/* Draw a circle representing a node. */
void Node_T::DrawNode(void) const
{
    if (true == visible)
    {
        setfillstyle(SOLID_FILL, (true == selected) ? RED : _COLOR_BACKGROUND);
		setbkcolor((true == selected) ? RED : _COLOR_BACKGROUND);
        setcolor(color);
        fillellipse(pos_x, pos_y, RADIUS, RADIUS);
		settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(pos_x, pos_y, (char *) name);
    }
}

void Node_T::DrawAvailablePath(void)
{
	static int blink_color = _COLOR_BACKGROUND;
	blink_color = (_COLOR_BACKGROUND == blink_color) ? WHITE : _COLOR_BACKGROUND;

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
void Node_T::Connect(Node_T* new_node)
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

    neighbour_node[neighbour_count - 1] = new_node;
}

void Node_T::Disconnect(Node_T* node)
{

}

bool Node_T::isConnectedTo(Node_T* node) const
{
	bool connected = false;

	for (int i = 0; i < neighbour_count; i++)
	{
		if (neighbour_node[i]->id == node->id)
		{
			connected = true;
			break;
		}
	}

	return connected;
}

void Node_T::Select(void)
{
    selected = true;
}

void Node_T::Unselect(void)
{
	selected = false;
}

void Node_T::Show(void)
{
    visible = true;
}

void Node_T::Hide(void)
{
    visible = false;
}

bool Node_T::isVisible(void) const
{
	return visible;
}

class Map_T
{
    private:
        static const int NODE_COUNT = 5;
		NodeName_T selected;

	public:
		Node_T node[NODE_COUNT] =
        {
            Node_T(300, 300, DISTRICT, HOME,    "Home"),
            Node_T(200, 100, DISTRICT, PARKING, "Parking"),
            Node_T(100, 100, DISTRICT, PUB,     "Pub"),
            Node_T(100, 300, DISTRICT, FOREST,  "Forest"),
			Node_T(400, 100, DISTRICT, SHOP,    "Shop")
        };
            
        Map_T();
        void Draw(void);
        void Select(NodeName_T node);
};

Map_T::Map_T()
{
	selected = HOME;
	node[selected].Select();
}

void Map_T::Draw(void)
{
    for (int i = 0; i < NODE_COUNT; i++) { node[i].DrawConnection(); }
    for (int i = 0; i < NODE_COUNT; i++) { node[i].DrawDirection();  }
    for (int i = 0; i < NODE_COUNT; i++) { node[i].DrawNode();       }

	while (!kbhit())
	{
		node[selected].DrawAvailablePath();
		delay(350);
		node[selected].DrawAvailablePath();
		delay(350);
	}
}

void Map_T::Select(NodeName_T idx)
{
	if (true == node[idx].isVisible())
	{
		if (true == node[selected].isConnectedTo(&node[idx]))
		{
			node[selected].Unselect();
			node[idx].Select();
			selected = idx;
		}
	}
}

enum SceneID_T
{
	HOME_KITCHEN     = 0,
	HOME_BED_ROOM    = 1,
	HOME_LIVING_ROOM = 2,
	HOME_STUDIO      = 3
};

class Scene_T
{

	private:
		static const int TOP       = 0; 
		static const int LEFT      = 0;
		static const int BOTTOM    = 378; // TODO: Bind it somehow with constant Inventory_T->TOP!!
		static const int RIGHT     = 639 - 10; /* There must be some bug in the WinBGIm library. */

		SceneID_T id;
		const char* background;
		int item_count;
		Item_T** item;

	public:
		Scene_T(SceneID_T ident, const char* scene_bitmap);
		void AddItem(Item_T *new_item);
		Item_T* RemoveItem(ItemId_T item_id);
		void Draw(void);
};

Scene_T::Scene_T(SceneID_T ident, const char* scene_bitmap)
{
	id         = ident;
	background = scene_bitmap;
	item_count = 0;
	item       = NULL;
}

/* TODO: Zeby adept na <TEMPLATE> ?? */
void Scene_T::AddItem(Item_T *new_item)
{
	if (NULL == item)
	{
		item_count++;
		item = new Item_T* [item_count];
		item[item_count - 1] = new_item;
	}
	else
	{
		/* Check if an item which we want to add already exists in the item array. */
		bool item_already_exists = false;
		for (int i = 0; i < item_count; i++)
		{
			if (item[i]->id == new_item->id)
			{
				item_already_exists = true;
				break;
			}
		}

		if (false == item_already_exists)
		{
			/* Save the item pointer array to temp. */
			Item_T** temp = new Item_T* [item_count];
			for (int i = 0; i < item_count; i++)
			{
				temp[i] = item[i];
			}

			delete[] item;
			item_count++;

			/* Load the item pointer array from temp. */
			item = new Item_T* [item_count];
			for (int i = 0; i < item_count - 1; i++)
			{
				item[i] = temp[i];
			}

			item[item_count - 1] = new_item;
		}
		else
		{
			// TODO: output ID names instead of ID numbers.
			cout << "WARNING (Scene_T::AddItem()): Item with ID=" << new_item->id << " already exists in a scene with ID=" << this->id << endl;
		}
	}
}

Item_T* Scene_T::RemoveItem(ItemId_T item_id)
{
	Item_T* retval = NULL;

	if (NULL != item)
	{
		/* Check if an item which we want to remove exists in the item array. */
		bool item_exists = false;
		for (int i = 0; i < item_count; i++)
		{
			if (item[i]->id == item_id)
			{
				item_exists = true;
				break;
			}
		}

		if (true == item_exists)
		{
			if (1 == item_count)
			{
				retval = item[0];
				delete[] item;
				item = NULL;
				item_count = 0;
			}
			else
			{
				/* Find the item which we want to remove and copy all other items to a temp array. */
				Item_T** temp = new Item_T* [item_count - 1];
				int j = 0;
				for (int i = 0; i < item_count; i++)
				{
					if (item[i]->id == item_id)
					{
						retval = item[i];
					}
					else
					{
						temp[j] = item[i];
						j++;
					}
				}
				delete[] item;

				item_count--;

				/* Copy the temp array back to the item array. */
				item = new Item_T* [item_count];
				for (int i = 0; i < item_count; i++)
				{
					item[i] = temp[i];
				}
				delete[] temp;
			}
		}
		else
		{
			// TODO: output ID names instead of ID numbers.
			cout << "WARNING (Scene_T::RemoveItem()): Item with ID=" << item_id << " does not exist in a scene with ID=" << this->id << endl;
		}
	}

	return retval;
}

void Scene_T::Draw(void)
{
	/* Print background image. */
	//viewporttype viewport;
	//getviewsettings(&viewport);
	//setbkcolor(LIGHTGREEN);
	//clearviewport();


	/* Print background image. */
	//setviewport(LEFT, TOP, RIGHT, BOTTOM, 0);
	readimagefile(background, 0, 0, RIGHT, BOTTOM);

	for (int i = 0; i < item_count; i++)
	{
		item[i]->Draw();
	}
}

void Handler_WM_MOUSEMOVE(int x, int y)
{

}

void Handler_WM_LBUTTONDOWN(int x, int y)
{
	//if (MAP == view)
	//{

	//}
}

void Handler_WM_LBUTTONDBLCLK(int x, int y)
{

}

void Handler_WM_LBUTTONUP(int x, int y)
{

}

void Handler_WM_MBUTTONDBLCLK(int x, int y)
{

}

void Handler_WM_MBUTTONDOWN(int x, int y)
{

}

void Handler_WM_MBUTTONUP(int x, int y)
{

}

void Handler_WM_RBUTTONDBLCLK(int x, int y)
{

}

void Handler_WM_RBUTTONDOWN(int x, int y)
{

}

void Handler_WM_RBUTTONUP(int x, int y)
{

}

class Cursor_T
{
	private:
		static const int SIZE = 20;

		int pos_x;
		int pos_y;

		const char* icon;

	public:
		Cursor_T();
		void GetPosition(void);
		void Draw(void);
};

Cursor_T::Cursor_T()
{
	pos_x = 0;
	pos_y = 0;

	icon = NULL;

	registermousehandler(WM_MOUSEMOVE,     Handler_WM_MOUSEMOVE);
	registermousehandler(WM_LBUTTONDOWN,   Handler_WM_LBUTTONDOWN);
	registermousehandler(WM_LBUTTONUP,     Handler_WM_LBUTTONUP);
	registermousehandler(WM_LBUTTONDBLCLK, Handler_WM_LBUTTONDBLCLK);
	registermousehandler(WM_MBUTTONDOWN,   Handler_WM_MBUTTONDOWN);
	registermousehandler(WM_MBUTTONUP,     Handler_WM_MBUTTONUP);
	registermousehandler(WM_MBUTTONDBLCLK, Handler_WM_MBUTTONDBLCLK);
	registermousehandler(WM_RBUTTONDOWN,   Handler_WM_RBUTTONDOWN);
	registermousehandler(WM_RBUTTONUP,     Handler_WM_RBUTTONUP);
	registermousehandler(WM_RBUTTONDBLCLK, Handler_WM_RBUTTONDBLCLK);
}

void Cursor_T::GetPosition(void)
{
	pos_x = mousex();
	pos_y = mousey();
}

void Cursor_T::Draw(void)
{
	readimagefile(icon, pos_x, pos_y, pos_x - SIZE, pos_y - SIZE);
}

static int GetMaxX(viewporttype &viewport)
{
	return viewport.right - viewport.left;
}

static int GetMaxY(viewporttype &viewport)
{
	return viewport.bottom - viewport.top;
}

static void Frame(int left, int top, int right, int bottom, int thickness, int linestyle = SOLID_LINE)
{
	setlinestyle(linestyle, 0, NORM_WIDTH);
	for (int i = 0; i < thickness; i++)
	{
		rectangle(left + i, top + i, right - i, bottom - i);
	}
}

class Inventory_T
{
	private:
		static const int VISIBLE_ITEMS_COUNT = 5;
		static const int FRAME_THICKNESS = 4;
		static const int LEFT      = 0;
		static const int TOP       = 379; // TODO: Bind somehow to the Scene dimensions.
		static const int BOTTOM    = 479 - 10; /* There must be some bug in the WinBGIm library. */
		static const int SLOT_SIZE = (BOTTOM - TOP) - FRAME_THICKNESS * 2;
		static const int ITEM_SIZE = (BOTTOM - TOP) - FRAME_THICKNESS * 4;
		static const int RIGHT     = (SLOT_SIZE - FRAME_THICKNESS) * VISIBLE_ITEMS_COUNT +
			3 * FRAME_THICKNESS;

		const char* background;
		int item_count;
		Item_T** item;

public:
	Inventory_T();
	void Add(Item_T* new_item);
	Item_T* Remove(ItemId_T item_id);
	void ShiftRight(void);
	void ShiftLeft(void);
	void Draw(void);
};

Inventory_T::Inventory_T()
{
	background = NULL;
	item_count = 0;
	item       = NULL;
}

void Inventory_T::Add(Item_T *new_item)
{
	if (NULL == item)
	{
		item_count++;
		item = new Item_T* [item_count];
		item[item_count - 1] = new_item;
	}
	else
	{
		/* Check if an item which we want to add already exists in the item array. */
		bool item_already_exists = false;
		for (int i = 0; i < item_count; i++)
		{
			if (item[i]->id == new_item->id)
			{
				item_already_exists = true;
				break;
			}
		}

		if (false == item_already_exists)
		{
			/* Save the item pointer array to temp. */
			Item_T** temp = new Item_T* [item_count];
			for (int i = 0; i < item_count; i++)
			{
				temp[i] = item[i];
			}

			delete[] item;
			item_count++;

			/* Load the item pointer array from temp. */
			item = new Item_T* [item_count];
			for (int i = 0; i < item_count - 1; i++)
			{
				item[i] = temp[i];
			}

			item[item_count - 1] = new_item;
		}
		else
		{
			// TODO: output ID names instead of ID numbers.
			//cout << "WARNING (Scene_T::AddItem()): Item with ID=" << new_item->id << " already exists in a scene with ID=" << this->id << endl;
		}
	}
}

Item_T* Inventory_T::Remove(ItemId_T item_id)
{
	Item_T* retval = NULL;

	if (NULL != item)
	{
		/* Check if an item which we want to remove exists in the item array. */
		bool item_exists = false;
		for (int i = 0; i < item_count; i++)
		{
			if (item[i]->id == item_id)
			{
				item_exists = true;
				break;
			}
		}

		if (true == item_exists)
		{
			if (1 == item_count)
			{
				retval = item[0];
				delete[] item;
				item = NULL;
				item_count = 0;
			}
			else
			{
				/* Find the item which we want to remove and copy all other items to a temp array. */
				Item_T** temp = new Item_T* [item_count - 1];
				int j = 0;
				for (int i = 0; i < item_count; i++)
				{
					if (item[i]->id == item_id)
					{
						retval = item[i];
					}
					else
					{
						temp[j] = item[i];
						j++;
					}
				}
				delete[] item;

				item_count--;

				/* Copy the temp array back to the item array. */
				item = new Item_T* [item_count];
				for (int i = 0; i < item_count; i++)
				{
					item[i] = temp[i];
				}
				delete[] temp;
			}
		}
		else
		{
			// TODO: output ID names instead of ID numbers.
			//cout << "WARNING (Scene_T::RemoveItem()): Item with ID=" << item_id << " does not exist in a scene with ID=" << this->id << endl;
		}
	}

	return retval;
}

void Inventory_T::ShiftRight(void)
{

}

void Inventory_T::ShiftLeft(void)
{

}

void Inventory_T::Draw(void)
{
	/* Print background image. */
	viewporttype viewport;
	setviewport(LEFT, TOP, RIGHT, BOTTOM, 0);
	getviewsettings(&viewport);
	setbkcolor(LIGHTGREEN);
	clearviewport();

	/* Print frame around the inventory window. */
	setcolor(GREEN);
	Frame(0, 0 , GetMaxX(viewport), GetMaxY(viewport), FRAME_THICKNESS);

	/* Print slot frames. */
	setcolor(GREEN);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	int OFFSET_X = FRAME_THICKNESS;
	int OFFSET_Y = FRAME_THICKNESS;
	for (int i = 0; i < VISIBLE_ITEMS_COUNT; i++)
	{
		Frame(OFFSET_X + i * (SLOT_SIZE - FRAME_THICKNESS)            , OFFSET_Y + 0,
			  OFFSET_X + i * (SLOT_SIZE - FRAME_THICKNESS) + SLOT_SIZE, OFFSET_Y + SLOT_SIZE,
			  FRAME_THICKNESS);
	}

	/* Print inventory items. */
	for (int i = 0; i < VISIBLE_ITEMS_COUNT; i++)
	{
		if (i < item_count)
		{
			/* Print item. */
			OFFSET_X = 2 * FRAME_THICKNESS;
			OFFSET_Y = 2 * FRAME_THICKNESS;
			item[i]->SetPosition(i * (SLOT_SIZE - FRAME_THICKNESS) + OFFSET_X, OFFSET_Y);
			item[i]->SetSize(ITEM_SIZE, ITEM_SIZE);
			item[i]->Draw();
		}
		else
		{
			/* Print "Empty". */
			OFFSET_X = 1 * FRAME_THICKNESS + SLOT_SIZE / 2;
			OFFSET_Y = 2 * FRAME_THICKNESS;
			int x = OFFSET_X + i * (SLOT_SIZE - FRAME_THICKNESS);
			int y = OFFSET_Y + SLOT_SIZE / 2;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			outtextxy(x, y, "Empty");
		}
	}

	/* Print selection frame. */
	setcolor(YELLOW);
	const int SELECT = 2;
	OFFSET_X = 2 * FRAME_THICKNESS;
	OFFSET_Y = 2 * FRAME_THICKNESS;
	Frame(SELECT * (SLOT_SIZE - FRAME_THICKNESS) + OFFSET_X , OFFSET_Y + 0,
		SELECT * (SLOT_SIZE - FRAME_THICKNESS) + SLOT_SIZE, SLOT_SIZE,
		  FRAME_THICKNESS);
}

static const int ITEM_COUNT_TOTAL = 9;

Item_T item[ITEM_COUNT_TOTAL] =
{
	Item_T(KOFOLA,   100, 100, STATIC, "..\\kofola.gif", 25, 75),
	Item_T(RUM,      200, 100, STATIC, "..\\rum.jpg",    75, 75),
	Item_T(GUITAR,   300, 100, STATIC, "..\\guitar.jpg"),
	Item_T(NOTEBOOK, 400, 100, STATIC, "..\\notebook.jpg"),
	Item_T(FRIDGE,   500, 80,  STATIC, "..\\fridge.jpg", 75, 200),
	Item_T(OVEN,     300, 100, STATIC, "..\\oven.jpg"),
	Item_T(BOOTS,    300, 100, STATIC, "..\\boots.jpg"),
	Item_T(PICTURE,  300, 100, STATIC, "..\\picture.jpg"),
	Item_T(TV,       300, 100, STATIC, "..\\tv.jpg")
};

static const int SCENE_COUNT = 4;
Scene_T scene[SCENE_COUNT] =
{
	Scene_T(HOME_KITCHEN,     "..\\test.jpg"),
	Scene_T(HOME_BED_ROOM,    "..\\test.jpg"),
	Scene_T(HOME_LIVING_ROOM, "..\\test.jpg"),
	Scene_T(HOME_STUDIO,      "..\\skusobna.jpg"),
};

//enum View_T
//{
//	MAP = 0,
//	SCENE = 1
//};
//View_T view = MAP;

Inventory_T inventory;

static void __inventory(void)
{
	inventory.Add(&item[KOFOLA]);
	inventory.Add(&item[RUM]);
	inventory.Add(&item[GUITAR]);
	inventory.Add(&item[NOTEBOOK]);
	inventory.Add(&item[FRIDGE]);
	inventory.Add(&item[OVEN]);
	inventory.Add(&item[BOOTS]);
	inventory.Add(&item[PICTURE]);
	inventory.Add(&item[TV]);
	inventory.Draw();
	getch();

	inventory.Remove(KOFOLA);
	inventory.Draw();
	getch();

	inventory.Remove(RUM);
	inventory.Draw();
	getch();

	inventory.Remove(GUITAR);
	inventory.Draw();
	getch();

	inventory.Remove(NOTEBOOK);
	inventory.Draw();
	getch();

	inventory.Remove(FRIDGE);
	inventory.Draw();
	getch();

	inventory.Remove(OVEN);
	inventory.Draw();
	getch();

	inventory.Remove(BOOTS);
	inventory.Draw();
	getch();

	inventory.Remove(PICTURE);
	inventory.Draw();
	getch();

	inventory.Remove(TV);
	inventory.Draw();
}

static void __scene(void)
{
	//scene[HOME_STUDIO].AddItem(&item[RUM]);
	//scene[HOME_STUDIO].AddItem(&item[GUITAR]);
	//scene[HOME_STUDIO].AddItem(&item[NOTEBOOK]);
	//scene[HOME_STUDIO].AddItem(&item[FRIDGE]);
	scene[HOME_STUDIO].Draw();
}

static void __map(void)
{
	Map_T map;

	map.node[HOME   ].Show();
	map.node[PARKING].Show();
	map.node[PUB    ].Show();
	map.node[FOREST ].Show();
	map.node[SHOP   ].Show();

	map.node[HOME   ].Connect(&map.node[PARKING]);
	map.node[HOME   ].Connect(&map.node[PUB    ]);
	map.node[HOME   ].Connect(&map.node[FOREST ]);
	map.node[PARKING].Connect(&map.node[HOME   ]);
	map.node[PARKING].Connect(&map.node[SHOP   ]);

	//map.Select(HOME);
	//map.Draw();
	//getch();

	//map.Select(PARKING);
	map.Draw();
}

static void __WindowOpen(void)
{
    int width         = 640;
    int height        = 480;
    const char* title = "Adventure";
    int left          = 600;
    int top           = 20;
    bool dbflag       = true;
    bool closeflag    = true;
    initwindow(width, height, title, left, top, dbflag, closeflag);
    setvisualpage(1);
    setactivepage(1);
}

static void __WindowClose(void)
{
	closegraph();
}

int main(void)
{
    cout << "### Adventure ###" << std::endl;
	__WindowOpen();

	//__map();
	__scene();
	__inventory();
	getch();    

	__WindowClose();
    return 0;
}

