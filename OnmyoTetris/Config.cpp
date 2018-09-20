#include "Config.hpp"

string mkDir(const string filename, fileType type)
{
	switch (type)
	{
	case texture:
		return "./Src/Texture/" + filename;
		break;
	case sound:
		return "./Src/Sound/" + filename;
		break;
	case music:
		return "./Src/Music/" + filename;
		break;
	case font:
		return "./Src/Font/" + filename;
		break;
	}
}