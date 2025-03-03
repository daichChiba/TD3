#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class PuzzleCollection;

class PuzzleFactory {
public:
	std::unique_ptr<PuzzleCollection> CreatePuzzle15();
};
