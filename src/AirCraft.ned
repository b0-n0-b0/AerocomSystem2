module AirCraft
{	parameters:
    	int nDL = parent.nDL;
    gates:
        output AC_out[nDL];
    submodules:
        packetGenerator: PacketGenerator {
            @display("p=221,94");
        }
        linkSelector: LinkSelector {
            @display("p=364,96");
        }
    connections:
        // the PG sends packet to the LS which stores them in a queue and sends them when ready
        packetGenerator.PG_out --> linkSelector.LS_in;
        // each output of the LS is connected to one output of the AC
        // by selecting the i-th output in the link selector, we also select the i-th datalink
        for i=0..parent.nDL-1 {
            linkSelector.LS_out[i] --> AC_out[i];
        }
}
