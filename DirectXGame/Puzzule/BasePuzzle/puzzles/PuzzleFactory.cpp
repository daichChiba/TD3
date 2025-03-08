#include "PuzzleFactory.h"
#include "../BasePuzzle.h"
#include "Puzzle15/Puzzle15.h"
#include "CircuitPuzzle/CircuitPuzzle.h"

std::unique_ptr<BasePuzzle> PuzzleFactory::CreatePuzzle15() {
	std::unique_ptr<BasePuzzle> puzzle = std::make_unique<Puzzle15>();
	return puzzle;
}

std::unique_ptr<BasePuzzle> PuzzleFactory::CreateCircuitPuzzle() {
	std::unique_ptr<BasePuzzle> puzzle = std::make_unique<CircuitPuzzle>();
	return puzzle;
}
