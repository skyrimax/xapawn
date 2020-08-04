#pragma once

#include <vector>
#include "Coordinate.h"

template <class T>
class Grid
{
public:
	//Type to indicate size of container
	typedef size_t size_type;

	Grid(size_type nbRows = 0, size_type nbCols = 0);
	Grid(size_type nbRows, size_type nbCols, const T& val);
	Grid(size_type nbRows, size_type nbCols, const std::vector<T>& data);
	Grid(size_type nbRows, size_type nbCols, std::vector<T>&& data);
	Grid(const Grid<T>& grid);
	Grid(Grid<T>&& grid);
	~Grid();

	//Assignement operator overloading
	Grid<T>& operator=(const Grid<T>& grid);
	Grid<T>& operator=(Grid<T>&& grid);

	//Capacity related member functions
	size_type nbRows() const;
	size_type nbCols() const;
	void resize(size_type nbRows, size_type nbCols);
	void resize(size_type nbRows, size_type nbCols, T& val);
	bool empty();

	//Element access methods
	T& operator()(size_type row, size_type col);
	const T& operator()(size_type row, size_type col) const;
	T& operator()(const Coordinate& pos);
	const T& operator()(const Coordinate& pos) const;
	T& at(size_type row, size_type col);
	const T& at(size_type row, size_type col) const;
	T& at(const Coordinate& pos);
	const T& at(const Coordinate& pos) const;
	/*Grid<T> rows(size_type row, size_type n=1);
	const Grid<T> rows(size_type row, size_type n = 1) const;
	std::vector<T> row(size_type row);
	const std::vector<T> row(size_type row) const;
	Grid<T> cols(size_type col, size_type n = 1);
	const Grid<T> cols(size_type col, size_type n = 1) const;
	std::vector<T> col(size_type col);
	const std::vector<T> col(size_type col) const;
	Grid<T> firstRowGrid();
	const Grid<T> firstRowGrid() const;
	std::vector<T> firstRowVector();
	const std::vector<T> firstRowVector() const;
	Grid<T> lastRowGrid();
	const Grid<T> lastRowGrid() const;
	std::vector<T> lastRowVector();
	const std::vector<T> lastRowVector() const;
	Grid<T> firstColGrid();
	const Grid<T> firstColGrid() const;
	std::vector<T> firstColVector();
	const std::vector<T> firstColVector() const;
	Grid<T> lastColGrid();
	const Grid<T> lastColGrid() const;
	std::vector<T> lastColVector();
	const std::vector<T> lastColVector() const;*/
	std::vector<T> data();
	const std::vector<T> data() const;

	//Modifiers
	void assign(size_type nbRows, size_type nbCols, const T& val);
	/*void insertRows(size_type row, const Grid<T>& elements);
	void insertRow(size_type row, const std::vector<T>& elements);
	void insertCols(size_type col, const Grid<T>& elements);
	void insertCol(size_type col, const std::vector<T>& elements);
	void removeRows(size_type row, size_type n=1);
	void removeCols(size_type col, size_type n = 1);*/
	void swap(Grid<T>& grid);
	void clear();

private:
	std::vector<T> m_data;
	size_type m_nbRows;
	size_type m_nbCols;
};

#include "Grid.tpp"