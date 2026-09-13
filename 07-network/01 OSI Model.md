# OSI Model
  - [Overview](#overview)
  - [Network Devices](#network-devices)
  - [Packet Travelling](#packet-travelling)
    - [Tables](#tables)
    - [Process](#process)
  - [Question](#question)

## Overview
![OSI Model](https://i.imgur.com/QV4qzXs.jpg)  
 **OSI**(Open Systems Interconnection) Model is a communication standard comprises of 7 layers that have hierachical relationship for networking: Physical, Data link, Network, Transport, Session, Presentation and Application. Without a standard, it would've been very difficult to handle with numerous mediums and technologies such as LTE, statelite, fiber and so on.  

- Application (Layer 7) - HTTP/FTP/gRPC
- Presentation (Layer 6) - Encoding/Serialization (Protobuf, JSON...)
- Session (Layer 5) - TLS, Connection establishment
- Transport (Layer 4) - UDP/TCP (+ port, segment) 
- Network (Layer 3) - IP (packet)
- Data Link (Layer 2) - Frames, Mac Address Ethernet
- Physical (Layer 1) - Electric signals, fiber, radio waves


 TCP/IP model simplifies 7 layers into 4 layers, as boundary of some layers can be blurred and can work closely to each other.

## Network Devices
![swith, Router](https://i.imgur.com/6v3H5Iy.jpg)  
![Proxy, Router](https://xuri.me/wp-content/uploads/2013/09/forward-proxy-3.jpg)  
- **Swtich**: (Layer 2) It connects multiple hosts and makes a subnet. It needs only MAC address to find the destination within its subnet.
- **Router**: (Layer 3) A device connected to internet. It need packet(IP) to find the destination router.
- **Gateway**: (Layer 3) Ghttps://i.stack.imgur.com/oMOGd.png4 to maintain connections with multiple clients.
- **Firewall**: (Layer 4) A device that controls flow over ports.
- **Load Balancer/CDN**: (Layer 7) A server that caches content and redirects to an appropriate server.

## Packet Travelling
![Packet Travelling](https://i.imgur.com/hQhuzlF.jpg)  
| Refer to: [Youtube Video](https://www.youtube.com/watch?v=rYodcvhh7b8)  
### Tables
- **ARP Table**: Mapping of IP address to MAC address. Dynamically fills up.
- **MAC Table**: Mapping of Switch port number to MAC address. Dynamically fills up.
- **Routing Table**: Mapping of IP address to Interfaces. Packets are dropped when no IP address is matching.

### Process
A packet from **A**(IP: 11.8.8.11) to **B**(IP: 22.7.7.22) would traverse through the process below.  
1. Fill up routing tables in Hosts and Routers.
2. **A** first attaches L3 header with SIP and DIP. (Source, Destination IP) 
3. **A** tries to attach L2 header with SMAC and DMAC.  
   - DIP is not in the same subnet. DMAC should be the Default Gateway  
   - MAC for the Default Gateway is unknown, send ARP request to Swtich.
4. **Switch** sends ARP request to all the devices and fills up its MAC table on response.
   - **R1** responds to the ARP request
   - **Switch** send back the response to **A**
   - **A** receives the ARP response and fills up its ARP table.
5. **A** attaches L2 header and sends the packet to **R1**
   - from its MAC to the Default Gateway(Router) MAC
6. **R1** removes L2 header and sends the packet(L2 emptied) to internet
   - the pakcet traverses the internet until the subnet matches one of a router.
7. **R2** receives the packet and tries to attach L2 header.
   - do the same ARP request-record process as in **2**
8. **R2** attaches L2 header and send the packet to **B**
9. **B** finally receives the packet and do the same process to **A** for response.
    - response is faster as all the required info is already recorded

## Question
**| How does port forwarding work while router is a Layer 3 device?**  
: Port forwarding is managed by NAT router that maps external `ip:port` to internal `ip:port`. 