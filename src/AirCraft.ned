//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

module AirCraft
{
    gates:
        output AC_out[3];
    submodules:
        packetGenerator: PacketGenerator {
            @display("p=221,94");
        }
        linkSelector: LinkSelector {
            @display("p=364,96");
        }
    connections:
        packetGenerator.PG_out --> linkSelector.LS_in;
        linkSelector.LS_out --> AC_out;
}
