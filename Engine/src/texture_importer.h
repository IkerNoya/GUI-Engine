#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H
#include "stb_image.h"
#include "export.h"

class ENGINE_API TextureImporter {

public:
	TextureImporter();
	~TextureImporter();
	void LoadImage();
};

#endif // !TEXTURE_IMPORTER_H

