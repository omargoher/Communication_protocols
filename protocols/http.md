
# HTTP
## Index
- [What is HTTP](#what-is-http)
- [HTTP Flow](#http-flow)
- [HTTP different version](#http-different-versions)
  - [HTTP/1.0](#http1.0)
  - [HTTP/1.1](#http1.1)
  - [HTTP/2](#http2)
  - [HTTP/3](#http3)
- [HTTP Message](#http-message)
  - [HTTP request message](#http-request-message)
  - [HTTP response message](#http-response-message)
  - [HTTP Headers](#http-headers)
  - [HTTP Methods ("Verbs")](#http-methods-verbs)
  - [HTTP Status Codes](#http-status-codes)
- [HTTP Authentication](#http-authentication)
- [HTTP Compression](#http-compression)
- [HTTP Cookies](#http-cookies)
- [HTTP Caching](#http-caching)
- [Media types](#media-types)
- [Security](#security)
  - [CORS](#cors)

## What is HTTP
- **HTTP** stands for **HyperText Transfer Protocol**.
- It is an **application-layer protocol** used primarily for transmitting **hypermedia** documents, such as HTML, between clients (typically web browsers) and servers.
### Key Characteristics of HTTP
- **Simplicity**:  
    HTTP uses plain text for messages, making it human-readable and easy to implement.
- **Extensibility**:  
    HTTP supports new features and capabilities through **headers**, **methods**, and **status codes** without changing the core protocol.
- **Statelessness**:  
    Each HTTP request is **independent** — the server does not retain information about previous requests.
    - This improves scalability but makes it harder to track user sessions.
    - **Cookies**, **sessions**, and **tokens** are mechanisms used to simulate stateful behavior.
- **Connection-based (TCP)**:  
    HTTP relies on **TCP** (Transmission Control Protocol) to establish reliable, ordered, and error-checked communication between the client and server.
- **Client-server model**:
    - The **client** (e.g. a browser) initiates the connection, sends an HTTP request, and waits for a response.        
    - The **server** processes the request and returns an HTTP response.
---

## HTTP Flow
The basic flow of an HTTP transaction involves these steps:
1. **Establish a TCP connection**  
    The client initiates a TCP connection with the server (typically on port 80 for HTTP or 443 for HTTPS).
2. **Send HTTP Request**  
    The client sends a properly formatted HTTP request message
3. **Receive HTTP Response**  
    The server processes the request and sends back an HTTP response message.
4. **Close or Reuse the Connection**  
    Depending on the version and headers (like `Connection: keep-alive`), the TCP connection is either closed or reused for further requests.
## HTTP different versions
### HTTP/1.0
- Opens a **new TCP connection** for each request-response cycle.
- Results in **high latency** due to repeated TCP handshakes.
- Multiple connections per page (each image, CSS, JS file = one connection).
- `Host` header is **optional** (not originally part of the protocol).
### HTTP/1.1
- **Persistent Connections**
    - Default behavior: reuse TCP connections for multiple requests/responses.
- **Pipelining** _(rarely used)_
    - Allows sending multiple requests in a row without waiting for responses.
    - **Not widely adopted** due to **Head-of-Line (HOL) blocking**: a slow response blocks all others behind it.
- **Host Header**
    - Now **mandatory**, enabling virtual hosting (multiple domains on one IP).
- **Chunked Transfer Encoding**
    - Allows sending data in chunks without knowing total size upfront — useful for streaming content.
### HTTP/2
- **Single TCP Connection with Multiplexing**
    - All requests/responses share a single TCP connection.
    - Multiple streams run **in parallel**, avoiding HTTP-level HOL blocking.
- **Binary Framing Layer**
    - HTTP messages are encoded as binary frames rather than plain text — more compact and structured.
- **Stream Prioritization**
    - Allows assigning priority levels to different streams to optimize resource delivery.
- **Header Compression (HPACK)**
    - Compresses redundant headers to reduce overhead — especially helpful on mobile networks.
---
### HTTP/3
- **Uses QUIC Instead of TCP**
    - QUIC is a modern transport protocol built on **UDP**, with built-in encryption, reliability, and congestion control.
- **0-RTT and TLS 1.3 Built-in**
    - Supports **0-RTT**: allows sending data immediately during handshake.
    - All communication is **encrypted by default**, integrating TLS into the protocol itself.
- **Multiplexing Without TCP's HOL Blocking**
    - Like HTTP/2, supports parallel streams — but QUIC avoids TCP's packet-level HOL blocking.
- **Ideal for Mobile and Lossy Networks**
    - QUIC handles packet loss and switching networks more gracefully, improving real-world speed and resilience.
---
## HTTP Message
- Message in HTTP/1.1 and earlier are human-readable
- Message in HTTP/2 and after are embedded into binary structure "frame" 
### HTTP request message
![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fimage3.slideserve.com%2F5985213%2Fhttp-request-message-general-format-l.jpg&f=1&nofb=1&ipt=b58ee92ecce7ec789de349f43eeadb35e83bdb4377cf6ad1a01012518df7b495)
#### Example
	```HTTP
	POST /users HTTP/1.1
	Host: example.com
	Content-Type: application/x-www-form-urlencoded
	Content-Length: 49

	name=FirstName+LastName&email=bsmth%40example.com
	```
### HTTP response message
![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fslideplayer.com%2Fslide%2F16252639%2F95%2Fimages%2F13%2FHTTP%2Bresponse%2Bmessage%3A%2Bgeneral%2Bformat.jpg&f=1&nofb=1&ipt=10d73fc326088d3c67df14c2670e66f0f6cea8e63346cd518ae7b803636edd4d)
#### Example
	```HTTP
	HTTP/1.1 201 Created
	Content-Type: application/json
	Location: http://example.com/users/123

	{
	  "message": "New user created",
	  "user": {
	    "id": 123,
	    "firstName": "Example",
	    "lastName": "Person",
	    "email": "bsmth@example.com"
	  }
	}
	```
### HTTP Headers
HTTP headers are key-value pairs sent in both **requests and responses** to carry **metadata** about the HTTP message or resource. Headers help clients and servers describe capabilities, preferences, authentication, caching, content type, and more.
#### Authentication Headers
Used to identify and authenticate the user or client trying to access protected resources.
- **Authorization** Header
	- Sent by the **client** to provide credentials to authenticate itself with the server.
	- Grants access to **protected resources**.
	- Syntax
		- `Authorization: <auth-scheme> <authorization-parameters>`
- **WWW-Authenticate** Header
	- Defines the authentication method that should be used to access a resource.
	- Sent by the **server** in a `401 Unauthorized` response.
	- Tell the client how to Authenticate
	- Syntax
		- `WWW-Authenticate: <challenge>`
			- `challenge = <auth-scheme> <auth-param>, …, <auth-paramN>`
			- `challenge = <auth-scheme> <token68>`
- **Proxy-Authorization** Header
	- Sent by the **client** to authenticate itself with an **intermediate proxy server** (not the origin server).
	- Used when the proxy requires authentication before forwarding the request.
	- Syntax
		- `Proxy-Authorization: <auth-scheme> <credentials>`
- **Proxy-Authenticate** Header
	- Sent by the **proxy server** in a `407 Proxy Authentication Required` response.
	- Tells the client how to **authenticate with the proxy**.
	- Syntax
		- `Proxy-Authenticate: <challenge>`
			- `challenge = <auth-scheme> <auth-param>, …, <auth-paramN>`
			- `challenge = <auth-scheme> <token68>`
- *See [HTTP Authentication](#http-authentication) for more details.*
#### Caching
Caching headers help **browsers and proxies** know when and how to store and reuse resources without contacting the server again — saving time and bandwidth.
- **Cache-Control** Header
	- Tells how and how long a response can be cached.
	- Set caching policies
	- Syntax
		- `Cache-Control: <directive>=<value>, ...`
- **Expire** Header
	- The date/time after which the response is considered stale.
	- If use max-age in cache-control will ignore it
	- Syntax
		- `Expires: <day-name>, <day> <month> <year> <hour>:<minute>:<second> GMT`
- **Age** Header
	- Sent by proxies. Tells how many seconds the resource has already been cached.
	- Syntax
		- `Age: <delta-seconds>`
- **Clear-Site-Data** Header
	- Clears browsing data (e.g., cookies, storage, cache) associated with the requesting website.
	- Syntax
		- `Clear-Site-Data: "cache", "cookies"`

- **Validation & Conditional Requests**
	- These headers let the browser ask the server: **"Has this changed?"**  
	  If not, the server responds with `304 Not Modified`, saving time and bandwidth.
- **ETag** Header
	- ETag - Entity tag
	- Identifier for specific version of resource
	- Syntax
		- `ETag: "<etag_value>"`
- **Last-Modified** Header
	- The last modification date of the resource 
	- Syntax
		- `Last-Modified: <day-name>, <day> <month> <year> <hour>:<minute>:<second> GMT`
- **If-Match** Header
	- Only perform this operation if the ETag **matches**.
	- Syntax
		- `If-Match: <etag_value>`
- **If-None-Match** Header
	- Send me the resource **only if the ETag does NOT match** my cached one.
	- Used with `GET` and `HEAD`.
	- **Response**: `200 OK` (changed) or `304 Not Modified` (unchanged).
	- Syntax
		- `If-None-Match: "<etag_value>"`
- **If-Modified-Since** Header
	- Only perform the action if the resource **was NOT modified since** this date..
	- Syntax
		- `If-Modified-Since: <day-name>, <day> <month> <year> <hour>:<minute>:<second> GMT`
- **If-UnModified-Since** Header
	- Send me the resource **only if it was modified after** this date.
	- Syntax
		- `If-Unmodified-Since: <day-name>, <day> <month> <year> <hour>:<minute>:<second> GMT`
- **Vary** Header
	- how to match request headers to decide whether a cached response can be used
	- Syntax
		- `Vary: <header-name>, …, <header-nameN>`
- *See [HTTP Caching](#http-caching) for more details.*
#### Connection management
control how long the connection between the client and server should stay open.
- **Connection** Header
	- Controls whether the network connection stays open after the current transaction finishes.
	- If the value sent is `keep-alive`, the connection is persistent and not closed.
	- Syntax
		- `Connection: keep-alive`
		- `Connection: close`
 - **Keep-Alive** Header
	- Controls how long a persistent connection should stay open.
	- Syntax
		- `Keep-Alive: <parameters>`
#### Content negotiation
how the client tells the server what kind of content it can accept
- **Accept** Header
	- Tell the server what content types ([MIME Types](#media-types)) the client is will handle.
	- Syntax
		- `Accept: <media-type>/<MIME_subtype>`
 - **Accept-Encoding** Header
	- indicates the content encoding (usually a compression algorithm) that the sender can understand.
	- Syntax
		- `Accept-Encoding: <encoding-algorithm>`
	- see [HTTP Compression](#http-compression) for more
 - **Accept-Language** Header
	- Informs the server about the human language the server is expected to send back.
	- Syntax
		- `Accept-Language: <language>`
 - **Accept-Patch** Header
	- which [media type] the server is able to understand in a `PATCH` request.
	- Syntax
		- `Accept-Encoding: <encoding-algorithm>`
 - **Accept-Post** Header
	- which [media type] the server is able to understand in a `POST` request.
	- Syntax
		- `Accept-Encoding: <encoding-algorithm>`
#### Cookies
Cookies are small pieces of data stored in the browser and sent with each HTTP request.
- Show [HTTP Cookies](#http-cookies) for full explanation.
- **Set-Cookie** Header
	- Sent by the **server** to the browser to **store a cookie**.
	- Syntax
		- `Set-Cookie: <name>=<value>;`
- **Cookie** Header
	- Sent by the **client (browser)** to the server.
	- Syntax
		- `Cookie: <name>=<value>;`
#### Message body information
These headers describe the **content of the HTTP message body**
- **Content-Length** Header
	- The size of the resource, in decimal number of bytes.
	- Syntax
		- `Content-Length: 3495`
- **Content-Type** Header
	- Indicates the [media type](#media-types) of the resource.
	- Syntax
		- `Content-Type: <value>`
- **Content-Encoding** Header
	- Used to specify the compression algorithm.
	- Syntax
		- `Content-Encoding: gzip`
- **Content-Language** Header
	- Specifies the **natural language** of the content.
	- Syntax
		- `Content-Language: en-US`
- **Content-Location** Header
	- Indicates an alternate location for the returned data.
	- Syntax
		- `Content-Location: /cached/page.html`
#### Request context
These headers give the server information about **who is making the request and from where**.
- **Host** Header
	- Specifies the **domain** and **port** of the server being requested.
	- Syntax
		- `Host: omargoher.dev`
- **Referer** Header
	- The address of the previous web page from which a link to the currently requested page was followed.
	- Syntax
		- `Referer: https://google.com/search?q=http`
- **User-Agent** Header
	- Identifies the **browser, operating system, and device** making the request.
	- Syntax
		- `User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)`
#### Redirects
- **Location** Header
	- Specifies the **URL to redirect** the client to.
	- Used with 3xx status codes like `301`, `302`, or `307`.
	- Syntax
		- `Location: https://omargoher.dev/new-page`
---
### HTTP Methods ("Verbs")
HTTP methods define **what action** the client wants the server to perform.
- A **safe** method: does **not change** the state of the server.
- An **idempotent** method: calling it **multiple times** has the **same effect** as calling it **once**.
#### GET
- **Purpose**: Retrieve data (read-only).
- Safe | Idempotent
- **Use when**: You want to **fetch** or **view** data.
- **Example**:
    ```HTTP
    GET / HTTP/1.1
    Host: omargoher.dev
	```
#### HEAD
- **Purpose**: Same as `GET`, but returns **only headers**, no body.
- Safe | Idempotent
- **Use when**: You want to **check metadata**, **verify caching**, or **see if a file exists**.
- **Example**:
    ```HTTP
    HEAD /file.pdf HTTP/1.1
    Host: omargoher.dev
	```
#### POST
- **Purpose**: Send data to the server (e.g., create a new resource).
- Not Safe | Not Idempotent
- **Use when**: You want to **create** something or trigger a **side-effect**.
- **Example**:
    ```HTTP
    POST /api/register HTTP/1.1
    Content-Type: application/json
    
    {
      "name": "Omar",
      "email": "omar@omargoher.dev"
    }
	```
#### PUT
- **Purpose**: Fully replace an existing resource or create one if it doesn’t exist.
- Not Safe | Idempotent
- **Use when**: You want to **fully update** or **upload** a resource.
- **Example**:
    ```HTTP
    PUT /api/users/123 HTTP/1.1
    Content-Type: application/json
    
    {
      "name": "Omar",
      "email": "omar@omargoher.dev"
    }
	``` 
#### PATCH
- **Purpose**: **Partially** update a resource.
- Not Safe | Not Idempotent (usually)
- **Use when**: You want to **change specific fields** in a resource.
- **Example**:
    ```HTTP
    PATCH /api/users/123 HTTP/1.1
    Content-Type: application/json
    
    {
      "email": "omar@gmail.com"
    }
	```
#### DELETE
- **Purpose**: Remove the specified resource.
- Not Safe | Idempotent
- **Use when**: You want to **delete** a resource.
- **Example**:
    ```HTTP
    DELETE /api/users/123 HTTP/1.1
    Host: omargoher.dev
	``` 
#### OPTIONS
- **Purpose**: Ask the server which methods are supported for a resource.
- Safe | Idempotent
- **Use when**: Checking CORS permissions or allowed methods.
- **Example**:
    ```HTTP
    OPTIONS /api/users/123 HTTP/1.1
    Host: omargoher.dev
    ```
---
### HTTP Status Codes
| Code Range | Category      | Meaning                              |
| ---------- | ------------- | ------------------------------------ |
| 1xx        | Informational | Request received, continuing process |
| 2xx        | Success       | Request successfully received        |
| 3xx        | Redirection   | Further action needs to be taken     |
| 4xx        | Client Error  | Client made a bad request            |
| 5xx        | Server Error  | Server failed to fulfill a request   |
#### 1xx – Informational
- 100 Continue
	- Client should continue the request
- 101 Switching Protocols
#### 2xx – Success
- 200 OK
	- Successful GET, POST, etc.
- 201 Created
	- Resource created (POST, PUT)
- 202 Accepted
	- Request accepted, not yet processed
- 204 No Content
	- Successful but no response body
- 206 Partial Content
	- Range requests (e.g., video chunks)
#### 3xx – Redirection
- 301 Moved Permanently
	- The URL of the requested resource has been changed permanently. The new URL is given in the response.
- 302 Found
	- The resource is temporarily at a different URI.
- 303 See Other
	- The server tells the client to **GET another URI** to retrieve the resource.
- 304 Not Modified
	- It tells the client that the response has not been modified, so the client can continue to use the same [cached](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Caching) version of the response.
- 307 Temporary Redirect
	- Same as 302, but **strictly preserves the HTTP method**.
- 308 Permanent Redirect
	- Same as 301 (permanent), but **does not allow changing the method**.
#### 4xx – Client Error
- 400 Bad Request
	- Invalid input or syntax error
- 401 Unauthorized
	- Missing or bad auth
- 403 Forbidden
	- Auth ok, but not allowed
- 404 Not Found
	- Resource doesn't exist
- 405 Method Not Allowed
- 408 Request Timeout
	- Client took too long
- 409 Conflict
	- Duplicate resource
- 410 Gone
	- Resource permanently deleted
- 429 Too Many Requests 
#### 5xx – Server Error
- 500 Internal Server Error
	- Invalid input or syntax error
- 501 Not Implemented
	- Method not supported
- 502 Bad Gateway
	- Invalid response from upstream
- 503 Service Unavailable
	- Server down or overloaded
- 504 Gateway Timeout
	- Upstream server timeout
---
## HTTP Authentication
a **mechanism used to restrict access to resources on a web server** by verifying the identity of a user or client using credentials.
### Flow
1. Client requests a protected resource
	```HTTP
	  GET /admin HTTP/1.1
	  Host: example.com
	```
2. Server responds with `401 Unauthorized`
	- `WWW-Authenticate` Header
		- Used by the **server** to tell the client that it needs to authenticate
	```HTTP
	HTTP/1.1 401 Unauthorized
	WWW-Authenticate: <challenge>
	```
3. Client resends request with credentials
	- `Authorization` Header
		- Used by the **client** to send credentials to the server
	```HTTP
	Authorization: <type> <credentials>
	```
### Types of HTTP Authentication
#### Basic Authentication
- client send username & password for every request
- encoded in `base64`
- **Format**: Base64-encoded `username:password`
- **request Header**
	```HTTP
	Authorization: Basic <base64(username:password)>
	```
- **response Header**
	```HTTP
	WWW-Authenticate: Basic realm="Admin Area"
	```
- The **realm** is just a description for what the user is authenticating to.
- **Security**: Insecure if not using HTTPS (credentials exposed in base64).
- **Use Case**: Testing, internal APIs behind HTTPS, legacy systems.
#### Bearer Authentication
- client to access protected resources by sending a **token** instead of a username/password with each HTTP request.
- **Flow**
	1. **Client logs in with credentials**
		```HTTP
		POST /login Content-Type: application/json  
			{
			  "username": "omar",
			  "password": "1234" 
			}
		```
	2. **Server responds with a token**
		- Usually a JWT (JSON Web Token) or a random string:
			```json
	            {
	            "token":"eyJhbGciOiJIUzI1NiIsInR5cCI6I..." 
				}
		```	
	3. **Client uses the token for all future requests**
		- Each protected request includes the token in the `Authorization` header:
			```HTTP
				GET /api/user 
				Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...
		 ```
	4. **Server verifies the token**
	- If valid ➜ allow access  
	- If expired or invalid ➜ `401 Unauthorized`
- **Token Types**
	- JWT
	- Opaque Token
	- API Keys
### Security 
#### Man-in-the-middle attacks
- An attacker intercepts network traffic between client and server, potentially stealing tokens.
- **Solution**
	- Always use HTTPS
#### Token theft (XSS)
- Malicious scripts injected into your frontend steal tokens from browser storage
- **Solution**
	- Store tokens in HTTP-only cookies
#### Token replay
- An attacker uses a stolen token again and again to access protected resources.
- **Solution**
	- Use **short-lived access tokens** + **refresh tokens**
#### CSRF attacks
- An attacker tricks the user’s browser into making unauthorized requests using their session or token.
- **Solution**
	- Use **SameSite cookies**
	- Use **CSRF tokens**
#### Brute-force login
- An attacker tries thousands of username/password combinations to guess valid credentials.
- **Solution**
	- Use **rate-limiting**
	- Use **CAPTCHA**
---
## HTTP Compression
**reducing the size of the data sent over the network** between a server and a client
### Why?
- Reduced page load times
- Lower bandwidth costs
- Better performance for mobile users and slow networks
- Improved SEO (faster pages = better ranking)
### How is Work?
1. **Client indicates support:**  
    The client sends an `Accept-Encoding` header listing supported compression algorithms.
    - `Accept-Encoding: gzip, deflate, br`
2. **Server compresses response:**
    The server chooses one supported method and compresses the response body.
3. **Server informs client:**  
    The server adds a `Content-Encoding` header telling the client which compression was applied.
    - `Content-Encoding: gzip`
4. **Client decompresses:**  
    The client decompresses the response and displays it to the user.
### Common HTTP Compression Algorithms
- `gzip` - *Most common*
- `deflate`
- `br`
- `compress` - *rarely used now*
---
## HTTP Cookies
is a small piece of data a server sends to a user's web browser.
### Why?
- **Session management**
- **Personalization**
- **Tracking**
### Creating and Updating cookies
- the server create and updating cookies use `Set-Cookie` Header with the response and client store it
	- `Set-Cookie: <cookie-name>=<cookie-value>`
- if have the cookie with the same name update it to the new value
### Remove cookies
- `Expires` attribute
	- `Set-Cookie: id=a3fWa; Expires=Thu, 31 Oct 2021 07:28:00 GMT;`
- `Max-Age` attribute
	- `Set-Cookie: id=a3fWa; Max-Age=2592000`
### HTTP Stateful using cookies
- when server set cookie and client store it, client send cookies with values in the requests using `Cookie` Header
### Security
#### Block access to your cookies
- `Secure` attribute
	- only sent to the server with an encrypted request over the HTTPS protocol
- `HttpOnly` attribute
	- can't be accessed by JavaScript
#### Where cookies are sent
- `Domain` attribute
	- specifies which server can receive a cookie.
	- cookies are available on the specified server and its subdomains.
- `Path` attribute
	- Indicates a URL path that must exist in the requested URL in order to send the `Cookie` header.
#### Controlling third-party cookies 
- `SameSite`
	- `Strict`: browser to only send the cookie in response to requests originating from the cookie's origin site.
	- `Lax` *default*: similar as `strict`, except the browser also sends the cookie when the user _navigates_ to the cookie's origin site (even if the user is coming from a different site).
	- `None`: cookies are sent on both originating and cross-site requests.
#### Cookies prefix
- `__Host-`
	- it's accepted in a `Set-Cookie` header only if 
	- have `Secure` attribute
	- must not include `Domain` 
	- `path` attribute = `/`
- `__Secure-`
	- it's accepted in a `Set-Cookie` header only if 
	- have `Secure` attribute
---
## HTTP Caching
Sore web object to reuse to another requests
### Types of caching
![](https://mdn.github.io/shared-assets/images/diagrams/http/cache/type-of-cache.svg)
#### Private caches "Browser Cache"
- cache tied to a specific client
- `Cache-Control: private`
#### shared caches
- located between the client and the server and can store responses that can be shared among users.
- **Proxy caches** "Forward Proxy Cache"
	- Caching done by middleboxes like proxy servers (e.g., corporate networks, ISPs).
	- Managed by the **client or network** (like ISP)
	- Used to reduce bandwidth usage and speed up access.
	- Not managed by your app—rely only on standard headers to control it.
	- `Cache-Control: public, max-age=3600`
		- the resource can be cached **anywhere** (browser, proxy, CDN), for 1 hour.
	- this caching not work in HTTPS (HTTP + TLS) because message is encrypted 
- **Managed Cache**
	- A **server-side cache** controlled by the developer/site owner.
	- Used to **store responses**, especially static or infrequently changing ones.
	- Managed through **custom configuration**, **code**, or **dashboards**.
	- **types**
		- Reverse proxies
			- Intercepts requests before reaching the origin server
		- CDNs "Content Delivery Network"
			- Distributed network of edge servers near users
		- Service workers with the Cache API
			- JavaScript-controlled caching on the client
### Control Caching
- `Cache-Control` Header
	- `public` Can be stored by any cache (browser, CDN, etc.)
	- `private` Only store in the user's browser
	- `no-cache` Must validate with server before using cached response
	- `no-store` Never store this response in any cache
	- `max-age=SECONDS` How long (in seconds) the resource is fresh
	- `must-revalidate` Once expired, must validate with server before reuse
- Use `ETag`, `If-None-Match`, `Last-Modified`, `If-Modified-Since` to control caching
### Caching Flow
- Client requests resource.
- Server responds with headers: `Cache-Control`, `ETag`, etc.
- Browser or CDN caches the response.
- Future request:
    - If resource still fresh → Use cache.
    - If stale → Revalidate (using ETag or Last-Modified).
## Media types
### Format
- `type/subtype; parameter=value`
### Common media type
#### Text-Based Types
|Media Type|Use Case|
|---|---|
|`text/plain`|Plain text|
|`text/html`|HTML webpages|
|`text/css`|Stylesheets|
|`text/javascript` *|JavaScript code (older usage)|
|`application/javascript`|JavaScript code (modern standard)

#### Data/Document Types
|Media Type|Use Case|
|---|---|
|`application/json`|JSON data (APIs, configs)|
|`application/xml`|XML data|
|`application/pdf`|PDF files|
|`application/rtf`|Rich Text Format documents|
|`application/octet-stream`|Generic binary files (used for downloads)|
#### Image Types
| Media Type      | Use Case                       |
| --------------- | ------------------------------ |
| `image/png`     | PNG images                     |
| `image/jpeg`    | JPEG images                    |
| `image/gif`     | GIF images                     |
| `image/webp`    | Modern web image format        |
| `image/svg+xml` | Scalable Vector Graphics (SVG) |
#### Audio Types
|Media Type|Use Case|
|---|---|
|`audio/mpeg`|MP3 audio|
|`audio/ogg`|OGG audio|
|`audio/wav`|WAV audio|
#### Video Types
|Media Type|Use Case|
|---|---|
|`video/mp4`|MP4 video (most common)|
|`video/webm`|WebM video (web use)|
|`video/ogg`|OGG video|
#### Form & Multipart Types
|Media Type|Use Case|
|---|---|
|`application/x-www-form-urlencoded`|Default for HTML form submission|
|`multipart/form-data`|File uploads|
|`multipart/byteranges`|HTTP range requests (e.g. resume download)|
## Security
### CORS 
CORS - Cross-Origin Resource Sharing
security feature built into web browsers that controls how web pages can make requests to a different origin
![Diagrammatic representation of CORS mechanism](https://mdn.github.io/shared-assets/images/diagrams/http/cors/fetching-page-cors.svg)
#### Why?
- By default, browsers implement the **same-origin policy** for security
- so we need thing allow some different origin if need it
#### Headers
- Access-Control-Allow-Origin
	- Specifies which origin (domain) is allowed to access the resource.
	- `Access-Control-Allow-Origin: https://example.com`
- Access-Control-Allow-Methods
	- Lists which HTTP methods are allowed when accessing the resource in a cross-origin request.
	- `Access-Control-Allow-Methods: GET, POST, PUT, DELETE`
- Access-Control-Allow-Headers
	- Specifies which custom headers the browser can send in the actual request.
	- `Access-Control-Allow-Headers: Content-Type, Authorization`
- Access-Control-Allow-Credentials
	- Tells the browser whether to send credentials (like cookies or HTTP auth) with the request.
	- true - allow credentials
	- false - block credentials
- Access-Control-Max-Age
	- Controls how long the results of a **preflight request** (using `OPTIONS`) can be cached by the browser (in seconds).
	- `Access-Control-Max-Age: 600`
## Resources & References
- [HTTP Documentation](https://developer.mozilla.org/en-US/docs/Web/HTTP)
