#include "graphics.h"
#include "class_collection.h"
#include "class_button.h"
#include "class_item.h"

Collection_T::Collection_T(const char* const text,
						   const int         id,
						   const int         pos_x,
						   const int         pos_y,
						   const int         width,
						   const int         height,
						   const char* const bitmap) : Base_T(text, id, pos_x, pos_y, width, height, bitmap)
{
	prev_highlighted = -1;
	selected_element = -1;
	count            = 0;
	element          = NULL;
}

void Collection_T::Add(Element_T* new_element)
{
	if (NULL == element)
	{
		count++;
		element = new Element_T * [count];
		element[count - 1] = new_element;
	}
	else
	{
		/* Check if an element which we want to add already exists in the element array. */
		bool element_already_exists = false;
		for (int i = 0; i < count; i++)
		{
			if (element[i]->GetId() == new_element->GetId())
			{
				element_already_exists = true;
				break;
			}
		}

		if (false == element_already_exists)
		{
			/* Save the item pointer array to temp. */
			Element_T** temp = new Element_T * [count];
			for (int i = 0; i < count; i++)
			{
				temp[i] = element[i];
			}

			delete[] element;
			count++;

			/* Load the item pointer array from temp. */
			element = new Element_T * [count];
			for (int i = 0; i < count - 1; i++)
			{
				element[i] = temp[i];
			}

			element[count - 1] = new_element;
		}
		else
		{
			cout << "WARNING (Collection_T::Add()): Element with ID=" << new_element->GetId() << " already exists in collection." << endl;
		}
	}
}

Element_T* Collection_T::Remove(const int item_id)
{
	Element_T* retval = NULL;

	if (NULL != element)
	{
		/* Check if an element which we want to remove exists in the element array. */
		bool item_exists = false;
		for (int i = 0; i < count; i++)
		{
			if (element[i]->GetId() == item_id)
			{
				item_exists = true;
				break;
			}
		}

		if (true == item_exists)
		{
			if (1 == count)
			{
				retval = element[0];
				delete[] element;
				element = NULL;
				count = 0;
			}
			else
			{
				/* Find the element which we want to remove and copy all other elements to a temp array. */
				Element_T** temp = new Element_T * [count - 1];
				int j = 0;
				for (int i = 0; i < count; i++)
				{
					if (element[i]->GetId() == item_id)
					{
						retval = element[i];
					}
					else
					{
						temp[j] = element[i];
						j++;
					}
				}
				delete[] element;

				count--;

				/* Copy the temp array back to the element array. */
				element = new Element_T* [count];
				for (int i = 0; i < count; i++)
				{
					element[i] = temp[i];
				}
				delete[] temp;
			}
		}
		else
		{
			cout << "WARNING (Collection_T::Remove()): Element with ID=" << item_id << " does not exist in collection." << endl;
		}
	}

	return retval;
}

int Collection_T::GetElementUnderCursor(const int cursor_x, const int cursor_y) const
{
	int node_under_cursor = -1;

	for (int i = 0; i < count; i++)
	{
		if (true == element[i]->IsCursorAbove(cursor_x, cursor_y))
		{
			node_under_cursor = i;
			break;
		}
	}

	return node_under_cursor;
}

void Collection_T::Select(const int element_under_cursor)
{
	element[selected_element]->Unselect();
	element[selected_element]->Draw();

	selected_element = element_under_cursor;
	element[selected_element]->Select();
	element[selected_element]->Draw();
}

void Collection_T::Highlight(const int element_under_cursor)
{
	if (prev_highlighted != element_under_cursor)
	{
		/* Light off previously highlighted element. */
		if (-1 != prev_highlighted)
		{
			element[prev_highlighted]->LightOff();
			element[prev_highlighted]->Draw();
			prev_highlighted = -1;
		}

		/* Light on newly highlighted element. */
		if ((-1 != element_under_cursor) &&
			element[element_under_cursor]->IsVisible() &&
			element[element_under_cursor]->IsEnabled())
		{
			element[element_under_cursor]->LightOn();
			element[element_under_cursor]->Draw();
			prev_highlighted = element_under_cursor;
		}
	}
}

void Collection_T::Draw(void) const
{
	if (NULL != bitmap)             { readimagefile(bitmap, pos_x, pos_y, pos_x + width, pos_y + height); }
	for (int i = 0; i < count; i++)	{ element[i]->Draw();                                              	  }
}

ostream& operator<<(ostream& os, Collection_T collection)
{
	/* Print name of a collection. */
	cout << collection.GetText() << endl;

	/* Print names of all elements contained in the collection. */
	if (0 == collection.count)
	{
		cout << "None" << endl;
	}
	else
	{
		for (int i = 0; i < collection.count; i++)
		{
			cout << "element[" << i << "] = \"" << collection.element[i]->GetText() << "\"" << endl;
		}
	}
	cout << endl;

	return os;
}
