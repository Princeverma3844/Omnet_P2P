# Omnet P2P Network

## Objective
The objective of this project is to make the Peer to Peer network in which the Peer are arranged in cyclic topology and sending the messages in log(n) to other clients using some additional connections and utilizing the Chord Hash Distribution Algorithm.

## Network Setup
- **Peer:** All the peer nodes divides the task into various subtask and send it the client having ID same as generated for the subtask.

## Input Format
The value of n will be given by the running of python script. This n is the number of peers present in the network.

## How To Run
1. Run the python script and provide the value of n in that script. You will be required to provide the absolute path of the files in the python file of the network.ned, client.ned and the value1 and value2 txt file present. 
2. Build and run the project and do the simulation.

## Proof of correctness
- **LOG(N) Messages sending:** We can clearly see from the console that message is send to at max Log(N) nodes in order to send the msg from the source to destination.
- **LOG(N) Messages receiving:** We can clearly see from the console that message is recieved by at max Log(N) nodes in order to receive the msg back from the destination to source.
- **gossips:** All the clients starts to propagate gossips the with neighbour clients as soon as they get all the subtask result.
- **broadcast:** Broadcast msg is visible in the console which shows that msg is broadcasted.

