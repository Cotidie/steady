# UDP & TCP
## UDP (User Datagram Protocol)
![UDP](https://i.imgur.com/C9cNJRP.jpg)  
 UDP is a Layer 4 protocol that doesn't required `connection`, thereby provides faster connection speed and smaller datagram size. Header is only 8 bytes that only contain ports, length and checksum for 2 bytes each. VPN, Video Streaming, DNS, WebRTC, etc. prefers UDP over TCP since it's faster and stateless.  
 - UDP doesn't care datagram loss or error (One way delivery)
 - **Stateless**: No ordered datagram and no flow control (doesn't request re-send) 
### TCPDUMP
```bash
# Sniff udp traffic to or from Google DNS Server (8.8.8.8)
> sudo tcpdump -ni wlp0s20f3 'udp and (src 8.8.8.8 or dst 8.8.8.8)'
# Look for ip address via Google DNS Server
> nslookup naver.com 8.8.8.8

# ToS(Type of Service) indicates priority of the packet (0 is normal)
# Source: 10.0.0.48:33191, Query ID: 41500 for identifying the response.
IP (tos 0x0, ttl 64, id 64855, offset 0, flags [none], proto UDP (17), length 55)
    10.0.0.48.33191 > 8.8.8.8.53: 41500+ A? naver.com. (27)
IP (tos 0x0, ttl 122, id 27583, offset 0, flags [none], proto UDP (17), length 119)
    8.8.8.8.53 > 10.0.0.48.33191: 41500 4/0/0 naver.com. A 223.130.200.104, naver.com. A 223.130.195.95, naver.com. A 223.130.195.200, naver.com. A 223.130.200.107 (91)
```
  
## TCP (Transmission Control Protocol)
  TCP is a bidirectional protocol that offers reliable, ordered and error-checked delivery of data. It does Three way Handshake with `SYN, ACK` when making a connection, and Four way Handshake with `FIN, ACK` to destroy a connection. It guarantees the delivery by **Flow Control**, **Congestion Control** and `ACK`
  - **Head of Line Blocking**: If the head of segments doesn't arrive it should wait for time-out and resend everything
  - **TCP Meltdown**: If VPN uses TCP connection between Dest and Source, too much calculation is needed for communication
### Segment (Header)
![TCP Header](https://i.imgur.com/MQQfXWc.png)  
- **Sequence Number**: Segment offset, number of total sequence is largely affected by target's MTU (normaly 1500 bytes).
-  **ACK Number**: ACK for a Sequence Number. it matches Seq number since ACK response doesn't carry data and standalone.
-  **Window Size**: Receiver's available buffer(window) size. It can be scaled by window scaling option.
### Handshake
| Three Way      | Four Way |
| :-----------: | :-----------: |
| ![Three Way](https://i.imgur.com/h178fj8.png)      | ![Four Way](https://i.imgur.com/b2ieX1g.jpg)       |
### Three way
- Client sends `SYN` request to establish a connection
- Server sends `SYN/ACK` response to notify a socket is open. 
  - socket should be open beforehand
- Client sends `ACK` response that connection is established.

### Four way
- Client sends `FIN` request to close a connection
- Server sets a connection to `CLOSE_WAIT` status and sends `ACK`, `FIN`
  - `CLOSE_WAIT` is to wait for `ACK`s to ensure all the data is sent, and there's no packet loss. 
- Client sets a connection to `TIME_WAIT` status and sends `ACK`
  - `TIME_WAIT` does the same role as `CLOSE_WAIT`.
- Server closes connection
- Client closes connection after timeout 

### Flow Control
![Flow Control](https://i.imgur.com/2rHXlEB.png)  
 Flow Control is all about limiting the amount of packets to send/receive. It uses **sliding window** method to manage buffer size and packets. Receiver sends available window size in each `ACK`'s TCP header, and sender adjusts the number of packets to send next. Note that window size is adjustable by `window size scaling factor`, which multiplies the window size by 2^n. (if the factor is 4, then multiply by 2^4=16)
 1. In handshake phase, client and server negotiate window scaling factor.
   - Client offers desirable scaling factor when `SYN`, then Server selects compatible scaling size when `SYN/ACK`  
 2. n packets are sent by sender, then receiver `ACK`s with the number it received and updated window size.
    - `ACK` with the number less than n means there's packet loss
 3. sender slides the window according to `ACK` number, and adjusts the amount of packets for the next.
    - If there's packet loss, the window just shrinks and doesn't move to ensure round trip.

### Congestion Control
![Congestion Control](https://i.imgur.com/AsO6eWn.jpg)  
 Congestion control is about preventing packet loss when travelling between routers, as routers would drop packets exceeding MTU or when their buffer lacks space. Sender first exponentially increase the window size until it reaches its threshold(**Slow Start**), and then slowly increase the size until congestion happens(**Congestion Avoidance**). The size shrinks to its half and start over again.
- **Slow Start**: increase the size of CWND by 1 * MSS on each `ACK`
  - if `ACK` is accumulated by `n`, `n` * MSS increases. 
- **Congestion Avoidance**: increase the size of CWND by 1 * MSS on each finished round trip
  - Round Trip means a complete trasmission of packets in CWND
  - If there's packet loss, CWND can't move forth.


## Questions
**| Why is UDP/TCP header contained in IP packet?**  
 It's because that datagram/packet is formed from higher layer to lower layer, attaching headers. 

**| How does a client receive UDP data, when it's not sure if ready to receive?**  
 UDP data is accepted only when client checks the socket to receive the data from. System call `select()` waits or checks data in a socket, then `rcvfrom()` fetch the data.

**| What's the relationship between MSS and Congestion Window?**  
 MSS(Maximum Segment Size) affects the number of packets while CWND manages the total size of window, which segmented packets reside. If MSS increases while CWND remains the same, the number of packets increase, while data transfer rate remains almost the same.