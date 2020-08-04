#pragma once

#include "Game.h"
#include "Pawn.h"

class Xapawn :
	public Game
{
public:
	Xapawn(int nbRows=0, int nbColumns=0, AbstractPlayer whitePlayer=AbstractPlayer(), AbstractPlayer blackPlayer=AbstractPlayer());
	~Xapawn();

protected:
	virtual bool gameFinished(Piece::Team* winner) override;
};