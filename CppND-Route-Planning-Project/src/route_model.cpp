#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {

vector<Model::Node> allModelNode;
vector<RouteModel::Node> allRouteModelNode;
//RouteModel temp;

allModelNode = this->Nodes();
for(int i=0; i< allModelNode.size();i++)
{
    m_Nodes.push_back(RouteModel::Node(i, this, allModelNode[i]));
   // m_Nodes.push_back(this->Node);
}

CreateNodeToRoadHashmap();

//void FindNeighbor(vector<int> node_indices);

}

void RouteModel::Node::FindNeighbors()
{
    vector<int> allNodeIndices;
    //vector<Road> allRoads = parent_model->Model::Roads();
    
    
    
    for(auto & pToRoadsOfANode : parent_model->node_to_road[index])
    {
        allNodeIndices = parent_model->Ways()[pToRoadsOfANode->way].nodes;
    
        RouteModel::Node * neighborNodes= FindNeighbor(allNodeIndices);
        if(neighborNodes!=NULL)
        {
        this->neighbors.push_back(neighborNodes);
        //Neighbors.push_back(*neighborNodes);
        }
    }

    
}

RouteModel::Node & RouteModel::FindClosestNode (float x, float y)
{
    Node temp;
    temp.x = x;
    temp.y = y;

    float min_dist = std::numeric_limits<float>::max();
    int closest_idx;

    //auto allRoads = this->Model::Roads();
    //Model::Road road;
    for(auto &road : Roads())
    {
        if(road.type != Model::Road::Type::Footway)
        {
            for(int nodeIndex : Model::Ways()[road.way].nodes)
            {
                int dist = temp.distance(SNodes()[nodeIndex]);
                if(dist < min_dist)
                {
                    min_dist = dist ;
                    closest_idx = nodeIndex;
                }

            }
        }
       


    }

    return SNodes()[closest_idx];

    
}

RouteModel::Node * RouteModel::Node::FindNeighbor(vector<int>node_indices)
{
    Node * closest_Node = nullptr;
    Node node;
    for(int nodeIndex: node_indices)
    {
        node = parent_model->SNodes()[nodeIndex]; 
        if((distance(node)) && (visited==false))
        {
            if((closest_Node == nullptr) || ((distance(node) < (distance(*closest_Node)))))
            {
            closest_Node = &(parent_model->SNodes()[nodeIndex]);
            }

        }

    }

    return closest_Node;

}



/*void RouteModel::CreateNodeToRoadHashmap()
{
   vector<Road> allRoads;
    vector<Way> allWays;
    vector<int> nodeIndices;

    allRoads = Roads();
    allWays = Ways();
    
    for(int i=0; i< allRoads.size(); i++)
    {
        if(allRoads[i].type !=Model::Road::Type::Footway)
        {
        nodeIndices = allWays[allRoads[i]].way.nodes;

        for(int j=0; j<nodeIndices.size();j++)
        {
            int node_idx = nodeIndices[j];
            if(node_to_road.find(node_idx) == node_to_road.end())
            {
           // cout << "Node Index not found ";
            node_to_road[node_idx] = std::vector<const Model::Road *> ();
           
            //node_to_road[j]push_back(&allWays[i]);
            
            }

            node_to_road[node_idx].push_back(&allRoads[i]);
            
        }
        
        }
    }
}
*/



void RouteModel::CreateNodeToRoadHashmap()
{
    for(auto &road : Roads())
    {
        if(road.type != Model::Road::Type::Footway)
        {
            for(auto node_idx: Ways()[road.way].nodes)
            {
                if(node_to_road.find(node_idx)==node_to_road.end())
                {
                    node_to_road[node_idx]=vector<const Model::Road *>();
                }
                node_to_road[node_idx].push_back(&road);
            }
        }
    }
}