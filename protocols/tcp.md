# TCP (Transport Control Protocol)
* A **Transport Layer** protocol used for **reliable**, **ordered**, and **error-checked** delivery of data.
---
## Pros
- **Acknowledgment**
    - Every received segment is acknowledged (ACK).
- **Guaranteed Delivery**
    - Ensures all data arrives correctly and completely.
- **Connection-based**
    - Uses a 3-way handshake to establish a connection before data transfer.
- **Congestion Control**
    - Adapts sending rate using algorithms like **Slow Start**, **Congestion Avoidance**, **Fast Retransmit**, and **Fast Recovery**.
- **Ordered Packets**
    - Reorders out-of-order packets before handing them to the application.
---
## Cons
- Larger headers (compared to UDP).
- More bandwidth and processing required.
- Slower than UDP due to reliability features.
- **Stateful** — maintains connection state on both ends.
- **Server memory overhead** — each connection consumes resources.
--- 
## TCP Segment Structure 
![TCP Header](https://external-content.duckduckgo.com/iu/?u=http%3A%2F%2Ffiberbit.com.tw%2Fwp-content%2Fuploads%2F2013%2F12%2FTCP-segment.png&f=1&nofb=1&ipt=7c5aabfd267f76a5b455cfa58c6ce5512475ade9651206747077f4fe441cdf5d)

---
## TCP Flags
| Flag  | Full Name      | Purpose                                      |
| ----- | -------------- | -------------------------------------------- |
| `SYN` | Synchronize    | Initiates a connection (used in handshake)   |
| `ACK` | Acknowledgment | Acknowledges received data or connection     |
| `FIN` | Finish         | Requests graceful connection termination     |
| `RST` | Reset          | Abruptly terminates connection (e.g., error) |
| `PSH` | Push           | Forces immediate delivery to the application |
| `URG` | Urgent         | Indicates urgent data (rarely used)          |

---
## Sequence Number
- Indicates the **number of the first byte** in that segment.
- Example (sending 100 bytes in 5 segments of 20 bytes):
    - Segment 1: SEQ = 0
    - Segment 2: SEQ = 20
    - Segment 3: SEQ = 40
    - Segment 4: SEQ = 60
    - Segment 5: SEQ = 80
---
## Acknowledgment Number
- Indicates the **next expected byte**.
- Example:
    - After segment 1 (20 bytes): ACK = 20
    - After segment 2 (20 bytes): ACK = 40
    - After segment 3 (20 bytes): ACK = 60
    - After segment 4 (20 bytes): ACK = 80
    - After segment 5: ACK = 100
---
## 3 way handshack
* Establishes a **reliable TCP connection**.
![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fblogger.googleusercontent.com%2Fimg%2Fa%2FAVvXsEjIUASFkF_POjScbsYOIdCOrWT2D7-y9wyfWFKihkMJjMKle6r1-dVh5bCjIDku3fWhS2Jka8hvEKNsNPvfA_PRKhnSU8uY20dXGTtbxmZOKL3P8jiyetzr-3BPKogwjjTJH-HaKQCc551Yvnj0WB1v3dCGDK_2jha1TNRgZnsM1ho-VjKQZFIjhOZeOw%3Dw640-h480&f=1&nofb=1&ipt=d4ca6e6410dc4798bbf764f3d556dad14cc25376f57183c6624ab026ee97479b)
--- 
## 4 way Handshake
* Gracefully closes a TCP connection in **both directions**.
![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fraw.githubusercontent.com%2FHIT-Alibaba%2Finterview%2Fmaster%2Fimg%2Ftcp-connection-closed-four-way-handshake.png&f=1&nofb=1&ipt=5c4401a2f2ec4c1a0804390aa2764e4de7d443045acaf856f362c80a73f4cc54) 
## Checksum
* Checksum: is a 16-bit field in the TCP header used for **error detection**
* How work ?
	* **In Sender:**
		1. Divide segment into 16-bit words.
		2. Sum all words (ignoring overflow).
		3. Take **1's complement** (invert).
	* **In Receiver:**
		1. Sum all 16-bit words including checksum.
		2. Result = 0xFFFF (all 1s) → valid.
---
## Sliding Window
- **Flow control mechanism**.
- Sender can transmit **multiple segments** before needing an ACK.
- Controlled by **window size** (tells sender how much unacknowledged data it can send).

