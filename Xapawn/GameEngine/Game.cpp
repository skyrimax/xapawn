#include "Game.h"

#include <exception>

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

Grid<int> Game::state() const
{
	//size_t i(0);

	const std::vector<Square>& board = m_board.data();
	//std::vector<int> state(m_board.nbRows()*m_board.nbCols());
	std::vector<int> state;
	state.reserve(m_board.nbRows()*m_board.nbCols());

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
		//state[i] = sq.isEmpty() ? 0 : (int)sq.piece()->type() + (int)sq.piece()->team() * 10;
		state.push_back(sq.isEmpty() ? 0 : (int)sq.piece()->type() + (int)sq.piece()->team() * 10);

		//++i;
	}

	return Grid<int>(m_board.nbRows(), m_board.nbCols(), std::move(state));
}

std::vector<Coordinate*> Game::possibleMoves(const Coordinate& piece)
{
	if (!m_board(piece).isEmpty())
	{
		return m_board(piece).piece()->possibleMoves();
	}

	return std::vector<Coordinate*>();
}

void Game::addPiece(Piece * piece, const Coordinate & pos)
{
	if (std::find(m_board.data().begin(), m_board.data().end(), piece) == m_board.data().end()) {
		m_board(pos).setPiece(piece);

		m_players[(int)piece->team()].m_player->addPiece(piece);
	}
	else {
		throw std::logic_error("Game : addPiece : Piece already exist in this board");
	}
}

void Game::movePiece(Coordinate start, Coordinate end)
{
	Square& sqStart = m_board(start);
	Square& sqEnd = m_board(end);

	if (!sqEnd.isEmpty()) {
		removePiece(end);
	}

	if (start != end) {
		Piece* piece = sqStart.piece();

		// Remove piece from previous position
		sqStart.setPiece(nullptr);

		// Place piece at new position
		sqEnd.setPiece(piece);
		// Tell the piece that it moved and it's new position
		piece->movePiece(end);
	}
}

void Game::removePiece(Coordinate piece)
{
	Square& sq = m_board(piece);
	Piece* pc = sq.piece();

	pc->removePiece();
	sq.setPiece(nullptr);
	m_players[(int)pc->team()].m_graveyard.push_back(pc);
}

void Game::playTurn()
{
	Coordinate chosenPiece, chosenEndPosition;

	m_players[m_currentPlayer].m_player->playTurn(state(), m_previousState, chosenPiece, chosenEndPosition);

	if (chosenPiece != chosenEndPosition) {
		updatePrviousState();

		movePiece(chosenPiece, chosenEndPosition);
	}
	else
	{
		playTurn();
	}
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