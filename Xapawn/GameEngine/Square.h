#pragma once

#include "Piece.h"

//class Piece;

class Square
{
public:
	Square(Piece* piece=nullptr);
	~Square();

	//Accesseur
	bool isEmpty() const;
	Piece* piece();
	const Piece * const piece() const;

	//Mutateurs
	void setPiece(Piece* piece);

private:
	bool m_isEmpty;
	Piece* m_piece;
};

