#include <KamataEngine.h>
using namespace KamataEngine;

//#define BOARD_H
//
#include "Tile.h"
//#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class Board {
	 public:
		Board();
	//	void display() const;
		bool MoveTile(int index);
	//	bool isSolved() const;
	    void ShowSliderPuzzle();
	    void ImGuiX();
	/*
		void Initialize();
		void Update();
		void Draw();*/
	
	 private:
		static const int SIZE = 4;
		std::vector<int> tiles;
	    static const int EMPTY_TILE = 0;
	   // std::array<int, SIZE * SIZE> tiles = {1, 2, 3, 4, 5, 6, 7, 8, EMPTY_TILE};
	    int emptyIndex; // 空白の位置

		void Shuffle();
	//	std::pair<int, int> findEmptyTile() const;

		int row;
	    int emptyRow;
	    int col;
	    int emptyCol;

//public:
//
//	void Initialize(Model* model, const Vector3 position);
//	void Update(Camera* camera);	
//	void ImGui();
//
//public:
//	static const int SIZE = 4;
//	std::vector<std::vector<Tile>> tiles;
//
//	Board() {
//		int num = 1;
//		tiles.resize(SIZE, std::vector<Tile>(SIZE));
//		for (int y = 0; y < SIZE; y++) {
//			for (int x = 0; x < SIZE; x++) {
//				tiles[x][y] = Tile(num++);
//			}
//		}
//		tiles[SIZE - 1][SIZE - 1] = Tile(0); // 空白タイル
//		shuffle();
//	}
//
//	void shuffle() {
//		std::vector<int> flatTiles;
//		for (int y = 0; y < SIZE; y++) {
//			for (int x = 0; x < SIZE; x++) {
//				flatTiles.push_back(tiles[x][y].number);
//			}
//		}
//	}
//
//	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//	//std::shuffle(flatTiles.begin(), flatTiles.end(), std::default_random_engine(seed));
//
//	int index = 0;
//	
//
//    std::pair<int, int>
//        findEmptyTile() const {
//    	for (int y = 0; y < SIZE; y++) {
//    		for (int x = 0; x < SIZE; x++) {
//    			if (tiles[x][y].isEmpty()) {
//    				return {x, y};
//    			}
//    		}
//    	}
//    	return {-1, -1};
//    }
//
//    bool moveTile(int dx, int dy) {
//    	auto [emptyX, emptyY] = findEmptyTile();
//    	int targetX = emptyX + dx;
//    	int targetY = emptyY + dy;
//    
//    	if (targetX >= 0 && targetX < SIZE && targetY >= 0 && targetY < SIZE) {
//    		std::swap(tiles[emptyX][emptyY], tiles[targetX][targetY]);
//    		return true;
//    	}
//    	return false;
//    }
//
//    bool isSolved() const {
//    	int num = 1;
//    	for (int y = 0; y < SIZE; y++) {
//    		for (int x = 0; x < SIZE; x++) {
//    			if (y == SIZE - 1 && x == SIZE - 1) {
//    				return true;
//    			}
//    			if (tiles[x][y].number != num++) {
//    				return false;
//    			}
//    		}
//    	}
//    	return true;
//    }
//
//private:
//
//	Model* model_ = nullptr;
//
//	Model* cube_ = nullptr;
//
//	// ワールドトランスフォーム
//	WorldTransform worldTransform_;

};