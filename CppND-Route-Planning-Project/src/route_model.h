#ifndef ROUTE_MODEL_H
#define ROUTE_MODEL_H

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>
#include<vector>

class RouteModel : public Model {

  public:
    class Node : public Model::Node {
      public:
        // Add public Node variables and methods here.
         RouteModel::Node *parent = nullptr;
        float h_value =std::numeric_limits<float>::max();
        float g_value = 0.0;
        bool visited = false;
        vector<RouteModel::Node*> neighbors;
        vector<Node> Neighbors;

        Node(){}
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}
        
        float distance ( const RouteModel::Node nearestNode)
        {
        float x1 = x;
        float y1 = y;

        float x2 = nearestNode.x;
        float y2 = nearestNode.y;

        return sqrt(pow((x1-x2),2)+pow((y1-y2),2));

       }

      void FindNeighbors();

      private:
        // Add private Node variables and methods here.
        int index;
       
        RouteModel * parent_model = nullptr;

         RouteModel::Node * FindNeighbor(vector<int>node_indices);
    };
    
     unordered_map<int, vector<const Model::Road *>>& GetNodeToRoadMap(){ return node_to_road;}


    // Add public RouteModel variables and methods here.
    

    RouteModel(const std::vector<std::byte> &xml);  
    std::vector<Node> path; // This variable will eventually store the path that is found by the A* search.
    
    vector<RouteModel::Node> & SNodes() {return m_Nodes;}

    Node & FindClosestNode(float x, float y);
  
   //auto &GetNodeToRoadMap(){return node_to_road;}
  private:
    // Add private RouteModel variables and methods here.
  
  unordered_map<int, vector<const Model::Road *>> node_to_road;
  
 

  vector<RouteModel::Node> m_Nodes;


  void CreateNodeToRoadHashmap ();
  
};

#endif