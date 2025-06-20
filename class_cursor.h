#ifndef CLASS_CURSOR_T
#define CLASS_CURSOR_T

extern bool gMapVisible;

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
		void Draw(void) const;
};

//void Handler_WM_MOUSEMOVE(int x, int y);
//void Handler_WM_LBUTTONDOWN(int x, int y);
//void Handler_WM_LBUTTONUP(int x, int y);
//void Handler_WM_LBUTTONDBLCLK(int x, int y);
//void Handler_WM_MBUTTONDOWN(int x, int y);
//void Handler_WM_MBUTTONUP(int x, int y);
//void Handler_WM_MBUTTONDBLCLK(int x, int y);
//void Handler_WM_RBUTTONDOWN(int x, int y);
//void Handler_WM_RBUTTONUP(int x, int y);
//void Handler_WM_RBUTTONDBLCLK(int x, int y);

#endif
