#ifndef DATATYPE
#define DATATYPE

// TODO: problem pri vkladani, cyklicka zavislost.
/* By design, order of scenes in the gScene array must be the same like order of enums in the SceneID_T type. */
enum SceneID_T
{
	SCENE_NONE        = -1,
	SCENE_KITCHEN     =  0,
	SCENE_BED_ROOM    =  1,
	SCENE_LIVING_ROOM =  2,
	SCENE_STUDIO      =  3,
	SCENE_BRIDGE      =  4,
	SCENE_PUB         =  5,
	SCENE_FOREST      =  6,
	SCENE_SHOP        =  7,
	SCENE_DOWNTOWN    =  8,
	SCENE_HOME        =  9,

	SCENE_GO_TO_MAP   = 99,
};

#endif
