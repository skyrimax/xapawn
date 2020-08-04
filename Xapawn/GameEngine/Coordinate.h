#pragma once
class Coordinate
{
public:
	Coordinate(size_t row=0, size_t column=0);
	~Coordinate()=default;

	// Accesseurs
	size_t row() const { return m_row; }
	size_t column() const { return m_column; }

	// Mutateurs
	void setRow(size_t row) { m_row = row; }
	void setColumn(size_t column) { m_column = column; }

	// Boolean comparation operators
	bool operator==(const Coordinate& other);
	bool operator!=(const Coordinate& other);

private:
	size_t m_row;
	size_t m_column;
};

