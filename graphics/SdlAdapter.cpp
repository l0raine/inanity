#include "SdlAdapter.hpp"
#include "SdlMonitor.hpp"
#include "../platform/Sdl.hpp"
#include "../Exception.hpp"
#include <SDL2/SDL_video.h>

BEGIN_INANITY_GRAPHICS

SdlAdapter::SdlAdapter(int videoDriverIndex) :
	sdl(Platform::Sdl::Get(SDL_INIT_VIDEO)),
	monitorsInitialized(false)
{
	BEGIN_TRY();

	const char* videoDriverName = SDL_GetVideoDriver(videoDriverIndex);
	if(!videoDriverName)
		THROW_SECONDARY("Can't get video driver name", Platform::Sdl::Error());
	name = videoDriverName;

	END_TRY("Can't create SDL adapter");
}

String SdlAdapter::GetId() const
{
	return name;
}

String SdlAdapter::GetName() const
{
	return name;
}

const Adapter::Monitors& SdlAdapter::GetMonitors()
{
	BEGIN_TRY();

	if(!monitorsInitialized)
	{
		int monitorsCount = SDL_GetNumVideoDisplays();
		if(monitorsCount <= 0)
			THROW_SECONDARY("Can't get number of video displays", Platform::Sdl::Error());
		monitors.resize(monitorsCount);
		for(int i = 0; i < monitorsCount; ++i)
			monitors[i] = NEW(SdlMonitor(i));

		monitorsInitialized = true;
	}

	return monitors;

	END_TRY("Can't get SDL monitors");
}

void SdlAdapter::GetAdapters(Adapters& adapters)
{
	int adaptersCount = SDL_GetNumVideoDrivers();
	for(int i = 0; i < adaptersCount; ++i)
		adapters.push_back(NEW(SdlAdapter(i)));
}

END_INANITY_GRAPHICS
