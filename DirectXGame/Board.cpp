#include "Board.h"
#include <cstdlib>
#include <ctime>

#include <array>
#include <algorithm>

Board::Board() {
	tiles.resize(SIZE * SIZE);
	for (int i = 0; i < SIZE * SIZE - 1; ++i) {
		tiles[i] = i + 1;
	}
	tiles[SIZE * SIZE - 1] = EMPTY_TILE;
	emptyIndex = SIZE * SIZE - 1;
	Shuffle();
}

void Board::Shuffle() {
	
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(tiles.begin(), tiles.end(), g);
	emptyIndex =(int) std::distance(tiles.begin(), std::find(tiles.begin(), tiles.end(), EMPTY_TILE));

}

bool Board::MoveTile(int index) {
	
	row = index / SIZE;
	col = index % SIZE;
	emptyRow = emptyIndex / SIZE;
	emptyCol = emptyIndex % SIZE;

	if ((std::abs(row - emptyRow) + std::abs(col - emptyIndex)) == 1) {
		std::swap(tiles[index], tiles[emptyIndex]);
		emptyIndex = index;
		return true;
	}

	return false;

}

void Board::ShowSliderPuzzle() {
	ImGuiX(); 
}

void Board::ImGuiX() { 

	 ImGui::Begin("Slide Puzzle");

	for (int y = 0; y < SIZE; y++) {
		 for (int x = 0; x < SIZE; x++) {
			int index = y * SIZE + x;
			if (tiles[index] != EMPTY_TILE) {
				if (ImGui::Button(std::to_string(tiles[index]).c_str(), ImVec2(50, 50))) {
					MoveTile(index);
				}
			} else {
				ImGui::Button(" ", ImVec2(50, 50)); // 空白のマス
			}

			// 右端以外は横に並べる
			if (x < SIZE - 1)
				ImGui::SameLine();
		 }

	}

	if (ImGui::Button("Shuffle")) {
		Shuffle();
	}

	ImGui::End();

}
