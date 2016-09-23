
Algorithm explaination:

COPY PASTED FROM MY_GRID.CC 
This algorithm finds the paths for each route one at a time. It starts with a BFS on the 
first connection and retraces back from the sink using Lee's numbers. After the path is found, 
the map resets all Lees numbers to 0 and goes onto the next route. 

Pre-BFS: In order to make sure that paths with no intersections have paths found first, two 
vectors are used to organize the route numbers.

BFS: Using a border vector containing all the outside points, the program loops until the sink 
is found. If the border vector is empty and the sink hasn't been found, it means that the route 
has an impossible path.

Retrace: The algorithm for retrace first starts by using the step variable to determine the 
direction to go. Every time the retrace changes direcion, a path segment is added to a temporary 
path segment. Because the retrace moves backwards towards the source, the sources and sinks of 
path segments are flipped. When a path is found, the path segments are pushed into a correct 
path variable. The path is then pushed into the private my_grid vector paths. The neighbors flags 
exists to tell the program that the sink and source are next to each other. We also have a vector 
final paths so that the paths are in the conological order and not the order that was used to 
make sure the non intersecting paths went first.


Known Bugs:

- When map dimentions are NxM where N and M are different, the program terminates with an uncaught 
exeption of out_of_range vector.
- Print map only works if map dimentions are the same. Otherwise, it throws an out_of_range error 
and crashes the program. 
- Blockers cannot be place on x = 0 or y = 0. 

Grid Orientation: 
See Raw version of README2.md
_________________________ y-axis
|
|
|
|
|
|
|
|
|
|
|
x-axis

^
|	blocker width
v

<---->	blocker height
