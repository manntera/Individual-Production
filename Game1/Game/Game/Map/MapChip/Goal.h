#pragma once
#include "MapChip.h"

class Goal : public MapChip
{
public:
	Goal();

	~Goal();

	void Update()override;

private:
};