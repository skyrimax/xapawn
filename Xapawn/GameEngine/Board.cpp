#include "Board.h"

#include <exception>
#include <vector>

Board::Board(size_t nbRows, size_t nbColumns)
	: m_board(nbRows, nbColumns, Square()), m_nbRows(nbRows), m_nbColumns(nbColumns)
{
}

Grid<int> Board::state() const
{
	size_t i(0);

	const std::vector<Square>& board = m_board.data();
	std::vector<int> state(m_nbRows*m_nbColumns);

	//for (i = 0; i < m_nbRows; i++) {
	//	for (j = 0; j < m_nbColumns; j++) {
	//		if (m_board(i, j).isEmpty()) {
	//			state(i, j) = 0;
	//		}
	//		else {
	//			state(i, j) = (int)m_board(i, j).piece()->type() + (int)m_board(i, j).piece()->equipe() * 10;
	//		}
	//	}
	//}

	for (const auto& sq : board) {
		state[i] = sq.isEmpty() ? 0 : (int)sq.piece()->type() + (int)sq.piece()->team() * 10;

		++i;
	}

	return Grid<int>(m_nbRows, m_nbColumns, std::move(state));
}

std::vector<Coordinate*> Board::possibleMoves(const Coordinate& piece)
{
	size_t row = piece.row();
	size_t column = piece.column();

	if (!m_board(row, column).isEmpty())
	{
		return m_board(row, column).piece()->possibleMoves();
	}

	return std::vector<Coordinate*>();
}

void Board::addPiece(Piece * piece, const Coordinate & pos)
{
	m_board(pos).setPiece(piece);
}

void Board::movePiece(Coordinate start, Coordinate end)
{
	if (!m_board(end).isEmpty()) {
		removePiece(end);
	}

	if (start != end) {
		Piece* piece = m_board(start).piece();

		// Place piece at new position
		addPiece(piece, end);
		// Tell the piece that it moved and it's new position
		piece->movePiece(end);

		// Remove piece from previous position
		removePiece(start);
	}
}

void Board::removePiece(Coordinate piece)
{
	m_board(piece).setPiece(nullptr);
}

Square & Board::operator()(size_t row, size_t column)
{
	return m_board(row, column);
}

const Square & Board::operator()(size_t row, size_t column) const
{
	return m_board(row, column);
}
Square & Board::operator()(const Coordinate & pos)
{
	return m_board(pos);
}

const Square & Board::operator()(const Coordinate & pos) const
{
	return m_board(pos);
}

Square & Board::at(size_t row, size_t col)
{
	try
	{
		return at(row, col);
	}
	catch (const std::exception& except)
	{
		throw except;
	}
}

const Square & Board::at(size_t row, size_t col) const
{
	try
	{
		return at(row, col);
	}
	catch (const std::exception& except)
	{
		throw except;
	}
}

Square & Board::at(const Coordinate & pos)
{
	try
	{
		return at(pos);
	}
	catch (const std::exception& except)
	{
		throw except;
	}
}

const Square & Board::at(const Coordinate & pos) const
{
	try
	{
		return at(pos);
	}
	catch (const std::exception& except)
	{
		throw except;
	}
}