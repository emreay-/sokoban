//
//  astar.cpp
//  Sokoban
//
//  Created by Emre Ay on 05/03/2017.
//  Copyright © 2017 Emre Ay. All rights reserved.
//

#include <iostream>
#include "astar.h"

namespace astar {
    Astar::Astar(sokoban::Verbose verbose) : verbose_(verbose)  {
        actions_[gridmap::kDirections[0]] = "U"; // up
        actions_[gridmap::kDirections[1]] = "L"; // left
        actions_[gridmap::kDirections[2]] = "D"; // down
        actions_[gridmap::kDirections[3]] = "R"; // right
    };
    Astar::~Astar() {};
    
    gridmap::Coordinate Astar::SubtractCoordinates(gridmap::Coordinate c1, gridmap::Coordinate c2) {
        int line1 = c1.first;
        int column1 = c1.second;
        int line2 = c2.first;
        int column2 = c2.second;
        return std::make_pair(line1 - line2, column1 - column2);
    }
    
    std::string Astar::RecoverPath(LinkType parent, const gridmap::Coordinate start, const gridmap::Coordinate target) {
        std::string action_output = "";
        gridmap::Coordinate current = target;
        while (current != start) {
            gridmap::Coordinate previous = parent[current];
            gridmap::Coordinate difference = SubtractCoordinates(current, previous);
            action_output += actions_[difference];
            action_output += " ";
            current = previous;
        }
        reverse(action_output.begin(), action_output.end());
        action_output.erase(0,1);        
        //action_output += '\n';
        
        return action_output;
    }
    
    std::string Astar::FindPath(gridmap::GridMap &map_input, gridmap::Coordinate player, gridmap::Coordinate target) {
        std::string action_output = "";
        NodeQueue check_list;
        CostType gcost;
        LinkType parent;
        gridmap::Coordinate start = player;
        // overall cost of start node is zero
        check_list.emplace(0,start);
        gcost[start] = 0;
        // no parent for start node
        parent[start] = start;
        gridmap::Coordinate previous = start;
        bool no_path = false;
        
        while (!check_list.empty()) {
            // get the node with the smallest cost (check list is a priority queue sorted from low to high in cost)
            gridmap::Coordinate current = check_list.top().second;
            // remove the selected node (i.e. with highest priority = lowest cost)
            check_list.pop();
            
            //if (sokoban::verbose) std::cout << "Current node:\t" << current.first << "," << current.second << std::endl;
            if (current == target) {
                break;
            } else {
                gridmap::CoordinateVector neighbours = map_input.GetNeighbours(current);
                if (!neighbours.empty()) {
                    for (gridmap::Coordinate neighbour : neighbours) {
                        int next_gcost = movement_cost + gcost[current];
                        if (gcost.count(neighbour) == 0 || next_gcost < gcost[neighbour]) {
                            gcost[neighbour] = next_gcost;
                            int hcost = map_input.ManhattanDistance(neighbour, target) * hcost_multiplier;
                            int fcost = next_gcost + hcost;
                            check_list.emplace(fcost,neighbour);
                            parent[neighbour] = current;
                        }
                            
                    }
                        
                }
            }
        } /* end while !checklist.empty() */
        
        if (check_list.empty()) {
            no_path = true;
            action_output = kNoPathOutput;
        }
        if (!no_path) {
            action_output = RecoverPath(parent, start, target);
        }
        
        return action_output;
    }
    
    void Astar::Visualize(std::string path_to_visualize, gridmap::Coordinate start, gridmap::GridMap& grid_map) {
        gridmap::MapType map_to_show_path = grid_map.getMap();
        gridmap::Coordinate current;
        gridmap::Coordinate previous = start;
        for (size_t i = 0; i < path_to_visualize.length(); i++) {
            char c = path_to_visualize[i];
            current = previous;
            switch (c) {
                case 'D':
                    current.first++;
                    break;
                    
                case 'U':
                    current.first--;
                    break;
                    
                case 'L':
                    current.second--;
                    break;
                    
                case 'R':
                    current.second++;
                    break;
                    
                default:
                    break;
            }
            map_to_show_path[current.first][current.second] = sokoban::kShowPath;
            previous = current;
        }
        
        for (size_t line = 0; line < map_to_show_path.size(); line++) {
            std::cout << line << "\t";
            for (size_t col = 0; col < map_to_show_path[line].size(); col++) {
                std::cout << map_to_show_path[line][col];
            }
            std::cout << std::endl;
        }

    }
} /* namespace astar */
