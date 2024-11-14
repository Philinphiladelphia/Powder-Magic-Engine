#include "Platform.h"
#include "common/PTString.h"
#include "Config.h"
#include <SDL.h>
#include <memory>

namespace Platform
{
ByteString DefaultDdir()
{
	auto ddir = std::shared_ptr<char>(SDL_GetPrefPath(NULL, APPDATA));
	return ddir.get();
}
}
