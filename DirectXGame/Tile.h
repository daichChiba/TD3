#pragma once
#define TILE_H
#include <KamataEngine.h>
using namespace KamataEngine;

class Tile {
public:
	int number; // タイルの番号（0 は空白）

	Tile(int num = 0);
	bool isEmpty() const;
};
