
Readme for kdtrees:

Our implemenation of the Kdtree works and is drawn in glut accurately.  We have added functionality so that one can switch between test cases.  Because our grid proportions are different we had to modify the functions. To switch between cases use 1-4. The diagonal line case (number 4) works best with n < 100, whereas the grid case (number 3) works best at certain set of n values. We made it so the nvalue for the grid test case is always 200 because it works best with the scaling to our alternate window dimensions. Also, the way that we draw the Mondrian style picture from the Kdtree could be more efficient: using two vectors to separately store the segments to be drawn and the squares to color could proably be streamlined into using one vector, which would use less space.  


The project includes:

geom.h -> class header  file for the kdtree, point2D and helper classes
geom.cpp -> class file for the KD tree, includes implementation to build the Kd tree
kd.cpp -> includes the main function and all glut implementation 
makefile -> a pretty basic makefile to streamline compiling 

