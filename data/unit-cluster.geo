Point(1) = {0, .5, 0, 1.0};
Point(2) = {0, -.5, 0, 1.0};
Point(3) = {.5, 0, .5, 1.0};
Point(4) = {-0.5, 0, .5, 1.0};
Point(5) = {.5, 0, -.5, 1.0};
Point(6) = {-.5, 0, -.5, 1.0};
Line(1) = {1, 2};
Line(2) = {1, 3};
Line(3) = {1, 4};
Line(4) = {1, 5};
Line(5) = {1, 6};
Line(6) = {2, 3};
Line(7) = {2, 4};
Line(8) = {2, 5};
Line(9) = {2, 6};
Line(10) = {3, 4};
Line(11) = {4, 6};
Line(12) = {5, 6};
Line(13) = {5, 3};

//+
Curve Loop(1) = {11, -5, 3};
//+
Plane Surface(1) = {1};
//+
Surface(2) = {1};
//+
Recursive Delete {
  Surface{1}; Surface{2}; 
}
//+
Line(14) = {1, 6};
//+
Line(15) = {6, 4};
//+
Line(16) = {4, 1};
//+
Curve Loop(2) = {14, 15, 16};
//+
Plane Surface(1) = {2};
//+
Compound Surface {1};
