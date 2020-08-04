#pragma once

#include "Piece.h"

class Pawn: public Piece
{
public:
	Pawn(Team team = Team::White, Board* board = nullptr, size_t row = 0, size_t column = 0);
	Pawn(Team team=Team::White, Board* board=nullptr, const Coordinate& pos=Coordinate(0,0));
	~Pawn()=default;

	Type type() const;

	std::vector<Coordinate*>& possibleMoves();
};

