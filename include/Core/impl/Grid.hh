#ifdef AVR_CORE_GRID_HPP

namespace avr {

template <class T, size_t rows, size_t cols> inline Grid<T, rows, cols>::Grid()
   : wCell(0), hCell(0), wGrid(0), hGrid(0) {/* ctor */}
template <class T, size_t rows, size_t cols> inline Grid<T, rows, cols>::Grid(size_t cellw, size_t cellh)
   : wCell(cellw), hCell(cellh), wGrid(wCell * nCols), hGrid(hCell * nRows) {/* ctor */}

template <class T, size_t rows, size_t cols> inline Grid<T, rows, cols>::Grid(const Grid<T, rows, cols>& grid)
   : wCell(0), hCell(0), wGrid(0), hGrid(0)
{
   this->Copy(grid, *this);
}
template <class T, size_t rows, size_t cols> inline Grid<T, rows, cols>& Grid<T, rows, cols>::operator = (const Grid<T, rows, cols>& grid) {
   this->Copy(grid, *this);
   return * this;
}

// access by cell index
template <class T, size_t rows, size_t cols> inline Cell<T>& Grid<T, rows, cols>::operator () (size_t ri, size_t ci) {
   if(ri < nRows && ci < nCols)
      return data[ri][ci];
   throw std::out_of_range("Cell index is out of the grid");
}
template <class T, size_t rows, size_t cols> inline const Cell<T>& Grid<T, rows, cols>::operator () (size_t ri, size_t ci) const {
   if(ri < nRows && ci < nCols)
      return data[ri][ci];
   throw std::out_of_range("Cell index is out of the grid");
}

// access by point in grid
template <class T, size_t rows, size_t cols> template <typename Tp> inline Cell<T>& Grid<T, rows, cols>::operator () (const cv::Point_<Tp>& p) {
   size_t ri = size_t(p.y)/hCell, ci = size_t(p.x)/wCell;
   if(ri < nRows && ci < nCols)
      return data[ri][ci];
   throw std::out_of_range("Point is out of the grid");
}
template <class T, size_t rows, size_t cols> template <typename Tp> inline const Cell<T>& Grid<T, rows, cols>::operator () (const cv::Point_<Tp>& p) const {
   size_t ri = size_t(p.y)/hCell, ci = size_t(p.x)/wCell;
   if(ri < nRows && ci < nCols)
      return data[ri][ci];
   throw std::out_of_range("Point is out of the grid");
}

template <class T, size_t rows, size_t cols> inline void Grid<T, rows, cols>::Copy(const Grid<T, rows, cols>& src, Grid<T, rows, cols>& dtn) {
   const_cast<size_t&>(dtn.wCell) = src.wCell;
   const_cast<size_t&>(dtn.hCell) = src.hCell;
   const_cast<size_t&>(dtn.wGrid) = dtn.wCell * dtn.nCols;
   const_cast<size_t&>(dtn.hGrid) = dtn.hCell * dtn.nRows;

   for(size_t i = 0; i < dtn.nRows; i++)
      for(size_t j = 0; j < dtn.nCols; j++)
         dtn.data[i][j] = src.data[i][j];
}

// cell class methods
template <class T> inline Cell<T>::Cell()
   : std::set<T>() {/* ctor */}
template <class T> inline Cell<T>& Cell<T>::operator = (const T& value) {
   this->insert(value);
   return * this;
}
template <class T> inline Cell<T>& Cell<T>::operator += (const Cell<T>& cell) {
   this->insert(cell.begin(), cell.end());
   return * this;
}
template <class T> inline Cell<T> Cell<T>::operator + (const Cell<T>& cell) {
   Cell<T> res(*this);
   res.insert(cell.begin(), cell.end());
   return res;
}

} // avr

#endif // AVR_CORE_GRID_HPP
