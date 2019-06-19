Now that you have a `RouteModel` class and you have completed the `RouteModel::Node` nested class, you can create `RouteModel` nodes. 

When the `RouteModel` constructor is called, it calls the `Model` constructor with the open street map data. When this happens, a collection of `Model:Node` objects are created. However, in order to perform the A\* search, you will need to use `RouteModel::Node` objects instead. 

In this exercise, you will modify the `RouteModel` constructor. The constructor will use the vector of `Model:Node` objects to create new `RouteModel::Node` objects. These `RouteModel::Node` objects will then be stored in the `m_Nodes` vector of the `RouteModel`.


## To complete this exercise:
---
- In the `RouteModel` constructor in `route_model.cpp`, write a for loop with a counter to loop over the vector of `Model::Node`s given by `this->Nodes()`. 
- For each `Model` node in the loop, use the `RouteModel::Node` constructor to create a new node, and  push the new node to the back of `m_Nodes`. 
- To do this, you should use the `RouteModel::Node` constructor that accepts three arguments:
  ```
  Node(int idx, RouteModel * search_model, Model::Node node)
  ```

  The first argument is given by the counter. The second argument should be a pointer to the `RouteModel` instance that the `Node` belongs to. Since you are writing your code inside the `RouteModel` constructor, you can use the `this` keyword to get a pointer to the current `RouteModel` instance. In other words, you can pass `this` as the second argument. The last argument is given by the `Model` node in the for loop.