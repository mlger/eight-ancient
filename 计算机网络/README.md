## 1. TCP/IP

### **1. 网络接口层 (Network Interface Layer / Link Layer)**

- **功能**：负责在物理介质（如网线、光纤、Wi-Fi）上传输数据帧，处理与硬件的直接交互。
- 核心协议：
  - **以太网 (Ethernet)**、**Wi-Fi (IEEE 802.11)**
  - **ARP**（地址解析协议）：将 IP 地址映射为物理 MAC 地址。
- **数据单位**：**帧 (Frame)**

------

### **2. 网络层 (Internet Layer)**

- **功能**：实现主机到主机的逻辑寻址和路由选择，跨越不同网络传输数据包。
- 核心协议：
  - **IP**（网际协议）：定义 IP 地址和路由规则（IPv4/IPv6）。
  - **ICMP**（控制报文协议）：用于网络诊断（如 `ping`）。
  - **路由协议**：如 OSPF、BGP。
- **数据单位**：**包 (Packet)**

------

### **3. 传输层 (Transport Layer)**

- **功能**：提供端到端（进程到进程）的数据传输控制，确保可靠性和流量管理。
- 核心协议：
  - **TCP**（传输控制协议）：面向连接，保证可靠传输（如文件下载）。
  - **UDP**（用户数据报协议）：无连接，高效但不可靠（如视频流、DNS）。
- **关键概念**：端口号（区分应用程序）、流量控制、错误校验。
- **数据单位**：**段 (Segment)**（TCP）/ **数据报 (Datagram)**（UDP）

------

### **4. 应用层 (Application Layer)**

- **功能**：直接为用户应用程序提供网络服务接口。
- 核心协议：
  - **HTTP/HTTPS**（网页浏览）
  - **DNS**（域名解析）
  - **FTP**（文件传输）
  - **SMTP/POP3**（电子邮件）
  - **SSH**（安全远程登录）
- **数据单位**：应用层报文（Message）

------

### **补充说明**

- **与 OSI 模型对比**：
  - TCP/IP 的 **网络接口层** ≈ OSI 的 **物理层 + 数据链路层**
  - TCP/IP 的 **应用层** ≈ OSI 的 **会话层 + 表示层 + 应用层**
  - **网络层** 和 **传输层** 在两种模型中完全对应。
- **5 层模型**：
   有时将网络接口层拆分为：
  - **物理层**（硬件信号传输）
  - **数据链路层**（MAC 寻址/帧同步）
    形成 **5 层模型**（物理层、链路层、网络层、传输层、应用层）。

## 2. 域名解析

​	![域名解析的工作流程](https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/%E9%94%AE%E5%85%A5%E7%BD%91%E5%9D%80%E8%BF%87%E7%A8%8B/6.jpg)

## 3. TCP 三握四挥

![TCP 三次握手](https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4/%E7%BD%91%E7%BB%9C/TCP%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B.drawio.png)

## 4. ARP 协议

广播获取 IP 地址对应的 MAC 地址

## 5. 网卡

![数据包](https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4/%E7%BD%91%E7%BB%9C/%E6%95%B0%E6%8D%AE%E5%8C%85.drawio.png)

## 6. 交换机

![交换机的 MAC 地址表](https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/%E9%94%AE%E5%85%A5%E7%BD%91%E5%9D%80%E8%BF%87%E7%A8%8B/23.jpg)

当地址表中找不到指定 MAC 地址时, 将包转发到除了源端口的所有端口.

