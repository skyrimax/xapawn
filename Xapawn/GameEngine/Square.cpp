#include "Square.h"

#include "Piece.h"

Square::Square(Piece* piece)
	: m_piece(piece), m_isEmpty(!piece)
{
}

Square::~Square()
{
	if (m_piece!=nullptr){
		delete m_piece;
	}
}

bool Square::isEmpty() const
{
	return m_isEmpty;
}

Piece * Square::piece()
{
	return m_piece;
}

const Piece * const Square::piece() const
{
	return m_piece;
}

void Square::setPiece(Piece * piece)
{
	m_piece = piece;

	if (piece = nullptr) {
		m_isEmpty = true;
	}
	else{
		m_isEmpty = false;
	}
}
