#pragma once
#include "MonochromeFilter.h"

class PostEffect
{
public:
	void Init();

	void Draw();
private:
	MonochromeFilter m_monochrome;
};