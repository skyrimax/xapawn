#include "Coordinate.h"

Coordinate::Coordinate(size_t row, size_t column)
{
	m_row = row;
	m_column = column;
}

bool Coordinate::operator==(const Coordinate & other)
{
	return m_row == other.m_row && m_column == other.m_column;
}

bool Coordinate::operator!=(const Coordinate & other)
{
	return !((*this) == other);
}