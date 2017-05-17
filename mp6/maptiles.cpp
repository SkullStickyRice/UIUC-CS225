/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
	MosaicCanvas *newCanvas = new MosaicCanvas(theSource.getRows(),theSource.getColumns());

	vector< Point<3> > Tiles;
	map< Point<3>, TileImage > TileImageMap;

	for(size_t i = 0; i < theTiles.size(); i++) {
		RGBAPixel avgcolor = theTiles[i].getAverageColor();
		Point<3> pt (avgcolor.red, avgcolor.green, avgcolor.blue);
		TileImageMap[pt] = theTiles[i];
		Tiles.push_back(pt);		
	}
	
	KDTree<3> tree(Tiles);

	for(int i = 0; i < theSource.getRows(); i++) {
		for(int j = 0; j < theSource.getColumns(); j++) {
			RGBAPixel regcolor = theSource.getRegionColor(i,j);
			Point<3> regpt (regcolor.red, regcolor.green, regcolor.blue);
			Point<3> clspt = tree.findNearestNeighbor(regpt);
			newCanvas->setTile(i,j,TileImageMap[clspt]);
		}
	}	

    return newCanvas;
}

