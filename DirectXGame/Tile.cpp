#include "Tile.h"

Tile::Tile(int num) : number(num) {}

bool Tile::isEmpty() const {
	return number == 0; // 空白タイルか？
}
