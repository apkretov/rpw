#include "Texture.h"
#include <cassert>

Texture::Texture(Image image) : image_(std::move(image)) {
	for (const auto &line : image_)
		assert(line.size() == image_[0].size());
}

Size Texture::GetSize() const {
	auto width = static_cast<int>(image_.empty() ? 0 : image_[0].size());
	auto height = static_cast<int>(image_.size());
	return {width, height};
}
