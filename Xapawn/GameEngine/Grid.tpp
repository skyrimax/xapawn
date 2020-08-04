#include "Grid.h"

#pragma once

#include <exception>
#include <utility>

template<class T>
Grid<T>::Grid(size_type nbRows, size_type nbCols)
	: m_data(nbRows*nbCols), m_nbRows(nbRows), m_nbCols(nbCols)
{
}

template<class T>
Grid<T>::Grid(size_type nbRows, size_type nbCols, const T & val)
	: m_data(nbRows*nbCols, val), m_nbRows(nbRows), m_nbCols(nbCols)
{
}

template<class T>
Grid<T>::Grid(size_type nbRows, size_type nbCols, const std::vector<T>& data)
	: m_data(nbRows*nbCols == data.size() ? data :
		throw std::invalid_argument("Invalid argument: nbRows*nbCols MUST equal the size of the data vector")),
	m_nbRows(nbRows), m_nbCols(nbCols)
{
}

template<class T>
Grid<T>::Grid(size_type nbRows, size_type nbCols, std::vector<T>&& data)
	: m_data(nbRows*nbCols == data.size() ? std::move(data) :
		throw std::invalid_argument("Invalid argument: nbRows*nbCols MUST equal the size of the data vector")),
	m_nbRows(nbRows), m_nbCols(nbCols)
{
}

template<class T>
Grid<T>::Grid(const Grid<T>& grid)
	: m_data(grid.m_data), m_nbRows(grid.m_nbRows), m_nbCols(grid.m_nbCols)
{
}

template<class T>
Grid<T>::Grid(Grid<T>&& grid)
	: m_data(std::move(grid.m_data)), m_nbRows(grid.m_nbRows), m_nbCols(grid.m_nbCols)
{
}

template<class T>
Grid<T>::~Grid()
{
}

template<class T>
Grid<T>& Grid<T>::operator=(const Grid<T>& grid)
{
	m_nbRows = grid.m_nbRows;
	m_nbCols = grid.m_nbCols;
	m_data = grid.m_data;

	return *this;
}

template<class T>
Grid<T>& Grid<T>::operator=(Grid<T>&& grid)
{
	m_nbRows = grid.m_nbRows;
	m_nbCols = grid.m_nbCols;
	m_data = std::move(grid.m_data);

	return *this;
}

template<class T>
typename Grid<T>::size_type Grid<T>::nbRows() const
{
	return m_nbRows;
}

template<class T>
typename Grid<T>::size_type Grid<T>::nbCols() const
{
	return m_nbCols;
}

template<class T>
void Grid<T>::resize(size_type nbRows, size_type nbCols)
{
	std::vector<T>newArray(nbRows*nbCols);

	for (int i = 0; i < m_nbRows && i < nbRows; ++i) {
		for (int j = 0; j < m_nbCols && j < nbCols; ++j) {
			newArray[i*nbCols + j] = this(i, j);
		}
	}

	m_data.swap(newArray);

	m_nbRows = nbRows;
	m_nbCols - nbCols;
}

template<class T>
void Grid<T>::resize(size_type nbRows, size_type nbCols, T & val)
{
	std::vector<T>newArray(nbRows*nbCols, val);

	for (int i = 0; i < m_nbRows && i < nbRows; ++i) {
		for (int j = 0; j < m_nbCols && j < nbCols; ++j) {
			newArray[i*nbCols + j] = this(i, j);
		}
	}

	m_data.swap(newArray);

	m_nbRows = nbRows;
	m_nbCols - nbCols;
}

template<class T>
bool Grid<T>::empty()
{
	return m_data.empty();
}

template<class T>
T & Grid<T>::operator()(size_type row, size_type col)
{
	return m_data[row*m_nbCols + col];
}

template<class T>
const T & Grid<T>::operator()(size_type row, size_type col) const
{
	return m_data[row*m_nbCols + col];
}

template<class T>
T & Grid<T>::operator()(const Coordinate & pos)
{
	return m_data[pos.row()*m_nbCols + pos.column()];
}

template<class T>
const T & Grid<T>::operator()(const Coordinate & pos) const
{
	return m_data[pos.row()*m_nbCols + pos.column()];
}

template<class T>
T & Grid<T>::at(size_type row, size_type col)
{
	if (row < m_nbRows && col < m_nbCols) {
		return m_data[row*m_nbCols + col];
	}
	else {
		throw std::out_of_range("vector::_M_range_check");
	}
}

template<class T>
const T & Grid<T>::at(size_type row, size_type col) const
{
	if (row < m_nbRows && col < m_nbCols) {
		return m_data[row*m_nbCols + col];
	}
	else {
		throw std::out_of_range("vector::_M_range_check");
	}
}

template<class T>
T & Grid<T>::at(const Coordinate & pos)
{
	size_t row(pos.row());
	size_t col(pos.column());

	if (row < m_nbRows && col < m_nbCols) {
		return m_data[row*m_nbCols + col];
	}
	else {
		throw std::out_of_range("vector::_M_range_check");
	}
}

template<class T>
const T & Grid<T>::at(const Coordinate & pos) const
{
	size_t row(pos.row());
	size_t col(pos.column());

	if (row < m_nbRows && col < m_nbCols) {
		return m_data[row*m_nbCols + col];
	}
	else {
		throw std::out_of_range("vector::_M_range_check");
	}
}

//template<class T>
//Grid<T> Grid<T>::rows(size_type row, size_type n)
//{
//	Grid<T>rowsToReturn(n, m_nbCols);
//
//	for (int i = row; i < n && i < m_nbRows; ++i) {
//		for (int j = 0; j < m_nbCols; ++j) {
//			rowsToReturn.m_data[i*m_nbCols + j] = m_data[i*m_nbCols + j];
//		}
//	}
//
//	return rowsToReturn;
//}

//template<class T>
//const Grid<T> Grid<T>::rows(size_type row, size_type n) const
//{
//	Grid<T&>rowsToReturn(n, m_nbCols);
//
//	for (int i = row; i < n; ++i) {
//		for (int j = 0; j < m_nbCols; ++j) {
//			rowsToReturn.m_data[i*m_nbCols + j] = m_data[i*m_nbCols + j];
//		}
//	}
//
//	return rowsToReturn;
//}

//template<class T>
//std::vector<T> Grid<T>::row(size_type row)
//{
//	std::vector<T>rowToReturn(m_nbCols);
//
//	for (int i = 0; i < m_nbCols; ++i) {
//		rowToReturn[i] = m_data[row*m_nbCols + i];
//	}
//
//	return rowToReturn;
//}

//template<class T>
//const std::vector<T> Grid<T>::row(size_type row) const
//{
//	std::vector<T>rowToReturn(m_nbCols);
//
//	for (int i = 0; i < m_nbCols; ++i) {
//		rowToReturn[i] = m_data[row*m_nbCols + i];
//	}
//
//	return rowToReturn;
//}

//template<class T>
//Grid<T> Grid<T>::cols(size_type col, size_type n)
//{
//	Grid<T>colsToReturn(m_nbRows, n);
//
//	for (int i = 0; i < m_nbRows; ++i) {
//		for (int j = 0; j < n; i++) {
//			colsToReturn.m_data[i*m_nbRows + j] = m_data[i*m_nbRows + j];
//		}
//	}
//
//	return colsToReturn;
//}

//template<class T>
//const Grid<T> Grid<T>::cols(size_type col, size_type n) const
//{
//	Grid<T>colsToReturn(m_nbRows, n);
//
//	for (int i = 0; i < m_nbRows; ++i) {
//		for (int j = 0; j < n; i++) {
//			colsToReturn.m_data[i*m_nbRows + j] = m_data[i*m_nbRows + j];
//		}
//	}
//
//	return colsToReturn;
//}

//template<class T>
//std::vector<T> Grid<T>::col(size_type col)
//{
//	std::vector<T> colToReturn(m_nbRows);
//
//	for (int i = 0; i < m_nbRows; ++i) {
//		colToReturn[i] = m_data[i*m_nbCols + col];
//	}
//
//	return colToReturn;
//}

//template<class T>
//const std::vector<T> Grid<T>::col(size_type col) const
//{
//	std::vector<T> colToReturn(m_nbRows);
//
//	for (int i = 0; i < m_nbRows; ++i) {
//		colToReturn[i] = m_data[i*m_nbCols + col];
//	}
//
//	return colToReturn;
//}

//template<class T>
//Grid<T> Grid<T>::firstRowGrid()
//{
//	return rows(0);
//}

//template<class T>
//const Grid<T> Grid<T>::firstRowGrid() const
//{
//	return rows(0);
//}

//template<class T>
//std::vector<T> Grid<T>::firstRowVector()
//{
//	return row(0);
//}

//template<class T>
//const std::vector<T> Grid<T>::firstRowVector() const
//{
//	return row(0);
//}

//template<class T>
//Grid<T> Grid<T>::lastRowGrid()
//{
//	return rows(m_nbRows - 1);
//}

//template<class T>
//const Grid<T> Grid<T>::lastRowGrid() const
//{
//	return rows(m_nbRows - 1);
//}

//template<class T>
//std::vector<T> Grid<T>::lastRowVector()
//{
//	return row(m_nbRows - 1);
//}

//template<class T>
//const std::vector<T> Grid<T>::lastRowVector() const
//{
//	return row(m_nbRows - 1);
//}

//template<class T>
//Grid<T> Grid<T>::firstColGrid()
//{
//	return cols(0);
//}

//template<class T>
//const Grid<T> Grid<T>::firstColGrid() const
//{
//	return cols(0);
//}

//template<class T>
//std::vector<T> Grid<T>::firstColVector()
//{
//	return col(0);
//}

//template<class T>
//const std::vector<T> Grid<T>::firstColVector() const
//{
//	return col(0);
//}

//template<class T>
//Grid<T> Grid<T>::lastColGrid()
//{
//	return cols(m_nbCols-1);
//}

//template<class T>
//const Grid<T> Grid<T>::lastColGrid() const
//{
//	return cols(m_nbCols - 1);
//}

//template<class T>
//std::vector<T> Grid<T>::lastColVector()
//{
//	return col(m_nbCols - 1);
//}

//template<class T>
//const std::vector<T> Grid<T>::lastColVector() const
//{
//	return col(m_nbCols - 1);
//}

template<class T>
std::vector<T> Grid<T>::data()
{
	return m_data;
}

template<class T>
const std::vector<T> Grid<T>::data() const
{
	return m_data;
}

template<class T>
void Grid<T>::assign(size_type nbRows, size_type nbCols, const T & val)
{
	std::vector<T>newArray(nbRows*nbCols, val);

	m_data.swap(newArray);

	m_nbRows = nbRows;
	m_nbCols = nbCols;
}

//template<class T>
//void Grid<T>::insertRows(size_type row, const Grid<T>& elements)
//{
//	int i;
//	int j;
//
//	std::vector<T> newArray((m_nbRows + elements.m_nbRows)*m_nbCols);
//
//	for (i = 0; i < row; ++i) {
//		for (j = 0; j < m_nbCols; ++j) {
//			newArray[i*m_nbCols + j] = m_data[i*m_nbCols + j];
//		}
//	}
//
//	for (i = row; i < row + elements.m_nbRows; ++i) {
//		for (j = 0; j < m_nbCols && j < elements.m_nbCols; ++j) {
//			newArray[i*m_nbCols + j]=elements.m_data[i*m_nbCols + j];
//		}
//
//		for (j=elements.m_nbCols; j < m_nbRows; ++j) {
//			newArray[i*m_nbCols + j] = T();
//		}
//	}
//
//	for (i = row + elements.m_nbRows; i < m_nbRows; ++i) {
//		for (j = 0; j < m_nbCols; ++j) {
//			newArray[i*m_nbCols + j] = m_data[(i-elements.m_nbRows)*m_nbCols + j];
//		}
//	}
//
//	m_data.swap(newArray);
//}

//template<class T>
//void Grid<T>::insertRow(size_type row, const std::vector<T>& elements)
//{
//	int i;
//	int j;
//
//	std::vector<T>newArray((m_nbRows + 1)*m_nbCols);
//
//	for (i = 0; i < row; ++i) {
//		for (j = 0; j < m_nbCols; ++j) {
//			newArray[i*m_nbCols + j] = m_data[i*m_nbCols + j];
//		}
//	}
//
//	for (i = row; i < row + 1; ++i) {
//		for (j = 0; j < m_nbCols && j < elements.size(); ++j) {
//			newArray[i*m_nbCols + j] = elements[j];
//		}
//
//		for (j = elements.size(); j < m_nbRows; ++j) {
//			newArray[i*m_nbCols + j] = T();
//		}
//	}
//
//	for (i = row + elements.m_nbRows; i < m_nbRows; ++i) {
//		for (j = 0; j < m_nbCols; ++j) {
//			newArray[i*m_nbCols + j] = m_data[(i - 1)*m_nbCols + j];
//		}
//	}
//
//	m_data.swap(newArray);
//}

//template<class T>
//void Grid<T>::insertCols(size_type col, const Grid<T>& elements)
//{
//	int i;
//	int j;
//
//	std::vector<T>newArray(m_nbRows*(m_nbCols+elements.m_nbCols));
//
//	for (j = 0; j < col; ++j) {
//		for (i = 0; i < m_nbRows; ++i) {
//			newArray[i*m_nbCols + j] = m_data[i*m_nbCols + j];
//		}
//	}
//
//	for (j = col; j < col + elements.m_nbCols; ++j) {
//		for (i = 0; i < m_nbRows && i < elements.m_nbRows; ++i) {
//			newArray[i*m_nbCols + j] = elements.m_data[i*m_nbCols + j];
//		}
//
//		for (i=elements.m_nbRows; i < m_nbRows; ++i) {
//			newArray[i*m_nbCols + j] = T();
//		}
//	}
//
//	for (j = col + elements.m_nbCols; j < m_nbCols; ++j) {
//		for (i = 0; i < m_nbRows; ++i) {
//			newArray[i*m_nbCols + j] = m_data[i*m_nbCols + (j - elements.m_nbRows)];
//		}
//	}
//
//	m_data.swap(newArray);
//}

//template<class T>
//void Grid<T>::insertCol(size_type col, const std::vector<T>& elements)
//{
//	int i;
//	int j;
//
//	std::vector<T>newArray(m_nbRows*(m_nbCols + 1));
//
//	for (j = 0; j < col; ++j) {
//		for (i = 0; i < m_nbRows; ++i) {
//			newArray[i*m_nbCols + j] = m_data[i*m_nbCols + j];
//		}
//	}
//
//	for (j = col; j < col + 1; ++j) {
//		for (i = 0; i < m_nbRows && i < elements.size(); ++i) {
//			newArray[i*m_nbCols + j] = elements[j];
//		}
//
//		for (i = elements.size(); i < m_nbRows; ++i) {
//			newArray[i*m_nbCols + j] = T();
//		}
//	}
//
//	for (j = col + elements.m_nbCols; j < m_nbCols; ++j) {
//		for (i = 0; i < m_nbRows; ++i) {
//			newArray[i*m_nbCols + j] = m_data[(i - 1)*m_nbCols + j];
//		}
//	}
//
//	m_data.swap(newArray);
//}

//template<class T>
//void Grid<T>::removeRows(size_type row, size_type n)
//{
//	int i;
//	int j;
//
//	int newNbRows = (m_nbRows - row > n) ? m_nbRows - n : row + 1;
//
//	std::vector<T>newArray(newNbRows*m_nbCols);
//
//	for (i = 0; i < row; ++i) {
//		for (j = 0; j < m_nbCols; ++j) {
//			newArray[i*m_nbCols + j] = m_data[i*m_nbCols + j];
//		}
//	}
//
//	for (i = row + n; i < m_nbRows; ++i) {
//		for (j = 0; j < m_nbCols; ++j) {
//			newArray[(i - n)*m_nbCols + j] = m_data[i*m_nbCols + j];
//		}
//	}
//}

//template<class T>
//void Grid<T>::removeCols(size_type col, size_type n)
//{
//	int i;
//	int j;
//
//	int newNbCols = (m_nbCols - col > n) ? m_nbCols - n : col + 1;
//
//	std::vector<T>newArray(m_nbRows*newNbCols);
//
//	for (j = 0; j < col; ++j) {
//		for (i = 0; i < m_nbRows; ++i) {
//			newArray[i*m_nbCols + j] = m_data[i*m_nbCols + j];
//		}
//	}
//
//	for (j = col + n; j < m_nbCols; ++j) {
//		for (i = 0; i < m_nbCols; ++i) {
//			newArray[i*m_nbCols + j - n] = m_data[i*m_nbCols + j];
//		}
//	}
//}

template<class T>
void Grid<T>::swap(Grid<T>& grid)
{
	int holdNbRows(m_nbRows);
	int holdNbCols(m_nbCols);

	m_data.swap(grid.m_data);

	m_nbRows = grid.m_nbRows;
	m_nbCols = grid.m_nbCols;

	grid.m_nbRows = holdNbRows;
	grid.m_nbCols = holdNbCols;
}

template<class T>
void Grid<T>::clear()
{
	m_data.clear();

	m_nbCols = 0;
	m_nbRows = 0;
}
