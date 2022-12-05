network AerocomSys
{
    parameters:
        int nDL = default(5);
    types:
    submodules:
        controlTower: ControlTower {
            @display("p=115,109");
        }
        airCraft: AirCraft {
            @display("p=390,52");
        }
        dataLink[nDL]: DataLink {
            @display("p=220,109");
        }
    connections:
        // TODO: discuss if we want to implement more then one AC at a time
        // each AC is connected to every DL via the output gate AC_out
        for i=0..nDL-1{
            airCraft.AC_out[i] --> dataLink[i].DL_in;
        }	
        // each DL is connected to the CT via the output gate DL_out
        for i=0..nDL-1 {
            dataLink[i].DL_out --> controlTower.CT_in[i];
        }
}
