#include "node.h"
#include <iostream>

using namespace std;

// in this function, each node sends it's information to all the nodes
void routingAlgo(vector<RoutingNode*> nd){
  for(int i=0; i<nd.size();i++){
    for(int j=0; j<nd.size();j++){
      nd[j]->sendMsg();
    }
  }
}


void RoutingNode::recvMsg(RouteMsg *msg) {
  //extracting the attributes of the message (the routing table of the sender, the ip address of the sender, the ip address of the receiver)
  routingtbl* routing_table = msg->mytbl;
  string ip_sender= msg->from;
  string ip_receiver= msg->recvip;

  for(int i=0; i< routing_table->tbl.size();i++){
    int flag=1;
    
    //get each entry in the routing table
    RoutingEntry routing_entry = routing_table->tbl[i];

    for(int j=0; j<mytbl.tbl.size();j++){
      //checking if the destination ip addresses are equal in the two entries??
      if(mytbl.tbl[j].dstip == routing_entry.dstip){
        //checking if their is improvement in the cost??
        if(mytbl.tbl[j].cost>routing_entry.cost+1){
          //So, update the attributes of the entry
          mytbl.tbl[j].ip_interface=ip_receiver;
          mytbl.tbl[j].nexthop=ip_sender;
          mytbl.tbl[j].cost=routing_entry.cost+1;
        }
        flag=0;
        break;
      }
    }

     //checking if the flag doesn't change --> then it is the first time to insert the entry
    if(flag==1){
      RoutingEntry entry;
      entry.ip_interface=ip_receiver;
      entry.nexthop=ip_sender;
      entry.dstip=routing_entry.dstip;
      entry.cost=routing_entry.cost+1;

      mytbl.tbl.push_back(entry);
    }
  }
}
