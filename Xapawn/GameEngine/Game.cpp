#include "Game.h"

Game::Game()
{
}

Game::Game(int nbRows, int nbColumns, const AbstractPlayer& whitePlayer, const AbstractPlayer& blackPlayer)
	: m_board(nbRows, nbColumns), m_currentPlayer(0), m_players{whitePlayer.clone(), blackPlayer.clone()}
{
}

Game::Game(int nbRows, int nbColumns, AbstractPlayer && whitePlayer, AbstractPlayer && blackPlayer)
{
}

Game::Game(const Game & game)
{
}

Game::Game(Game && game)
{
}

Game::~Game()
{
	size_t i, j;

	for (i = 0; i < m_board.nbRows(); i++) {
		for (j = 0; j < m_board.nbRows(); j++) {
			delete m_board(i, j).piece();
		}
	}

	for (auto& player : m_players) {
		for (auto& a : player.m_graveyard) {
			delete a;
		}
	}
}

Piece::Team Game::playGame()
{
	Piece::Team winningPlayer;

	do
	{
		playTurn();

		changePlayer();
	} while (!gameFinished(&winningPlayer));

	return winningPlayer;
}

void Game::playTurn()
{
	Coordinate chosenPiece, chosenEndPosition;

	m_players[m_currentPlayer].m_player->playTurn(m_board, chosenPiece, chosenEndPosition);

	m_board.updatePrviousState();

	if (!m_board(chosenEndPosition).isEmpty()) {
		m_players[(m_currentPlayer + 1) % 2].m_player->removePiece(m_board(chosenEndPosition).piece());
		m_players[(m_currentPlayer + 1) % 2].m_graveyard.push_back(m_board(chosenEndPosition).piece());
	}

	m_board.movePiece(chosenPiece, chosenEndPosition);
}

void Game::changePlayer()
{
	//if (m_currentPlayer == 0) {
	//	m_currentPlayer = 1;
	//}
	//else if (m_currentPlayer == 1) {
	//	m_currentPlayer = 0;
	//}

	m_currentPlayer = (m_currentPlayer + 1) % 2;
}

Game::Player::Player(const Player & player)
	: m_player(player.m_player)
{
	m_graveyard.reserve(player.m_graveyard.size());

	for (auto const& a : player.m_graveyard) {
		m_graveyard.push_back(a->clone());
	}
}

Game::Player::Player(Player && player)
	: m_player(player.m_player)
{
	m_graveyard.reserve(player.m_graveyard.size());

	for (auto& a : player.m_graveyard) {
		m_graveyard.push_back(a->move_clone());
	}
}

Game::Player::~Player()
{
	delete m_player;

	for (auto const& a : m_graveyard) {
		delete a;
	}
}