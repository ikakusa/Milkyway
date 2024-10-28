#pragma once
namespace mce {
	struct Blob {
		struct Deleter {

		};

		BUILD_ACCESS(Deleter, blob, 0x0);
		BUILD_ACCESS(unsigned __int64, size, 0x10);
	};
	enum class ImageUsage : __int8 {

	};
	struct Image {
		BUILD_ACCESS(__int64, imageFormat, 0x0); //data!!!
		BUILD_ACCESS(int32_t, width, 0x4);
		BUILD_ACCESS(int32_t, height, 0x8);
		BUILD_ACCESS(ImageUsage, usage, 0x10);
	};
}