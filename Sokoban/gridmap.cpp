//
//  gridmap.cpp
//  Sokoban
//
//  Created by Emre Ay on 05/03/2017.
//

#include <stdio.h>
#include <iostream>
#include "gridmap.h"

namespace gridmap {
    
    int GridMap::SearchMap(const char char2find, CoordinateVector &locations) {
        int number_of_found = 0;
        const size_t map_line_number = this->map_.size();
        for (size_t line = 0; line < map_line_number; line++) {
            std::vector<char>::iterator it;
            std::vector<char> temp_line = this->map_[line];
            //search for char2find in the temporary line
            it = find(temp_line.begin(), temp_line.end(), char2find);
            int count = 0;
            //while char2find is found
            while (it != temp_line.end()) {
                count++;
                int found_column = int(distance(temp_line.begin(),it));
                locations.push_back(std::make_pair(line,found_column));
                
//                if (sokoban::verbose) {
//                    std::cout << "Char " << char2find <<" found at " << line << "th line " << found_column << "th char" << std::endl;
//                }
                //increase the offset to find the next instance of char2find
                it++;
                //search for the next instance of char2find in that line
                it = find(it, temp_line.end(), char2find);
            }
            
            number_of_found += count;
        }
        
        return number_of_found;
    } /* function GridMap::SearchMap */
    
    CoordinateVector GridMap::GetNeighbours(Coordinate location) {
        int current_line = location.first;
        int current_column = location.second;
        CoordinateVector neighbours;
        
        for (Coordinate direction : kDirections) {
            int line_direction = direction.first;
            int column_direction = direction.second;
            int line_of_neighbour = current_line + line_direction;
            int column_of_neighbour = current_column + column_direction;
            if(this->map_[line_of_neighbour][column_of_neighbour] == sokoban::kFreeSpace ||
               this->map_[line_of_neighbour][column_of_neighbour] == sokoban::kGoal) {
                neighbours.push_back(std::make_pair(line_of_neighbour,column_of_neighbour));
            }
        }
        return neighbours;
    } /* function GridMap::GetNeighbours */
    
    int GridMap::ManhattanDistance(Coordinate c1, Coordinate c2) {
        return abs(c1.first - c2.first) + abs(c1.second - c2.second);
    }
    
    void GridMap::AddLineToMap(std::vector<char> line_input) {
        this->map_.push_back(line_input);
    }
    
    
    
    
}// namespace gridmap
