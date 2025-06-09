# TCP & UDP

I learned about **TCP** and **UDP**, summarized what I studied, and implemented simple TCP and UDP servers in C++ using sockets.

---

## 📁 Structure

- [`server_code/tcp_server.cpp`](server_code/tcp_server.cpp) — Simple TCP server example in C++.
- [`server_code/udp_server.cpp`](server_code/udp_server.cpp) — Simple UDP server example in C++.
- [`tcp.md`](tcp.md) — Summary and notes on the **TCP protocol**.
- [`udp.md`](udp.md) — Summary and notes on the **UDP protocol**.

---

# # ⚙️ Build & Run

### 🔧 Requirements

- C++ compiler (e.g. `g++`)
- Clone this repo:

```bash
  git clone https://github.com/omargoher/tcp_udp.git
  cd tcp_udp
```

---

### 🚀 Run TCP Server

**Compile:**

```bash
g++ server_code/tcp_server.cpp -o tcp
```

**Run:**

```bash
./tcp
```

**Connect using Telnet:**

```bash
telnet 127.0.0.1 8080
```

---

### 🚀 Run UDP Server

**Compile:**

```bash
g++ server_code/udp_server.cpp -o udp
```

**Run:**

```bash
./udp
```

**Connect using netcat:**

```bash
nc -u 127.0.0.1 8080
```

---

## 📚 Useful Resources

* [Beej's Guide to Network Programming (C/C++)](https://beej.us/guide/bgnet/)
* [Socket Programming Crash Course – YouTube](https://youtu.be/JgsfWw8WKGA?si=niwFIE7Dopv-wtM7)
* [UDP Explained Simply – YouTube](https://youtu.be/rijCvso-TIo?si=84mNEDmboCMqNPoU)
* [TCP Explained Simply – YouTube](https://youtu.be/GbOKlvxunlM?si=nRrCijeZpNvsZyYB)
* [TCP/UDP Full Playlist – YouTube](https://www.youtube.com/watch?v=qqRYkcta6IE&list=PLQnljOFTspQX_Zkt_8teMRsdY4sNt4BX6)

---


