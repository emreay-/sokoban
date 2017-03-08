//
//  main.cpp
//  Sokoban
//
//  Created by Emre Ay on 05/03/2017.
//  
//
#include <iostream>
#include "astar.h"

int main(int argc, const char * argv[]) {
    gridmap::GridMap game_map(sokoban::Verbose::NONE);
    astar::Astar path_finder(sokoban::Verbose::INTERACTIVE);
    std::string input_map_line;
    std::vector< char > temp_map_line;
    
    // reading from std input and passing it to the map object
    while(getline(std::cin, input_map_line))
    {
        for (size_t i = 0; i < input_map_line.size(); i++) temp_map_line.push_back(input_map_line[i]);
        game_map.AddLineToMap(temp_map_line);
        temp_map_line.clear();
    }
    // contianer coord. vectors to be used in map search for their symbols (i.e player, goal, player on goal)
    gridmap::CoordinateVector player_coordinate, goal_coordinate, on_goal_coordinate;
    // search map for player, return the number of instances and push their coordinates to the input vector if any
    int number_of_player = game_map.SearchMap(sokoban::kPlayer, player_coordinate);
    if (number_of_player == 0) {
        int number_of_player_on_goal = game_map.SearchMap(sokoban::kPlayerOnGoal, on_goal_coordinate);
        if (number_of_player_on_goal != 0) std::cout << astar::kPlayerOnGoalOutput; // end of game
        else std::cout << astar::kNoPathOutput << std::endl;
    } else if (number_of_player == 1) {
        // if a not-on-the-goal player is found, search the map for goals
        int number_of_goals = game_map.SearchMap(sokoban::kGoal, goal_coordinate);
        if (number_of_goals != 0) {
            gridmap::Coordinate player = player_coordinate[0];
            std::string output = "";
            for (auto goal : goal_coordinate) {
                output = path_finder.FindPath(game_map, player, goal);
                if (output != astar::kNoPathOutput) {
                    break;
                }
            }
            std::cout << output << std::endl;
        } else {
            std::cout << astar::kNoPathOutput << std::endl;
        }
    }
    return 0;
}
