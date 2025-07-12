#pragma once

#include "common.h"
#include "ITexture.h"

class Texture : public ITexture {
	Image image_;
public:
	Texture(Image image);
	Size GetSize() const override;
	const Image &GetImage() const override;
};