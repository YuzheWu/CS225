/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     vector<Point<3>> tileColors;
     map<Point<3>, TileImage*> colorToTile;
     for (size_t i = 0; i<theTiles.size(); i++) {
         Point<3> avgColor = convertToXYZ(theTiles[i].getAverageColor());
         tileColors.push_back(avgColor);
         colorToTile[avgColor] = &(theTiles[i]);
     }

     KDTree<3> colorTree(tileColors);
     MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
     Point<3> currColor, nearestColor;
     for (int row = 0; row<theSource.getRows(); row++) {
         for (int col = 0; col<theSource.getColumns(); col++) {
             currColor = convertToXYZ(theSource.getRegionColor(row, col));
             nearestColor = colorTree.findNearestNeighbor(currColor);
             canvas->setTile(row, col, colorToTile[nearestColor]);
         }
     }

    return canvas;
}
