#pragma once

#include "Board.h"
#include "AbstractPlayer.h"

class Game
{
public:
	Game();
	Game(int nbRows, int nbColumns, const AbstractPlayer& whitePlayer, const AbstractPlayer& blackPlayer);
	Game(int nbRows, int nbColumns, AbstractPlayer&& whitePlayer, AbstractPlayer&& blackPlayer);
	Game(const Game& game);
	Game(Game&& game);

	virtual ~Game();

	Piece::Team playGame();

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

	Board m_board;
	int m_currentPlayer;
	Player m_players[2];
};

