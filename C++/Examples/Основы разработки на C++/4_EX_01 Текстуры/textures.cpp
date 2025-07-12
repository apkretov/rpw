#include <memory>
#include "Texture.h"
#include "ITexture.h"
#include "common.h"
using namespace std;

unique_ptr<ITexture> MakeTextureSolid(Size size, char pixel) {
	Image image(size.height, string(size.width, pixel));
	return make_unique<Texture>(std::move(image));
}

unique_ptr<ITexture> MakeTextureCheckers(Size size, char pixel1, char pixel2) {
	Image image(size.height, string(size.width, pixel1));

	for (int i = 0; i < size.height; ++i)
		for (int j = 0; j < size.width; ++j)
			if ((i + j) % 2 != 0)
				image[i][j] = pixel2;

	return make_unique<Texture>(std::move(image));
}

unique_ptr<ITexture> MakeTextureCow() {
	Image image = {R"(^__^            )",
				   R"((oo)\_______    )",
				   R"((__)\       )\/\)",
				   R"(    ||----w |   )",
				   R"(    ||     ||   )"};
	return make_unique<Texture>(std::move(image));
}