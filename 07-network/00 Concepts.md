# Network Concept
## Terms
- **interface**: a connection or medium between a computer and a network, such as ethernet or wifi.
- **MTU**: (Maximum Transmission Unit) a single maximum packet size that a network device can receive at one time.
- **File Descriptor**: a file descriptor is a unique identifier to a opened file or socket. It does a critical role of reading and writing data to a file/socket. Maximum number of file descriptor in memory is 4096.
- **TCB**: Transmission Control Block, something like PCB, stores connection status about a socket. It handles info such as the current sequence number and ack number.
- **Congestion**: Congestion happens when a router has no more space/buffer to consume a packet and drops the packet. It alerts the congestion(packet loss) to the sender.  
- **Bandwidth**: The maximum amount of data transmitting through a data pipe, simply the size of a pipeline.
 
 ## DNS
 ![Root Name Server](https://www.cloudflare.com/img/learning/dns/glossary/dns-root-server/dns-root-server.png)  
 ![DNS Server](https://i.imgur.com/3dpVtPb.png)  
 DNS is a human readable alias for an IP address. It is structured in a hierachy using **Root Name Server**, **TLD(Top Level Domain) Server** and **Authoritative Name Server** to acheive distributed system. DNS is a reliable load balancer that does traffic distribution by its nature. 
 - **Root Name Server**: Servers that distribute traffic to the nearest TLD. Only 13 IP addresses are hard-coded into DNS resolvers(e.g. routers), which IPs are managed by NASA, US Department of Defense, etc.
 - **TLD**: A server that maintains website information for top-level domains such as `.com`, `.org`, `.edu`, etc. 
 - **Authoritative Server**: Final destination of a DNS query, which maps full domain name to an IP address.