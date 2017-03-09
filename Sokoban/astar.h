//
//  astar.h
//  Sokoban
//
//  Created by Emre Ay on 05/03/2017.
//  Copyright © 2017 Emre Ay. All rights reserved.
//

#ifndef astar_h
#define astar_h

#include <queue>
#include <string>
#include "gridmap.h"

namespace astar {
    // type to use in priority queue. First element priority, second is location
    typedef std::pair< int, gridmap::Coordinate > Node;
    // priority queueu, sorted from lowest to highest
    typedef std::priority_queue< Node, std::vector<Node>, std::greater<Node> > NodeQueue;
    // map for g_cost, similar to Node but reverse
    typedef std::map< gridmap::Coordinate, int > CostType;
    // to map parent and child nodes
    typedef std::map< gridmap::Coordinate, gridmap::Coordinate > LinkType;
    const int movement_cost = 5;
    const int hcost_multiplier = 10;
    const std::string kPlayerOnGoalOutput = "";
    const std::string kNoPathOutput = "no path";
    
    class Astar {
    public:
        Astar(sokoban::Verbose verbose);
        ~Astar();
        std::string FindPath(gridmap::GridMap& map_input, gridmap::Coordinate player, gridmap::Coordinate target);
        void Visualize(std::string path_to_visualize, gridmap::Coordinate start, gridmap::GridMap& grid_map);
    private:
        // to map char actions to directions i.e. {-1,0} to 'U'
        std::map< const gridmap::Coordinate, std::string > actions_;
        gridmap::Coordinate SubtractCoordinates(gridmap::Coordinate c1, gridmap::Coordinate c2);
        std::string RecoverPath(LinkType link, const gridmap::Coordinate start, const gridmap::Coordinate target);
        sokoban::Verbose verbose_;
    };
    
} /* namespace astar */

#endif /* astar_h */
