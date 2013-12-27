#include "NpapiPluginInstance.hpp"
#include "NpapiPlugin.hpp"
#include "../input/Frame.hpp"

#if defined(___INANITY_PLATFORM_WINDOWS)
#include "Win32Window.hpp"
#include "../input/Win32WmManager.hpp"
#else
#error Unknown platform
#endif

BEGIN_INANITY_PLATFORM

NpapiPluginInstance::NpapiPluginInstance() :
	name("Inanity NPAPI Plugin"),
	description("Inanity NPAPI Plugin"),
	windowless(true),
	transparent(false),
	npp(nullptr)
{
#if defined(___INANITY_PLATFORM_WINDOWS)
	inputManager = NEW(Input::Win32WmManager());
#else
#error Unknown platform
#endif
}

void NpapiPluginInstance::Init(NPP npp)
{
	this->npp = npp;

	NpapiPlugin::browserFuncs.setvalue(npp, NPPVpluginWindowBool, (void*)!windowless);
	NpapiPlugin::browserFuncs.setvalue(npp, NPPVpluginTransparentBool, (void*)transparent);
	NpapiPlugin::browserFuncs.setvalue(npp, NPPVpluginUsesDOMForCursorBool, (void*)1);
}

NPError NpapiPluginInstance::SetWindow(NPWindow* npWindow)
{
#if defined(___INANITY_PLATFORM_WINDOWS)

	switch(npWindow->type)
	{
	case NPWindowTypeWindow:
		{
			HWND hNewWnd = (HWND)npWindow->window;
			if(window && window->GetHWND() != hNewWnd)
				window = Win32Window::CreateExisting(hNewWnd, false);
			hdc = 0;
		}
		break;
	case NPWindowTypeDrawable:
		{
			hdc = (HDC)npWindow->window;
			window = 0;
		}
		break;
	default:
		return NPERR_INVALID_PARAM;
	}

#else
#error Unknown platform
#endif

	return NPERR_NO_ERROR;
}

int16_t NpapiPluginInstance::HandleEvent(void* e)
{
#if defined(___INANITY_PLATFORM_WINDOWS)

	NPEvent* event = (NPEvent*)e;

	// process input events
	Input::Win32WmManager* inputManager = fast_cast<Input::Win32WmManager*>(&*this->inputManager);
	if(inputManager->ProcessWindowMessage(event->event, event->wParam, event->lParam))
		return 1;

	switch(event->event)
	{
	case WM_PAINT:
		{
			// get hdc to paint
			HDC hdc = this->hdc;
			PAINTSTRUCT ps;
			if(window)
				hdc = BeginPaint(window->GetHWND(), &ps);
			if(!hdc)
				return 0;

			// do painting
			Paint(hdc);

			if(window)
				EndPaint(window->GetHWND(), &ps);
		}
		return 1;
	default:
		return 0;
	}

#else
#error Unknown platform
#endif
}

#ifdef ___INANITY_PLATFORM_WINDOWS

void NpapiPluginInstance::Paint(HDC hdc)
{
	// do nothing by default
}

#endif

NPError NpapiPluginInstance::GetValue(NPPVariable variable, void* retValue)
{
	switch(variable)
	{
	case NPPVpluginNameString:
		*(const char**)retValue = name;
		break;
	case NPPVpluginDescriptionString:
		*(const char**)retValue = description;
		break;
	case NPPVpluginWindowBool:
		*(bool*)retValue = !windowless;
		break;
	case NPPVpluginTransparentBool:
		*(bool*)retValue = transparent;
		break;
	default:
		return NPERR_INVALID_PARAM;
	}

	return NPERR_NO_ERROR;
}

END_INANITY_PLATFORM
