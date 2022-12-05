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
        for i=0..nDL-1{
            airCraft.AC_out[i] --> dataLink[i].DL_in;
        }	
        
        for i=0..nDL-1 {
            dataLink[i].DL_out --> controlTower.CT_in[i];
        }
}
