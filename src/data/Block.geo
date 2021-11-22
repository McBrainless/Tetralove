// Gmsh project created on Sat Nov 20 23:14:59 2021
//+
SetFactory("OpenCASCADE");
Circle(1) = {0, -0, 0, 0.5, 0, 2*Pi};
//+
Wire(1) = {1};
Extrude { Curve{1}; } Using Wire {1}

//+
Extrude {0, 0, 1} {
  Curve{1}; 
}
