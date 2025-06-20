#include "class_cursor.h"
#include "class_map.h"
#include "graphics.h"
#include "definitions.h"
#include <iostream>

extern View_T gView;
extern Map_T gMap;
extern int gNodeUnderCursor;
extern bool gUserInput;

Cursor_T::Cursor_T()
{
	pos_x = 0;
	pos_y = 0;

	icon = NULL;

	//registermousehandler(WM_MOUSEMOVE,     Handler_WM_MOUSEMOVE);
	//registermousehandler(WM_LBUTTONDOWN,   Handler_WM_LBUTTONDOWN);
	//registermousehandler(WM_LBUTTONUP,     Handler_WM_LBUTTONUP);
	//registermousehandler(WM_LBUTTONDBLCLK, Handler_WM_LBUTTONDBLCLK);
	//registermousehandler(WM_MBUTTONDOWN,   Handler_WM_MBUTTONDOWN);
	//registermousehandler(WM_MBUTTONUP,     Handler_WM_MBUTTONUP);
	//registermousehandler(WM_MBUTTONDBLCLK, Handler_WM_MBUTTONDBLCLK);
	//registermousehandler(WM_RBUTTONDOWN,   Handler_WM_RBUTTONDOWN);
	//registermousehandler(WM_RBUTTONUP,     Handler_WM_RBUTTONUP);
	//registermousehandler(WM_RBUTTONDBLCLK, Handler_WM_RBUTTONDBLCLK);
}

void Cursor_T::GetPosition(void)
{
	pos_x = mousex();
	pos_y = mousey();
}

void Cursor_T::Draw(void) const
{
	readimagefile(icon, pos_x, pos_y, pos_x - SIZE, pos_y - SIZE);
}

//void Handler_WM_MOUSEMOVE(int x, int y)
//{
//
//	//switch (gView)
//	//{		
//	//	case MAP:
//	//		gNodeUnderCursor = gMap.CheckCursor();
//	//		gUserInput = true;
//	//		break;
//
//	//	case SCENE:
//	//		break;
//	//}
//}
//
//void Handler_WM_LBUTTONDOWN(int x, int y)
//{
//	//switch (gView)
//	//{		
//	//	case MAP:
//	//		break;
//
//	//	case SCENE:
//	//		break;
//	//}
//}
//
//void Handler_WM_LBUTTONDBLCLK(int x, int y)
//{
//
//}
//
//void Handler_WM_LBUTTONUP(int x, int y)
//{
//
//}
//
//void Handler_WM_MBUTTONDBLCLK(int x, int y)
//{
//
//}
//
//void Handler_WM_MBUTTONDOWN(int x, int y)
//{
//
//}
//
//void Handler_WM_MBUTTONUP(int x, int y)
//{
//
//}
//
//void Handler_WM_RBUTTONDBLCLK(int x, int y)
//{
//
//}
//
//void Handler_WM_RBUTTONDOWN(int x, int y)
//{
//
//}
//
//void Handler_WM_RBUTTONUP(int x, int y)
//{
//
//}
