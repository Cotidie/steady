# Internet Protocol (IP)
  - [Overview](#overview)
  - [Private Network](#private-network)
  - [IP Packet](#ip-packet)
  - [ICMP (Internet Control Message Protocol)](#icmp-internet-control-message-protocol)
  - [ARP (Address Resolution Protocol)](#arp-address-resolution-protocol)
  - [NAT (Network Address Translation)](#nat-network-address-translation)
  - [Exercise](#exercise)
    - [TCPDUMP](#tcpdump)

## Overview
![ipv4](https://i.imgur.com/8ZY9szA.jpg)  
 IP is the address for host to host communication along with MAC address. It's the data that Layer 3 handles with packets, represented as **network.host/subnet** foramt.
- If destination ip resides in the same subnet, it only uses MAC address(L2) for communication
- If not, packet(L3) is delivered to the Default Gateway(Router)

## Private Network
![Private IP](https://i.imgur.com/QarFwtr.jpg)  
 IPv4 has private IP range which is managed by routers and forms subnet. Any private network can make use of those ranges but in practice, it's devided into multiple subnets to better apply policies per subnet, e.g. blocking certain domain or allowing only text data.
  
## IP Packet
![IP Packet](https://i.imgur.com/YbOmhi9.png)  
- **Version**: IP Protocol's version (v4, v6)
- **IHL(HLEN)**: (Internet Header Length) Number of header's rows. Minimum 5.
- **Total Length**: Total size of a packet. 20 Bytes(Header) + user data (up to around 64kb)
- **Identification**: IP packet's unique ID, in case of fragmentation.
- **Flag/Fragmentation offset**: flags of status to fragmented or not and the offset of current fragmentation.
- **TTL**: Timeout limit. Routers decrease TTL when sending a packet.
- **Protocol**: Indicates which Protocols reside in user data (e.g. ICMP)

## ICMP (Internet Control Message Protocol)
![ICMP Datagram](https://download.huawei.com/mdl/image/download?uuid=9c21763198b14ae78941f0493a33605d)  
![ICMP code](https://static.javatpoint.com/tutorial/computer-network/images/icmp-protocol2.png)  
 ICMP is a Layer 3 protocol that adds observability over IP packets. When enabled, ICMP header and data reside in IP packet's data area. **Ping** and **Traceroute** are built upon ICMP.
 - When TTL is exceeded, a medium router sends back ICMP packet to the Source IP with error code.
 - **Ping**: `ping <destination>`. Measures latency and connection status.
 - **Traceroute**: `traceroute <destination>`. Finds routing path to the destination, by sending multiple pings with incremented TTL.

## ARP (Address Resolution Protocol)
![ARP](https://i.imgur.com/WfVpdfj.jpg)  
  Over L3 devices manage ARP table that maps IP address to MAC address. Any data frames(L2) that carry ARP request or replay are to be examined and help filling up ARP table dynamically. ARP protocol resides in L2 data so that L2 devices like switch can broadcast over network. It plays a critical role in Load Balancing as some server should absorb traffic which otherwise would be directed to a broken server.
- **ARP Request**: Broadcasted to all the devices within a subnet.
- **ARP Reply**: Unicast that a device with target IP sends to the source device.

## NAT (Network Address Translation)
![NAT Router](https://i.imgur.com/eOcCuAf.png)  
 NAT is a technique used by routers to allow devices on a private network to share a single public IP. Router with NAT maintains NAT table that maps SourceIP:Port to PublicIP:PublicPort, and PublicIP:PublicPort to DestIP:Port. It assigns available public port to a private device which requests connection. 
 - Router + NAT is a Layer 4 device, while router is just a Layer 3 device
 - Public Port is unique entry in NAT table in most cases
 - Multiple private devices can share the same public port in special cases.
   - **Outgoing**: maps the combination of SourceAddress and DestAddress
   - **Incoming**: maps the combination of DestAddress and PublicAddress


## Exercise
### TCPDUMP
```shell
> sudo tcpdump -nvi <network interface> <protocol> <expression>

> sudo tcpdump -nvi wlp0s20f3 arp src 10.0.0.1 or dest 10.0.0.1
ARP, Ethernet (len 6), IPv4 (len 4), Request who-has 10.0.0.48 tell 10.0.0.1, length 42
ARP, Ethernet (len 6), IPv4 (len 4), Reply 10.0.0.48 is-at 00:93:37:2c:7c:16, length 28

> sudo tcpdump -ni wlp0s20f3 icmp
IP 10.0.0.48 > 8.8.8.8: ICMP echo request, id 10336, seq 1, length 64
IP 8.8.8.8 > 10.0.0.48: ICMP echo reply, id 10336, seq 1, length 64
```
tcpdump allows sniffing network traffic on specific interface(wireless/ethernet...). Example above shows ARP traffic on `wlp0s20f3` interface, wirelss lan.