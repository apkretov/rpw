#pragma once

#include "common.h"

class ITexture { // Объект текстуры должен быть удалён в тот момент, когда нет больше фигур, которые имеют данную текстуру. Это может произойти при удалении фигуры, или при назначении фигуре другой текстуры.
public:
	virtual ~ITexture() = default;
	virtual Size GetSize() const = 0;
	virtual const Image &GetImage() const = 0;
};
