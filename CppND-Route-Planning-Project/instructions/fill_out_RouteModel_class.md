The `Model` class that exists in the current code doesn't contain all the data or methods that will be needed to perfom an A\* search, so we are going to extend that class with a `RouteModel` class. In this exercise, you will fill out the `RouteModel` class in `route_model.h`. In the next exercises, you will also fill out the `RouteModel::Node` class as well.


In `route_model.h`:
1. Add a private vector of `Node` objects named `m_Nodes`. This will store all of the nodes from the Open Street Map data.
2. Add a public "getter" method `SNodes`. This method should return a reference to the vector of `Nodes` stored as `m_Nodes`.