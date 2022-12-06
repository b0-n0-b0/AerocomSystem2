network AerocomSys
{
    parameters:
        int nDL = default(20);
        int nAC = default(10);
    types:
    submodules:
        controlTower: ControlTower {
            @display("p=115,109");
        }
        airCraft[nAC]: AirCraft {
            @display("p=390,52");
        }
        dataLink[nDL]: DataLink {
            @display("p=220,109");
        }
    connections:
        // each AC is connected to every DL via the output gate AC_out
        for j=0..nAC-1, for i=0..nDL-1{
            airCraft[j].AC_out[i] --> dataLink[i].DL_in[j];
        }	
        // each DL is connected to the CT via the output gate DL_out
        for i=0..nDL-1 {
            dataLink[i].DL_out --> controlTower.CT_in[i];
        }
}
