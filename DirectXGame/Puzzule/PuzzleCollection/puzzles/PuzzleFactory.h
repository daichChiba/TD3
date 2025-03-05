#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class PuzzleCollection;

class PuzzleFactory {
public:
	/// <summary>
	/// パズル15を作成
	/// </summary>
	/// <returns></returns>
	std::unique_ptr<PuzzleCollection> CreatePuzzle15();
};
