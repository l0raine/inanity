#ifndef ___INANITY_GRAPHICS_SDL_PRESENTER_HPP___
#define ___INANITY_GRAPHICS_SDL_PRESENTER_HPP___

#include "Presenter.hpp"
#include "../platform/platform.hpp"

BEGIN_INANITY_PLATFORM

class SdlWindow;

END_INANITY_PLATFORM

BEGIN_INANITY_GRAPHICS

class GlDevice;
class GlFrameBuffer;

/// Presenter class using SDL.
class SdlPresenter : public Presenter
{
private:
	ptr<GlDevice> device;
	ptr<GlFrameBuffer> frameBuffer;
	ptr<Platform::SdlWindow> window;

public:
	SdlPresenter(ptr<GlDevice> device, ptr<GlFrameBuffer> frameBuffer, ptr<Platform::SdlWindow> window);

	//*** Presenter's methods.
	ptr<Device> GetDevice() const;
	ptr<FrameBuffer> GetFrameBuffer() const;
	void SetMode(ptr<MonitorMode> mode);
	void Present();
	void Resize(int width, int height);
};

END_INANITY_GRAPHICS

#endif