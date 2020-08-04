#pragma once

#include<vector>
#include<initializer_list>

#include"Piece.h"

class AbstractPlayer
{
public:
	AbstractPlayer(Piece::Team team = Piece::Team::White);
	AbstractPlayer(Piece::Team team, const std::vector<Piece*>& pieces);
	AbstractPlayer(Piece::Team team, std::vector<Piece*>&& pieces);
	AbstractPlayer(Piece::Team team, std::initializer_list<Piece*>& pieces);
	AbstractPlayer(const AbstractPlayer& player);
	AbstractPlayer(AbstractPlayer&& player);
	~AbstractPlayer();

	// Cloning method returning pointer to clone
	virtual AbstractPlayer* clone() const = 0;
	virtual AbstractPlayer* move_clone() = 0;

	// Accesseur and mutators
	Piece::Team team();
	void setTeam(Piece::Team team);
	const std::vector<Piece*>& pieces() const;

	// Methode to add chess piece to the player's team
	void addPiece(Piece* piece);
	void removePiece(Piece* piece);

	// Méthod to play a turn using function pointer
	virtual void playTurn(const Board& board, Coordinate& start, Coordinate& end) = 0;

private:
	Piece::Team m_team;
	std::vector<Piece*> m_activePieces;
};