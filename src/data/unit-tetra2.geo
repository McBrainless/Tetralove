Point(1) = {0, .5, 0, 1.0};
Point(2) = {0, -.5, 0, 1.0};
Point(3) = {.5, 0, .5, 1.0};
Point(4) = {-.5, 0, .5, 1.0};
Line(1) = {1, 4};
Line(2) = {1, 3};
Line(3) = {1, 2};
Line(4) = {3, 4};
Line(5) = {2, 3};
Line(6) = {2, 4};
Curve Loop(1) = {1, -4, -2};
Curve Loop(2) = {1, -6, -3};
Curve Loop(3) = {5, 4, -6};
Curve Loop(4) = {5, -2, 3};
Surface(1) = {1};
Surface(2) = {2};
Surface(3) = {3};
Surface(4) = {4};
Surface Loop(1) = {2, 1, 3, 4};
Volume(1) = {1};
Physical Volume("internal") = {1};
Physical Surface("face1") = {1};
Physical Surface("face2") = {2};
Physical Surface("face3") = {3};
Physical Surface("face4") = {4};
