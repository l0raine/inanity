#include "GlSystem.hpp"
#ifdef ___INANITY_WINDOWS
#include "../windows.hpp"
#endif
#include "../Exception.hpp"

ptr<Window> GlSystem::CreateWindow()
{
#ifdef ___INANITY_WINDOWS
	return Win32Window::CreateForOpenGL();
#endif
#ifdef ___INANITY_LINUX
	return NEW(X11Window());
#endif
}

ptr<Device> GlSystem::CreatePrimaryDevice()
{
	try
	{
#ifdef ___INANITY_WINDOWS
		// получить всё устройства
		DISPLAY_DEVICE deviceInfo;
		deviceInfo.cb = sizeof(deviceInfo);
		for(DWORD i = 0; EnumDisplayDevices(NULL, i, &deviceInfo, 0); ++i)
			// если устройство primary
			if(deviceInfo.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
				// вернуть его
				return NEW(GlDevice(this, deviceInfo.DeviceName, 0));

		// в MSDN написано, устройство всегда есть, так что этого быть не должно
		THROW_PRIMARY_EXCEPTION("Can't find primary device");
#endif
	}
	catch(Exception* exception)
	{
		THROW_SECONDARY_EXCEPTION("Can't create primary device", exception);
	}
}

static void GlSystem::CheckErrors(const char* primaryExceptionString)
{
	GLenum error = glGetError();
	// если есть хотя бы одна ошибка
	if(error != GL_NO_ERROR)
	{
		// согласно спецификации, может быть несколько ошибок
		// получаем их, пока не кончатся
		String errorStrings = "OpenGL error(s):";
		do
		{
			// получить строку ошибки
			const char* errorString;

#define DEFINE_GL_ERROR(code) \
	case code: \
		errorString = " " #code; \
		break

			switch(error)
			{
				DEFINE_GL_ERROR(GL_INVALID_ENUM);
				DEFINE_GL_ERROR(GL_INVALID_VALUE);
				DEFINE_GL_ERROR(GL_INVALID_OPERATION);
				DEFINE_GL_ERROR(GL_INVALID_FRAMEBUFFER_OPERATION);
				DEFINE_GL_ERROR(GL_OUT_OF_MEMORY);
			default:
				errorString = "Unknown OpenGL error";
				break;
			}

#undef DEFINE_GL_ERROR

			errorStrings += errorString;
		}
		while((error = glGetError()) != GL_NO_ERROR);

		// всё, ошибки кончились, и флаги ошибок очищены
		// бросить исключение
		if(primaryExceptionString)
			THROW_SECONDARY_EXCEPTION(primaryExceptionString, NEW(Exception(errorStrings)));
		else
			THROW_PRIMARY_EXCEPTION(errorStrings);
	}
}

bool GlSystem::GetTextureFormat(PixelFormat pixelFormat, GLint& internalFormat, GLenum& format, GLenum& type)
{
	switch(pixelFormat)
	{
	case PixelFormats::intR8G8B8A8:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		return true;
	case PixelFormats::floatR11G11B10:
		internalFormat = GL_R11F_G11F_B10F;
		format = GL_RGB;
		type = GL_UNSIGNED_BYTE;
		return true;
	//case PixelFormats::typelessR32:
	case PixelFormats::floatR32:
		internalFormat = GL_R32F;
		format = GL_RED;
		type = GL_UNSIGNED_BYTE;
		return true;
	case PixelFormats::floatR32Depth:
		internalFormat = GL_DEPTH_COMPONENT_32F;
		format = GL_DEPTH_COMPONENT;
		type = GL_FLOAT;
		return true;
	case PixelFormats::unknown:
	default:
		return false;
	}
}
