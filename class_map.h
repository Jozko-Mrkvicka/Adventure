#ifndef CLASS_MAP_T
#define CLASS_MAP_T

#include "class_node.h"
#include "class_collection.h"

class Map_T : public Collection_T
{
	private:

	public:
		enum MapDrawOption_T
		{
			ALL        = 0,
			NODE       = 1,
			CONNECTION = 2,
			DIRECTION  = 3,
			BACKGROUND = 4,
		};

		Map_T(const char* const text,
			  const int         pos_x,
			  const int         pos_y,
			  const int         width,
			  const int         height,
			  const char* const bitmap);
};

#endif
