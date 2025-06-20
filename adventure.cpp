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
#include "class_button.h"

using std::cout;
using std::cin;
using std::endl;

View_T gView = MAP;
//Node_T::Id_T gNodeUnderCursor = Node_T::NONE;
SceneID_T gActiveScene = SCENE_STUDIO;

Inventory_T gInventory("Inventory", 50, 360, NULL);

class Menu_T
{
	private:
		static const int FRAME_THICKNESS = 6;

		int pos_x;
		int pos_y;
		int btn_cnt;
		int longest_button;

	public:
		Button_T *button;
		int prev_highlighted_button;
		static const int LETTER_HEIGHT = 24;
		static const int LETTER_WIDTH  = 24;
		Menu_T(int init_btn_cnt, int init_pos_x, int init_pos_y, Button_T *init_button);
		int Menu_T::getButtonUnderCursor(const int cursor_x, const int cursor_y) const;
		void Draw(void) const;
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
		int len = strlen(button[i].GetText());
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
		if (true == button[i].IsCursorAbove(cursor_x, cursor_y))
		{
			button_under_cursor = i;
			break;
		}
	}

	return button_under_cursor;
}

void Menu_T::Draw(void) const
{
	const int RAKUSKA_KONSTANTA = 1;

	setcolor(GREEN);
	Frame(pos_x                                  - 1 * FRAME_THICKNESS,
		  pos_y                                  - 0 * FRAME_THICKNESS,
		  pos_x + LETTER_WIDTH  * longest_button + 1 * FRAME_THICKNESS,
		  pos_y + LETTER_HEIGHT * btn_cnt        + 1 * FRAME_THICKNESS - RAKUSKA_KONSTANTA,
		  FRAME_THICKNESS);

	for (int i = 0; i < btn_cnt; i++)
	{
		button[i].Draw();
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

//Button_T gButtons_MenuMain[] =
//{
//	/*       Id                                                   X  Y  Frame  Click  GoToScene   Bitmap Text        */
//	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_MAINMENU*/, 0, 0, false, false, SCENE_NONE, NULL,  "   Menu   "),
//	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_NEWGAME */, 0, 0, false, false, SCENE_NONE, NULL,  " New game "),
//	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_SAVE    */, 0, 0, false, false, SCENE_NONE, NULL,  "   Save   "),
//	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_LOAD    */, 0, 0, false, false, SCENE_NONE, NULL,  "   Load   "),
//	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_SETTINGS*/, 0, 0, false, false, SCENE_NONE, NULL,  " Settings "),
//	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_CREDIT  */, 0, 0, false, false, SCENE_NONE, NULL,  "  Credit  "),
//	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_EXIT    */, 0, 0, false, false, SCENE_NONE, NULL,  "   Exit   "),
//	Button_T(Button_T::Id_T::NONE/*(ButtonId_T)ID_BTN_CANCEL  */, 0, 0, false, false, SCENE_NONE, NULL,  "  Cancel  "),
//};
//Menu_T gMenuMain(sizeof(gButtons_MenuMain) / sizeof(Button_T), 200, 50, gButtons_MenuMain);

//Button_T gButtons_MenuCredit[] =
//{
//	/*       Id                    X  Y  Frame  Click  GoToScene   Bitmap Text              */
//	Button_T(Button_T::Id_T::NONE, 0, 0, false, false, SCENE_NONE, NULL,  "     Credit     "),
//	Button_T(Button_T::Id_T::NONE, 0, 0, false, false, SCENE_NONE, NULL,  "Programming:    "),
//	Button_T(Button_T::Id_T::NONE, 0, 0, false, false, SCENE_NONE, NULL,  "  Jozko Mrkvicka"),
//	Button_T(Button_T::Id_T::NONE, 0, 0, false, false, SCENE_NONE, NULL,  "                "),
//	Button_T(Button_T::Id_T::NONE, 0, 0, false, false, SCENE_NONE, NULL,  "Level design:   "),
//	Button_T(Button_T::Id_T::NONE, 0, 0, false, false, SCENE_NONE, NULL,  "  Janko Haluska "),
//	Button_T(Button_T::Id_T::NONE, 0, 0, false, false, SCENE_NONE, NULL,  "                "),
//	Button_T(Button_T::Id_T::NONE, 0, 0, false, false, SCENE_NONE, NULL,  "Graphics:       "),
//	Button_T(Button_T::Id_T::NONE, 0, 0, false, false, SCENE_NONE, NULL,  "  5o            "),
//};
//Menu_T gMenuCredit(sizeof(gButtons_MenuCredit) / sizeof(Button_T), 200, 100, gButtons_MenuCredit);

void MouseMove(void);
void MouseClickLeft(void);


////////////////////////////////////////////////////////////////////////////////////
//                        Buttons/Control initialization
////////////////////////////////////////////////////////////////////////////////////
static const int BUTTON_COUNT = 4;
static Button_T gButton[BUTTON_COUNT] =
{
	/*        Text       Id                       X    Y  Bitmap Frame GoToScene   Click */
	Button_T( "<\n<\n<", Button_T::ARROW_LEFT,   50,  50, NULL,  true, SCENE_NONE, false ),
	Button_T( ">\n>\n>", Button_T::ARROW_RIGHT, 100,  50, NULL,  true, SCENE_NONE, false ),
	Button_T( " Map  " , Button_T::MAP,         476,  50, NULL,  true, SCENE_NONE, false ),
	Button_T( " Menu " , Button_T::MENU,        476, 100, NULL,  true, SCENE_NONE, false ),
};
Control_T gControl;

static void InitControl(void)
{
	gControl.Add(&gButton[Button_T::ARROW_LEFT ]);
	gControl.Add(&gButton[Button_T::ARROW_RIGHT]);
	gControl.Add(&gButton[Button_T::MAP        ]);
	gControl.Add(&gButton[Button_T::MENU       ]);
}


////////////////////////////////////////////////////////////////////////////////////
//                               Item initialization
////////////////////////////////////////////////////////////////////////////////////
/* By design, order of items in the gItem array must be the same as order of enums
   in the ItemId_T type. */
static const int ITEM_COUNT_TOTAL = 12;
Item_T gItem[ITEM_COUNT_TOTAL] =
{   /*      Text            Id_T                    X    Y    W    H  Bitmap             Frame  GoToScene        Type               */
	Item_T( "Kofola",       Item_T::KOFOLA,       400, 300,  75,  75, "..\\kofola.jpg",  false, SCENE_NONE,      Item_T::COLLECTIBLE ),
	Item_T( "Rum",          Item_T::RUM,          490, 300,  75,  75, "..\\rum.jpg",     false, SCENE_NONE,      Item_T::COLLECTIBLE ),
	Item_T( "Guitar",       Item_T::GUITAR,       200, 180,  75,  75, "..\\guitar.jpg",  false, SCENE_NONE,      Item_T::COLLECTIBLE ),
	Item_T( "Notebook",     Item_T::NOTEBOOK,     200, 300,  50,  50, "..\\notebook.jpg",false, SCENE_NONE,      Item_T::COLLECTIBLE ),
	Item_T( "Fridge",       Item_T::FRIDGE,       500, 120, 100, 150, "..\\fridge.jpg",  true,  SCENE_NONE,      Item_T::STATIC      ),
	Item_T( "Oven",         Item_T::OVEN,         420, 100,  75,  75, "..\\oven.jpg",    false, SCENE_NONE,      Item_T::COLLECTIBLE ),
	Item_T( "Boots",        Item_T::BOOTS,         80, 250,  50,  50, "..\\boots.jpg",   false, SCENE_NONE,      Item_T::COLLECTIBLE ),
	Item_T( "Picture",      Item_T::PICTURE,       75,  75, 100, 100, "..\\picture.jpg", false, SCENE_NONE,      Item_T::COLLECTIBLE ),
	Item_T( "Tv",           Item_T::TV,           400, 170, 100, 100, "..\\tv.jpg",      false, SCENE_NONE,      Item_T::STATIC      ),
	Item_T( "Door",         Item_T::DOOR,         291, 102,  85, 145, "..\\door.jpg",    false, SCENE_HOME,      Item_T::LINK        ),
	Item_T( "Car",          Item_T::CAR,          250, 220, 350, 145, "..\\car.jpg",     false, SCENE_GO_TO_MAP, Item_T::LINK        ),
	Item_T( "Studio_entry", Item_T::STUDIO_ENTRY, 170, 180,  60,  40, NULL,              false, SCENE_STUDIO,    Item_T::LINK        ),
};


////////////////////////////////////////////////////////////////////////////////////
//                             Scene initialization
////////////////////////////////////////////////////////////////////////////////////
/* By design, order of scenes in the gScene array must be the same as order of enums
   in the SceneID_T type. */
static const int SCENE_COUNT = 10;
Scene_T gScene[SCENE_COUNT] =
{   /*       Text           Id                 X  Y         W    H  Bitmap             */
	Scene_T( "Kitchen",     SCENE_KITCHEN,     0, 0, 639 - 10, 378, "..\\test.jpg"     ),
	Scene_T( "Bed_room",    SCENE_BED_ROOM,    0, 0, 639 - 10, 378, "..\\test.jpg"     ),
	Scene_T( "Living_room", SCENE_LIVING_ROOM, 0, 0, 639 - 10, 378, "..\\test.jpg"     ),
	Scene_T( "Studio",      SCENE_STUDIO,      0, 0, 639 - 10, 378, "..\\studio.jpg"   ),
	Scene_T( "Bridge",      SCENE_BRIDGE,      0, 0, 639 - 10, 378, "..\\bridge.jpg"   ),
	Scene_T( "Pub",         SCENE_PUB,         0, 0, 639 - 10, 378, "..\\pub.jpg"      ),
	Scene_T( "Forest",      SCENE_FOREST,      0, 0, 639 - 10, 378, "..\\forest.jpg"   ),
	Scene_T( "Shop",        SCENE_SHOP,        0, 0, 639 - 10, 378, "..\\shop.jpg"     ),
	Scene_T( "Downtown",    SCENE_DOWNTOWN,    0, 0, 639 - 10, 378, "..\\downtown.jpg" ),
	Scene_T( "Home",        SCENE_HOME,        0, 0, 639 - 10, 378, "..\\home.jpg"     ),
};

static void InitScene(void)
{
	gScene[SCENE_STUDIO].Add(&gItem[Item_T::FRIDGE]);
	gScene[SCENE_STUDIO].Add(&gItem[Item_T::KOFOLA]);
	gScene[SCENE_STUDIO].Add(&gItem[Item_T::TV]);
	gScene[SCENE_STUDIO].Add(&gItem[Item_T::RUM]);
	gScene[SCENE_STUDIO].Add(&gItem[Item_T::GUITAR]);
	gScene[SCENE_STUDIO].Add(&gItem[Item_T::BOOTS]);
	gScene[SCENE_STUDIO].Add(&gItem[Item_T::NOTEBOOK]);
	gScene[SCENE_STUDIO].Add(&gItem[Item_T::OVEN]);
	gScene[SCENE_STUDIO].Add(&gItem[Item_T::PICTURE]);
	gScene[SCENE_STUDIO].Add(&gItem[Item_T::DOOR]);

	//gScene[SCENE_HOME].AddItem(&gItem[Item_T::CAR]);
	//gScene[SCENE_HOME].AddItem(&gItem[Item_T::STUDIO_ENTRY]);
}


////////////////////////////////////////////////////////////////////////////////////
//                           Inventory initialization
////////////////////////////////////////////////////////////////////////////////////
static void InitInventory(void)
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


////////////////////////////////////////////////////////////////////////////////////
//                               Map initialization
////////////////////////////////////////////////////////////////////////////////////
static const int NODE_COUNT = 6;
static Node_T gMapNode[NODE_COUNT] =
{
	/*      Text        Id                X    Y    Bitmap Frame  GoToScene       */
	Node_T( "Home",     Node_T::HOME,     100, 300, NULL,  false, SCENE_STUDIO   ),
	Node_T( "Bridge",   Node_T::BRIDGE,   500, 400, NULL,  false, SCENE_BRIDGE   ),
	Node_T( "Pub",      Node_T::PUB,      600, 250, NULL,  false, SCENE_PUB      ),
	Node_T( "Forest",   Node_T::FOREST,   100, 100, NULL,  false, SCENE_FOREST   ),
	Node_T( "Shop",     Node_T::SHOP,     460, 180, NULL,  false, SCENE_SHOP     ),
	Node_T( "Downtown", Node_T::DOWNTOWN, 340, 240, NULL,  false, SCENE_DOWNTOWN ),
};
Map_T gMap("Map", 0, 0, 640 - 10, 480, "../map.jpg");

static void InitMap(void)
{
	gMap.Add(&gMapNode[Node_T::HOME    ]);
	gMap.Add(&gMapNode[Node_T::BRIDGE  ]);
	gMap.Add(&gMapNode[Node_T::PUB     ]);
	gMap.Add(&gMapNode[Node_T::FOREST  ]);
	gMap.Add(&gMapNode[Node_T::SHOP    ]);
	gMap.Add(&gMapNode[Node_T::DOWNTOWN]);

	((Node_T*) gMap.element[Node_T::HOME    ])->Show();
	((Node_T*) gMap.element[Node_T::BRIDGE  ])->Show();
	((Node_T*) gMap.element[Node_T::PUB     ])->Show();
	((Node_T*) gMap.element[Node_T::FOREST  ])->Show();
	((Node_T*) gMap.element[Node_T::SHOP    ])->Show();
	((Node_T*) gMap.element[Node_T::DOWNTOWN])->Show();

	((Node_T*) gMap.element[Node_T::HOME    ])->newly_created = false;
	((Node_T*) gMap.element[Node_T::BRIDGE  ])->newly_created = false;
	((Node_T*) gMap.element[Node_T::PUB     ])->newly_created = true;
	((Node_T*) gMap.element[Node_T::FOREST  ])->newly_created = false;
	((Node_T*) gMap.element[Node_T::SHOP    ])->newly_created = false;
	((Node_T*) gMap.element[Node_T::DOWNTOWN])->newly_created = false;

	((Node_T*) gMap.element[Node_T::HOME    ])->Enable();
	((Node_T*) gMap.element[Node_T::PUB     ])->Enable();
	((Node_T*) gMap.element[Node_T::BRIDGE  ])->Enable();
	((Node_T*) gMap.element[Node_T::FOREST  ])->Enable();

	((Node_T*) gMap.element[Node_T::HOME    ])->Connect(* (Node_T*) gMap.element[Node_T::BRIDGE  ]);
	((Node_T*) gMap.element[Node_T::HOME    ])->Connect(* (Node_T*) gMap.element[Node_T::DOWNTOWN]);
	((Node_T*) gMap.element[Node_T::HOME    ])->Connect(* (Node_T*) gMap.element[Node_T::FOREST  ]);
	((Node_T*) gMap.element[Node_T::BRIDGE  ])->Connect(* (Node_T*) gMap.element[Node_T::HOME    ]);
	((Node_T*) gMap.element[Node_T::DOWNTOWN])->Connect(* (Node_T*) gMap.element[Node_T::SHOP    ]);
	((Node_T*) gMap.element[Node_T::DOWNTOWN])->Connect(* (Node_T*) gMap.element[Node_T::PUB     ]);

	gMap.element[gMap.selected_element]->Select();
}


////////////////////////////////////////////////////////////////////////////////////
//                                Main program
////////////////////////////////////////////////////////////////////////////////////
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

int main(void)
{
    cout << "### Adventure ###" << std::endl;
	WindowOpen();

	InitControl();
	InitMap();
	InitScene();
	InitInventory();
	gMap.Draw();

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
				/* We need to shift cursor coordinates because the origin of a node is placed in center of the node
				   (contrary to rectangles where the origin is placed in top-left corner). */
				int element_under_cursor = gMap.GetElementUnderCursor(mouse_x + Node_T::RADIUS, mouse_y + Node_T::RADIUS);
				gMap.Highlight(element_under_cursor);
				break;
			}
			
//			case SCENE:
//			{
//				int button_under_cursor = gControl.getButtonUnderCursor(mouse_x, mouse_y);
//
//				if (gControl.prev_highlighted_button != button_under_cursor)
//				{
//					/* Light off previously highlighted button. */
//					if (-1 != gControl.prev_highlighted_button)
//					{
//						gControl.button[gControl.prev_highlighted_button].LightOff();
//						gControl.button[gControl.prev_highlighted_button].Draw();
//						gControl.prev_highlighted_button = Node_T::NONE;
//					}
//
//					/* Light on newly highlighted button. */
//					if ((-1 != button_under_cursor) /*&&
//						gControl.button[button_under_cursor].isVisible() &&
//						gControl.button[button_under_cursor].isEnabled()*/)
//					{
//						gControl.button[button_under_cursor].LightOn();
//						gControl.button[button_under_cursor].Draw();
//						gControl.prev_highlighted_button = button_under_cursor;
//					}
//				}
//				break;
//			}
//
//			case MENU:
//			{
//				int button_under_cursor = gMenuMain.getButtonUnderCursor(mouse_x, mouse_y);
//				cout << button_under_cursor << endl;
//				if (gMenuMain.prev_highlighted_button != button_under_cursor)
//				{
//					/* Light off previously highlighted button. */
//					if (-1 != gMenuMain.prev_highlighted_button)
//					{
//						gMenuMain.button[gMenuMain.prev_highlighted_button].LightOff();
//						gMenuMain.button[gMenuMain.prev_highlighted_button].Draw();
//						gMenuMain.prev_highlighted_button = Node_T::NONE;
//					}
//
//					/* Light on newly highlighted button. */
//					if ((-1 != button_under_cursor) /*&&
//						gMenuMain.button[button_under_cursor].isVisible() &&
//						gMenuMain.button[button_under_cursor].isEnabled()*/)
//					{
//						gMenuMain.button[button_under_cursor].LightOn();
//						gMenuMain.button[button_under_cursor].Draw();
//						gMenuMain.prev_highlighted_button = button_under_cursor;
//					}
//				}
//				break;
//			}
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
		//Button_T::Id_T button_under_cursor = Button_T::NONE;
		int mouse_x = -1;
		int mouse_y = -1;
		getmouseclick(WM_LBUTTONDOWN, mouse_x, mouse_y);

		switch (gView)
		{
			case MAP:
			{
				/* We need to shift cursor coordinates because the origin of a node is placed in center of the node
				   (contrary to rectangles where the origin is placed in top-left corner). */
				int element_under_cursor = gMap.GetElementUnderCursor(mouse_x + Node_T::RADIUS, mouse_y + Node_T::RADIUS);

				if ((Node_T::NONE != element_under_cursor) &&
					gMap.element[element_under_cursor]->IsVisible() &&
					gMap.element[element_under_cursor]->IsEnabled())
				{
					gMap.Select(element_under_cursor);

					SceneID_T id = gMap.element[element_under_cursor]->go_to_scene;
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
				int element_under_cursor = gScene[gActiveScene].GetElementUnderCursor(mouse_x, mouse_y);
				//button_under_cursor = gControl.getButtonUnderCursor(mouse_x, mouse_y);

				if (Item_T::NONE != element_under_cursor)
				{
					switch (((Item_T*) gScene[gActiveScene].element[element_under_cursor])->type)
					{
						case Item_T::COLLECTIBLE:
						{
							Element_T* element /*Item_T* item*/ = /*(Item_T*)*/ gScene[gActiveScene].Remove(gScene[gActiveScene].element[element_under_cursor]->GetId());
							gInventory.Add(element/*item*/);
							gScene[gActiveScene].Draw();
							gInventory.Draw();
							gControl.Draw();
							break;
						}

	//					case Item_T::LINK:
	//						SceneID_T next_scene = gScene[gActiveScene].item[element_under_cursor]->go_to_scene;

	//						if (SCENE_NONE == next_scene)
	//						{
	//							cout << "WARNING: A link to next scene not defined." << endl;
	//						}
	//						else if (SCENE_GO_TO_MAP == next_scene)
	//						{
	//							gMap.Draw(Map_T::ALL);
	//							gView = MAP;
	//						}
	//						else
	//						{
	//							gActiveScene = next_scene;
	//							gScene[gActiveScene].Draw();
	//							gInventory.Draw();
	//							gControl.Draw();
	//						}
	//						break;
						}
				}

	//			if (Button_T::NONE != button_under_cursor)
	//			{
	//				switch (gControl.button[button_under_cursor].id)
	//				{
	//					case Button_T::Id_T::ARROW_LEFT:
	//						gInventory.ShiftView(Inventory_T::Direction_T::SCROLL_LEFT);  // TODO: Add a function pointer to the button class and call shiftview() via this pointer.
	//						gInventory.Draw();
	//						gControl.Draw();
	//						break;

	//					case Button_T::Id_T::ARROW_RIGHT:
	//						gInventory.ShiftView(Inventory_T::Direction_T::SCROLL_RIGHT);
	//						gInventory.Draw();
	//						gControl.Draw();
	//						break;

	//					case Button_T::Id_T::MAP:
	//						gMap.Draw(Map_T::ALL);
	//						gView = MAP;
	//						break;

	//					case Button_T::Id_T::MENU:
	//						gButtons_MenuMain[0].header = true;
	//						gMenuMain.Draw();

	//						//gButtons_MenuCredit[0].header = true;
	//						//gMenuCredit.Draw();

	//						gView = MENU;
	//						break;
	//				}
	//			}
				break;
			}

	//		case MENU:
	//		{
	//			//int button_under_cursor = gMenuMain.getButtonUnderCursor(mouse_x, mouse_y);
	//			//if (BTN_NONE != button_under_cursor)
	//			//{
	//			//	switch (gMenuMain.button[button_under_cursor].id)
	//			//	{
	//			//		case ID_BTN_CANCEL:
	//						gScene[gActiveScene].Draw();
	//						gInventory.Draw();
	//						gControl.Draw();
	//						gView = SCENE;
	//			//			break;
	//			//	}
	//			//}
	//			break;
	//		}
		}

#ifdef DEBUG
		system("cls");
		cout << gControl;
		cout << gMap;
		cout << gInventory;
		cout << gScene[gActiveScene];
#endif
	}
}
