import ned.IdealChannel;

network Network
{
    parameters:
        int n = 17;
        int m = 5;
//        @display("bgb=584,450");

        @display("bgb=1017,466");
    submodules:
        clients[n]: Client {
//            @display("p=310,78; i=device/server");
//			  @display("p=" + intuniform(100, 400) + ',' + intuniform(100, 400));
        }
    connections allowunconnected: // network level connections
        
        for i=0..n-1 {
            clients[i].topo_out --> clients[(i+1)%n].topo_in;
        }
        
        for i = 0..n-1, for j = 0..m-1 {
            clients[i].out[j] --> clients[(i + (1 << j)) % n].in[j];
        }

}

