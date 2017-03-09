# Sokoban Pathfind Exercise

In this exercise a map, a player and targets are given and it is asked for directions of a path such as up, down, left, right. 

The details can be found in https://kth.kattis.com/problems/kth.ai.sokobanpathfinding. (For some reason which I suspect to be syntax related, my implementation did not pass all the tests on kattis. )

When the code is build and the executable run with a map file as;

```
  ./Sokoban < test_maps/wall.txt
```
The output will be the path with directions according to the player's initial point (i.e. "U R R R U"...). If the verbose level is interactive, the map and path would also be shown. 

# Tests
I tested the code with many different maps and scenarios. 

**Input**
```
#################
#               # 
#       #       # 
#   @   #   .   # 
#       #       #
#               #
#################
```
**Output**
```
0	#################
1	#      ,,,,,,   # 
2	#      ,#   ,   # 
3	#   @,,,#   ,   # 
4	#       #       #
5	#               #
6	#################      
R R R U U R R R R R D D
```
In case of no goals or no players exist in the map, it returns `no path`. If there are multiple players and/or multiple goals, the returns the shortest path if there exists one. For example;

```
##################################################
#                                       #        #
#                   .                    #       #
#                                         #      #
# #                     #                  #     #
#{ #                    #                     .  #
# #                     #                    #   #
#               ######  #                     #  #
#       ######  #    #  #                      # #
#       #    #  #   .#  #                       ##
#       #    #  ## ###  #                        #
#       #    #          #                        #
#       #    ############                        #
#       #                                        #
#       #                                        #
#      # #                            @          #
#       @                                        #
#                                                #
#                                                #
##################################################
```
There are two players and three goals in the upper map, the selected path is the shortes one.
```
0	##################################################
1	#                                       #        #
2	#                   .                    #       #
3	#                                         #      #
4	# #                     #                  #     #
5	#{ #                    #             ,,,,,,,,,  #
6	# #                     #             ,      #   #
7	#               ######  #             ,       #  #
8	#       ######  #    #  #             ,        # #
9	#       #    #  #   .#  #             ,         ##
10	#       #    #  ## ###  #             ,          #
11	#       #    #          #             ,          #
12	#       #    ############             ,          #
13	#       #                             ,          #
14	#       #                             ,          #
15	#      # #                            @          #
16	#       @                                        #
17	#                                                #
18	#                                                #
19	##################################################
U U U U U U U U U U R R R R R R R R
```
