#ifndef AVR_CORE_GRID_HPP
#define AVR_CORE_GRID_HPP

#include <Core/Core.hpp>

namespace avr {

//! Utility cell class for grid
template <class T> struct Cell : std::set<T> {
public:
   Cell();
   // add an new element
   Cell& operator = (const T& value);
   // join cells operators
   Cell& operator += (const Cell&);
   Cell operator + (const Cell&);
   // compare cells operators
   bool operator == (const Cell&);
   bool operator != (const Cell&);

   // print cell elements
   friend std::ostream& operator << (std::ostream& out, const Cell& cell) {
      out << "["; for(const auto& v : cell) out << v << " ";
      return (out << (cell.empty() ? "]" : "\b]"));
   }

   using std::set<T>::begin;
   using std::set<T>::end;
   using std::set<T>::size;
   using std::set<T>::empty;
};

//! Basic grid structure
template <class T, size_t rows, size_t cols> struct Grid {
public:
   const size_t nRows = rows; // number of rows
   const size_t nCols = cols; // number of collums
   const size_t wCell, hCell; // size of a cell
   const size_t wGrid, hGrid; // size of the grid

   Grid(); //< invalid grid
   Grid(size_t cellw, size_t cellh);

   // deep-copy constructor and assign operator
   Grid(const Grid&);
   Grid& operator = (const Grid&);

   // cell-access operator by cell index
   Cell<T>& operator () (size_t ri, size_t ci);
   const Cell<T>& operator () (size_t ri, size_t ci) const;

   // cell-access operator by a point in grid
   template <typename Tp> Cell<T>& operator () (const cv::Point_<Tp>& p);
   template <typename Tp> const Cell<T>& operator () (const cv::Point_<Tp>& p) const;

private:
   Cell<T> data[rows][cols];

   void Copy(const Grid&, Grid&);
};

} // avr

#include "impl/Grid.hh"

#endif // AVR_CORE_GRID_HPP
