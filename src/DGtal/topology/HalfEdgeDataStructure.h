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
 * @file HalfEdgeDataStructure.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2017/02/03
 *
 * Header file for module HalfEdgeDataStructure.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(HalfEdgeDataStructure_RECURSES)
#error Recursive header files inclusion detected in HalfEdgeDataStructure.h
#else // defined(HalfEdgeDataStructure_RECURSES)
/** Prevents recursive inclusion of headers. */
#define HalfEdgeDataStructure_RECURSES

#if !defined HalfEdgeDataStructure_h
/** Prevents repeated inclusion of headers. */
#define HalfEdgeDataStructure_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <array>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /// Defines the invalid half-edge (i.e. exterior).
  ///
  /// @note It is defined external to the HalfEdgeDataStructure
  /// because there was link error with gcc 4.8.4 for all variants
  /// within HalfEdgeDataStructure (e.g. BOOST_STATIC_CONSTANT, c++
  /// constexpr, c++ constexpr with const reference).
  static std::size_t const HALF_EDGE_INVALID_INDEX = boost::integer_traits<std::size_t>::const_max;
  
  /////////////////////////////////////////////////////////////////////////////
  // class HalfEdgeDataStructure
  /**
   * Description of template class 'HalfEdgeDataStructure' <p> \brief
   * Aim: This class represents an half-edge data structure, which is
   * a structure for representing the topology of a combinatorial
   * 2-dimensional surface or an embedding of a planar graph in the
   * plane. It does not store any geometry. As a minimal example,
   * these lines of code build two triangles connected by the edge
   * {1,2}.
   *
   * \code
   * std::vector< HalfEdgeDataStructure::Triangle > triangles( 2 );
   * triangles[0].v = { 0, 1, 2 };
   * triangles[1].v = { 2, 1, 3 };
   * HalfEdgeDataStructure mesh;
   * mesh.build( triangles );
   * std::cout << mesh << std::endl;
   * \endcode
   *
   * @todo For now, the construction of the half-edge structure
   * (method HalfEdgeDataStructure::build) is limited to triangles. It
   * would be not difficult to adapt it to cellular surfaces.
   * 
   * @note Large parts of this class are taken from
   * https://github.com/yig/halfedge, written by Yotam Gingold.
   */
  class HalfEdgeDataStructure
  {
  public:

    /// The type for counting elements.
    typedef std::size_t    Size;
    /// The type used for numbering half-edges (an offset an the half-edges structure).
    typedef std::size_t    Index;
    /// The type used for numbering half-edges (alias)
    typedef Index   HalfEdgeIndex;
    /// The type for numbering vertices
    typedef Index   VertexIndex;
    /// The type for numbering edges
    typedef Index   EdgeIndex;
    /// The type for numbering faces
    typedef Index   FaceIndex;

    // Defines the invalid index.
    // JOL: works with Apple LLVM version 8.1.0 (clang-802.0.42), but does not work with gcc 4.8.4
    //
    // static constexpr Index const& INVALID_INDEX = boost::integer_traits<Index>::const_max;
    //
    // JOL: does NOT work with Apple LLVM version 8.1.0 (clang-802.0.42)
    // (undefined reference at link time).
    // static constexpr Index const INVALID_INDEX = boost::integer_traits<Index>::const_max;
    // static Index const INVALID_INDEX = boost::integer_traits<Index>::const_max;
    // BOOST_STATIC_CONSTANT( Index, INVALID_INDEX = boost::integer_traits<Index>::const_max );
    
    typedef std::vector<HalfEdgeIndex> HalfEdgeIndexRange;
    typedef std::vector<VertexIndex>   VertexIndexRange;
    typedef std::vector<EdgeIndex>     EdgeIndexRange;
    typedef std::vector<FaceIndex>     FaceIndexRange;

    /// An arc is a directed edge from a first vertex to a second vertex.
    typedef std::pair<VertexIndex, VertexIndex> Arc;
    // A map from an arc (a std::pair of VertexIndex's) to its
    // half edge index (i.e. and offset into the 'halfedge' sequence).
    typedef std::map< Arc, Index > Arc2Index;
    // A map from an arc (a std::pair of VertexIndex's) to its face
    // index.
    typedef std::map< Arc, FaceIndex > Arc2FaceIndex;
    
    /// Represents an unoriented edge as two vertex indices, the first
    /// lower than the second.
    struct Edge
    {
      /// The two vertex indices.
      VertexIndex v[2];
      
      VertexIndex& start() { return v[0]; }
      const VertexIndex& start() const { return v[0]; }
      
      VertexIndex& end() { return v[1]; }
      const VertexIndex& end() const { return v[1]; }
      
      Edge()
      {
        v[0] = v[1] = -1;
      }
      Edge( VertexIndex vi, VertexIndex vj )
      {
        if ( vi <= vj ) { v[0] = vi; v[1] = vj; }
        else            { v[0] = vj; v[1] = vi; }
      }
      bool operator<( const Edge& other ) const
      {
        return ( start() < other.start() )
          || ( ( start() == other.start() ) && ( end() < other.end() ) );
      }
    };

    /// Represents an unoriented triangle as three vertices.
    struct Triangle
    {
      /// The three vertex indices.
      std::array<VertexIndex,3> v;
      
      VertexIndex& i() { return v[0]; }
      const VertexIndex& i() const { return v[0]; }
      
      VertexIndex& j() { return v[1]; }
      const VertexIndex& j() const { return v[1]; }
      
      VertexIndex& k() { return v[2]; }
      const VertexIndex& k() const { return v[2]; }
      
      Triangle()
      {
        v[0] = v[1] = v[2] = -1;
      }
      Triangle( VertexIndex v0, VertexIndex v1, VertexIndex v2 )
      {
        v[0] = v0;
        v[1] = v1;
        v[2] = v2;
      }
    };

    /// Defines an arbitrary polygonal face as a vector of vertex
    /// indices. To be valid, its size must be at least 3.
    typedef std::vector<VertexIndex> PolygonalFace;
    
    /// The half edge structure. Each half-edge points to some Vertex,
    /// is incident to one face, lies on one undirected edge, has an
    /// opposite half-edge lying on the same edge, and has a next
    /// half-edge along the face.
    struct HalfEdge
    {
      /// The end vertex of this half-edge as an index into the vertex array.
      VertexIndex toVertex;
      /// Index into the face array.
      FaceIndex face;
      /// Index into the edges array.
      EdgeIndex edge;
      /// Index into the halfedges array.
      Index opposite;
      /// Index into the halfedges array.
      Index next;

      /// Default constructor. The half-edge is invalid.
      HalfEdge() :
        toVertex( HALF_EDGE_INVALID_INDEX ),
        face( HALF_EDGE_INVALID_INDEX ),
        edge( HALF_EDGE_INVALID_INDEX ),
        opposite( HALF_EDGE_INVALID_INDEX ),
        next( HALF_EDGE_INVALID_INDEX )
      {}
    };

  public:
    /// Default constructor. The data structure is empty. @see build
    HalfEdgeDataStructure() {}
    
    /** 
     * Computes all the unoriented edges of the given triangles. 
     *
     * @note Method build() needs the unordered edges of the mesh.  If
     * you don't have them, call this first.
     *
     * @param[in] triangles the vector of input oriented triangles.
     *
     * @param[out] edges_out the vector of all the unoriented edges of
     * the given triangles.
     *
     * @return the total number of different vertices (note that the
     * vertex numbering should be between 0 and this number minus
     * one).
     */
    static Size getUnorderedEdgesFromTriangles
    ( const std::vector<Triangle>& triangles, std::vector< Edge >& edges_out )
    {
      typedef std::set< Edge > EdgeSet;
      typedef std::set< VertexIndex > VertexIndexSet;
      VertexIndexSet vertexSet;
      EdgeSet edgeSet;
      for( const Triangle& T : triangles )
        {
          edgeSet.insert( Edge( T.i(), T.j() ) );
          edgeSet.insert( Edge( T.j(), T.k() ) );
          edgeSet.insert( Edge( T.k(), T.i() ) );
          vertexSet.insert( T.i() );
          vertexSet.insert( T.j() );
          vertexSet.insert( T.k() );
        }
      edges_out.resize( edgeSet.size() );
      Size e = 0;
      for ( const Edge& edge : edgeSet )
        {
          edges_out.at(e) = edge;
          ++e;
        }
      return vertexSet.size();
    }

    /** 
     * Computes all the unoriented edges of the given polygonal faces.
     *
     * @note Method build() needs the unordered edges of the mesh.  If
     * you don't have them, call this first.
     *
     * @param[in] polygonal_faces the vector of input oriented polygonal faces.
     *
     * @param[out] edges_out the vector of all the unoriented edges of
     * the given triangles.
     *
     * @return the total number of different vertices (note that the
     * vertex numbering should be between 0 and this number minus
     * one).
     */
    static Size getUnorderedEdgesFromPolygonalFaces
    ( const std::vector<PolygonalFace>& polygonal_faces, std::vector< Edge >& edges_out );
    
    /**
     * Builds the half-edge data structures from the given triangles
     * and edges.  It keeps the numbering of vertices given in the
     * input \a triangles as well as the numbering of triangles in the
     * vector \a triangles.
     *
     * @note Parameter \a edges can be computed from \a triangles by calling
     * getUnorderedEdgesFromTriangles() before.
     *
     * @note Both \a triangles and \a edges are not needed after the call to build()
     * completes and may be destroyed. 
     *
     * @param[in] num_vertices the number of vertices (one more than the
     * maximal vertex index).
     *
     * @param[in] triangles the vector of input triangles.
     * @param[in] edges the vector of input unoriented edges.
     *
     * @return 'true' if everything went well, 'false' if their was
     * error in the given topology (for instance, three triangles
     * sharing an edge).
     */
    bool build( const Size num_vertices, 
                const std::vector<Triangle>& triangles,
                const std::vector<Edge>&     edges );

    /**
     * Builds the half-edge data structures from the given polygonal faces
     * and edges.  It keeps the numbering of vertices given in the
     * input \a polygonal_faces as well as the numbering of faces in the
     * vector \a polygonal_faces.
     *
     * @note Parameter \a edges can be computed from \a polygonal_faces by calling
     * getUnorderedEdgesFromPolygonalFaces() before.
     *
     * @note Both \a polygonal_faces and \a edges are not needed after the call to build()
     * completes and may be destroyed. 
     *
     * @param[in] num_vertices the number of vertices (one more than the
     * maximal vertex index).
     *
     * @param[in] polygonal_faces the vector of input polygonal_faces.
     * @param[in] edges the vector of input unoriented edges.
     *
     * @return 'true' if everything went well, 'false' if their was
     * error in the given topology (for instance, three triangles
     * sharing an edge).
     */
    bool build( const Size                        num_vertices, 
                const std::vector<PolygonalFace>& polygonal_faces,
                const std::vector<Edge>&          edges );

    /**
     * Builds the half-edge data structure from the given triangles.
     * It keeps the numbering of vertices given in the input \a
     * triangles as well as the numbering of triangles in the vector
     * \a triangles.
     *
     * @param[in] triangles the vector of input triangles.
     */
    bool build( const std::vector<Triangle>& triangles )
    {
      std::vector<Edge> edges;
      const int nbVtx = getUnorderedEdgesFromTriangles( triangles, edges );
      return build( nbVtx, triangles, edges );
    }

    /**
     * Builds the half-edge data structure from the given polygonal faces.
     * It keeps the numbering of vertices given in the input \a
     * polygonal_faces as well as the numbering of faces in the vector
     * \a polygonal_faces.
     *
     * @param[in] polygonal_faces the vector of input polygonal faces.
     */
    bool build( const std::vector<PolygonalFace>& polygonal_faces )
    {
      std::vector<Edge> edges;
      const int nbVtx = getUnorderedEdgesFromPolygonalFaces( polygonal_faces, edges );
      return build( nbVtx, polygonal_faces, edges );
    }

    /// Clears the data structure.
    void clear()
    {
      myHalfEdges.clear();
      myVertexHalfEdges.clear();
      myFaceHalfEdges.clear();
      myEdgeHalfEdges.clear();
      myArc2Index.clear();
    }

    /// @return the number of half edges in the structure.
    Size nbHalfEdges() const { return myHalfEdges.size(); }

    /// @return the number of vertices in the structure.
    Size nbVertices() const { return myVertexHalfEdges.size(); }

    /// @return the number of unoriented edges in the structure.
    Size nbEdges() const { return myEdgeHalfEdges.size(); }
    
    /// @return the number of faces in the structure.
    Size nbFaces() const { return myFaceHalfEdges.size(); }

    /// @return the euler characteristic of the corresponding combinatorial mesh.
    long Euler() const
    { return (long) nbVertices() - (long) nbEdges() + (long) nbFaces(); }
    
    /// @param i any valid half-edge index.
    /// @return the half-edge of index \a i.
    const HalfEdge& halfEdge( const Index i ) const { return myHalfEdges.at( i ); }

    /// @param i any valid half-edge index.
    /// @return the corresponding directed edge as an arc (v(opp(i)), v(i)).
    Arc arcFromHalfEdgeIndex( const Index i ) const
    {
      const HalfEdge& he = myHalfEdges[ i ];
      return std::make_pair( myHalfEdges[ he.opposite ].toVertex, he.toVertex );
    }

    /// @param i the vertex index of some vertex.
    /// @param j the vertex index of some other vertex.
    /// @return the index of the half-edge from \a i to \a j or HALF_EDGE_INVALID_INDEX if not found.
    Index halfEdgeIndexFromArc( const VertexIndex i, const VertexIndex j ) const
    { return halfEdgeIndexFromArc( std::make_pair( i, j ) ); }
    
    /// @param arc any directed edge (i,j)
    /// @return the index of the half-edge from \a i to \a j or HALF_EDGE_INVALID_INDEX if not found.
    Index halfEdgeIndexFromArc( const Arc& arc ) const
    {
      auto result = myArc2Index.find( arc );
      return ( result == myArc2Index.end() ) ? HALF_EDGE_INVALID_INDEX : result->second;
    }

    /// @param[in] vi any vertex index.
    /// @return the index of an half-edge originating from \a vi.
    Index halfEdgeIndexFromVertexIndex( const VertexIndex vi ) const
    { return myVertexHalfEdges[ vi ]; }

    /// @param[in] fi any face index.
    /// @return the index of an half-edge that borders the face \a fi.
    Index halfEdgeIndexFromFaceIndex( const FaceIndex fi ) const
    { return myFaceHalfEdges[ fi ]; }

    /// @param[in] ei any edge index.
    /// @return the index of an half-edge that borders the edge \a ei.
    Index halfEdgeIndexFromEdgeIndex( const EdgeIndex ei ) const
    { return myEdgeHalfEdges[ ei ]; }
    
    /// @param[in] vi any vertex index.
    /// @param[out] result the sequence of vertex neighbors of the given vertex \a vi (clockwise if triangles were given ccw).
    void getNeighboringVertices( const VertexIndex vi, VertexIndexRange& result ) const
    {
      result.clear();
      const Index start_hei = halfEdgeIndexFromVertexIndex( vi );
      Index hei = start_hei;
      do
        {
          const HalfEdge& he = halfEdge( hei );
          result.push_back( he.toVertex );
          hei = halfEdge( he.opposite ).next;
        }
      while ( hei != start_hei );
    }

    /// @param[in] vi any vertex index.
    /// @return the sequence of vertex neighbors of the given vertex \a vi (clockwise if triangles were given ccw).
    VertexIndexRange neighboringVertices( const VertexIndex vi ) const
    {
      VertexIndexRange result;
      getNeighboringVertices( vi, result );
      return result;
    }

    /// @param[in] vi any vertex index.
    /// @return the number of vertex neighbors to \a vi.
    Size nbNeighboringVertices( const Index vi ) const
    {
      Size nb = 0;
      const Index start_hei = halfEdgeIndexFromVertexIndex( vi );
      Index hei = start_hei;
      do
        {
          const HalfEdge& he = halfEdge( hei );
          nb++;
          hei = halfEdge( he.opposite ).next;
        }
      while ( hei != start_hei );
      return nb;
    }

    /// @param[in] vi any vertex index.
    /// @param[out] result the sequence of neighboring faces of the given vertex \a vi .
    void getNeighboringFaces( const VertexIndex vi, FaceIndexRange& result ) const
    {
      result.clear();
      const Index start_hei = halfEdgeIndexFromVertexIndex( vi );
      Index hei = start_hei;
      do
        {
          const HalfEdge& he = halfEdge( hei );
          if( HALF_EDGE_INVALID_INDEX != he.face ) result.push_back( he.face );
          hei = halfEdge( he.opposite ).next;
        }
      while ( hei != start_hei );
    }

    /// @param[in] vi any vertex index.
    /// @return the sequence of neighboring faces of the given vertex \a vi .
    FaceIndexRange neighboringFaces( const VertexIndex vi ) const
    {
      FaceIndexRange result;
      getNeighboringFaces( vi, result );
      return result;
    }

    /// @param[in] vi any vertex index.
    /// @return true if and only if the vertex \a vi lies on the boundary.
    bool isVertexBoundary( const VertexIndex vi ) const
    {
      return HALF_EDGE_INVALID_INDEX == halfEdge( myVertexHalfEdges[ vi ] ).face;
    }

    /// @return a sequence containing the indices of the vertices
    /// lying on the boundary.
    ///
    /// @note O(nb half-edges) operation.
    /// @note no particular order.
    VertexIndexRange boundaryVertices() const
    {
      VertexIndexRange result;
      // std::set< VertexIndex > result;
      for( Index hei = 0; hei < myHalfEdges.size(); ++hei )
        {
          const HalfEdge& he = halfEdge( hei );
          if( HALF_EDGE_INVALID_INDEX == he.face )
            result.push_back( he.toVertex );
        }
      return result;
    }

    /// @return a sequence containing the indices of half-edges  lying on the boundary.
    /// @note O(nb half-edges) operation.
    /// @note no particular order.
    std::vector< Index > boundaryHalfEdgeIndices() const
    {
      std::vector< Index > result;
      for( Index hei = 0; hei < myHalfEdges.size(); ++hei )
        {
          const HalfEdge& he = halfEdge( hei );
          if( HALF_EDGE_INVALID_INDEX == he.face )
            result.push_back( hei );
        }
      return result;
    }
    /// @return a sequence containing the arcs lying on the boundary.
    /// @note O(nb half-edges) operation.
    /// @note no particular order.
    std::vector< Arc > boundaryArcs() const
    {
        std::vector< Arc > result;
        for( Index hei = 0; hei < myHalfEdges.size(); ++hei )
          {
            const HalfEdge& he = halfEdge( hei );
            if( HALF_EDGE_INVALID_INDEX == he.face )
              result.push_back( arcFromHalfEdgeIndex( hei ) );
          }
        return result;
    }

    /// @param hei any valid half-edge index.
    /// @return the number of sides of the face that contains the half-edge \a hei.
    Size nbSides( Index hei ) const
    {
       ASSERT( hei != HALF_EDGE_INVALID_INDEX );
       Size nb = 0;
       const Index start = hei;
       do {
         hei = halfEdge( hei ).next;
         nb++;
       }
       while ( hei != start );
       return nb;
    }

    /// @param f any valid face index.
    /// @return the number of sides of the face \a f.
    Size nbSidesOfFace( const FaceIndex f ) const
    {
      return nbSides( halfEdgeIndexFromFaceIndex( f ) );
    }
    
    /// @param f any valid face index.
    /// @return the sequence of vertices of the face \a f.
    VertexIndexRange verticesOfFace( const FaceIndex f ) const
    {
      VertexIndexRange result;
      result.reserve( 3 );
      Index hei = halfEdgeIndexFromFaceIndex( f );
      const Index start = hei;
       do {
         const HalfEdge& he = halfEdge( hei );
         result.push_back( he.toVertex );
         hei = he.next;
       }
       while ( hei != start );
       return result;
    }

    // -------------------- Modification services -------------------------
  public:
    
    /// An edge is (topologically) flippable iff: (1) it does not lie
    /// on the boundary, (2) it is bordered by two triangles.
    ///
    /// @param hei any valid half-edge index.
    /// @return 'true' if the edge containing \a hei is topologically flippable.
    bool isFlippable( const Index hei ) const
    {
      ASSERT( hei != HALF_EDGE_INVALID_INDEX );
      const HalfEdge& he = halfEdge( hei );
      const Index    hei2 = he.opposite;
      // check if hei borders an infinite face.
      if ( he.face == HALF_EDGE_INVALID_INDEX ) return false; 
      // check if hei2 borders an infinite face.
      if ( halfEdge( hei2 ).face == HALF_EDGE_INVALID_INDEX ) return false; 
      // Checks that he1 and he2 border a triangle.
      return ( nbSides( hei ) == 3 ) && ( nbSides( hei2 ) == 3);
    }

    /// Tries to flip the edge containing \a hei.
    ///
    /// @param hei any valid half-edge index.
    ///
    /// @param update_arc2index (optimisation parameter), when 'true'
    /// updates everything consistently; when 'false' do not update
    /// myArc2Index map, which means you cannot get an half edge from
    /// two vertices afterwards. Use 'false' only if you know that you
    /// never use this mapping (e.g. no call to halfEdgeIndexFromArc)
    ///
    /// @pre the edge must be flippable, `isFlippable( hei ) == true`
    /// @see isFlippable
    void flip( const Index hei, bool update_arc2index = true )
    {
      const Index       i1 = hei;
      HalfEdge&        he1 = myHalfEdges[ i1 ];
      const Index       i2 = he1.opposite;
      HalfEdge&        he2 = myHalfEdges[ i2 ];
      const VertexIndex v2 = he1.toVertex;
      const VertexIndex v1 = he2.toVertex;
      const Index  i1_next = he1.next;
      const Index  i2_next = he2.next;
      HalfEdge&   he1_next = myHalfEdges[ i1_next ];
      HalfEdge&   he2_next = myHalfEdges[ i2_next ];
      const Index i1_next2 = he1_next.next;
      const Index i2_next2 = he2_next.next;
      myHalfEdges[ i1_next2 ].next = i2_next;
      myHalfEdges[ i2_next2 ].next = i1_next;
      he2_next.next  = i1;
      he1_next.next  = i2;
      he2_next.face  = he1.face;
      he1_next.face  = he2.face;
      he1.next       = i1_next2;
      he2.next       = i2_next2;
      he1.toVertex   = he1_next.toVertex;
      he2.toVertex   = he2_next.toVertex;
      // Reassign the mapping vertex v -> index of half edge starting from v
      // (JOL): must check before reassign for boundary vertices.
      if ( myVertexHalfEdges[ v1 ] == i1 ) myVertexHalfEdges[ v1 ] = i2_next;
      if ( myVertexHalfEdges[ v2 ] == i2 ) myVertexHalfEdges[ v2 ] = i1_next;
      // Reassign the mapping face f -> index of half edge contained in f
      myFaceHalfEdges[ he1.face ] = i1;
      myFaceHalfEdges[ he2.face ] = i2;
      // No need to reassign edge... it has just changed of vertices
      // but still is based on half-edges i1 and i2
      if ( update_arc2index ) 
        {
          myArc2Index.erase( Arc( v1, v2 ) );
          myArc2Index.erase( Arc( v2, v1 ) );
          const VertexIndex v2p = he1.toVertex;
          const VertexIndex v1p = he2.toVertex;
          myArc2Index[ Arc( v1p, v2p ) ] = i1;
          myArc2Index[ Arc( v2p, v1p ) ] = i2;
        }
    }
    
    /// Checks the whole half-edge structure for consistency.
    /// @return 'true' iff all checks have passed.
    bool isValid( bool check_arc2index = true ) const
    {
      bool ok = true;
      // Checks that opposite are correct
      for ( Index i = 0; i < nbHalfEdges(); i++ )
        {
          const Index j = myHalfEdges[ i ].opposite;
          if ( j == HALF_EDGE_INVALID_INDEX ) {
            trace.warning() << "[HalfEdgeDataStructure::isValid] "
                            << "half-edge " << i << " has invalid opposite half-edge." << std::endl;
            ok = false;
          }
          if ( myHalfEdges[ j ].opposite != i ) {
            trace.warning() << "[HalfEdgeDataStructure::isValid] "
                            << "half-edge " << i << " has opposite half-edge " << j
                            << " but the latter has opposite half-edge " << myHalfEdges[ j ].opposite << std::endl;
            ok = false;
          }
        }
      // Checks that vertices have a correct starting half-edge.
      for ( VertexIndex i = 0; i < nbVertices(); i++ )
        {
          const Index        j = myVertexHalfEdges[ i ];
          const Index     jopp = myHalfEdges[ j ].opposite;
          const VertexIndex ip = myHalfEdges[ jopp ].toVertex;
          if ( ip != i ) {
            trace.warning() << "[HalfEdgeDataStructure::isValid] "
                            << "vertex " << i << " is associated to half-edge " << j
                            << " but its opposite half-edge " << jopp << " points to vertex " << ip << std::endl;
            ok = false;
          }
        }
      // Checks that faces have a correct bordering half-edge.
      for ( FaceIndex f = 0; f < nbFaces(); f++ )
        {
          const Index        i = myFaceHalfEdges[ f ];
          if ( myHalfEdges[ i ].face != f ) {
            trace.warning() << "[HalfEdgeDataStructure::isValid] "
                            << "face " << f << " is associated to half-edge " << i
                            << " but its associated face is " << myHalfEdges[ i ].face << std::endl;
            ok = false;
          }
        }
      // Checks that following next half-edges turns around the same face.
      for ( FaceIndex f = 0; f < nbFaces(); f++ )
        {
          Index           i = myFaceHalfEdges[ f ];
          const Index start = i;
          do {
            const HalfEdge& he = halfEdge( i );
            if ( he.face != f ) {
              trace.warning() << "[HalfEdgeDataStructure::isValid] "
                              << "when turning around face " << f << ", half-edge " << i
                              << " is associated to face " << he.face << std::endl;
              ok = false;
            }
            i = he.next;
          }
          while ( i != start );          
        }
      // Checks that boundary vertices have specific associated half-edges.
      VertexIndexRange bdryV = boundaryVertices();
      for ( VertexIndex i : bdryV ) {
        const Index j = myVertexHalfEdges[ i ];
        if ( halfEdge( j ).face != HALF_EDGE_INVALID_INDEX ) {
          trace.warning() << "[HalfEdgeDataStructure::isValid] "
                          << "boundary vertex " << i << " is associated to the half-edge " << j 
                          << " that does not lie on the boundary but on face " << halfEdge( j ).face 
                          << std::endl;
          ok = false;
        }
      }

      // Checks that edges have a correct associated half-edge.
      if ( check_arc2index )
        {
          for ( auto arc2idx : myArc2Index )
            {
              const VertexIndex v1 = arc2idx.first.first;
              const VertexIndex v2 = arc2idx.first.second;
              const Index        i = arc2idx.second;
              if ( myHalfEdges[ i ].toVertex != v2 ) {
                trace.warning() << "[HalfEdgeDataStructure::isValid] "
                                << "arc (" << v1 << "," << v2 << ") is associated to half-edge " << i 
                                << " but it points to vertex " << myHalfEdges[ i ].toVertex << std::endl;
                ok = false;
              }
              const Index       i2 = myHalfEdges[ i ].opposite;
              if ( myHalfEdges[ i2 ].toVertex != v1 ) {
                trace.warning() << "[HalfEdgeDataStructure::isValid] "
                                << "arc (" << v1 << "," << v2 << ") is associated to half-edge " << i 
                                << " but its opposite half-edge " << i2 << " points to vertex " << myHalfEdges[ i2 ].toVertex 
                                << std::endl;
                ok = false;
              }
            }
        }
      return ok;
    }

  protected:

    /// Stores all the half-edges.
    std::vector< HalfEdge > myHalfEdges;
    /// Offsets into the 'halfedges' sequence, one per
    /// vertex. Associates to each vertex index the index of an half-edge
    /// originating from this vertex.
    std::vector< Index > myVertexHalfEdges;
    /// Offset into the 'halfedges' sequence, one per face. Associates
    /// to each face index the index of an half-edge lying on the
    /// border of this face.
    std::vector< Index > myFaceHalfEdges;
    /// Offset into the 'halfedges' sequence, one per edge (unordered
    /// pair of vertex indices). Associates to each edge index the
    /// index of an half-edge on this edge.
    std::vector< Index > myEdgeHalfEdges;
    /// The mapping between arcs to their half-edge index.
    Arc2Index myArc2Index;
    

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    // ------------------------- Hidden services ------------------------------
  protected:

    static
    FaceIndex arc2FaceIndex( const Arc2FaceIndex& de2fi,
                             VertexIndex vi, VertexIndex vj )
    {
      ASSERT( !de2fi.empty() );

      Arc2FaceIndex::const_iterator it = de2fi.find( Arc( vi, vj ) );
      // If no such directed edge exists, then there's no such face in the mesh.
      // The edge must be a boundary edge.
      // In this case, the reverse orientation edge must have a face.
      if( it == de2fi.end() )
        {
          ASSERT( de2fi.find( Arc( vj, vi ) ) != de2fi.end() );
          return HALF_EDGE_INVALID_INDEX;
        }
      return it->second;
    }
    
  }; // end of class HalfEdgeDataStructure


  /**
   * Overloads 'operator<<' for displaying objects of class 'HalfEdgeDataStructure'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'HalfEdgeDataStructure' to write.
   * @return the output stream after the writing.
   */
  std::ostream&
  operator<< ( std::ostream & out, const HalfEdgeDataStructure & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/HalfEdgeDataStructure.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined HalfEdgeDataStructure_h

#undef HalfEdgeDataStructure_RECURSES
#endif // else defined(HalfEdgeDataStructure_RECURSES)
