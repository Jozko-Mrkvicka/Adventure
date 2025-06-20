#ifndef CLASS_COLLECTION_T
#define CLASS_COLLECTION_T

#include "class_collection.h"
#include "class_base.h"
#include "class_element.h"

class Collection_T : public Base_T
{
	private:

	protected:
		int count;

	public:
		int selected_element;
		int prev_highlighted;
		Element_T** element;

		Collection_T(const char* const text,
					 const int         id,
					 const int         pos_x,
					 const int         pos_y,
					 const int         width,
					 const int         height,
					 const char* const bitmap);

		void Add(Element_T* new_element);
		Element_T* Remove(const int item_id);
		void Select(const int element_under_cursor);
		void Highlight(const int element_under_cursor);
		void Draw(void) const;
		int GetElementUnderCursor(const int cursor_x, const int cursor_y) const;

		friend ostream& operator<<(ostream& os, Collection_T collection);
};

#endif
