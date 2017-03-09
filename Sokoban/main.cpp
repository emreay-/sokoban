//
//  main.cpp
//  Sokoban
//
//  Created by Emre Ay on 05/03/2017.
//  
//
#include <iostream>
#include <algorithm>
#include "astar.h"

int main(int argc, const char * argv[]) {
    sokoban::Verbose verbose = sokoban::Verbose::NONE;
    gridmap::GridMap game_map(verbose);
    astar::Astar path_finder(verbose);
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
        if (number_of_player_on_goal != 0) { std::cout << astar::kPlayerOnGoalOutput; std::cerr << std::endl; } // end of game
        else { std::cout << astar::kNoPathOutput << std::endl; std::cerr << std::endl; }
    } else if (number_of_player != 0) {
        // if a not-on-the-goal player is found, search the map for goals
        int number_of_goals = game_map.SearchMap(sokoban::kGoal, goal_coordinate);
        if (number_of_goals != 0) {
            std::map< std::string, gridmap::Coordinate > map_path_to_player;
            std::vector< std::string > output;
            for (auto player : player_coordinate) {
                for (auto goal : goal_coordinate) {
                    std::string temp = path_finder.FindPath(game_map, player, goal);
                    if (temp != astar::kNoPathOutput) {
                        output.push_back(temp);
                        map_path_to_player[temp] = player;
                    }
                }
            }
            if (output.empty()) {
                std::cout << astar::kNoPathOutput << std::endl;
                std::cerr << std::endl;
            } else {
                std::sort(output.begin(), output.end(), [] (const std::string& s1, const std::string& s2) {
                                                            return s1.length() < s2.length(); });
                if (verbose == sokoban::Verbose::INTERACTIVE) {
                    path_finder.Visualize(output.front(), map_path_to_player[output.front()], game_map);
                }
                std::cout << output.front() << std::endl;
                std::cerr << std::endl;
            }
        } else {
            std::cout << astar::kNoPathOutput << std::endl;
            std::cerr << std::endl;
        } 
    }
    return 0;
}
