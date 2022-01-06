#include "node.h"
#include <iostream>

using namespace std;

void routingAlgo(vector<RoutingNode*> nd){
  for(int i=0; i<nd.size();i++){
    for(int j=0; j<nd.size();j++){
      nd[j]->sendMsg();
    }
  }
}


void RoutingNode::recvMsg(RouteMsg *msg) {
  routingtbl* routing_table = msg->mytbl;
  string ip_sender= msg->from;
  string ip_receiver= msg->recvip;

  for(int i=0; i< routing_table->tbl.size();i++){
    int flag=1;

    RoutingEntry routing_entry = routing_table->tbl[i];

    for(int j=0; j<mytbl.tbl.size();j++){
      if(mytbl.tbl[j].dstip == routing_entry.dstip){
        if(mytbl.tbl[j].cost>routing_entry.cost+1){
          mytbl.tbl[j].ip_interface=ip_receiver;
          mytbl.tbl[j].nexthop=ip_sender;
          mytbl.tbl[j].cost=routing_entry.cost+1;
        }
        flag=0;
        break;
      }
    }

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