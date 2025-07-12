#pragma once

#include <cassert>
#include "common.h"
#include "ITexture.h"

class Texture : public ITexture {
	Image image_;
public:
	Texture(Image image) : image_(std::move(image)) {
		for (const auto &line : image_)
			assert(line.size() == image_[0].size());
	}

	Size GetSize() const override {
		auto width = static_cast<int>(image_.empty() ? 0 : image_[0].size());
		auto height = static_cast<int>(image_.size());
		return {width, height};
	}

	const Image &GetImage() const override { return image_; }
};
