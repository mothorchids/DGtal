/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file KhalimskySpaceND.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/02/08
 *
 * Header file for module KhalimskySpaceND.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(KhalimskySpaceND_RECURSES)
#error Recursive header files inclusion detected in KhalimskySpaceND.h
#else // defined(KhalimskySpaceND_RECURSES)
/** Prevents recursive inclusion of headers. */
#define KhalimskySpaceND_RECURSES

#if !defined KhalimskySpaceND_h
/** Prevents repeated inclusion of headers. */
#define KhalimskySpaceND_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/CUnsignedInteger.h"
#include "DGtal/kernel/CSignedInteger.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/kernel/SpaceND.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /**
     Represents an (unsigned) cell in a cellular grid space by its
     Khalimsky coordinates.
   */
  template < Dimension dim,
	     typename TInteger = DGtal::int32_t >
  struct KhalimskyCell
  {

    //Integer must be a model of the concept CInteger.
    BOOST_CONCEPT_ASSERT(( CInteger<TInteger> ) );
    //Integer must be signed to characterize a ring.
    BOOST_CONCEPT_ASSERT(( CSignedInteger<TInteger> ) );
    
  public:
    typedef TInteger Integer;
    
    typedef typename IntegerTraits<Integer>::UnsignedVersion UnsignedInteger;
    typedef PointVector< dim, Integer > Point;

    PointVector< dim, TInteger > myCoordinates;

    /**
     * Constructor.
     */
    KhalimskyCell();
    
    /**
     * Copy constructor.
     *
     * @param other any other cell.
     */
    KhalimskyCell( const KhalimskyCell & other );

    /**
     * constructor from point.
     *
     * @param other any point.
     */
    KhalimskyCell( const Point & point );

    /**
     * Copy constructor.
     *
     * @param other any other cell.
     */
    KhalimskyCell & operator=( const KhalimskyCell & other );

    /**
       Equality operator.
       @param other any other cell.
    */
    bool operator==( const KhalimskyCell & other ) const;

    /**
       Difference operator.
       @param other any other cell.
    */
    bool operator!=( const KhalimskyCell & other ) const;

    /**
       Inferior operator. (lexicographic order).
       @param other any other cell.
    */
    bool operator<( const KhalimskyCell & other ) const;
  }; 

  template < Dimension dim,
	     typename TInteger >
  std::ostream & 
  operator<<( std::ostream & out, 
	      const KhalimskyCell< dim, TInteger > & object );

  /**
     Represents a signed cell in a cellular grid space by its
     Khalimsky coordinates and a boolean value.
   */
  template < Dimension dim,
	     typename TInteger = DGtal::int32_t >
  struct SignedKhalimskyCell
  {
    //Integer must be a model of the concept CInteger.
    BOOST_CONCEPT_ASSERT(( CInteger<TInteger> ) );
    //Integer must be signed to characterize a ring.
    BOOST_CONCEPT_ASSERT(( CSignedInteger<TInteger> ) );
 
  public:
    typedef TInteger Integer;
    typedef typename IntegerTraits<Integer>::UnsignedVersion UnsignedInteger;
    typedef PointVector< dim, Integer > Point;

    PointVector< dim, TInteger > myCoordinates;
    bool myPositive;

    /**
     * Constructor.
     */
    SignedKhalimskyCell();
    
    /**
     * Copy constructor.
     *
     * @param other any other cell.
     */
    SignedKhalimskyCell( const SignedKhalimskyCell & other );

    /**
     * constructor from point.
     *
     * @param other any point.
     * @param 'true' if cell has positive sign.
     */
    SignedKhalimskyCell( const Point & point, bool positive );

    /**
     * Copy constructor.
     *
     * @param other any other cell.
     */
    SignedKhalimskyCell & operator=( const SignedKhalimskyCell & other );

    /**
       Equality operator.
       @param other any other cell.
    */
    bool operator==( const SignedKhalimskyCell & other ) const;

    /**
       Difference operator.
       @param other any other cell.
    */
    bool operator!=( const SignedKhalimskyCell & other ) const;

    /**
       Inferior operator. (lexicographic order).
       @param other any other cell.
    */
    bool operator<( const SignedKhalimskyCell & other ) const;

  }; 

  template < Dimension dim,
	     typename TInteger >
  std::ostream & 
  operator<<( std::ostream & out, 
	      const SignedKhalimskyCell< dim, TInteger > & object );

  /**
     This class is useful for looping on all "interesting" coordinates of a
     cell. For instance, surfels in Z3 have two interesting coordinates (the
     ones spanned by the surfel).
     @code
     KSpace::Cell p;
     KnSpace::DirIterator q;
     for ( q = ks.uDirs( p ); q != 0; ++q ) 
     { 
        KSpace::Dimension dir = *q;
	...
     } 
     @endcode
   */
  template < Dimension dim,
	     typename TInteger = DGtal::int32_t >
  class CellDirectionIterator 
  {
  public:
    typedef TInteger Integer;
    // Cells
    typedef KhalimskyCell< dim, Integer > Cell;
    typedef SignedKhalimskyCell< dim, Integer > SCell;

  public:
    /**
     * Constructor from cell.
     * @param cell any unsigned cell
     */
    CellDirectionIterator( Cell cell, bool open = true );

    /**
     * Constructor from signed cell.
     * @param scell any signed cell
     */
    CellDirectionIterator( SCell scell, bool open = true );

    /**
     * @return the current direction.
     */
    Dimension operator*() const;

    /**
     * Pre-increment. Go to next direction.
     */
    CellDirectionIterator & operator++();
    
    /** 
     * Fast comparison with unsigned integer (unused
     * parameter). Comparison is 'false' at the end of the iteration.
     *
     * @return 'true' if the iterator is finished.
     */
    bool operator!=( const Integer ) const;

    /** 
     * @return 'true' if the iteration is ended.
     */
    bool end() const;

    /** 
     * Slow comparison with other iterator. Useful to check for end of loop.
     * @param other any direction iterator.
     */
    bool operator!=( const CellDirectionIterator & other ) const;

    /** 
     * Slow comparison with other iterator.
     * @param other any direction iterator.
     */
    bool operator==( const CellDirectionIterator & other ) const;
    
  private:
    /** the current direction. */
    Dimension myDir;
    /** the cell. */
    Cell myCell;
    /** If 'true', returns open coordinates, otherwise returns closed
	coordinates. */
    bool myOpen;

  private:
    /** Look for next valid coordinate. */
    void find();
  };


  /////////////////////////////////////////////////////////////////////////////
  // template class KhalimskySpaceND
  /**
   * Description of template class 'KhalimskySpaceND' <p> \brief Aim:
   * This class is a model of CCellularGridSpaceND. It represents the
   * cubical grid as a cell complex, whose cells are defined as an
   * array of integers. The topology of the cells is defined by the
   * parity of the coordinates (even: closed, odd: open). 
   *
   * The space is generally finite (except for arbitrary size
   * integers). The user should choose between a closed (default) cell
   * space or an open cell space.
   *
   * @tparam dim the dimension of the digital space.
   * @tparam TInteger the Integer class used to specify the arithmetic computations (default type = int32).
   */
  template < Dimension dim,
	     typename TInteger = DGtal::int32_t >
  class KhalimskySpaceND
  {
    //Integer must be a model of the concept CInteger.
    BOOST_CONCEPT_ASSERT(( CInteger<TInteger> ) ); 
    //Integer must be signed to characterize a ring.
    BOOST_CONCEPT_ASSERT(( CSignedInteger<TInteger> ) );

  public:
    ///Arithmetic ring induced by (+,-,*) and Integer numbers.
    typedef TInteger Integer;
    
    ///Type used to represent sizes in the digital space.
    typedef typename IntegerTraits<Integer>::UnsignedVersion Size;
      
    // Cells
    typedef KhalimskyCell< dim, Integer > Cell;
    typedef SignedKhalimskyCell< dim, Integer > SCell;
    typedef bool Sign;
    typedef CellDirectionIterator< dim, Integer > DirIterator;
    
    //Points and Vectors
    typedef PointVector< dim, Integer > Point;
    typedef PointVector< dim, Integer > Vector;
    
    typedef SpaceND<dim, Integer> Space;
    typedef KhalimskySpaceND<dim, Integer> KhalimskySpace;

    // static constants
//     static const Dimension dimension = dim;
//     static const Dimension DIM = dim;
//     static const Sign POS = true;
//     static const Sign NEG = false;
    static const Dimension dimension;
    static const Dimension DIM;
    static const Sign POS;
    static const Sign NEG;

    template <typename CellType>
    struct AnyCellCollection : public std::deque<CellType> {
      typedef CellType ValueType;
      typedef typename std::deque<CellType> Container;
      typedef typename std::deque<CellType>::iterator Iterator;
      typedef typename std::deque<CellType>::const_iterator ConstIterator;
      // inline
      // Iterator begin()            { return myCells.begin(); }
      // inline
      // Iterator end()              { return myCells.end(); }
      // inline
      // ConstIterator begin() const { return myCells.begin(); }
      // inline
      // ConstIterator end() const   { return myCells.end(); }
    };

    // Neighborhoods, Incident cells, Faces and Cofaces
    typedef AnyCellCollection<Cell> Cells;
    typedef AnyCellCollection<SCell> SCells;
    typedef AnyCellCollection<Cell> Neighborhood;
    typedef AnyCellCollection<SCell> SNeighborhood;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~KhalimskySpaceND();

    /**
     * Constructor.
     */
    KhalimskySpaceND();

    /**
     * Specifies the upper and lower bounds for the maximal cells in
     * this space.
     *
     * @param lower_included the lowest point in this space (digital coords)
     * @param upper_included the upper point in this space (digital coords)
     * @param closed 'true' if this space is closed, 'false' if open.
     *
     * @return true if the initialization was valid (ie, such bounds
     * are representable with these integers).
     */
    bool init( const Point & lower,
	       const Point & upper,
	       bool closed );

    // ------------------------- Basic services ------------------------------
  public:

    /**
     * @param k a coordinate (from 0 to 'dim()-1').
     * @return the width of the space in the [k]-dimension.
     */
    Size size( Dimension k ) const;

    // ----------------------- Cell creation services --------------------------
  public:

    /**
     * From the Khalimsky coordinates of a cell, builds the
     * corresponding unsigned cell.
     *
     * @param kp an integer point (Khalimsky coordinates of cell).
     * @return the unsigned cell.
     */
    Cell uCell( const Point & kp ) const;

    /**
     * From the digital coordinates of a point in Zn and a cell type,
     * builds the corresponding cell.
     *
     * @param p an integer point (digital coordinates of cell).
     * @param c another cell defining the topology.
     *
     * @return the cell having the topology of [c] and the given
     * digital coordinates [p].
     */
    Cell uCell( const Point & p, const Cell & c ) const;

    /**
     * From the Khalimsky coordinates of a cell and a sign, builds the
     * corresponding unsigned cell.
     *
     * @param kp an integer point (Khalimsky coordinates of cell).
     * @param sign the sign of the cell (either POS or NEG).
     * @return the unsigned cell.
     */
    SCell sCell( const Point & kp, Sign sign = POS ) const;

    /**
     * From the digital coordinates of a point in Zn and a signed cell
     * type, builds the corresponding signed cell.
     *
     * @param p an integer point (digital coordinates of cell).
     * @param c another cell defining the topology and sign.
     *
     * @return the cell having the topology and sign of [c] and the given
     * digital coordinates [p].
     */
    SCell sCell( const Point & p, const SCell & c ) const;

   /**
     * From the digital coordinates of a point in Zn, creates the spel
     * (cell of maximal dimension) with these coordinates.
     *
     * @param p an integer point (digital coordinates of cell).
     *
     * @return the spel having the given digital coordinates [p].
     */
    Cell uSpel( const Point & p ) const;

   /**
     * From the digital coordinates of a point in Zn, creates the spel
     * (cell of maximal dimension) with these coordinates.
     *
     * @param p an integer point (digital coordinates of cell).
     * @param sign the sign of the cell (either POS or NEG).
     *
     * @return the signed spel having the given digital coordinates [p].
     */
    SCell sSpel( const Point & p, Sign sign = POS ) const;

   /**
     * From the digital coordinates of a point in Zn, creates the pointel
     * (cell of dimension 0) with these coordinates.
     *
     * @param p an integer point (digital coordinates of cell).
     *
     * @return the pointel having the given digital coordinates [p].
     */
    Cell uPointel( const Point & p ) const;

   /**
     * From the digital coordinates of a point in Zn, creates the pointel
     * (cell of dimension 0) with these coordinates.
     *
     * @param p an integer point (digital coordinates of cell).
     * @param sign the sign of the cell (either POS or NEG).
     *
     * @return the signed pointel having the given digital coordinates [p].
     */
    SCell sPointel( const Point & p, Sign sign = POS ) const;


    // ----------------------- Read accessors to cells ------------------------
  public:
    /**
     * @param c any unsigned cell.
     * @param k any valid dimension.
     * @return its Khalimsky coordinate along [k].
     */
    Integer uKCoord( const Cell & c, Dimension k ) const;

    /**
     * @param c any unsigned cell.
     * @param k any valid dimension.
     * @return its digital coordinate  along [k].
     */
    Integer uCoord( const Cell & c, Dimension k ) const;

    /**
     * @param c any unsigned cell.
     * @return its Khalimsky coordinates.
     */
    Point uKCoords( const Cell & c ) const;

    /**
     * @param c any unsigned cell.
     * @return its digital coordinates.
     */
    Point uCoords( const Cell & c ) const;

    /**
     * @param c any signed cell.
     * @param k any valid dimension.
     * @return its Khalimsky coordinate along [k].
     */
    Integer sKCoord( const SCell & c, Dimension k ) const;

    /**
     * @param c any signed cell.
     * @param k any valid dimension.
     * @return its digital coordinate  along [k].
     */
    Integer sCoord( const SCell & c, Dimension k ) const;

    /**
     * @param c any signed cell.
     * @return its Khalimsky coordinates.
     */
    Point sKCoords( const SCell & c ) const;

    /**
     * @param c any signed cell.
     * @return its digital coordinates.
     */
    Point sCoords( const SCell & c ) const;

    /**
     * @param c any signed cell.
     * @return its sign.
     */
    Sign sSign( const SCell & c ) const;

    // ----------------------- Write accessors to cells ------------------------
  public:

    /**
     * Sets the [k]-th Khalimsky coordinate of [c] to [i].
     * @param c any unsigned cell.
     * @param k any valid dimension.
     * @param i an integer coordinate within the space.
     */
    void uSetKCoord( Cell & c, Dimension k, const Integer & i ) const;

    /**
     * Sets the [k]-th Khalimsky coordinate of [c] to [i].
     * @param c any signed cell.
     * @param k any valid dimension.
     * @param i an integer coordinate within the space.
     */
    void sSetKCoord( SCell & c, Dimension k, const Integer & i ) const;

    /**
     * Sets the [k]-th digital coordinate of [c] to [i].
     * @param c any unsigned cell.
     * @param k any valid dimension.
     * @param i an integer coordinate within the space.
     */
    void uSetCoord( Cell & c, Dimension k, const Integer & i ) const;

    /**
     * Sets the [k]-th digital coordinate of [c] to [i].
     * @param c any signed cell.
     * @param k any valid dimension.
     * @param i an integer coordinate within the space.
     */
    void sSetCoord( SCell & c, Dimension k, const Integer & i ) const;

    /**
     * Sets the Khalimsky coordinates of [c] to [kp].
     * @param c any unsigned cell.
     * @param kp the new Khalimsky coordinates for [c].
     */
    void uSetKCoords( Cell & c, const Point & kp ) const;

    /**
     * Sets the Khalimsky coordinates of [c] to [kp].
     * @param c any signed cell.
     * @param kp the new Khalimsky coordinates for [c].
     */
    void sSetKCoords( SCell & c, const Point & kp ) const;

    /**
     * Sets the digital coordinates of [c] to [kp].
     * @param c any unsigned cell.
     * @param kp the new Khalimsky coordinates for [c].
     */
    void uSetCoords( Cell & c, const Point & kp ) const;

    /**
     * Sets the digital coordinates of [c] to [kp].
     * @param c any signed cell.
     * @param kp the new Khalimsky coordinates for [c].
     */
    void sSetCoords( SCell & c, const Point & kp ) const;

    /**
     * Sets the sign of the cell.
     * @param c (modified) any signed cell.
     * @param s any sign.
     */
    void sSetSign( SCell & c, Sign s ) const;

    // -------------------- Conversion signed/unsigned ------------------------
  public:
    /**
     * Creates a signed cell from an unsigned one and a given sign.
     * @param p any unsigned cell.
     * @param s a sign.
     * @return the signed version of the cell [p] with sign [s].
     */
    SCell signs( const Cell & p, Sign s ) const;

    /**
     * Creates an unsigned cell from a signed one.
     * @param p any signed cell.
     * @return the unsigned version of the cell [p].
     */
    Cell unsigns( const SCell & p ) const;

    /**
     * Creates the signed cell with the inverse sign of [p].
     * @param p any signed cell.
     * @return the cell [p] with opposite sign.
     */
    SCell sOpp( const SCell & p ) const;

    // ------------------------- Cell topology services -----------------------
  public:
    /**
     * @param p any unsigned cell.
     * @return the topology word of [p].
     */
    Integer uTopology( const Cell & p ) const;

    /**
     * @param p any signed cell.
     * @return the topology word of [p].
     */
    Integer sTopology( const SCell & p ) const;

    /**
     * @param p any unsigned cell.
     * @return the dimension of the cell [p].
     */
    Dimension uDim( const Cell & p ) const;

    /**
     * @param p any signed cell.
     * @return the dimension of the cell [p].
     */
    Dimension sDim( const SCell & p ) const;

    /**
     * @param b any unsigned cell.
     * @return 'true' if [b] is a surfel (spans all but one coordinate).
     */
    bool uIsSurfel( const Cell & b ) const;

    /**
     * @param b any signed cell.
     * @return 'true' if [b] is a surfel (spans all but one coordinate).
     */
    bool sIsSurfel( const SCell & b ) const;
    
    /**
       @param p any cell.
       @param k any direction.
       @return 'true' if [p] is open along the direction [k].
    */
    bool uIsOpen( const Cell & p, Dimension k ) const;

    /**
       @param p any signed cell.
       @param k any direction.
       @return 'true' if [p] is open along the direction [k].
    */
    bool sIsOpen( const SCell & p, Dimension k ) const;

    // -------------------- Iterator services for cells ------------------------
  public:

    /**
     Given an unsigned cell [p], returns an iterator to iterate over
     each coordinate the cell spans. (A spel spans all coordinates; a
     surfel all but one, etc). Example:

     @code
     KSpace::Cell p;
     ...
     for ( KnSpace::DirIterator q = ks.uDirs( p ); q != 0; ++q ) 
     { 
        KSpace::Dimension dir = *q;
	...
     } 
     @endcode
     
     @param p any unsigned cell.
     
     @return an iterator that points on the first coordinate spanned
     by the cell.
    */
    DirIterator uDirs( const Cell & p ) const;

    /**
     Given a signed cell [p], returns an iterator to iterate over
     each coordinate the cell spans. (A spel spans all coordinates; a
     surfel all but one, etc). Example:

     @code
     KSpace::SCell p;
     ...
     for ( KnSpace::DirIterator q = ks.uDirs( p ); q != 0; ++q ) 
     { 
        KSpace::Dimension dir = *q;
	...
     } 
     @endcode
     
     @param p any signed cell.
     
     @return an iterator that points on the first coordinate spanned
     by the cell.
    */
    DirIterator sDirs( const SCell & p ) const;

    /**
     Given an unsigned cell [p], returns an iterator to iterate over each 
     coordinate the cell does not span. (A spel spans all coordinates; 
     a surfel all but one, etc). Example: 

     @code
     KSpace::Cell p;
     ...
     for ( KnSpace::DirIterator q = ks.uOrthDirs( p ); q != 0; ++q ) 
     { 
        KSpace::Dimension dir = *q;
	...
     } 
     @endcode
     
     @param p any unsigned cell.
     
     @return an iterator that points on the first coordinate spanned
     by the cell.
    */
    DirIterator uOrthDirs( const Cell & p ) const;

    /**
     Given a signed cell [p], returns an iterator to iterate over each 
     coordinate the cell does not span. (A spel spans all coordinates; 
     a surfel all but one, etc). Example: 

     @code
     KSpace::SCell p;
     ...
     for ( KnSpace::DirIterator q = ks.uOrthDirs( p ); q != 0; ++q ) 
     { 
        KSpace::Dimension dir = *q;
	...
     } 
     @endcode
     
     @param p any signed cell.
     
     @return an iterator that points on the first coordinate spanned
     by the cell.
    */
    DirIterator sOrthDirs( const SCell & p ) const;

    /**
       Given an unsigned surfel [s], returns its orthogonal direction (ie,
       the coordinate where the surfel is closed).
       
       @param s an unsigned surfel
       @return the orthogonal direction of [s]
    */
    Dimension uOrthDir( const Cell & s ) const;

    /**
       Given a signed surfel [s], returns its orthogonal direction (ie,
       the coordinate where the surfel is closed).

       @param s a signed surfel
       @return the orthogonal direction of [s]
    */
    Dimension sOrthDir( const SCell & s ) const;

  // -------------------- Unsigned cell geometry services --------------------
 public:

    /**
       @return the first cell of the space with the same type as [p].
    */
    Cell uFirst( const Cell & p ) const;
    
    /**
       @return the last cell of the space with the same type as [p].
    */
    Cell uLast( const Cell & p ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       
       @return the same element as [p] except for the incremented
       coordinate [k].
    */
    Cell uGetIncr( const Cell & p, Dimension k ) const;
 
    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the tested coordinate.
       
       @return true if [p] cannot have its [k]-coordinate augmented
       without leaving the space.
    */
    bool uIsMax( const Cell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the concerned coordinate.
       
       @return the cell similar to [p] but with the maximum allowed
       [k]-coordinate.
    */
    Cell uGetMax( const Cell & p, Dimension k ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       
       @return the same element as [p] except for an decremented
       coordinate [k].
     */
    Cell uGetDecr( const Cell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the tested coordinate.
       
       @return true if [p] cannot have its [k]-coordinate decreased
       without leaving the space.
    */
    bool uIsMin( const Cell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the concerned coordinate.
       
       @return the cell similar to [p] but with the minimum allowed
       [k]-coordinate.
    */
    Cell uGetMin( const Cell & p, Dimension k ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       @param x the increment.
       
       @return the same element as [p] except for a coordinate [k]
       incremented with x.
    */
    Cell uGetAdd( const Cell & p, Dimension k, const Integer & x ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       @param x the decrement.

       @return the same element as [p] except for a coordinate [k]
       decremented with x.
    */
    Cell uGetSub( const Cell & p, Dimension k, const Integer & x ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the coordinate that is tested.
       @return the number of increment to do to reach the maximum value.
    */
    Integer uDistanceToMax( const Cell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the coordinate that is tested.
       
       @return the number of decrement to do to reach the minimum
       value.
    */
    Integer uDistanceToMin( const Cell & p, Dimension k ) const;

    /**
       Add the vector [vec] to [p]. 
       NB: you can go out of the space.
       @param p any cell.
       @param vec any pointel.
       @return the unsigned code of the cell [p] translated by [coord].
    */
    Cell uTranslation( const Cell & p, const Vector & vec ) const;

    /**
       Return the projection of [p] along the [k]th direction toward
       [bound]. Otherwise said, p[ k ] == bound[ k ] afterwards.

       @param p any cell.
       @param bound the element acting as bound (same topology as p).
       @param k the concerned coordinate.
       @return the projection.
    */
    Cell uProjection( const Cell & p, const Cell & bound, Dimension k ) const;

    /**
       Projects [p] along the [k]th direction toward
       [bound]. Otherwise said, p[ k ] == bound[ k ] afterwards.

       @param p any cell.
       @param bound the element acting as bound (same topology as p).
       @param k the concerned coordinate.
       @return the projection.
    */
    void uProject( Cell & p, const Cell & bound, Dimension k ) const;

    /**
       Increment the cell [p] to its next position (as classically done in
       a scanning). Example:

       \code
       KSpace K;
       Cell first, last; // lower and upper bounds 
       Cell p = first;
       do 
       { // ... whatever [p] is the current cell
       }
       while ( K.uNext( p, first, last ) ); 
       \endcode
       
       @param p any cell.
       @param lower the lower bound.
       @param upper the upper bound.
       
       @return true if p is still within the bounds, false if the
       scanning is finished.
    */
    bool uNext( Cell & p, const Cell & lower, const Cell & upper ) const;

  // -------------------- Signed cell geometry services --------------------
 public:

    /**
       @return the first cell of the space with the same type as [p].
    */
    SCell sFirst( const SCell & p ) const;
    
    /**
       @return the last cell of the space with the same type as [p].
    */
    SCell sLast( const SCell & p ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       
       @return the same element as [p] except for the incremented
       coordinate [k].
    */
    SCell sGetIncr( const SCell & p, Dimension k ) const;
 
    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the tested coordinate.
       
       @return true if [p] cannot have its [k]-coordinate augmented
       without leaving the space.
    */
    bool sIsMax( const SCell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the concerned coordinate.
       
       @return the cell similar to [p] but with the maximum allowed
       [k]-coordinate.
    */
    SCell sGetMax( const SCell & p, Dimension k ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       
       @return the same element as [p] except for an decremented
       coordinate [k].
     */
    SCell sGetDecr( const SCell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the tested coordinate.
       
       @return true if [p] cannot have its [k]-coordinate decreased
       without leaving the space.
    */
    bool sIsMin( const SCell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the concerned coordinate.
       
       @return the cell similar to [p] but with the minimum allowed
       [k]-coordinate.
    */
    SCell sGetMin( const SCell & p, Dimension k ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       @param x the increment.
       
       @return the same element as [p] except for a coordinate [k]
       incremented with x.
    */
    SCell sGetAdd( const SCell & p, Dimension k, const Integer & x ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       @param x the decrement.

       @return the same element as [p] except for a coordinate [k]
       decremented with x.
    */
    SCell sGetSub( const SCell & p, Dimension k, const Integer & x ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the coordinate that is tested.
       @return the number of increment to do to reach the maximum value.
    */
    Integer sDistanceToMax( const SCell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the coordinate that is tested.
       
       @return the number of decrement to do to reach the minimum
       value.
    */
    Integer sDistanceToMin( const SCell & p, Dimension k ) const;

    /**
       Add the vector [vec] to [p]. 
       NB: you can go out of the space.
       @param p any cell.
       @param vec any pointel.
       @return the signed code of the cell [p] translated by [coord].
    */
    SCell sTranslation( const SCell & p, const Vector & vec ) const;

    /**
       Return the projection of [p] along the [k]th direction toward
       [bound]. Otherwise said, p[ k ] == bound[ k ] afterwards.

       @param p any cell.
       @param bound the element acting as bound (same topology as p).
       @param k the concerned coordinate.
       @return the projection.
    */
    SCell sProjection( const SCell & p, const SCell & bound, Dimension k ) const;

    /**
       Projects [p] along the [k]th direction toward
       [bound]. Otherwise said, p[ k ] == bound[ k ] afterwards.

       @param p any cell.
       @param bound the element acting as bound (same topology as p).
       @param k the concerned coordinate.
       @return the projection.
    */
    void sProject( SCell & p, const SCell & bound, Dimension k ) const;

    /**
       Increment the cell [p] to its next position (as classically done in
       a scanning). Example:

       \code
       KSpace K;
       Cell first, last; // lower and upper bounds 
       Cell p = first;
       do 
       { // ... whatever [p] is the current cell
       }
       while ( K.uNext( p, first, last ) ); 
       \endcode
       
       @param p any cell.
       @param lower the lower bound.
       @param upper the upper bound.
       
       @return true if p is still within the bounds, false if the
       scanning is finished.
    */
    bool sNext( SCell & p, const SCell & lower, const SCell & upper ) const;

    // ----------------------- Neighborhood services --------------------------
  public:

    /**
       Computes the 1-neighborhood of the cell [c] and returns
       it. It is the set of cells with same topology that are adjacent
       to [c].
       
       @param cell the unsigned cell of interest.
       @return the cells of the 1-neighborhood of [cell].
    */
    Cells uNeighborhood( const Cell & cell ) const;

    /**
       Computes the 1-neighborhood of the cell [c] and returns
       it. It is the set of cells with same topology that are adjacent
       to [c].
       
       @param cell the signed cell of interest.
       @return the cells of the 1-neighborhood of [cell].
    */
    SCells sNeighborhood( const SCell & cell ) const;

    /**
       Computes the proper 1-neighborhood of the cell [c] and returns
       it. It is the set of cells with same topology that are adjacent
       to [c].
       
       @param cell the unsigned cell of interest.
       @return the cells of the proper 1-neighborhood of [cell].
    */
    Cells uProperNeighborhood( const Cell & cell ) const;

    /**
       Computes the proper 1-neighborhood of the cell [c] and returns
       it. It is the set of cells with same topology that are adjacent
       to [c].
       
       @param cell the signed cell of interest.
       @return the cells of the proper 1-neighborhood of [cell].
    */
    SCells sProperNeighborhood( const SCell & cell ) const;

    // ----------------------- Incidence services --------------------------
  public:

    /**
       @param c any unsigned cell.
       @param k any coordinate.

       @param forward if 'true' the orientation is forward along axis
       [k], otherwise backward.
       
       @return the forward or backward unsigned cell incident to [c]
       along axis [k], depending on [forward].

       @note It may be a lower incident cell if [c] is open along axis
       [k], else an upper incident cell.

       @note The cell should have an incident cell in this
       direction/orientation.
    */
    Cell uIncident( const Cell & c, Dimension k, bool up ) const;

    /**
       @param c any signed cell.
       @param k any coordinate.

       @param forward if 'true' the orientation is forward along axis
       [k], otherwise backward.
       
       @return the forward or backward signed cell incident to [c]
       along axis [k], depending on [forward]. It is worthy to note
       that the forward and backward cell have opposite
       sign. Furthermore, the sign of these cells is defined so as to
       satisfy a boundary operator.

       @note It may be a lower incident cell if [c] is open along axis
       [k], else an upper incident cell.

       @note The cell should have an incident cell in this
       direction/orientation.
    */
    SCell sIncident( const SCell & c, Dimension k, bool up ) const;

    /**
       @param c any unsigned cell.
       @return the cells directly low incident to c in this space.
    */
    Cells uLowerIncident( const Cell & c ) const;

    /**
       @param c any unsigned cell.
       @return the cells directly up incident to c in this space.
    */
    Cells uUpperIncident( const Cell & c ) const;

    /**
       @param c any signed cell.
       @return the signed cells directly low incident to c in this space.
       @note it is the lower boundary of c expressed as a list of signed cells.
    */
    SCells sLowerIncident( const SCell & c ) const;

    /**
       @param c any signed cell.
       @return the signed cells directly up incident to c in this space.
       @note it is the upper boundary of c expressed as a list of signed cells.
    */
    SCells sUpperIncident( const SCell & c ) const;

    /**
       @param c any unsigned cell.
       @return the proper faces of [c] (chain of lower incidence).
    */
    Cells uFaces( const Cell & c ) const;

    /**
       @param c any unsigned cell.
       @return the proper cofaces of [c] (chain of upper incidence).
    */
    Cells uCoFaces( const Cell & c ) const;

    /**
       Return 'true' if the direct orientation of [p] along [k] is in
       the positive coordinate direction. The direct orientation in a
       direction allows to go from positive incident cells to positive
       incident cells.  This means that 
       @code
       K.sSign( K.sIncident( p, k, K.sDirect( p, k ) ) ) == K.POS
       @endcode
       is always true.

       @param p any signed cell.
       @param k any coordinate.

       @return the direct orientation of [p] along [k] (true is
       upward, false is backward).
    */
    bool sDirect( const SCell & p, Dimension k ) const;

    /**
       @param p any signed cell.
       @param k any coordinate.

       @return the direct incident cell of [p] along [k] (the incident
       cell along [k] whose sign is positive).
    */
    SCell sDirectIncident( const SCell & p, Dimension k ) const;

    /**
       @param p any signed cell.
       @param k any coordinate.

       @return the indirect incident cell of [p] along [k] (the incident
       cell along [k] whose sign is negative).
    */
    SCell sIndirectIncident( const SCell & p, Dimension k ) const;
   

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    Point myLower;
    Point myUpper;
    Cell myCellLower;
    Cell myCellUpper;
    bool myIsClosed;
    // ------------------------- Hidden services ------------------------------
  protected:


  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    KhalimskySpaceND ( const KhalimskySpaceND & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    KhalimskySpaceND & operator= ( const KhalimskySpaceND & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class KhalimskySpaceND


  /**
   * Overloads 'operator<<' for displaying objects of class 'KhalimskySpaceND'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'KhalimskySpaceND' to write.
   * @return the output stream after the writing.
   */
  template < Dimension dim,
	     typename TInteger >
  std::ostream&
  operator<< ( std::ostream & out, 
	       const KhalimskySpaceND<dim, TInteger > & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/KhalimskySpaceND.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined KhalimskySpaceND_h

#undef KhalimskySpaceND_RECURSES
#endif // else defined(KhalimskySpaceND_RECURSES)