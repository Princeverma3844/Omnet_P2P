#include "client.h"
#include <bits/stdc++.h>
#include "ArrayMessage_m.h"
#include <map>  // Include <map> header for std::map
#include <vector>  // Include <vector> header for std::vector

using namespace std;
map<pair<vector<int>, int>, int> ML;
int n;
int m;
int x = 3;
vector<int> response_vector[100];

// get the nearrest neighbor for sending the message in log(n) time.
int get_nearest_node(int start, int des) {
    if (start < des) {
        for (int i = 0; i < m; i++) {
            int cur_node = (start + (1 << i));
            if (cur_node == des) {
                return i;
            }
            else if (cur_node > des) {
                i--;
                return i;
            }
        }
    }
    else {
        for (int i = 0; i < m; i++) {
            int val = 1 << i;
            int cur_node = (start + val);
            if (cur_node % n == des) {
                return i;
            }
            else if (cur_node > n && cur_node % n > des) {
                i--;
                return i;
            }
        }
    }
    return m - 1;
}


void Client::initialize() {
    n = par("n");
    m = par("m");
    int cur_client = getIndex();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000);  // Range from 1 to 100
    vector<int> task(3 * n, -1);
//  generate the subtask
    for (int i = 0; i < 3 * n; i++) {
        task[i] = rand();
    }

    // Call the new function to send subtasks
    sendSubtasks(cur_client, task);
}

//sending all the subtasks
void Client::sendSubtasks(int cur_client, vector<int>& task) {
    ArrayMessage *subtask = new ArrayMessage("ArrayMessage");
    subtask->setArraySize(3);
    subtask->setSource(cur_client);
    subtask->setDir(1);
    int iter = 0;
    while(iter <= 3*(n/2)){
        if(iter%3 == 0 && iter != 0){
            int rand_index = rand();
            while(rand_index%n == cur_client){
                rand_index = rand();
            }
            subtask->setDes(rand_index%n);
            cout<<"client"<<cur_client<<" sending the sub_task"<<iter/3<< " to "<<rand_index%n;
            cout<<" with elements as "<<subtask->getArrayData(0)<<" "<<subtask->getArrayData(1)<<" "<<subtask->getArrayData(2)<<endl;
            int index = get_nearest_node(cur_client, rand_index%n);
            send(subtask->dup(), "out", index);
        }
        subtask->setArrayData(iter%3, task[iter]);
        iter ++;
    }
}

//handle the incoming task
void Client::handleMessage(cMessage *msg) {
    // Handle incoming messages if needed
    int cur_client = getIndex();
    ArrayMessage *message = dynamic_cast<ArrayMessage *>(msg);
    int destination = message->getDes();
    int check_propagate = message->getProp();
    if(check_propagate == 1){
//      check for the propagate condition, if satisfied send this msg to other clients if recieved first time.
        vector<int> temp;
        for(int i=0;i<n/2;i++){
            temp.push_back(message->getArrayData(i));
        }
        if(ML[{temp,message->getSource()}] == 0){
            ML[{temp,message->getSource()}] = 1;
            cout<<"Message propagated by the Client"<<cur_client<<endl;
            send(message->dup(), "topo_out");
        }
    }
    else{
        if(destination == cur_client){
//          check if the msg has recieved the destination
            if(message->getDir() == 1){
//              check whether the destination is the source from where task is send or not.
                ArrayMessage *response = new ArrayMessage("ArrayMessage");
                int val1 = message->getArrayData(0);
                int val2 = message->getArrayData(1);
                int val3 = message->getArrayData(2);
                int val = max(val1, max(val2 ,val3));
                int index = get_nearest_node(cur_client, message->getSource());
                response->setDes(message->getSource());
                response->setSource(cur_client);
                response->setDir(0);
                response->setArrayData(0, val);
                cout<<"Message recieved by the destination client"<<message->getDes()<< " and Response sent back to the client"<<message->getSource()<<endl;
                send(response->dup(), "out", index);  // Send a copy of the message
            }
            else{
//              gets the response from all the clients assigned with subtasks.
                int maxi_val = message->getArrayData(0);
                cout<<"Recieved the maxi value by Client"<<cur_client<<" as "<<maxi_val<<" from the client"<<message->getSource()<<endl;
                response_vector[cur_client].push_back(maxi_val);
                ArrayMessage *propagate_msg = new ArrayMessage("ArrayMessage");
                if(response_vector[cur_client].size() == n/2){
                    propagate_msg->setProp(1);
                    propagate_msg->setSource(cur_client);
                    int task_result = INT_MIN;
                    for(int i=0;i<n/2;i++){
                        propagate_msg->setArrayData(i, response_vector[cur_client][i]);
                        task_result = max(task_result, response_vector[cur_client][i]);
                    }
                    cout<<"Propagated the message by the Client"<<cur_client<<" and overall maximum value is "<<task_result<<endl;
                    send(propagate_msg->dup(), "topo_out");
                }
            }
        }
        else{
//          if destination not reached send it to the next nearest client.
            int next_client = get_nearest_node(cur_client, destination);
            cout<<"Message sent by Client"<<message->getSource()<<" for the destination Client"<<message->getDes()<<" passed from Client"<<cur_client<<endl;
            send(message->dup(), "out", next_client);
        }
    }
    delete msg;  // Delete the message
}

Define_Module(Client);
