#pragma once

#include <string>
#include <vector>

namespace ModelInfo {
	enum Model_NAMES {
		ALTAIR,
		BACKPACK,
		CASTLE,
		CYBORG,
		DRAGON,
		GODZILLA,
		GRASS,
		KINGKONG,
		NANOSUIT,
		PLANET,
		ROCK,
		TABLE,
		TEAPOT,
		TREE
	};
	const int count = 14;
	const char* modelNames[] = { 
		"ALTAIR",
		"BACKPACK",
		"CASTLE",
		"CYBORG",
		"DRAGON",
		"GODZILLA",
		"GRASS",
		"KINGKONG",
		"NANOSUIT",
		"PLANET",
		"ROCK",
		"TABLE",
		"TEAPOT",
		"TREE" 
	};

	std::vector<Model_NAMES> modelEnums = {
		ALTAIR,
		BACKPACK,
		CASTLE,
		CYBORG,
		DRAGON,
		GODZILLA,
		GRASS,
		KINGKONG,
		NANOSUIT,
		PLANET,
		ROCK,
		TABLE,
		TEAPOT,
		TREE
	};

	std::string getPath(Model_NAMES model)
	{
		switch (model)
		{
		case ALTAIR:
			return "res/models/altair/assassins-creed-altair.obj";
			break;
		case BACKPACK:
			return "res/models/backpack/backpack.obj";
			break;
		case CASTLE:
			return "res/models/new castle/castle-tower.obj";
			break;
		case CYBORG:
			return "res/models/cyborg/cyborg.obj";
			break;
		case DRAGON:
			return "res/models/dragon/alduin-dragon.obj";
			break;
		case GODZILLA:
			return "res/models/godzilla/godzilla-earth.obj";
			break;
		case GRASS:
			return "res/models/grass/grass.obj";
			break;
		case KINGKONG:
			return "res/models/kingkong/king-kong.obj";
			break;
		case NANOSUIT:
			return "res/models/nanosuit/nanosuit.obj";
			break;
		case PLANET:
			return "res/models/planet/planet.obj";
			break;
		case ROCK:
			return "res/models/rock/rock.obj";
			break;
		case TABLE:
			return "res/models/table/table.obj";
			break;
		case TEAPOT:
			return "res/models/teapot/utah-teapot.obj";
			break;
		case TREE:
			return "res/models/tree/tree.obj";
			break;
		default:
			return "res/models/backpack/backpack.obj";
			break;
		}
	}

}


