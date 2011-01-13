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

/**
 * @file DSS.cpp
 * @ingroup Examples
 * @author Isabelle Sivignon (\c isabelle.sivignon@gipsa-lab.grenoble-inp.fr )
 * gipsa-lab Grenoble Images Parole Signal Automatique (CNRS, UMR 5216), CNRS, France
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France

 * @date 2010/11/30
 *
 * An example file named DSS.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
///////////////////////////////////////////////////////////////////////////////

#include "DGtal/geometry/2d/ArithmeticalDSS.h"
#include "DGtal/geometry/2d/FreemanChain.h"
#include "DGtal/base/BasicTypes.h"
#include "DGtal/geometry/2d/GreedyDecomposition.h"
#include "DGtal/io/DGtalBoard.h"
#include "DGtal/helpers/StdDefs.h"

using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
//TRIS
//redondance avec greedy-dss-decomposition
/*
  typedef FreemanChain<Space::Integer> ContourType; 
  
  // Construction of a contour defined as a Freeman chain  code
  std::stringstream ss (stringstream::in | stringstream::out);
  ss << "0 0 00010010033030" << endl;
  
  ContourType theContour(ss);
  
  // Basic tests
  trace.info()<< "Freeman chain set to " << theContour.chain << endl; 
  trace.info() << "isClosed():" << theContour.isClosed()<< endl;
  
  // Draw the contour and save the image
  DGtalBoard board;
  board << theContour;
  board.saveSVG("exampleDSS-1.svg");
  board.saveEPS("exampleDSS-1.eps");
  board.saveFIG("exampleDSS-1.fig");
  
  // Get and display the list of contour points
  vector<Point> ContourPoints; 
  theContour.getContourPoints(theContour, ContourPoints);
  trace.info() << "List of points: ";
  for (unsigned int i =0; i < ContourPoints.size(); i++){
    trace.info()<< "(" << ContourPoints.at(i).at(0) << "," << ContourPoints.at(i).at(1) << ")";  
  }
  trace.info() << endl;
  
  // Recognition of a DSS beginning at the first point of the contour
  trace.beginBlock("Recognition of a DS along the contour");
  trace.info() << "Initialisation of a DSS with the first two points of the contour" << endl;
  ContourType::ConstIterator iter = theContour.begin();
  
  // Initialisation with the first two points
  Point a = iter.get(); //or a = *(iter)
  ++iter;
  Point b = iter.get(); 
  DSS4 aDSS(a,b);
  ++iter;
  while (aDSS.addFront(iter.get()) && iter != theContour.end())
    ++iter;
  trace.info() << "Last point added:" << iter.getPosition()-1 << endl;
  trace.endBlock();

  
  // Recognition of a DSS beginning at the first point of the contour
  // trace.beginBlock("Recognition of a DSS along the contour");
  // trace.info() << "Initialisation of a DSS with the first two contour points" << endl;
  // DSS4 aDSS(ContourPoints[0],ContourPoints[1]);
  // trace.info() << "Add the points iteratively while the union is a DSS" << endl;
  // int i = 2;
  // while (aDSS.addFront(ContourPoints[i]) && i<ContourPoints.size())
  //   i++;
  // trace.info() << "Last point added:" << i-1 << endl;
  // trace.endBlock();
  
  // Draw the DSS as its bounding box
  board << SetMode(aDSS.styleName(), "BoundingBox") << aDSS;
  board.saveSVG("exampleDSS-2.svg");
  board.saveEPS("exampleDSS-2.eps");
  board.saveFIG("exampleDSS-2.fig");
  
  // Clear the board 
  board.clear();
  
  // Decomposition of the contour into DSSs
  trace.beginBlock("Decomposition of the contour into DSSs");
  GreedyDecomposition<ContourType,DSS4> theDecomposition(theContour);
  
  // Draw the contour and set the bounding box mode for DSS drawing
  board << theContour << SetMode(aDSS.styleName(), "BoundingBox");
  
  // Iterate over the decomposition DSSs
  GreedyDecomposition<ContourType,DSS4>::ConstIterator it = 
    theDecomposition.begin();
  for ( ; it != theDecomposition.end(); ++it) {
    trace.info() << "segment number " << it.getPosition() << std::endl;
    DSS4 segment(*it); 
    // Display and draw the DSS on the board
    trace.info() << segment << std::endl; 
    board << segment; // draw each segment
  } 
  trace.endBlock();
 
  board.saveSVG("exampleDSS-3.svg");
  board.saveEPS("exampleDSS-3.eps");
  board.saveFIG("exampleDSS-3.fig");
*/
  

	/////////////////////////// DSS4 //////////////////////////////////
	{
		// Input points
		std::vector<Point> contour;
		contour.push_back(Point(0,0));
		contour.push_back(Point(1,0));
		contour.push_back(Point(1,1));
		contour.push_back(Point(2,1));
		contour.push_back(Point(3,1));
		contour.push_back(Point(3,2));
		contour.push_back(Point(4,2));
		contour.push_back(Point(5,2));
		contour.push_back(Point(6,2));
		contour.push_back(Point(6,3));
		contour.push_back(Point(6,4));

		
		// Add points while it is possible
		DSS4 theDSS4(contour.at(0));		
		unsigned int i = 1;
		while ( (i<contour.size())
					&&(theDSS4.extend(contour.at(i))) ) {
			i++;
		}

		// Output parameters
		cout << theDSS4 << endl;

		// Draw the grid
		DGtalBoard board;
	
		Domain domain( Point(0,0), Point(10,10) );
		board << SetMode(domain.styleName(), "Grid")
					<< domain;		

		// Draw the points of the DSS
		board << SetMode("PointVector", "Grid")
			    << SetMode(theDSS4.styleName(), "Points") 
					<< theDSS4;
		// Draw the bounding box
		board << SetMode(theDSS4.styleName(), "BoundingBox") 
					<< theDSS4;
	
		board.saveSVG("DSS4.svg");
	}

	////////////////////// DSS8 ///////////////////////////////
	{

		// Input points
		std::vector<Point> boundary;
		boundary.push_back(Point(0,0));
		boundary.push_back(Point(1,1));
		boundary.push_back(Point(2,1));
		boundary.push_back(Point(3,2));
		boundary.push_back(Point(4,2));
		boundary.push_back(Point(5,2));
		boundary.push_back(Point(6,3));
		boundary.push_back(Point(6,4));

		// Add points while it is possible
		DSS8 theDSS8(boundary.at(0));		
		unsigned int i = 1;
		while ( (i<boundary.size())
					&& (theDSS8.extend(boundary.at(i))) ) {
			i++;
		}
		// Output parameters
		cout << theDSS8 << endl;

		//Draw the pixels
		DGtalBoard board;
		Domain domain( Point(0,0), Point(10,10) );
		board << SetMode(domain.styleName(), "Paving")
					<< domain;		
	
		//Draw the points of the DSS
		board << SetMode("PointVector", "Both");
		board << SetMode(theDSS8.styleName(), "Points") 
					<< theDSS8;

		//Draw the bounding box of the DSS
		board << SetMode(theDSS8.styleName(), "BoundingBox") 
					<< theDSS8;
		
		
		board.saveSVG("DSS8.svg");

	}

  return 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////