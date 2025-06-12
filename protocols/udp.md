# UDP (User Datagram Protocol)
- A **Transport Layer** protocol used for **fast**, **connectionless**, and **unreliable** data transmission.
---
## Pros
- Smaller packets (8-byte header)
- Less bandwidth usage
- Faster than TCP (no handshake or retransmission)
- Stateless (no connection state maintained)
---
## Cons
- No acknowledgments (no ACK)
- No guaranteed delivery (packets can be lost)
- No congestion control (can overwhelm the network)
- Connectionless (no session management)
- No ordering (packets may arrive out of order)
- No built-in security or reliability features
---
## UDP Segment Structure
![UDP Header](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fcheapsslsecurity.com%2Fblog%2Fwp-content%2Fuploads%2F2022%2F06%2Fudp-header.png&f=1&nofb=1&ipt=cdcd4c1c5f5ce397fb2c40aad6afa579eade92c82c4696d4852b4057fe7595b0)
