#include "Piece.h"

Piece::Piece(Piece::Team team, Board* board, size_t row, size_t column)
	: m_team(team), m_board(board), m_coordinate(row, column), m_hasMoved(false)
{
}

Piece::Piece(Team team, Board * board, const Coordinate & pos)
	: m_team(team), m_board(board), m_coordinate(pos), m_hasMoved(false)
{
}

Piece::~Piece()
{
}

Piece::Team Piece::team() const
{
	return m_team;
}

Coordinate & Piece::pos()
{
	return m_coordinate;
}

const Coordinate & Piece::pos() const
{
	return m_coordinate;
}

void Piece::movePiece(Coordinate newPos)
{
	m_coordinate = newPos;

	m_hasMoved = true;
}
