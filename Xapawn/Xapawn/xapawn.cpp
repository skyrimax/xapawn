#include "Xapawn.h"

Xapawn::Xapawn(int nbRows, int nbColumns, AbstractPlayer whitePlayer, AbstractPlayer blackPlayer)
	: Game(nbRows, nbColumns, whitePlayer, blackPlayer)
{
	size_t i;

	Piece* nextPiece;

	for (i = 0; i < nbColumns; i++) {
		nextPiece = new Pawn(Piece::Team::White, &m_board, 0, i);
		m_board(0, i).setPiece(nextPiece);
		whitePlayer.addPiece(nextPiece);

		nextPiece = new Pawn(Piece::Team::Black, &m_board, nbColumns - 1, i);
		m_board(nbRows - 1, i).setPiece(nextPiece);
		blackPlayer.addPiece(nextPiece);
	}
}

Xapawn::~Xapawn()
{
}

bool Xapawn::gameFinished(Piece::Team * winner)
{
	bool gameEnded = false;
	int i;

	//Test if the player that just played has reached the other side
	if (m_currentPlayer = 1) { //White player just played
		for (i = 0; i < m_board.nbColumns(); i++) {
			if (!m_board(m_board.nbRows() - 1, i).isEmpty()) {
				if (m_board(m_board.nbRows() - 1, i).piece()->team() == Piece::Team::White) {
					gameEnded = true;
				}
			}
		}
		
		// If the white player has brought a piece to the other side, they win
		if (gameEnded) {
			*winner = Piece::Team::White;
		}
	}
	else if (m_currentPlayer = 0) { //Black player just played
		for (i = 0; i < m_board.nbColumns(); i++) {
			if (!m_board(0, i).isEmpty()) {
				if (m_board(0, i).piece()->team() == Piece::Team::Black) {
					gameEnded = true;
				}
			}
		}

		// If the black player has brought a piece to the other side, they win
		if (gameEnded) {
			*winner = Piece::Team::Black;
		}
	}

	//Test if the next player can play there next turn
	if (!gameEnded) {
		gameEnded = true;

		for (auto const& piece : players[m_currentPlayer].pieces()) {
			if (!piece->possibleMoves().empty()) {
				gameEnded = false;
			}
		}

		if (gameEnded) {
			*winner = m_currentPlayer == 0 ? Piece::Team::Black : Piece::Team::White;
		}
	}

	return gameEnded;
}
