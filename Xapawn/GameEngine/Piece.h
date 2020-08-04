#pragma once

#include <vector>

#include "Coordinate.h"
#include "Grid.h"

class Board;

// Purely virtual class containing the behaviours common to all chest pieces 
class Piece
{
public:
	enum class Team : int{
		White=0,
		Black=1
	};

	enum class Type : int{
		King=0,
		Queen=1,
		Rook=2,
		Bishop=3,
		Knight=4,
		Pawn=5
	};

	Piece(Team team, Board* board, size_t row, size_t column);
	Piece(Team team, Board* board, const Coordinate& pos);
	virtual ~Piece();

	Team team() const;
	virtual Type type() const = 0;
	Coordinate& pos();
	const Coordinate& pos() const;

	void movePiece(Coordinate newPos);
	virtual void removePiece() = 0;

	// Virtual fonction returning a list of possible moving positions
	virtual std::vector<Coordinate*>& possibleMoves()=0;

protected:
	Team m_team;
	Coordinate m_coordinate;
	bool m_hasMoved;

	// Pointer toward board the piece is a part of
	// Will be used to retrieve state of the board
	Board* m_board;
};

