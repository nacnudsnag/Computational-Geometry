README for Motion Planning

Authors: 
	Dustin Hines, dhines@bowdoin.edu
	Duncan Gans, dgans@bowdoin.edu
	

Includes:
	-geom.cpp: file for geometric functions used to compute visibility graphy
	-geom.h
	-motion.cpp: main file 
	-mouse1.cpp
	-mouse2.cpp
	
Instructions:

When running the motion executable, press 'S' and click twice to place the start and end points.  'V' will draw the visibility graph
and 'D' will compute the shortest path.  To draw a new obstacle course, press 'Z' and then 'C' for each new polygon.

Known Issues:

  - Will seg fault is there is a high number of intersecting polygons
  - In our dijkstra implementation one of our two methods uses a priority queue. Occasionally the priority queue 
    method crashes at seemingly random situations. For the most part is still works fine. However, we decided to
    comment out the priority queue method and use the other method to avoid these errors. If curious about the 
    priority queue method, it can be appropriately commented in.



	
	
