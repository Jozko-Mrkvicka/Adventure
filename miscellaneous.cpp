#include "miscellaneous.h"
#include "graphics.h"

void Frame(const int left, const int top, const int right, const int bottom, const int thickness, const int linestyle)
{
	setlinestyle(linestyle, 0, NORM_WIDTH);
	for (int i = 0; i < thickness; i++)
	{
		rectangle(left + i, top + i, right - i, bottom - i);
	}
}

/* Dummy implementation of missing functions. */
int installuserdriver(char* name, int* fp) { return 0;     }
int installuserfont(char* name)            { return 0;     }
int registerbgidriver(void* driver)        { return 0;     }
int registerbgifont(void* font)            { return 0;     }
unsigned setgraphbufsize(unsigned bufsize) { return 0;     }
void clearresizeevent(void)                {               }
bool isresizeevent(void)                   { return false; }

//static int GetMaxX(viewporttype &viewport)
//{
//	return viewport.right - viewport.left;
//}
//
//static int GetMaxY(viewporttype &viewport)
//{
//	return viewport.bottom - viewport.top;
//}
