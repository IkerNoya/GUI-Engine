#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H
#include "stb_image.h"
#include "export.h"

class ENGINE_API TextureImporter {
	const char* _path;
	unsigned int _texture;
public:
	TextureImporter();
	TextureImporter(const char* path);
	TextureImporter(int width, int height, const char* path, bool transparency);
	~TextureImporter();
	void LoadImage(int width, int height, bool transparency);
	void SetPath(const char* path);
	const char* GetPath();
	unsigned int GetTexture();
};

#endif // !TEXTURE_IMPORTER_H

