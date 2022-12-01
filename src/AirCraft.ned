module AirCraft
{	parameters:
    	int nDL = parent.nDL;
    gates:
        output AC_out[parent.nDL];
    submodules:
        packetGenerator: PacketGenerator {
            @display("p=221,94");
        }
        linkSelector: LinkSelector {
            @display("p=364,96");
        }
    connections:
        packetGenerator.PG_out --> linkSelector.LS_in;
//        by selecting the i-th output in the link selector, we also select the i-th datalink
        for i=0..parent.nDL-1 {
            linkSelector.LS_out[i] --> AC_out[i];
        }
}
