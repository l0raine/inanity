#include "FontManager.hpp"
#include "Font.hpp"
#include "TextureManager.hpp"
#include "../ResourceManager.ipp"
#include "../InputStream.hpp"

FontManager::FontManager(ptr<FileSystem> fileSystem, ptr<TextureManager> textureManager)
: ResourceManager(fileSystem), textureManager(textureManager) {}

ptr<Font> FontManager::Load(const String& fontName)
{
	return Font::Deserialize(fileSystem->LoadStream(fontName), textureManager);
}
