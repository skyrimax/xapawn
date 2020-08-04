#include "Pawn.h"

#include "Board.h"

Pawn::Pawn(Team team, Board * board, size_t row, size_t column)
	: Piece(team, board, row, column)
{
}

Pawn::Pawn(Team team, Board * board, const Coordinate & pos)
	: Piece(team, board, pos)
{
}

Piece::Type Pawn::type() const
{
	return Type();
}

std::vector<Coordinate*>& Pawn::possibleMoves()
{
	std::vector<Coordinate*>*moves = new std::vector<Coordinate*>;

	size_t row = m_coordinate.row();
	size_t column = m_coordinate.column();
	const Grid<int> boardState = m_board->state();
	const Grid<int> previousBoardState = m_board->previousState();

	if (m_team == Piece::Team::White) {
		//Square in front of the pawn is free
		if (boardState(row + 1, column) == 0) {
			moves->push_back(new Coordinate(row+1, column));
			if (!m_hasMoved) {
				if (boardState(row + 2, column) == 0) {
					moves->push_back(new Coordinate(row + 2, column));
				}
			}
		}

		//An ennemy piece on left diagonal can be eaten
		if (boardState(row + 1, column - 1) / 10 == (int)Piece::Team::Black) {
			moves->push_back(new Coordinate(row + 1, column-1));
		}

		//An ennemy piece on right diagonal can be eaten
		if (boardState(row + 1, column + 1) / 10 == (int)Piece::Team::Black) {
			moves->push_back(new Coordinate(row + 1, column + 1));
		}

		//Tests for En Passant
		//Is there a piece on the left of the pawn
		if (boardState(row, column - 1) != 0) {
			//Is the piece an enemy pawn
			if (boardState(row, column - 1) == (int)Piece::Team::Black * 10 + (int)Piece::Type::Pawn) {
				//Did that pawn just moved to squares forward
				if (boardState(row + 2, column - 1) == 0 and
					previousBoardState(row + 2, column - 1) == (int)Piece::Team::Black * 10 + (int)Piece::Type::Pawn) {
					moves->push_back(new Coordinate(row + 1, column - 1));
				}
			}
		}
		//Is there a piece on the right of the pawn
		if (boardState(row, column + 1) != 0) {
			//Is the piece an enemy pawn
			if (boardState(row, column + 1) == (int)Piece::Team::Black * 10 + (int)Piece::Type::Pawn) {
				//Did that pawn just moved to squares forward
				if (boardState(row + 2, column + 1) == 0 and
					previousBoardState(row + 2, column + 1) == (int)Piece::Team::Black * 10 + (int)Piece::Type::Pawn) {
					moves->push_back(new Coordinate(row + 1, column + 1));
				}
			}
		}
	}
	else if (m_team == Piece::Team::Black) {
		//Square in front of the pawn is free
		if (boardState(row - 1, column) == 0) {
			moves->push_back(new Coordinate(row - 1, column));
			if (!m_hasMoved) {
				if (boardState(row - 2, column) == 0) {
					moves->push_back(new Coordinate(row - 2, column));
				}
			}
		}

		//An ennemy piece on right diagonal can be eaten
		if (boardState(row - 1, column - 1) / 10 == (int)Piece::Team::White) {
			moves->push_back(new Coordinate(row - 1, column - 1));
		}

		//An ennemy piece on left diagonal can be eaten
		if (boardState(row - 1, column + 1) / 10 == (int)Piece::Team::White) {
			moves->push_back(new Coordinate(row - 1, column + 1));
		}

		//Tests for En Passant
		//Is there a piece on the right of the pawn
		if (boardState(row, column - 1) != 0) {
			//Is the piece an enemy pawn
			if (boardState(row, column - 1) == (int)Piece::Team::White * 10 + (int)Piece::Type::Pawn) {
				//Did that pawn just moved to squares forward
				if (boardState(row - 2, column - 1) == 0 and
					previousBoardState(row - 2, column - 1) == (int)Piece::Team::White * 10 + (int)Piece::Type::Pawn) {
					moves->push_back(new Coordinate(row - 1, column - 1));
				}
			}
		}
		//Is there a piece on the left of the pawn
		if (boardState(row, column + 1) != 0) {
			//Is the piece an enemy pawn
			if (boardState(row, column + 1) == (int)Piece::Team::White * 10 + (int)Piece::Type::Pawn) {
				//Did that pawn just moved to squares forward
				if (boardState(row - 2, column + 1) == 0 and
					previousBoardState(row - 2, column + 1) == (int)Piece::Team::White * 10 + (int)Piece::Type::Pawn) {
					moves->push_back(new Coordinate(row - 1, column + 1));
				}
			}
		}
	}

	return *moves;
}
