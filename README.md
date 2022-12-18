
### Computer Engineering

### Performance Evaluation of Computer Systems and Networks

# Aerocom System 2

### Project Documentation


<p style="text-align: right">
Alessio Di Ricco</p>


<p style="text-align: right">
Edoardo Geraci</p>


<p style="text-align: right">
Mariella Melechì</p>


Anno accademico 2022/2023



## Table of Contents



1. **Introduction**
    1. Objectives
2. **Model**
    2.1. Components 
    3.1. Assumptions
3. **Model Validation**
4. **Warm-up Analysis**
5. **Validation Experiments**
6. **Experiments**
7. **Factorial Analysis**
8. **Conclusions**



## Objectives:

measure the queue length, waiting time, response time, service time in all of the execution modes

## Components:



* **Aircraft (AC)**: Main module of the analysis composed by
    * **Packet Generator**: Sub Module which generates the fixed length packets with uniform interarrival distribution. These packets will be handled by the link selector which is to be described later.
    * **Link Selector**: Sub Module which manages a FIFO queue, which is responsible for sending packets. In the non monitored operation mode the DL is chosen once for all the simulation  at the start. In the monitored one the link selector scans periodically all the available data links every **m** seconds and selects the one with the highest capacity. In the monitored mode there’s also a malus due to the monitoring delay **X**. After the delay the operations are handled as usual.** **
* **Data Link (DL)**:There is a fixed number of DataLinks available to all the ACs. Each of the DLs varies its capacity linearly in a time **t**. 
* **Control Tower (CT)**: Receive packets and drop them. It’s a simplification of the behavior of a real Control Tower since this element is not the main focus of the analysis.
* **Packet**: Created by the packet generator, store information and sending time.

## Assumptions:



* Communication channels between ACs and CT are considered **ideal**; each channel can be used by any number of ACs at the same time without concurrency or interference.
* ACs are independent and the handling of messages by one AC does not interfere with the handling of all the others.
* The capacity of a DL is the number of bytes per second that the DL is able to forward. Knowing the size of each packet, which is fixed, and the capacity at the time of communication we can then compute the service time easily:
    * sPCK: size of the packet [byte]
    * cDL: capacity of the DL [byte/second]
    * ST: Service Time = 
* The malus X is composed of a fixed part and an additive part which is related to the number of DLs that the system has to scan.
* Wr have 3 different RNGs, one for the interarrival time, one for the capacity setting time (should we use one more for nextCapacity)?

<table style="text-align: center">
  <tr>
   <td>
<strong>Parameter</strong>
   </td>
   <td><strong>Values</strong>
   </td>
  </tr>
  <tr>
   <td>Capacity malus
   </td>
   <td>X
   </td>
  </tr>
  <tr>
   <td>Capacity time generation mode
   </td>
   <td>Exponential / Lognormal
   </td>
  </tr>
  <tr>
   <td>data-link capacity
   </td>
   <td>cDL
   </td>
  </tr>
  <tr>
   <td>Mean setting capacity time
   </td>
   <td>t
   </td>
  </tr>
  <tr>
   <td>Monitoring time
   </td>
   <td>mt
   </td>
  </tr>
  <tr>
   <td>Number of Aircrafts
   </td>
   <td>nAC
   </td>
  </tr>
  <tr>
   <td>Number of data-link
   </td>
   <td>nDL
   </td>
  </tr>
  <tr>
   <td>Operation mode
   </td>
   <td>monitored / non-monitored
   </td>
  </tr>
  <tr>
   <td>Packet generation time
   </td>
   <td>k
   </td>
  </tr>
  <tr>
   <td>Packet Size
   </td>
   <td>sPCK
   </td>
  </tr>
</table>

