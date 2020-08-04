#pragma once

#include "Grid.h"
#include "Square.h"
#include "Piece.h"

class Board
{
public:
	Board(size_t nbRows = 0, size_t nbColomns=0);
	~Board()=default;

	// Accesseurs
	const Grid<int> previousState() const { return m_previousState; }
	size_t nbRows() const { return m_nbRows; }
	size_t nbColumns() const { return m_nbColumns; }

	// Méthodes
	Grid<int> state() const;
	std::vector<Coordinate*> possibleMoves(const Coordinate& piece);
	void addPiece(Piece* piece, const Coordinate& pos);
	void movePiece(Coordinate start, Coordinate end);
	void removePiece(Coordinate piece);
	void updatePrviousState() { m_previousState = state(); }

	Square& operator()(size_t row, size_t column);
	const Square& operator()(size_t row, size_t column) const;
	Square& operator()(const Coordinate& pos);
	const Square& operator()(const Coordinate& pos) const;
	Square& at(size_t row, size_t col);
	const Square& at(size_t row, size_t col) const;
	Square& at(const Coordinate& pos);
	const Square& at(const Coordinate& pos) const;

private:
	Grid<Square> m_board;
	Grid<int> m_previousState;

	size_t m_nbRows;
	size_t m_nbColumns;
};