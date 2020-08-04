#pragma once

#include "Grid.h"
#include "AbstractPlayer.h"
#include "Square.h"

class Game
{
public:
	Game();
	Game(int nbRows, int nbColumns, const AbstractPlayer& whitePlayer, const AbstractPlayer& blackPlayer);
	Game(int nbRows, int nbColumns, AbstractPlayer&& whitePlayer, AbstractPlayer&& blackPlayer);
	Game(const Game& game);
	Game(Game&& game);

	virtual ~Game();

	// Accesseurs
	const Grid<int> previousState() const { return m_previousState; }
	size_t nbRows() const { return m_board.nbRows(); }
	size_t nbColumns() const { return m_board.nbCols(); }

	Piece::Team playGame();

	// Méthodes
	Grid<int> state() const;
	std::vector<Coordinate*> possibleMoves(const Coordinate& piece);
	void addPiece(Piece* piece, const Coordinate& pos);
	void movePiece(Coordinate start, Coordinate end);
	void removePiece(Coordinate piece);
	void updatePrviousState() { m_previousState = state(); }

protected:
	struct Player {
		Player() :m_player(nullptr) {}
		Player(AbstractPlayer* player) :m_player(player) {}
		Player(const Player& player);
		Player(Player && player);
		~Player();

		AbstractPlayer* m_player;
		std::vector<Piece*> m_graveyard;
	};

	virtual bool gameFinished(Piece::Team* winner) = 0;

	void playTurn();

	void changePlayer();

	Grid<Square> m_board;
	Grid<int> m_previousState;
	int m_currentPlayer;
	Player m_players[2];
};

