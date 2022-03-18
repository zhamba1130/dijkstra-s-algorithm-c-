# dijkstras-algorithm-cpp
    Implement Dijkstra's algorithm by min heap data structure

# 1  Problem Description 
    The poison maze is a square room full of poisonous liquid, every step you go, you get hurt.  The maze can be described as an N×N grid.  For better understanding of the input data, we define +xdirection isRIGHT and +y direction is DOWN. Depending on the density of poison, walking on different grid points results in different amounts of damage. You start at point (1,1) (top left), and there is an exit at the diagonal corner (N, N) (bottom right).  The damage at each grid point is given.  You need to escape from this maze with as little damage as possible. In this problem, the main target is to implement a search algorithm to find a path from (1,1) to (N, N) with the smallest total damage.
    
# 3  Input
    There will be 10 test data in 3 different sizes.The first line of each input file contains an integer N, the maze will be a N×N Grid.  Then there will be N lines following, every lines contain N integers.  For the i-th line, the j-th number denote the damage of the point (i, j) when you walk on it

# 5  Output
    For each test, please output a file with 2 lines: In the first line, please output 2 integer C, S. C is the smallest possible damage (length of theshortest path), and S is the number of steps of this path. In the second line, please output a string of S−1 characters, consist of 4 characters: { ’U’, ’D’, ’L’, ’R’} (denoting “up”, “down”, “left”, “right”) describing every step from (1,1) to (N, N).

# 6  Samples
    Sample Input:
          3
          1 1 4 
          5 1 4 
          8 1 0
          
    Sample Output:
          4 5RDDR
