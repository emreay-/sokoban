//
//  sokoban.h
//  Sokoban
//
//  Created by Emre Ay on 05/03/2017.
//  Copyright © 2017 Emre Ay. All rights reserved.
//

#ifndef sokoban_h
#define sokoban_h
namespace sokoban {

    enum Verbose {
        NONE = 0,
        FEW = 1,
        INTERACTIVE = 2        
    };
    const char kFreeSpace = ' ';
    const char kWall = '#';
    const char kGoal = '.';
    const char kPlayer = '@';
    const char kPlayerOnGoal = '+';
    const char kBox = '$';
    const char kBoxOnGoal = '*';
    const char kShowPath = ',';
} /* namespace sokoban */

#endif /* sokoban_h */
