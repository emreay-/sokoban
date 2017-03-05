//
//  gridmap.h
//  Sokoban
//
//  Created by Emre Ay on 05/03/2017.
//  Copyright © 2017 Emre Ay. All rights reserved.
//

#ifndef gridmap_h
#define gridmap_h

#include <utility> //for std::pair
#include <vector>

namespace gridmap {
    typedef std::pair<int,int> Coordinate;
    typedef std::vector< std::vector<char> > MapType;
    typedef std::vector< Coordinate > CoordinateVector;
    
    class GridMap{
    public:
        GridMap();
        int SearchMap(const char char2find, CoordinateVector& locations);
        CoordinateVector GetNeighbours(Coordinate location);
        int ManhattanDistance(Coordinate c1, Coordinate c2);
        Coordinate SubtractCoordinates(Coordinate c1, Coordinate c2);

    private:
        MapType map_;

    }; // class GridMap

} // namespace gridmap




#endif /* gridmap_h */
