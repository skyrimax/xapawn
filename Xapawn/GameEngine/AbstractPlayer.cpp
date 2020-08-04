#include "AbstractPlayer.h"

#include <algorithm>

#include "Board.h"

AbstractPlayer::AbstractPlayer(Piece::Team team)
	: m_team(team)
{
}

AbstractPlayer::AbstractPlayer(Piece::Team team, const std::vector<Piece*>& pieces)
	: m_team(team), m_activePieces(pieces)
{
}

AbstractPlayer::AbstractPlayer(Piece::Team team, std::vector<Piece*>&& pieces)
	: m_team(team), m_activePieces(std::move(pieces))
{
}

AbstractPlayer::AbstractPlayer(Piece::Team team, std::initializer_list<Piece*>& pieces)
	: m_team(team), m_activePieces(pieces)
{
}

AbstractPlayer::AbstractPlayer(const AbstractPlayer & player)
	: m_team(player.m_team), m_activePieces(player.m_activePieces)
{
}

AbstractPlayer::AbstractPlayer(AbstractPlayer && player)
	: m_team(player.m_team), m_activePieces(std::move(player.m_activePieces))
{
}

AbstractPlayer::~AbstractPlayer()
{
}

Piece::Team AbstractPlayer::team()
{
	return m_team;
}

void AbstractPlayer::setTeam(Piece::Team team)
{
	m_team = team;
}

const std::vector<Piece*>& AbstractPlayer::pieces() const
{
	return m_activePieces;
}

void AbstractPlayer::addPiece(Piece * piece)
{
	m_activePieces.push_back(piece);
}

void AbstractPlayer::removePiece(Piece * piece)
{
	m_activePieces.erase(std::remove(m_activePieces.begin(), m_activePieces.end(), piece), m_activePieces.end());
}