<h1 align="center">CS F364 Assignment 1</h1>

#### Group members:

- T V Chandra Vamsi (2019A7PS0033H)
- Ruban S (2019A7PS0064H)
- Sathvik B (2019A7PS1200H)
- Kaustubh Bhanj (2019A7PS0009H)

<br>

<h2>Problem Statement</h2>

Consider a set of line segments on a plane. The aim of the problem is to compute all the intersection points of these line segments and report them.

<br>

<h2>The Sweep Line Algorithm</h2>

The Sweep Line Algorithm uses two data structures, namely, the **Event Queue** and the **Status** data structure. The algorithm mentions that a _sweep line_, which is a horizontal line of the form $y=c$, will be swept from top to bottom. Whenever the sweep line encounters an event point, the data structures are updated accordingly to keep track of line segments and points, and to count and store intersection points. This algorithm runs more efficiently than the brute-force approach with the help of the data structures, which will be briefed upon in the [Implementation Details](#implementation).

<br>

<h2 id="implementation">Implementation Details</h2>

We have used AVL Tree to implement the **Event Queue** and the **Status** data structures.

<h3>Event Queue</h3>

The Event Queue is a balanced binary search tree, where each node in the tree stores a point, which is endpoint of a line segment, or an intersection point. Initially the Event Queue contains all the endpoints of every line segment, in decreasing order of their $y$-coordinate, and increasing order of their $x$-coordinate if two or more points share the same $y$-coordinate. A point is removed from the Event Queue once the sweep line passes through it. A point is added to the Event Queue if it is not encountered by the sweep line yet, and is found to be an intersection point.

<h3>Status</h3>

The Status data structure is a balanced binary search tree, where each node in the tree stores a line segment, which in turn, is a structure containing two points - the endpoints of the line segment. If a sweep line passes through multiple line segments, the status stores the line segments in the order of $x$-coordinate at which the line segment intersects the sweep line. Initially, the status is empty. A line segment is inserted to the status whenever the sweep line passes through the upper point of the line segment, and is deleted from the data structure whenever the sweep line passes through the lower point of the line segment. Whenever the sweep line passes through an intersection point, all the lines containing the intersection point get reversed after the sweep line passes through the intersection point.

<br>

<h2>Complexity Analysis</h2>

In the algorithm, the `FindIntersections()` function takes the set of all line segments as inputs, adds each point of every line segment to the Event Queue `Q`. For every point in `Q`, `HandleEventPoint()` function is called. Since `Q` will contain every point of every line segment, as well as the intersection points detected, `HandleEventPoint()` will be called $2n+k$ times, where $n$ is the number of line segments and $k$ is the number of intersection points.

`HandleEventPoint()` contains insert, update and delete operations, all of which take $O(log(n))$ time since they are operations performed on a balanced binary search tree. `HandleEventPoint()` may or may not call `FindNewEvent()`, but `FindNewEvent()` takes $O(1)$ time.

Therefore, `FindIntersections()` is expected to take $O((2n+k)log(n))$ time, or $O((n+k)log(n))$ time.

<br>

<h2>Timing Analysis</h2>

<img align="center" src="timing_analysis.png"></img>

From the above plot, it is visible that even though the graph seems irregular since the code was tested with random testcases, it tends to follow a linear relationship with $(n+k)log(n)$.

$\dfrac{(n+k)log(n)}{t} = c \; \exists c > 0$

$t = \dfrac{(n+k)log(n)}{c} = p \cdot (n+k)log(n) \;\exists p > 0$

$= O((n+k)log(n))$

Hence, the time complexity of the code is similar to the time complexity of the original algorithm.

<br>

### Observing how time taken varies with output (number of intersections) - $t$ vs $k$

Keeping a fixed value of $n$, we generate random testcases so that we get different $k$ values and plot a $t$ vs $k$ graph.
We plot graphs for five different values of $n$: $100, 500, 1000, 2500$ and $5000$.
<img align="center" src="t_vs_k.png"></img>

<br>

<h2>Test Cases</h2>
The code was ran against various testcases and the results were as follows:

[Note: Intersection points are marked as red circles]

<ol>
<li> Endpoints of all lines have integral values
<img align="center" src=".\test-cases\integer-points\integer-points.png"></img>

<li> Set of line segments that contain vertical lines
<img align="center" src=".\test-cases\integer-points-with-vertical-lines\integer-points-with-vertical-lines.png"></img>

<li> Endpoints of line segments have non-integral values
<img align="center" src=".\test-cases\float-points\float-points.png"></img>

<li> Set of line segments that are very close to each other and parallel to each other
<img align="center" src=".\test-cases\close-parallel-lines\close-parallel-lines.png"></img>

<li> Line segments appear to intersect but they do not intersect
<img align="center" src=".\test-cases\almost-intersecting-but-not-really\almost-intersecting-but-not-really.png"></img>

<li> Set of line segments that meet at a single point (star shaped)
<img align="center" src=".\test-cases\star\star.png"></img>
</ol>

In cases 4 and 5, we get an intersection point even though the line segments do not intersect. This is because of the floating point inacurracies in C++.

Since we cannot compare two floating point values directly, we need to check whether the difference between the two values is less than a certain threshold. We have used the `EPSILON` constant in our code to define the threshold, which is $10^{-9}$.

<br>

<h2>Conclusion</h2>

In conclusion, the Line Sweep Algorithm is an efficient algorithm in finding out the intersection points of a set of lines on a plane.

The algorithm is useful not just in direct applications like combining of two or more maps to find connections, but also the idea of the algorithm itself is useful in other applications and fields, such as Computer Graphics, Processor Design and so on, to name a few.

<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>

<script type="text/x-mathjax-config">MathJax.Hub.Config({ tex2jax: {inlineMath: [['$', '$']]}, messageStyle: "none" });</script>
