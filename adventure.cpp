#include <iostream>
#include "graphics.h"
#include "definitions.h"
#include "miscellaneous.h"

#include "class_node.h"
#include "class_map.h"
#include "class_item.h"
#include "class_scene.h"
#include "class_inventory.h"
#include "class_cursor.h"
#include "class_control.h"

using std::cout;
using std::cin;
using std::endl;

View_T gView = MAP;
Node_T::Id_T gNodeUnderCursor = Node_T::NONE;
SceneID_T gActiveScene = SCENE_STUDIO;

Control_T gControl;
Inventory_T gInventory;
Map_T gMap;


class Menu_T
{
	private:

		int pos_x;
		int pos_y;
		int btn_cnt;
		int longest_button;

	public:
		Button_T *button;
		int prev_highlighted_button;
		static const int LETTER_HEIGHT = 23;
		static const int LETTER_WIDTH  = 24;
		Menu_T(int init_btn_cnt, int init_pos_x, int init_pos_y, Button_T *init_button);
		int Menu_T::getButtonUnderCursor(const int cursor_x, const int cursor_y) const;
		void Draw(void);
};

Menu_T::Menu_T(int init_btn_cnt, int init_pos_x, int init_pos_y, Button_T *init_button)
{
	btn_cnt = init_btn_cnt;
	pos_x = init_pos_x;
	pos_y = init_pos_y;
	button  = init_button;
	prev_highlighted_button = -1;

	/* Find length of the longest text string in the menu. */
	longest_button = -1;
	for (int i = 0; i < btn_cnt; i++)
	{
		int len = strlen(button[i].text);
		if (len > longest_button)
		{
			longest_button = len;
		}
	}

	/* Initialize positions and sizes of particular buttons in the menu. */
	for (int i = 0; i < btn_cnt; i++)
	{
		button[i].SetPosition(pos_x, pos_y + i * LETTER_HEIGHT);
		button[i].SetSize(LETTER_WIDTH * longest_button, LETTER_HEIGHT);
	}
}

int Menu_T::getButtonUnderCursor(const int cursor_x, const int cursor_y) const
{
	int button_under_cursor = -1;

	for (int i = 0; i < btn_cnt; i++)
	{
		if (true == button[i].isCursorAbove(cursor_x, cursor_y))
		{
			button_under_cursor = i;
			break;
		}
	}

	return button_under_cursor;
}

void Menu_T::Draw(void)
{
	const int FRAME_THICKNESS = 6;

	const int FRAME_WIDTH  = 2 * FRAME_THICKNESS + longest_button * LETTER_WIDTH;
	const int FRAME_HEIGHT = 1 * FRAME_THICKNESS + btn_cnt * LETTER_HEIGHT;

	const int FRAME_OFFSET_X = pos_x - FRAME_THICKNESS;
	const int FRAME_OFFSET_Y = pos_y /*- FRAME_THICKNESS*/;

	setcolor(GREEN);
	Frame(FRAME_OFFSET_X,
		  FRAME_OFFSET_Y,
		  FRAME_OFFSET_X + FRAME_WIDTH,
		  FRAME_OFFSET_Y + FRAME_HEIGHT,
		  FRAME_THICKNESS);

	for (int i = 0; i < btn_cnt; i++)
	{
		button[i].Draw(/*pos_x, pos_y + i * LETTER_HEIGHT*/);
	}
}

enum Buttons_MenuMain_T
{
	ID_BTN_MAINMENU = 0,
	ID_BTN_NEWGAME  = 1,
	ID_BTN_SAVE     = 2,
	ID_BTN_LOAD     = 3,
	ID_BTN_SETTINGS = 4,
	ID_BTN_CREDIT   = 5,
	ID_BTN_EXIT     = 6,
	ID_BTN_CANCEL   = 7,
};

Button_T gButtons_MenuMain[] =
{
	/*       Id                                                   X  Y  W  H  Frame  Click  GoToScene   Text        */
	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_MAINMENU*/, 0, 0, 0, 0, false, false, SCENE_NONE, "   Menu   "),
	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_NEWGAME */, 0, 0, 0, 0, false, false, SCENE_NONE, " New game "),
	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_SAVE    */, 0, 0, 0, 0, false, false, SCENE_NONE, "   Save   "),
	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_LOAD    */, 0, 0, 0, 0, false, false, SCENE_NONE, "   Load   "),
	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_SETTINGS*/, 0, 0, 0, 0, false, false, SCENE_NONE, " Settings "),
	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_CREDIT  */, 0, 0, 0, 0, false, false, SCENE_NONE, "  Credit  "),
	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_EXIT    */, 0, 0, 0, 0, false, false, SCENE_NONE, "   Exit   "),
	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_CANCEL  */, 0, 0, 0, 0, false, false, SCENE_NONE, "  Cancel  "),
};
Menu_T gMenuMain(sizeof(gButtons_MenuMain) / sizeof(Button_T), 200, 50, gButtons_MenuMain);

Button_T gButtons_MenuCredit[] =
{
	/*       Id                    X  Y  W  H  Frame  Click  GoToScene   Text              */
	Button_T(Button_T::Id_T::NONE, 0, 0, 0, 0, false, false, SCENE_NONE, "     Credit     "),
	Button_T(Button_T::Id_T::NONE, 0, 0, 0, 0, false, false, SCENE_NONE, "Programming:    "),
	Button_T(Button_T::Id_T::NONE, 0, 0, 0, 0, false, false, SCENE_NONE, "  Jozko Mrkvicka"),
	Button_T(Button_T::Id_T::NONE, 0, 0, 0, 0, false, false, SCENE_NONE, "                "),
	Button_T(Button_T::Id_T::NONE, 0, 0, 0, 0, false, false, SCENE_NONE, "Level design:   "),
	Button_T(Button_T::Id_T::NONE, 0, 0, 0, 0, false, false, SCENE_NONE, "  Janko Haluska "),
	Button_T(Button_T::Id_T::NONE, 0, 0, 0, 0, false, false, SCENE_NONE, "                "),
	Button_T(Button_T::Id_T::NONE, 0, 0, 0, 0, false, false, SCENE_NONE, "Graphics:       "),
	Button_T(Button_T::Id_T::NONE, 0, 0, 0, 0, false, false, SCENE_NONE, "  5o            "),
};
Menu_T gMenuCredit(sizeof(gButtons_MenuCredit) / sizeof(Button_T), 200, 100, gButtons_MenuCredit);


/* By design, order of items in the gItem array must be the same as order of enums in the ItemId_T type. */
static const int ITEM_COUNT_TOTAL = 12;
Item_T gItem[ITEM_COUNT_TOTAL] =
{   /*     Id_T                  X    Y    Frame  Type                 GoToScene          W    H  Bitmap              Text */
	Item_T(Item_T::KOFOLA,       400, 300, false, Item_T::COLLECTIBLE, SCENE_NONE,       75,  75, "..\\kofola.jpg",   "N/A"),
	Item_T(Item_T::RUM,          490, 300, false, Item_T::COLLECTIBLE, SCENE_NONE,       75,  75, "..\\rum.jpg",      "N/A"),
	Item_T(Item_T::GUITAR,       200, 180, false, Item_T::COLLECTIBLE, SCENE_NONE,       75,  75, "..\\guitar.jpg",   "N/A"),
	Item_T(Item_T::NOTEBOOK,     200, 300, false, Item_T::COLLECTIBLE, SCENE_NONE,       50,  50, "..\\notebook.jpg", "N/A"),
	Item_T(Item_T::FRIDGE,       500, 120, true,  Item_T::STATIC,      SCENE_NONE,      100, 150, "..\\fridge.jpg",   "N/A"),
	Item_T(Item_T::OVEN,         420, 100, false, Item_T::COLLECTIBLE, SCENE_NONE,       75,  75, "..\\oven.jpg",     "N/A"),
	Item_T(Item_T::BOOTS,         80, 250, false, Item_T::COLLECTIBLE, SCENE_NONE,       50,  50, "..\\boots.jpg"     "N/A"),
	Item_T(Item_T::PICTURE,       75,  75, false, Item_T::COLLECTIBLE, SCENE_NONE,      100, 100, "..\\picture.jpg",  "N/A"),
	Item_T(Item_T::TV,           400, 170, false, Item_T::STATIC,      SCENE_NONE,      100, 100, "..\\tv.jpg",       "N/A"),
	Item_T(Item_T::DOOR,         291, 102, false, Item_T::LINK,        SCENE_HOME,       85, 145, "..\\door.jpg",     "N/A"),
	Item_T(Item_T::CAR,          250, 220, false, Item_T::LINK,        SCENE_GO_TO_MAP, 350, 145, "..\\car.jpg",      "N/A"),
	Item_T(Item_T::STUDIO_ENTRY, 170, 180, false, Item_T::LINK,        SCENE_STUDIO,     60,  40, NULL,               "N/A"),
};

/* By design, order of scenes in the gScene array must be the same as order of enums in the SceneID_T type. */
static const int SCENE_COUNT = 10;
Scene_T gScene[SCENE_COUNT] =
{
	Scene_T(SCENE_KITCHEN,     "..\\test.jpg"),
	Scene_T(SCENE_BED_ROOM,    "..\\test.jpg"),
	Scene_T(SCENE_LIVING_ROOM, "..\\test.jpg"),
	Scene_T(SCENE_STUDIO,      "..\\studio.jpg"),
	Scene_T(SCENE_BRIDGE,      "..\\bridge.jpg"),
	Scene_T(SCENE_PUB,         "..\\pub.jpg"),
	Scene_T(SCENE_FOREST,      "..\\forest.jpg"),
	Scene_T(SCENE_SHOP,        "..\\shop.jpg"),
	Scene_T(SCENE_DOWNTOWN,    "..\\downtown.jpg"),
	Scene_T(SCENE_HOME,        "..\\home.jpg"),
};

void MouseMove(void);
void MouseClickLeft(void);

static void __control(void)
{
	
}

static void InitScene(void)
{
	gScene[SCENE_STUDIO].AddItem(&gItem[Item_T::FRIDGE]);
	gScene[SCENE_STUDIO].AddItem(&gItem[Item_T::KOFOLA]);
	gScene[SCENE_STUDIO].AddItem(&gItem[Item_T::TV]);
	gScene[SCENE_STUDIO].AddItem(&gItem[Item_T::RUM]);
	gScene[SCENE_STUDIO].AddItem(&gItem[Item_T::GUITAR]);
	gScene[SCENE_STUDIO].AddItem(&gItem[Item_T::BOOTS]);
	gScene[SCENE_STUDIO].AddItem(&gItem[Item_T::NOTEBOOK]);
	gScene[SCENE_STUDIO].AddItem(&gItem[Item_T::OVEN]);
	gScene[SCENE_STUDIO].AddItem(&gItem[Item_T::PICTURE]);
	gScene[SCENE_STUDIO].AddItem(&gItem[Item_T::DOOR]);

	gScene[SCENE_HOME].AddItem(&gItem[Item_T::CAR]);
	gScene[SCENE_HOME].AddItem(&gItem[Item_T::STUDIO_ENTRY]);
}

static void __inventory_init(void)
{
	//gInventory.Add(&item[FRIDGE]);
	//gInventory.Add(&item[KOFOLA]);
	//gInventory.Add(&item[TV]);
	//gInventory.Add(&item[RUM]);
	//gInventory.Add(&item[GUITAR]);
	//gInventory.Add(&item[BOOTS]);
	//gInventory.Add(&item[NOTEBOOK]);
	//gInventory.Add(&item[OVEN]);
	//gInventory.Add(&item[PICTURE]);
}

static void InitMap(void)
{
	gMap.node[Node_T::HOME    ].Show();
	gMap.node[Node_T::BRIDGE  ].Show();
	gMap.node[Node_T::PUB     ].Show();
	gMap.node[Node_T::FOREST  ].Show();
	gMap.node[Node_T::SHOP    ].Show();
	gMap.node[Node_T::DOWNTOWN].Show();

	gMap.node[Node_T::HOME    ].newly_created = false;
	gMap.node[Node_T::BRIDGE  ].newly_created = false;
	gMap.node[Node_T::PUB     ].newly_created = true;
	gMap.node[Node_T::FOREST  ].newly_created = false;
	gMap.node[Node_T::SHOP    ].newly_created = false;
	gMap.node[Node_T::DOWNTOWN].newly_created = false;

	gMap.node[Node_T::HOME    ].Enable();
	gMap.node[Node_T::PUB     ].Enable();
	gMap.node[Node_T::BRIDGE  ].Enable();
	gMap.node[Node_T::FOREST  ].Enable();

	gMap.node[Node_T::HOME    ].Connect(gMap.node[Node_T::BRIDGE  ]);
	gMap.node[Node_T::HOME    ].Connect(gMap.node[Node_T::DOWNTOWN]);
	gMap.node[Node_T::HOME    ].Connect(gMap.node[Node_T::FOREST  ]);
	gMap.node[Node_T::BRIDGE  ].Connect(gMap.node[Node_T::HOME    ]);
	gMap.node[Node_T::DOWNTOWN].Connect(gMap.node[Node_T::SHOP    ]);
	gMap.node[Node_T::DOWNTOWN].Connect(gMap.node[Node_T::PUB     ]);
}

static void WindowOpen(void)
{
    int width         = 640;
    int height        = 480;
    const char* title = "Adventure";
    int left          = 100;
    int top           = 20;
    bool dbflag       = true;
    bool closeflag    = true;
    initwindow(width, height, title, left, top, dbflag, closeflag);
    setvisualpage(1);
    setactivepage(1);
	Cursor_T cursor;
}

static void WindowClose(void)
{
	closegraph();
}

#include "class_element.h"


int main(void)
{
    cout << "### Adventure ###" << std::endl;
	WindowOpen();

//Element_T gPokusElement(5, 5, "Pokus Element");
//Item_T gPokusItem;
//cout << gPokusElement;
//cout <<	gPokusItem;
//(void) getchar();

	InitScene();
	//__inventory_init();
	InitMap();

	//gScene[gActiveScene].Draw();
	//gInventory.Draw();
	//gControl.Draw();

	//__control();
	gMap.Draw(Map_T::ALL);

	while (true)
	{
		MouseMove();
		MouseClickLeft();
	}

	WindowClose();
    return 0;
}

void MouseMove(void)
{
	if (true == ismouseclick(WM_MOUSEMOVE))
	{
		int mouse_x = -1;
		int mouse_y = -1;
		getmouseclick(WM_MOUSEMOVE, mouse_x, mouse_y);

		switch (gView)
		{
			case MAP:
			{
				Node_T::Id_T node_under_cursor = gMap.getNodeUnderCursor(mouse_x, mouse_y);
				if (gMap.prev_highlighted_node != node_under_cursor)
				{
					/* Light off previously highlighted node. */
					if (Node_T::NONE != gMap.prev_highlighted_node)
					{
						gMap.node[gMap.prev_highlighted_node].LightOff();
						gMap.node[gMap.prev_highlighted_node].DrawNode();
						gMap.prev_highlighted_node = Node_T::NONE;
					}

					/* Light on newly highlighted node. */
					if ((Node_T::NONE != node_under_cursor) &&
						gMap.node[node_under_cursor].isVisible() &&
						gMap.node[node_under_cursor].isEnabled())
					{
						gMap.node[node_under_cursor].LightOn();
						gMap.node[node_under_cursor].DrawNode();
						gMap.prev_highlighted_node = node_under_cursor;
					}
				}
				break;
			}

			
			case SCENE:
			{
				int button_under_cursor = gControl.getButtonUnderCursor(mouse_x, mouse_y);

				if (gControl.prev_highlighted_button != button_under_cursor)
				{
					/* Light off previously highlighted button. */
					if (-1 != gControl.prev_highlighted_button)
					{
						gControl.button[gControl.prev_highlighted_button].LightOff();
						gControl.button[gControl.prev_highlighted_button].Draw();
						gControl.prev_highlighted_button = Node_T::NONE;
					}

					/* Light on newly highlighted button. */
					if ((-1 != button_under_cursor) /*&&
						gControl.button[button_under_cursor].isVisible() &&
						gControl.button[button_under_cursor].isEnabled()*/)
					{
						gControl.button[button_under_cursor].LightOn();
						gControl.button[button_under_cursor].Draw();
						gControl.prev_highlighted_button = button_under_cursor;
					}
				}
				break;
			}

			case MENU:
			{
				int button_under_cursor = gMenuMain.getButtonUnderCursor(mouse_x, mouse_y);
				cout << button_under_cursor << endl;
				if (gMenuMain.prev_highlighted_button != button_under_cursor)
				{
					/* Light off previously highlighted button. */
					if (-1 != gMenuMain.prev_highlighted_button)
					{
						gMenuMain.button[gMenuMain.prev_highlighted_button].LightOff();
						gMenuMain.button[gMenuMain.prev_highlighted_button].Draw();
						gMenuMain.prev_highlighted_button = Node_T::NONE;
					}

					/* Light on newly highlighted button. */
					if ((-1 != button_under_cursor) /*&&
						gMenuMain.button[button_under_cursor].isVisible() &&
						gMenuMain.button[button_under_cursor].isEnabled()*/)
					{
						gMenuMain.button[button_under_cursor].LightOn();
						gMenuMain.button[button_under_cursor].Draw();
						gMenuMain.prev_highlighted_button = button_under_cursor;
					}
				}
				break;
			}
		}

#ifdef DEBUG
		setbkcolor(BLACK);
		setcolor(WHITE);
		settextstyle(DEFAULT_FONT, 0, 0);
		settextjustify(LEFT_TEXT, TOP_TEXT);
		outtextxy(0,  0, "     ");
		outtextxy(0, 16, "     ");
		outtextxy(0, 32, "     ");
		const char *view = (MAP == gView) ? "MAP" : (SCENE == gView) ? "SCENE" : "MENU";
		bgiout << "X=" << mouse_x << endl << "Y=" << mouse_y << endl << view;
		outstreamxy(0, 0);
#endif
	}
}

void MouseClickLeft(void)
{
	if (true == ismouseclick(WM_LBUTTONDOWN))
	{
		Button_T::Id_T button_under_cursor = Button_T::NONE;
		int mouse_x = -1;
		int mouse_y = -1;
		getmouseclick(WM_LBUTTONDOWN, mouse_x, mouse_y);

		switch (gView)
		{
			case MAP:
			{
				Node_T::Id_T node_under_cursor = gMap.getNodeUnderCursor(mouse_x, mouse_y);

				if ((Node_T::NONE != node_under_cursor) &&
					gMap.node[node_under_cursor].isVisible() &&
					gMap.node[node_under_cursor].isEnabled())
				{
					gMap.node[gMap.selected_node].Unselect();
					gMap.node[gMap.selected_node].DrawNode();
					gMap.node[node_under_cursor].Select();
					gMap.node[node_under_cursor].DrawNode();
					gMap.selected_node = node_under_cursor;

					SceneID_T id = gMap.node[node_under_cursor].go_to_scene;
					gScene[id].Draw();
					gInventory.Draw();
					gControl.Draw();

					gView = SCENE;
					gActiveScene = id;
				}
				break;
			}

			case SCENE:
			{
				int item_under_cursor = gScene[gActiveScene].getItemUnderCursor(mouse_x, mouse_y);
				button_under_cursor = gControl.getButtonUnderCursor(mouse_x, mouse_y);

				if (Item_T::NONE != item_under_cursor)
				{
					switch (gScene[gActiveScene].item[item_under_cursor]->type)
					{
					case Item_T::COLLECTIBLE:
					{
						Item_T* item = gScene[gActiveScene].RemoveItem(gScene[gActiveScene].item[item_under_cursor]->id);
						gInventory.Add(*item);
						gScene[gActiveScene].Draw();
						gInventory.Draw();
						gControl.Draw();
						break;
					}

					case Item_T::LINK:
						SceneID_T next_scene = gScene[gActiveScene].item[item_under_cursor]->go_to_scene;

						if (SCENE_NONE == next_scene)
						{
							cout << "WARNING: A link to next scene not defined." << endl;
						}
						else if (SCENE_GO_TO_MAP == next_scene)
						{
							gMap.Draw(Map_T::ALL);
							gView = MAP;
						}
						else
						{
							gActiveScene = next_scene;
							gScene[gActiveScene].Draw();
							gInventory.Draw();
							gControl.Draw();
						}
						break;
					}
				}

				if (Button_T::NONE != button_under_cursor)
				{
					switch (gControl.button[button_under_cursor].id)
					{
						case Button_T::Id_T::ARROW_LEFT:
							gInventory.ShiftView(Inventory_T::Direction_T::SCROLL_LEFT);  // TODO: Add a function pointer to the button class and call shiftview() via this pointer.
							gInventory.Draw();
							gControl.Draw();
							break;

						case Button_T::Id_T::ARROW_RIGHT:
							gInventory.ShiftView(Inventory_T::Direction_T::SCROLL_RIGHT);
							gInventory.Draw();
							gControl.Draw();
							break;

						case Button_T::Id_T::MAP:
							gMap.Draw(Map_T::ALL);
							gView = MAP;
							break;

						case Button_T::Id_T::MENU:
							gButtons_MenuMain[0].header = true;
							gMenuMain.Draw();

							//gButtons_MenuCredit[0].header = true;
							//gMenuCredit.Draw();

							gView = MENU;
							break;
					}
				}
				break;
			}

			case MENU:
			{
				//int button_under_cursor = gMenuMain.getButtonUnderCursor(mouse_x, mouse_y);
				//if (BTN_NONE != button_under_cursor)
				//{
				//	switch (gMenuMain.button[button_under_cursor].id)
				//	{
				//		case ID_BTN_CANCEL:
							gScene[gActiveScene].Draw();
							gInventory.Draw();
							gControl.Draw();
							gView = SCENE;
				//			break;
				//	}
				//}
				break;
			}
		}
	}
}
