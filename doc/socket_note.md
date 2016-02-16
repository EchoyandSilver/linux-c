##网络编程
#### 课程内容
* Linux网络编程之TCP/IP基础篇
* Linux网络编程之socket编程篇
* Linux网络编程之进程间通信
* Linux网络编程之线程篇
* Linux网络编程之实战篇（miniftpd实现）



### 01TCP/IP基础（一）
#### 本章目标
* ISO/OSI参考模型
* TCP/IP 四层模型
* 基本概念（对等通信，封装，分用，端口）

#### 1.模型对比
	
	应用层					
	表示层
	会话层		……^－－－－－－－－－－>应用层
	传输层		－－－－－－－－－－－－>传输层
	网络层		－－－－－－－－－－－－>网络层
	数据链路层  ……ν－－－－－－－－－－>链路层
	物理层
	
### 02TCP/IP基础（二）
#### 本章目标
* 最大传输单元（MTU）/路径MTU
* 以太网帧格式
* ICMP(协议用于传递差错信息，时间，回显，网络信息等控制数据)
* ARP（地址解析协议）
* RARP（反地址解析协议）

### 03TCP/IP基础（三）
#### 本章目标
* IP数据报格式
* 网际校验和
* 路由

### 04TCP/IP基础（四）
#### 本章目标
* TCP特点
* TCP报文格式
* 连接建立三次握手
* 连接终止四次握手
* TCP如何保证可靠性

#### 1.TCP特点
* 基于字节流
* 面向连接
* 可靠传输
* 缓存传输
* 全双工
* 流量控制

#### 2.TCP报文格式
	（1）源端口号与目的端口号
	（2）序号
	（3）确认号
	（4）头部长度：4位，TCP头部最多60个字节
	（5）保留位：6位，必须为0
	（6）6个标志位：
			URG：紧急指针有效
			ACK：确认序号有效
			PSH：接收方应尽快将这个报文段交给应用层
			RST：连接重置
			SYN：同步序号要用来发起一个连接
			FIN：表示将要终止一个连接
	（7）窗口大小（通过窗口来达到流量控制）
	（8）校验和（对tcp头与数据进行校验）
	（9）紧急指针
	（10）选项与填充（选项为4字节整数倍，否则用0填充）

### 05TCP/IP基础（五）
#### 本章目标
* 滑动窗口协议
* UDP特点
* UDP报文格式

#### 1.UDP特点
* 无连接
* 不可靠
* 一般情况下UDP更加高效

### 06socket编程（一）
#### 1.什么是socket
*  socket可以看成是用户进程与内核网络协议栈的编程接口
*  socket不仅可以用于本机的进程间通信，还可以用于网络上不同主机的进程间通信。

#### 2.IPv4套接口地址结构
* 通常也称为“网际套接字地址结构”，以“sockaddr_in”命名，定义在头文件<netinet/in.h>中。

struct sockaddr_in{  
	
	uint8 sin_len;  	
	sa_family_t sin_family;
	in_port_t sin_port;
	struct in_addr sin_addr;
	char sin_zero[8];
｝

* sin_len:整个sockaddr_in机构体的长度。
* sin_family:指定该地址家族，在这里必须设为AF_INET。
* sin_port:端口。
* sin_addr:IPv4的地址。
* sin_zero:暂时不用，一般将其设置为0。

#### 2.通用地址结构
* 通用地址结构用来指定与套接字关联的地址
 
 struct sockaddr{
 
	    uint8_t sin_len;  
   		sa_family_t sin_family;
   		char sa_data[14];

 }
 
* sin_len:整个sockaddr结构体的长度。
* sin_family:指定地址家族。
* sa_data:由sin_family决定它的形式。

#### 3.网络字节序
* 大端字节序：最高有效位存储于最低内存地址，最低有效位存储于最高内存地址处。
* 小短字节序：最高有效位存储于最高内存地址，最低有效位存储于最低内存地址处。
* 网络字节序规定为大端字节序。

#### 4.地址转换函数

* `#include <netinet/in.h> `
* `#include <arpa/inet.h>`
* `int inet_aton(const char *cp,struct in_addr *inp)`
* `in_addr_t inet_addr(const char *cp)`
* `char *inet_ntoa(struct in_addr in)` 

#### 5.套接字类型
* 流式套接字（SOCK_STREAM）：提供面向连接的，可靠的数据传输服务，数据无差错，无重复的发送，且按发送顺序接收。
* 数据报套接字（SOCK_DGRAM）：提供无连接的服务，不提供无错保证，数据可能丢失或重复，并且接收顺序混乱。
* 原始套接字（SOCK_RAW）

### 07socket编程（二）
#### 本章目标
* TCP客户/服务器模型
* 回射客户/服务器
* socket,bind,listen,accept,connect

#### 1.socket函数
* 包含头文件<sys/socket.h>
* 功能：创建一个套接字用于通信。
* 原型：

		int socket(int domain, int type, int protocol);

* 参数：

		domain:指定通信协议族（protocol family）。
		type:指定socket类型，流式套接字SOCK_STREAM,数据报套接字SOCK_DGRAM,原始套接字SOCK_RAM.
		protocol:协议类型。
		
* 返回值：成功返回非负整数，它与文件描述符类似，我们把它称为套接口描述字，简称套接字。失败返回－1.

#### 2.bind函数
* 包含头文件<sys/socket.h>
* 功能：绑定一个本地地址到套接字
* 原型：

		int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
		
* 参数：

		 sockfd:socket函数返回的套接字
		 addr:要绑定的地址
		 addrlen:地址长度
		 
#### 3.listen函数
* 包含头文件<sys/socket.h>
* 功能：将套接字用于监听进入的连接
* 原型：

		int listen(int sockfd, int backlog);
		
* 参数：

		sockfd:socket函数返回的套接字
		backlog:规定内核为此套接字排队的最大连接个数
		
* 返回值：成功返回0，失败返回－1.

* 一般来说，listen函数应该在调用socket和bind函数之后，调用函数accept之前调用。
* 对于给定的监听套接口，内核要维护两个队列：
		
		1，已由客户发出并到达服务器，服务器正在等待完成相应的TCP三次握手过程。
		2.已完成连接的队列。
		
#### 4.accept函数
* 包含头文件<sys/socket.h>
* 功能：从已完成连接队列返回第一个连接，如果已完成连接队列为空，则阻塞。
* 原型：

		int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
		
* 参数：

		sockfd:服务器套接字
		addr：将返回对方的套接字地址
		addrlen：返回对等方的套接字地址长度
		
* 返回值：成功返回非负整数，失败返回－1.

#### 5.connect函数
* 包含头文件<sys/socket.h>
* 功能：建立一个连接至addr所指的套接字
* 原型：

		int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
		
* 参数：

		sockfd:未连接的套接字
		addr:要连接的套接字地址
		addrlen:第二个参数addr长度
		
* 返回值：成功返回0，失败返回－1。

### 08socket编程（三）
#### 本章目标
* SO_REUSEADDR
* 处理多客户连接（process-per-conection）
* 点对点聊天程序实现

#### 1.SO_REUSEADDR
* 服务器端尽可能使用SO_REUSEADDR
* 在绑定之前尽可能调用setsockopt来设置SO_REUSEADDR套接字选项。
* 使用SO_REUSEADDR选项可以使得不必等待TIME_WAIT状态就可以重启服务器。


### 09socket编程（四）
#### 1.流协议与粘包
* tcp:  传送字节流，无边界。  udp:消息，数据包，有边界。
* 粘包本质上是在应用层维护消息与消息的边界。

#### 2.粘包的解决方案：
* 定长包，包尾加\r\n(ftp)，包头加上包体长度，更复杂的应用层协议。

### 10socket编程（五）
#### 本章目标
* read, write与 recv, send
* readline实现
* 用readline实现回射客户服务器
* getsockname, getpeername
* gethostname, gethostbyname, gethostbyaddr

### 11socket编程（六）
#### 1.TCP 回射客户／服务器。
* tcp是基于字节流传输的，只维护发送出去多少，确认了多少，没有维护消息与消息之间的边界，因而可能导致粘包问题。
* 粘包问题解决方法是在应用层维护消息边界。

#### 2.避免僵尸进程方法：
* (1)signal(SIGCHLD,SIG_IGN)
* (2)signal(SIGCHLD,handle_sigchld)

	`void handle_sig(int sig)`

	{
	
		/*	wait(NULL);	*/
		while(waitpid(-1,NULL,WNOHANG) > 0)
			;
	}
	
### 12socket编程（七）
#### 本章目标
* TCP11种状态
* 连接建立三次握手，连接终止四次握手
*  TIME_ WAIT与SO_ REUSEADDR
*  SIGPIPE

#### 1.SIGPIPE
* 往一个已经接收的FIN的套接字中写是允许的，接收到FIN仅仅代表对方不再发送数据。
* 在收到RST段之后，如果再调用write就会产生SIGPIPE信号，对于这个信号的处理我们通常忽略即可。

		signal(SIGPIPE, SIG_IGN);
	
	
		
	
### 13socket编程（八）
#### 1.五种I/O模型
* 阻塞I/O
* 非阻塞I/O : fcntl(fd,F_SETFL,flag|O_NONBLOCK)
* I/O复用(select和poll)
* 信号驱动I/O : 拉的机制，系统调用sigaction。
* 异步I/O : 推的机制，效率最高，调用aio_read。

#### 2.select
`int select(int nfds,fd_set *readfds,fd_set *writefds,fd_set *exceptfds,struct timeval *timeout);`

	void FD_CLR(int fd,fd_set);

	int FD_ISSET(int fd, fd_set *set);

	void FD_SET(int fd,fd_set *set);

	void FD_ZERO(fd_set *set);
	
* 参数的意思：感兴趣的文件描述符最大值＋1，可读事件集合，可写事件集合，异常事件集合，超时
	
### 14socket编程（九）
#### 本章目标
* select
* 读，写，异常事件的发生条件
* 用select改进回射服务器程序（并发服务器）

#### 1.select
* 中心管理器，管理多个I/O
* select并发服务器而不是并行
	
#### 2.读，写，异常事件发生条件
##### 可读：
* 套接口缓冲区有数据可读。
* 连接的读一半关闭，即接收到FIN段，读操作将返回0。
* 如果是监听套接口，已完成连接队列不为空时。

##### 可写：
* 套接口发送缓冲区有空间容纳数据。
* 连接的写一半关闭，即收到RST段之后，再调用write操作（SIGPIPE）。

##### 异常：
* 套接口存在外带数据

### 15socket编程（十）
#### 本章目标
* close与shutdown区别
* 进一步改进回射客户程序

####1.close与shutdown区别
* close终止了数据传送的俩个方向
* shutdown可以有选择的终止某个方向的数据传送或者终止数据传送的两个方向。
* shutdown how=1就可以保证对等方接收到一个EOF字符，而不管其他进程是否已经打开套接字。而close不能保证，直到套接字引用计数减为0时才发送。也就是说直到所有的进程都关闭了套接字。

### 16socket编程（十一）
#### 本章目标
* 套接字I/O超时设置方法
* 用select实现超时：

	1.read_timeout函数封装
	
	2.write_timeout函数封装
	
	3.accept_timeout函数封装
	
	4.connect_timeout函数封装
	
#### 1.套接字I/O超时设置方法
* alarm
* 套接字选项：

	(1)SO_SNDTIMEO 	
	(2)SO_RCVTIMEO
	
* select

#### 2.用select实现超时

* int read_timeout(int fd, unsigned int wait_seconds)
* int write_timeout(int fd, unsigned int wait_seconds)
* int accept_timeout(int fd, struct _ in *addr, unsigned int wait_seconds)
* int connect_timeout(int fd,struct sockaddr _ in *addr, unsigned int wait_seconds)

### 17socket编程（十二）
#### 本章目标
* 	select的限制
*  poll

#### 1.select限制
* 用select实现的并发服务器，能达到的并发数，受两方面限制

 1.一个进程能打开的最大文件描述符限制。这可以通过调整内核参数。

 （1）ulimit -n number(1024)	 
 （2）getrlimit(RLIMIT_NOFILE,&rlimit)  
 （3）setrlimit(RLIMIT_NOFILE,&rlimit)
 
 2.select的fd_set集合容量的限制（FD _ SETSIZE），这需要重新编译内核。
 
 #### 2.poll（可以替换select）

* int poll(struct pollfd *fd, nfds_t nfds, int timeout)  


### 18socket编程（十三）
#### 本章目标
* epoll使用
* epoll与select,poll区别
* epoll LT/ET模式

#### 1.poll的使用

	#include <sys/epoll.h> 
	int epoll_create(int size);
	int epoll_create1(int flags);
	int epoll_ctl(int epfd, int fd, struct epoll_event *event);
	int epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);
	
#### 2.epoll与select，poll区别
* 相比于select与poll,epoll最大的好处在于他不会随着监听fd数目增多而降低效率。
* 内核中的select与poll的实现是采用轮询来处理的，轮询的fd数目越多，自然耗时越多。
* epoll的实现是基于回调的，如果fd有期望的事件发生就通过回调函数将其加入epoll就绪队列中，也就是说它只关心‘活跃’的fd，与fd数目无关。
* 如何让内核把fd消息通知给用户空间？在这个问题上select/poll采取了内存拷贝方法，而epoll采用了共享内存的方式。
* epoll不仅会告诉应用程序有I/O 事件到来，还会告诉应用程序相关的信息，这些信息是应用程序填充的，因此根据这些应用信息应用程序就能直接定位到事件，而不必遍历整个fd集合，

#### 3.epoll  LT/ET模式
* EPOLLLT: 完全靠kernel epoll驱动，应用程序只需要处理从epoll_wait返回的fds,这些fds我们认为它们处于就绪状态。 
* EPOLLET
	
	（1）在这种模式下，系统仅仅通知应用程序哪些fds变成了就绪状态，一旦fd变成了就绪状态，epoll将不再关注这个fd的任何状态信息，（从epoll队列中移除）直到应用程序通过读写操作触发EAGAIN状态，epoll认为这个fd又变为空闲状态，那么epoll又重新关注这个fd的状态变化（又重新加入epoll队列）
	
	（2）随着epoll_wait的返回，队列中的fds是在减少的，所以在大并发的系统中，EPOLLET更有优势。对程序员的要求也就越高。

### 19socket编程（十四）
#### 本章目标
* UDP特点
* UDP客户／服务基本模型
* UDP 回射客户／服务器
* UDP注意点

#### 1.UDP特点
	（1）无连接
	（2）基于消息的数据传输服务
	（3）不可靠
	（4）一般情况下UDP更加高效
	
#### 2.UDP注意点
* UDP报文可能会丢失，重复。
* UDP报文可能会乱序。
* UDP缺乏流量控制。
* UDP协议数据报文截断。
* recvfrom返回0，不代表连接关闭，因为udp是无连接的。
* ICMP异步错误。
* UDP connect。
* UDP外出接口的确定。

### 20socket编程（十五）
#### 本章目标
* UDP聊天室的实现

### 21socket编程(十六)
#### 本章目标
* UNIX域协议特点
* UNIX域地址结构
* UNIX域字节流回射客户／服务
* UNIX域套接字编程注意点

#### 1.UNIX域协议特点
* UNIX域套接字与TCP套接字相比较，在同一台主机的传输速度前者是后者的两倍。
* UNIX域套接字可以在同一台主机上各进程之间传递描述符。
* UNIX域套接字与传统套接字的区别是用路径名来表示协议族的描述。

 #### 2.UNIX域地址结构
 		
 		#define UNIX_PATH_MAX 108
 		
 		struct sockaddr_un{
 			sa_family  sun_family;	/* AF_UNIX */
 			char  sun_path[UNIX_PATH_MAX];  /*pathname*/
 		}
 		
#### 3.UNIX套接字编程注意点
 * bind成功将会创建一个文件，权限为0777&~umask。
 * sun path最好用一个绝对路径。
 * UNIX域协议支持流式套接口与报式套接口。
 * UNIX域流式套接字connect发现监听队列满时，会立刻返回一个 ECONNREFUSED,这和TCP不同，如果监听队列满，会忽略到来的SYN,z这导致对方重传SYN.

### 22socket编程（十七）
#### 本章目标
* socketpair
* sendmsg/recvmsg
* UNIX域套接字传递描述字

#### 1.socketpair
* 创建一个全双工的流管道
* 原型
   
		int socketpair(int domain, int type, int protocol, int sv[2]);
		
* 参数

		domain:协议家族
		type:套接字类型
		protocol:协议类型
		sv:返回套接字对
		
* 返回值：成功返回0；失败返回－1；

#### 2.sendmsg/recvmsg
* ssize_t sendmsg(int socketfd, const struct msghdr *msg, int flags);
* ssize_t recvmsg(int socketfd, struct msghdr *msg, int flags);

#### 3.辅助数据处理宏
	
	（1）struct cmsghdr *CMSG_FIRSTHDR(struct msghdr);
	（2）struct cmsghdr *CMSG_NXTHDR(struct msghdr *msgh,struct cmsghdr *cmsg);
	（3）size_t CMSG_ALIGN(size_t length);
	（4）size_t CMSG_SPACE(size_t length);
	（5）size_t CMSG_LEN(size_t length);
	（6）unsigned char *CMSG_DATA(struct cmsghdr *cmsg);
	
### 23进程间通信介绍(一)
#### 本章目标
* 进程同步与进程互斥
* 进程间通信发展
* 进程间通信分类
* 进程间共享信息的三种方式
* IPC对象的持续性

#### 1.顺序程序与并发程序特征
* 顺序程序特征
		
		（1）顺序性
		（2）封闭性
		（3）确定性
		（4）可再现性
		
* 并发程序特征

		（1）共享性
		（2）并发性
		（3）随机性
		
#### 2.进程间通信的目的
* 数据传输
* 资源共享
* 通知事件
* 进程控制

#### 3.进程间通信分类
	
	（1）文件（2）文件锁（3）管道（pipe）和有名管道（FIFO）
	（4）信号（signal）（5）消息队列 （共享内存）（6）共享内存
	（7）信号量 （8）互斥量 （9）条件变量 （10）读写锁	
	（11）套接字（socket）
	
#### 4.System V IPC & POSIX IPC
* System V IPC

		（1）System V 消息队列
		（2）System V 共享内存
		（3）System V 信号量
	
* POSIX IPC 

		（1）消息队列
		（2）共享内存
		（3）信号量
		（4）互斥量
		（5）条件变量
		（6）读写锁
		
#### 5.进程间共享信息的三种方式
* 文件系统
* 内核中的共享信息
* 共享内存区

#### 6.IPC对象的持续性
* 随进程持续：一直存在直到打开的最后一个进程结束。（如pipe和FIFO）
* 随内核持续：一直存在直到内核自举或显式删除。（如System消息队列、共享内存、信号量）
* 随文件系统持续：一直存在到显式删除，即使内核自举还存在。（POSIX消息队列、共享内存、信号量如果是使用映射文件来实现的）

### 24进程间通信介绍（二）
#### 本章目标
* 死锁
* 信号量与PV原语
* 用原语解决司机与售票员问题
* 用原语解决明航售票问题
* 用原语解决汽车租赁问题

#### 1.死锁
* 死锁是指多个进程之间等待对方的资源，而在得到对方的资源之前又不释放自己的资源，这样造成循环等待的一种现象。如果所有进程都在等待一个不可能发生的事，则进程就死锁了。
* 死锁产生的必要条件

		（1）互斥条件：进程对资源进行排它性使用，即在一段时间内某些资源仅为一个进程所占用。
		（2）请求和保持条件：当进程因请求资源而阻塞时，对已获得的资源保持不放。
		（3）不可剥夺条件：进程已获得的资源在未使用完之前，不能被剥夺，只能在使用完时自己释放。
		（4）环路等待条件：各个进程组成封闭的环形链，每个进程都等待下一个进程所占用的资源。
	
* 防止死锁办法

		（1）资源一次性分配：（破坏请求和保持条件）
		（2）可剥夺资源：（破坏不可剥夺条件）
		（3）资源有序分配法：（破坏循环等待条件）
		
#### 2.信号量

	（1）信号量
			
			互斥： P、V在同一个进程中
			同步： P、V在不同进程中
			
	（2） 信号量含义
	
			S > 0: S表示可用资源的个数
			S = 0: 表示无可用资源， 无等待进程
			S < 0: |S|表示等待队列中进程个数
			
	（3）信号量
	
			struct semaphore
			{
				int value;
				pointer_PCB queue;
			}
			
	(4) P原语
	
			　p(s)
			　{
			　	s.value = s.value--;
			　	if(s.value < 0)
			　	{
			　		将进程状态置为等待状态
			　		将该进程的PCB插入相应的队列s.queue末尾
			　	}
			　						　
			　}
			　
	（5）V原语
	
			V(s)
			{
				s.value = s.value++;
				if(s.value <= 0)
				{
						唤醒相应的等待队列s.queue中等待的一个进程
						改变其状态为就绪态
						并将其插入就绪队列
				}				
			}
			
#### 3.用原语解决司机与售票员问题
* 解决同步问题

		司机进程：					售票员进程：
		S1(0);						s(2);
		while(1)					while(1)
		{							{
			P(S1)						关门
			启动车辆					V(S1)
			正常运行					售票
			到站停车					p(s2)
			v(s2)						开门
		}							}
		
#### 4.用PV原语解决民航售票问题
* 解决互斥问题

			票数 ＝ x
			S(1)
			
			P(S)
			if(x > 0)
				x--;
			V(S)
			
#### 5.用PV原语解决汽车租赁问题
* 解决同类资源

			S(2)
			P(S)
			租车
			还车
			V(S)
			
### 25 System V消息队列（一）
#### 本章目标
* 消息队列
* IPC对象数据结构
* 消息队列结构
* 消息队列在内核中的表示
* 消息队列函数

#### 1.消息队列
* 消息队列提供了从一个进程向另一个进程发送一块数据的方法。
* 每个数据块都被认为是有一个类型，接收者进程接收的数据块可以有不同的类型值。
* 消息队列也有管道一样的不足，就是每个消息最大长度是有限的（MSGMAX），每个消息队列的总字节数是有上限的（MSGMNB），系统上消息队列的总数也有一个上限（MSGMNI）。

#### 2.IPC对象的数据结构
* 内核为每个IPC对象维护一个数据结构
		
		struct ipc_perm{
			key_t  __key;	/* Key supplied to xxxget(2) */
			uid_t  uid; /* Effective UID of owner */
			gid_t  gid; /* Effective GID of owner */
			uid_t  cuid; /* Effective UID of creator */
			gid_t  cgid; /* Effective GID of creator */
			unsigned short modde; /* Permissions */
			unsigned short __seq; /* Sequence number */
		}
		
#### 3.消息队列结构
* 
	
 		struct msqid_ds{
			struct ipc_perm  msg_perm;
			time_t           msg_stime;
			time_t 			 msg_rtime;
			time_t 			 msg_ctime;
			unsigned long 	 __msg_cbytes;
			msgqnum_t 		 msg_qnum;
			msglen_t 			 msg_qbytes;
			pid_t				 msg_lspid;
			pid_t				 msg_lrpid;
		}
	
#### 4.消息队列函数
* 头文件

		#include <sys/types.h>
		#include <sys/ipc.h>
		#include <sys/msg.h>
		
* 相关函数

		in msgget(key_t, int msgflg);
		int msgctl(int msqid, int cmd, struct msqid_ds*buf);
		int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
		ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
		
* msgget函数
	
		（1）功能：用来创建和访问一个消息队列
		（2）原型：int msgget(key_t key, int msgflg)
		（3）参数：
				key:某个消息队列的名字
				msgflg:由九个权限标志构成，它们的用法和创建文件时使用的mode模式标志是一样的
		（4）返回值：成功返回一个非负数，即该消息队列的识别码；失败返回－1；
		
* msgctl函数

		（1）功能：消息队列控制函数
		（2）原型： int msgctl(int msqid, int cmd, struct msqid_ds *buf);
		（3）参数：
			msqid:由msgget函数返回的消息队列识别码
			cmd:是将要采取的动作（有三个可取值）
		（4）返回值：成功返回0，失败返回－1.
		
* cmd:将要采取的动作（三个可取值），分别如下：

		（1）IPC_STAT:把msqid_ds结构中的数据设置为消息队列的当前关联值。
		（2）IPC_SET:在进程有足够权限前提下，把消息队列的当前关联值设置为 msqid_ds数据结构中给出的值。
		（3）IPC_RMID:删除消息队列。
		
### 26 System V 消息队列（二）
#### 本章目标
* msgsnd函数
* msgrcv函数

#### 1.msgsnd函数
* 功能：把一条消息添加到消息队列中
* 原型

		int msgsnd(int msqid, const void *msgp,size_t msgsz, int msgflg);
		
* 参数

		msgid:由msgget函数返回的消息队列标识码。
		msgp:是一个指针，指针指向准备发送的消息。
		msgsz:是msg指向的消息长度，这个长度不含保存消息类型的那个long int 长整型。
		msgflg:控制着当前消息队列满或到达上限时将要发生的事情
		
* 返回值：成功返回0，失败返回－1

* msgflg=IPC_NOWAIT表示队列满不等待，返回 EAGAIN错误。
* 消息结构在两方面受到制约。首先，它必须小于系统规定的上限值；其次，它必须以一个long int 长整数开始，接收者函数将利用这个长整数确定消息的类型。
* 消息结构参考形式如下：

		struct msgbuf{
			long mtype;
			char mtext[1];
		}
		
#### 2.msgrcv函数
* 功能：从一个消息队列接收消息
* 原型
		
		int msgrcv(int msqid, void *msgp,size_t msgsz, long msgtyp, int msgflg);

* 参数

		msgid:由msgget函数返回的消息队列标识码。
		msgp:是一个指针，指针指向准备发送的消息。
		msgsz:是msg指向的消息长度，这个长度不含保存消息类型的那个long int 长整型。
		msgtype:它可以实现接收优先级的简单形式。
		msgflg:控制着队列中没有相应类型的消息可供接收时将要发生的事。
		
* 返回值：成功返回实际放到接收缓冲区里去的字符个数，失败返回－1。
* msgtype=0返回队列第一条信息。
* msgtype>0返回队列第一条类型等于msgtype的消息。
* msgtype<0返回队列第一条类型小于等于msgtype绝对值的消息。
* msgflag=IPC_NOWAIT,队列没有可读消息不等待，返回ENOMSG错误。
* msgflg=MSG_NOERROR,消息大小超过msgsz时被截断。
* msgtype>0且msgflg=MSG_EXCEPT，接收类型不等于msgtype的第一条消息。

### 27 System V消息队列（三）
####本章目标
* 消息队列实现回射客户／服务器

### 28 共享内存介绍
#### 本章目标
* 共享内存
* 管道、消息队列与共享内存传递数据对比
* mmap函数
* munmap函数
* msync函数

#### 1.共享内存
* 共享内存区是最快的IPC形式。一旦这样的内存映射到共享它的进程的地址空间，这些进程间数据传递不再涉及到内核，换句话说是进程不再通过执行进入内核的系统调用来传递彼此的数据。

#### 2.mmap函数
* 功能：将文件或者设备空间映射到共享内存区。
* 原型：void *mmap(void *addr, size_ t len, int prot, int flags, int fd, off_t offset);
* 参数：

		addr:要映射的起始地址，通常指定为NULL，让内核自动选择。
		len:映射到进程地址空间的字节数。
		prot:映射区保护方式。
		flags:标志。
		fd:文件描述符。
		offset：从文件头开始的偏移量。
		
* 返回值：成功返回映射到内存区的起始地址；失败返回－1.

* mmap函数prot参数

		PROT_READ:	页面可读
		PROT_WRITE:	页面可写
		PROC_EXEC:	页面可执行
		PROT_NONE:	页面不可访问
		
* mmap函数flags参数

		MAP_SHARED:	变动是共享的
		MAP_PRIVATE:	变动是私有的
		MAP_FIXED:	准确解释addr参数
		MAP_ANONYMOUS：建立匿名映射区，不涉及文件
		
#### 3.munmap函数
* 功能：取消 mmap函数建立的映射
* 原型：int munmap(void *addr, size_t len);
* 参数：

		addr : 映射的内存起始地址
		len : 映射到进程地址空间的字节数
		
* 返回值：成功返回0；失败返回－1.

### 4.msync函数
* 功能：对映射的共享内存执行同步操作
* 原型：int msync(void *addr, size_t len, int flags);
* 参数：

		addr : 内存起始地址
		len : 长度
		flags : 选项
		
* 返回值：成功返回0；失败返回－1。
* msync函数flags:

		MS_ASYNC:执行异步写
		MS_SYNC:执行同步写
		MS_INVALIDATE:使高速缓存的数据实效
		
* mmap注意点

		（1）：映射不能改变文件的大小。
		（2）可用于进程间通信的有效地址空间不完全受限于被映射文件的大小。
		（3）：文件一旦被映射后，所有对映射区域的访问实际上是对内存区域的访问。映射区域内容写回文件时，所写内容不能超过文件的大小。
		
### 29 System V 共享内存
#### 本章目标
* 共享内存数据结构
* 共享内存函数
* 共享内存示例

#### 1.共享内存数据结构
	struct shmid_ds{
		struct ipc_perm shm_perm; /*Ownership and permissions*/
		size_t      shm_segsz; /*Size of segment(bytes)*/
		time_t      shm_atime; /*Last attach time*/
		time_t      shm_dtime; /*Last detach time*/
		time_t      shm_ctime; /*Last change time*/
		pid_t       shm_cpid; 	/*PID of creator*/
		pid_t       shm_lpid;	/*PID of last shmat(2)/shmdt(2)*/
		shmatt_t    shm_nattch;	/*NO. of current attaches*/
	}
	
#### 2.共享内存函数
		#include <sys/ipc.h>
		#include <sys/shm.h>
		
		int shmget(key_t, size_t size, int shmflg);
		void *shmat(int sgmid, const void *shmaddr, int shmflg);
		int shmdt(const void *shmaddr);
		int shmctl(int shmid, int cmd, struct shmid_ds *buf);
		
#### 3.shmget函数
* 功能：用来创建共享内存
* 原型：int shmget(key_t key, size _t size, int shmflg);
* 参数：

		key:这个共享内存段名字
		size:共享内存大小
		shmflg:由九个权限标志构成，它们的用法和创建文件时使用的mode模式标志是一样的
		
* 返回值：成功返回一个非负整数，即该共享内存段的标识码；失败返回－1.

#### 4.shmat函数
* 功能：将共享内存段连接到进程地址空间
* 原型：void *shmat(int shmid, const void *shmaddr, int shmflg);
* 参数：

		shmid:共享内存标识
		shmaddr:指定连接的地址
		shmflg:它的两个可能取值是SHM_RND和SHM_RDONLY
		
* 返回值：成功返回一个指针，指向共享内存第一个字节；失败返回－1。
* shmaddr为NULL，核心自动选择一个地址。
* shmaddr不为NULL且shmflg无SHM_RND标记，则以shmaddr为连接地址。
* shmaddr不为NULL且shmflg设置了SHM_RND标记，则连接的地址自动向下调整为SHMLBA的整数倍。公式：shmaddr - (shmaddr%SHMLBA).
* shmflg=SHM_RDONLY,表示连接用来只读共享内存。

#### 5.shmdt函数
* 功能：将共享内存段与当前进程脱离
* 原型：int shmdt(const void *shmaddr);
* 参数：shmaddr：由shmat所返回的指针
* 返回值：成功返回0；失败返回－1.
* 注意：将共享内存段与当前进程脱离不等于删除共享内存段

#### 6.shmctl函数
* 功能：用来创建和访问一个共享内存
* 原型：int shmctl(int shmid, int cmd, struct shmid_ds *buf);
* 参数

		shmid:由shmget返回的共享内存标识码
		cmd:将要采取的动作（有三个可取值）
		buf:指向一个保存着共享内存的模式状态和访问权限的数据结构
	
* 返回值：成功返回0；失败返回－1.

* shmctl函数

		IPC_STAT:把shmid_ds结构中的数据设置为共享内存的当前关联值。
		IPC_SET:在进程有足够权限的前提下，把共享内存的当前关联值设置为shmid_ds数据结构中给出的值。
		IPC_RMID:删除共享内存段。
		
### 30 System V	 信号量
#### 本章目标
* 信号量
* 信号量集结构
* 信号量集函数
* 信号量示例

#### 1.信号量
* 信号量和P,V原语是由dijkstra(迪杰斯特拉提出)
* 信号量：

		互斥：P,V在同一个进程中
		同步：P,V在不同进程中
		
* 信号量值含义

		S>0: S表示可有资源的个数
		S=0: S表示无可用资源，无等待进程
		S<0: ｜S｜表示等待队列中进程的个数
		
		struct semaphore
		{
			int value;
			pointer_PCB queue;
		}

#### 2.信号量集结构


	struct semid_ds{
		struct ipc_perm   sem_perm; /*Ownership and permissions*/
		time_t 			  sem_otime; /*Last semop time*/
		time_t 		      sem_ctime; /*Last change time*/
		unsigned short    sem_nsems; /*No.of semaphores in set*/
		}
	
#### 3.信号量集函数
	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/sem.h>
	
	int senget(key_t key, int nsems, int semflg);
	int semctl(int semid, int semnum, int cmd, ...);
	int semop(int semid, struct sembuf *sops, unsigned nsops);
	
#### 4.semget函数
* 功能：用来创建和访问一个消息队列。
* 原型：int semget(key_t key, int nsems, int semflg);
* 参数

		key:信号集的名字
		nsems:信号集中信号量的个数
		semflg:由九个权限标志构成，它们的用法和创建文件使用的mode模式标志是一样的。
		
*  返回值：成功返回一个非负整数，即该信号集的标识码；失败返回－1.

#### 5.shmctl函数
* 功能：用于控制信号量集
* 原型：int semctl(int semid, int semnum, int cmd, ...);
* 参数

		semid:由semid返回的信号量标识码
		semnum:信号集中信号量的序号
		cmd:将要采取的动作（有三个可取值）
		最后一个参数根据命令不同而不同
		
* 返回值：成功返回0，失败返回－1.

		SETVAL:设置信号量集中的计数值。
		GETVAL:获取信号量集中的信号量计数值。
		IPC_STAT:把semid_ds结构中的数据设置为信号集的当前关联值。
		IPC_SET:在进程有足够权限的前提下，把信号集的当前关联值设置为semid_ds数据结构中给出的值。
		IPC_RMID:删除信号集。
		
#### 6.semop函数
* 功能：用来创建和访问一个信号量集。
* 原型：int semop(int semid, struct sembuf *sops, unsigned nsops);
* 参数：

		semid:是该信号的标识码，也就是semget函数的返回值。
		sops:是个指向一个结构数值的指针。
		nsops:信号量的个数。
		
* 返回值：成功返回0； 失败返回－1.
* sembuf结构体：

		struct sembuf{
			short sem_num;
			short semop;
			short sem_flg;			
		};

* sem_num是信号量的编号。
* sem_op是信号量一次PV操作时加减的数值，一般会用到两个值，一个是“－1”，，也就是P操作，等待信号量变得可用；另一个是“＋1”，也就是我们的V操作，发出信号量已经变得可用。
* sem_flag的两个取值是IPC_NOWAIT或SEM_UNDO.

### 31 System V 信号量（二）
#### 本章目标
* 用信号量实现进程互斥示例

### 32 System V 信号量（三）
### 本章目标
* 用信号量解决哲学家就餐问题

### 33 System V 共享内存与信号量综合
* 用信号量解决生产者消费者问题
* 实现shmfifo

#### 1.实现shmfifo
* shmfifo结构

		struct shmfifo
		{
			shmhead_t *p_shm;	//共享内存头部指针
			char *p_payload;	//有效负载的起始地址
			int shmid;			//共享内存IO
			int sem_mutex;		//用来互斥的信号量
			int sem_full;		//用来控制共享内存是否满的信号量
			int sem_empty;		//用来控制共享内存是否空的信号量
		}
		
### 34 POSIX 消息队列
#### 本章目标
* POSIX消息队列相关函数
* POSIX消息队列示例

#### 1.mq_open函数
* 功能：用来创建和访问一个消息队列
* 原型： 

		mqd_t mq_open(const char *name, int oflag);
		mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
		
* 参数：
	
		name:某个消息队列的名字
		oflag:与open函数类似，可以是O_RDONLY, O_WRONLY, O_RDWR, 还可以按位或上O_CREAT,O_EXCL,O_NONBLOCK等。
		mode:如果oflag指定了O_CREAT,需要设置mode.
		
* 返回值：成功返回消息队列文件描述符；失败返回－1.

#### 2. POSIX IPC 名字的限定
* 必须以／打头并且后续不能有其他／，形如／somename
* 长度不能超过 NAME_MAX

#### 3. mq_close函数
* 功能：关闭消息队列
* 原型：mqd_t mq_close(mqd_t mqdes);
* 参数：mqdes:消息队列描述符
* 返回值：成功返回0；失败返回－1.

#### 4. mq_unlink函数
* 功能：删除消息队列
* 原型：mqd_t mq_unlink(const char *name); 
* 参数：name:消息队列的名字
* 返回值：成功返回0；失败返回－1.

#### 5. mq_getattr/mq_setattr
* 功能：获取／设置消息队列属性
* 原型：

		mqd_t mq_getattr(mqd_t mqdes, struct mq_attr *attr);
		mqd_t mq_setattr(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr);
		
* 返回值：成功返回0；失败返回－1.
* mq_attr结构体

		struct mq_attr{
			long mq_flags;	/*Flags:0 or O_NONBLOCK*/
			long mq_maxmsg;	/*MAX.#of messages on queue*/
			long mq_msgsize; /*MAX.message size(bytes)*/
			long mq_curmsgs; /*#of messages currently in queue*/
		}
		
#### 6. mq_send函数
* 功能：发送消息
* 原型:

		mqd_t mqsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio);

* 参数：

		mqdes:消息队列描述符
		msg_ptr:指向消息的指针
		msg_len:消息长度
		msg_prio:消息优先级
		
* 返回值：成功返回0；失败返回－1.

#### 7. mq_receive函数
* 功能：接收消息
* 原型：

		ssize_t mq_receive(mqd_t mqdes, char *msg_ptr,size_t msg_len, unsigned *msg_prio);
		
* 参数：

		mqdes:消息队列描述符
		msg_ptr:返回接收到的消息
		msg_len:消息长度
		msg_prio:接收到的消息优先级
		
* 返回值：成功返回接收到的消息字节数；失败返回－1。
* 注意：返回指定消息队列中最高优先级的最早消息。

#### 8. mq_notify函数
* 功能：建立或者删除消息到达通知事件
* 原型：

		mqd_t mq_notity(mqd_t mqdes, const struct sigevent *notification);
		
* 参数：

		mqdes:消息队列描述符
		notification:
			(1)非空表示当消息到达且消息队列先前为空，那么将得到通知；
			(2)NULL表示撤销已注册的通知
			
* 返回值：成功返回0；失败返回－1.
* 通知方式：

		（1）产生一个信号
		（2）创建一个线程执行一个指定函数
		
*  结构体

		union sigval{
			int sival_int;		/*integer value*/
			void *sival_ptr;		/*pointer value*/
		}
		
		struct sigevent{
			int		sigev_notify;
			int		sigev_value
			void	(*sigev_notify_function)(union sigval);
			void	*sigev_notify_attributes;
		}
		
#### 9.mq_notify注意
* 任何时刻只能有一个进程可以被注册为接收某个给定队列的通知。
* 当有一个消息到达某个先前为空的队列，而且已有一个进程被注册为该接收队列的通知时，只有没有任何线程阻塞在该队列的mq_receive调用的前提下，通知才会发出。
* 当通知被发送给它的注册进程时，其注册被撤销。进程必须重新再次调用mq_notify以重新注册（如果需要的话），重新注册要放在从消息队列读出消息队列之前而不是之后。

### 35 posix共享内存
#### 本章目标
*  POSIX共享内存相关函数
*  POSIX共享内存示例

#### 1.shm_open函数功能
* 功能：用来创建或打开一个共享内存对象
* 原型：

		int shm_open(const char *name, int oflag, mode_t mode);
		
* 参数：

		name:共享内存对象的名字。
		oflag:与open函数类似，可以是O_RDONLY,O_RDWR,还可以按位或上O_CREAT,O_EXCL,O_TRUNC等。
		mode:此参数总是需设置，如果oflag没有指定了O_CREAT,还可以指定为0.
		
* 返回值：成功返回非负整数文件描述符；失败返回－1.

#### 2.修改共享内存大小ftruncate
* 功能：修改共享内存大小ftruncate.
* 原型：int ftruncate(int fd, off_t length);
* 参数：fd:文件描述符；length:长度
* 返回值：成功返回0，失败返回－1.

#### 3.获取共享内存对象信息
* 功能：获取共享内存对象信息。
* 原型：int fstat(int fd, struct stat *buf);
* 参数：fd:文件描述符；buf:返回共享内存状态
* 返回值：成功返回0；失败返回－1.

#### 4.shm_unlink函数
* 功能：删除一个共享内存对象。
* 原型：int shm_unlink(const char *name);
* 参数：name:共享内存对象的名字。
* 返回值：成功返回0；失败返回－1.

#### 5.共享内存对象的映射
* 功能：将共享内存对象映射到进程地址空间。
* 原型：void *mmap(void *addr, size_ t len, int prot, int flags, int fd, off_t offset);
* 参数：

		addr:要映射的起始地址，通常指定为NULL，让内核自动选择。
		len:映射到进程地址空间的字节数。
		prot:映射区保护方式。
		flags:标志。
		fd:文件描述符。
		offset：从文件头开始的偏移量。
		
* 返回值：成功返回映射到内存区的起始地址；失败返回－1.


### 36线程介绍
#### 本章目标
* 什么是线程
* 进程与线程
* 线程优缺点
* 线程模型

		(1)N:1用户线程模型
		(2)1:1核心线程模型
		(3)N:M混合线程模型
		
#### 1.什么是线程
* 在一个程序里的一个执行线路就叫做线程（thread）.更准确的定义是：线程是“一个进程内部的控制序列”。
* 一切进程至少都有一个执行线程。

#### 2.进程与线程
* 进程是资源竞争的基本单位
* 线程是程序执行的最小单位
* 线程共享进程数据，但也拥有自己的一部分数据：

		（1）线程ID（2）一组寄存器（3）栈（4）信号状态（5）优先级
		
#### 3.线程的优点
* 创建一个新线程的代价要比新进程小的多。
* 与进程之间的切换相比，线程之间的切换需要操作系统做的工作要少很多。
* 线程占用的资源要比进程少很多。
* 能充分利用多处理器的可并行数量。
* 在等待慢速I/O操作结束的同时，程序可执行其他的计算任务。
* 计算密集型应用，为了能在多处理器系统上运行，将计算分解到多个线程中实现。
* I/O密集型应用，为了提高性能，将I/O操作重叠。线程可以同时等待不同的I/O操作。

#### 4.线程的缺点
* 性能的损失
* 健壮性降低：线程之间缺乏保护的，容易影响其他线程。
* 缺乏访问控制：进程是访问控制的基本粒度，在一个线程中调用某些OS函数会对整个进程造成影响。
* 编写难度提高：编写与调试一个多线程程序比单线程程序困难的多。

#### 5. N:1用户线程模型
* “线程实现”建立在“进程控制”机制上，又用户空间的程序库来管理.OS内核完全不知道线程信息。这些线程称为用户空间线程。
* 这些线程都工作在“进程竞争范围”。
* 在N:1线程模型中，内核不干涉线程的任何生命活动，也不干涉同一进程中的线程环境切换。
* 在N:1线程模型中的多个线程只能调度到一个CPU，这种约束限制了一个“阻塞式”操作（如read），那么，进程中的所有线程都会阻塞，直到那个操作结束。为此，一些线程的实现都是为这些阻塞式函数提供包装器，用非阻塞版本替换这些系统调用，以消除这种限制。

#### 6.1:1核心线程模型
* 在1:1核心线程模型中，应用程序创建的每一个线程都是由一个核心线程直接管理。
* OS内核将每一个核心线程都调到系统CPU上，因此，所有线程都在“系统竞争范围”。
* 这种线程的创建与调度由内核完成，因为这种线程的系统开销比较大（但一般来说比进程开销小）。

#### 7. N:M混合线程模型
* N:M混合线程模型提供了两级控制，将用户线程映射为系统的可调度体以实现并行，这两个可调度体称为轻量级线程（LWP）。LWP再一一映射到核心线程。

### 37posix线程（一）
#### 本章目标
* POSIX线程库相关函数
* 用线程实现回射客户／服务器

#### 1.POSIX线程库
* 与线程有关的函数构成了一个完整的系列，绝大多数函数的名字都是以“pthread_”打头的.
* 要使用这些函数库，要通过引入头文<pthread.h>.
* 链接这些线程函数库时要使用编译器命令的“－lpthread”选项。

#### 2.pthread_create函数
* 功能：创建一个新的线程。
* 原型：

		int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg);
		
* 参数:
 
 		thread:返回线程ID。
 		attr:设置线程的属性，attr为NULL表示使用默认属性。
 		start_routine:是个函数地址，线程启动后要执行的函数。
 		arg:传给线程启动函数的参数。

* 返回值：成功返回0；失败返回错误码。

#### 3.错误检查
* 传统的一些函数是，成功返回0，失败返回－1，并且对全局变量errno赋值以指示错误。
* pthread函数出错时不会设置全局变量errno（而大部分其他POSIX函数会这样做）。而是将错误代码通过返回值返回。
* pthread同样也提供了线程内的errno变量，以支持其他使用的errno的代码。对于 pthreads函数的错误，建议通过返回值来判定，因为读取返回值要比读取线程内的errno变量的开销更小。

#### 4.pthread_exit函数
* 功能：线程终止。
* 原型：

		void pthread_exit(void *value_ptr);
		
* 参数：

		value_ptr:value_ptr不要指向一个局部变量
		
* 返回值：无返回值，跟进程一样，线程结束的时候无法返回到它的调用者（自身）。

#### 5.pthread_join函数
* 功能：等待线程结束
* 原型：

		int pthread_join(pthread_t thread, void **value_ptr);
		
* 参数：

		thread:线程ID.
		value_ptr:它指向一个指针，后者指向线程的返回值。
		
* 返回值：成功返回0；失败返回错误码。

#### 6.pthread_self函数
* 功能：返回线程ID.
* 原型：

		pthread_t pthread_self(void);
		
* 返回值：成功返回0.

#### 7.pthread_cancel函数
* 功能：取消一个执行中的线程。
* 原型：

		int pthread_cancel(pthread_t thread);
		
* 参数： thread:线程ID.
* 返回值：成功返回0；失败返回错误码。

#### 8.pthread_detach函数
* 功能：将一个线程分离。
* 原型：

		int pthread_detach(pthread_t thread);
* 参数：thread：线程ID.
* 返回值：成功返回0；失败返回错误码。

#### 9.线程与进程比较
	pid_t					thread_t
	fork					pthread_create
	waitpid					pthread_join	
	exit					pthread_exit	
	再main函数中		   	 在线程入口函数中
	调用return			  调用return
	
	僵进程						僵线程
	waitpid					pthread_join
	
							pthread_detach
	
	kill					pthread_cancel
	
	线程结束
	
	自杀:(1)pthread_exit (2)在线程入口函数中调用return。
	他杀:(2)pthread_cancel.
		
### 38posix线程（二）
#### 本章目标
* 线程属性
* 线程特定数据

#### 1.线程属性
* 初始化与销毁属性

		int pthread_attr_init(pthread_attr_t *attr);
		int pthread_attr_destory(pthread_attr_t *attr);
		
* 获取与设置分离属性

		int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
		int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
		
* 获取与设置栈大小

		int pthread_attr_setstacksize(pthread_attr *attr, size_t stacksize);
		int pthread_attr_getstacksize(pthread_attr *attr, size_t *stacksize);
		
* 获取与设置继承的调度策略

		int pthread_attr_getinheritsched(const pthread_attr_t *attr, int *inheritsched);
		int pthread_attr_setinheritsched(pthread_attr_t *attr, int inheritsched);
		
* 获取与设置调度参数

		int pthread_attr_getschedparam(const pthread_attr_t *attr, struct sched_param *param);
		int pthread_attr_setschedparam(pthread_attr_t *attr, const struct sched_param *param);
		
#### 2.并发级别
* 获取与设置并发级别

		int pthread_setconcurrency(int new_level);
		int pthread_setconcurrency(void);
		
* 仅在N:M线程模型中有效，设置并发级别，给内核一个提示：表示提供给定级别数量的核心线程来映射用户线程是高效的。

#### 3.线程特定数据
* 在单线程程序中，我们经常要用到“全局变量”以实现函数间共享数据。
* 在多线程环境下，由于数据空间是共享的，因此全局变量也为所有线程所共有。
* 但有时应用程序设计中有必要提供私有的全局变量，仅在某个线程中有效，但却可以跨越多个函数访问。
* POSIX线程库通过维护一定的数据来解决这个问题，这些数据成为（Thread-specific Data, 或TSD）。
* 线程特定数据相关函数
		
		int pthread_key_create(pthread_key_t *key, void (*destructor)(void*));
		int pthread_key_delete(pthread_key_t key);
		
		void *pthread_getspecific(pthread_key_t key);
		int pthread_setspecific(pthread_key_t key,const void *value);
		
		int pthread_once(pthread_once_t *once_control, void (*init_routine)(void)); 
		pthread_once_t once_control = PTHREAD_ONCE_INIT;
		
### 39POSIX信号量与互斥锁
#### 本章目标
* POSIX信号量相关函数
* POSIX互斥锁相关函数
* 生产者消费者问题
* 自选锁与读写锁介绍

#### 1.POSIX信号量相关函数
	有名信号量
	* sem_open
	* sem_close
	* sem_unlink
	无名信号量
	* sem_init
	* sem_destroy

	* sem_wait
	* sem_post

#### 2.POSIX互斥锁
	pthread_mutex_init
	pthread_mutex_lock
	pthread_mutex_unlock
	pthread_mutex_destory
	
#### 3.自选锁
* 自旋锁类似于互斥锁，它的性能比互斥锁更高。
* 自旋锁与互斥锁很重要的一个区别在于，线程在申请自选锁的时候，线程不会被挂起，它处于忙等待的状态。

		pthread_spin_init
		pthread_spin_destroy
		pthread_spin_lock
		pthread_spin_unlock
		
#### 4.读写锁
* 只要没有线程持有给定的读写锁用于写，那么任意数目的线程可以持有读写锁用于读。
* 仅当没有线程持有某个给定的读写锁用于读或者用于写时，才能分配读写锁用于写。
* 读写锁用于读称为共享锁，读写锁用于写称为排它锁。

		pthread_rwlock_init
		pthread_rwlock_destroy
		int pthread_rwlock_rdlock
		int pthread_rwlock_wrlock
		int pthread_rwlock_unlock
		
### 40POSIX条件变量
#### 本章目标
* 条件变量
* 条件变量函数
* 条件变量使用规范
* 使用条件变量解决生产者消费者问题

#### 1.条件变量函数
	pthread_cond_init
	pthread_cond_destroy
	pthread_cond_wait
	pthread_cond_signal
	pthread_cond_broadcast
	
#### 2.条件变量使用规范
* 等待条件代码

		pthread_mutex_lock(&mutex);
		while(条件为假)
			pthread_cond_wait(cond, mutex);
		修改条件
		pthread_mutex_unlock(&mutex);
		
* 给条件发送信号代码

		pthread_mutex_lock(&mutex);
		设置条件为真
		pthread_cond_signal(cond);
		pthread_mutex_unlock(&mutex);
		
* 相关代码：

		消费者（conmusers）
		while(1)
		{
			pthread_mutex_lock(&g_mutex);
			while(nready == 0)
			{
				pthread_cond_wait(&g_cond, &g_mutex);
			}
			--nready;
			pthread_mutex_unlock(&g_mutex);
			sleep(1);
		}
		生产者（producers）
		while(1)
		{
			pthread_mutex_lock(&g_mutex);
			++nready;
			if(nread > 0)
				pthread_cond_signal(&g_cond);
			pthread_mutex_unlock(&g_mutex);
			sleep(1);
		}
		
		pthread_cond_wai：
		(1):对g_mutex进行解锁。
		(2):等待条件，直到有线程向它发起通知。
		(3):重新对g_mutex进行加锁操作。
		
		pthread_cond_signal:
		向第一个等待条件的线程发起通知，如果没有任何一个线程处理等待条件的状态，这个通知将被忽略。
		
		pthread_cond_broadcast:
		向所有等待线程发起通知。
		
	
### 41一个简单的线程池的实现
#### 本章目标
* 线程池的实现

#### 1.线程池概念
* 用于执行大量相对短暂的任务。

		线程池拥有若干个线程
		
		用于执行大量的相对短暂的任务
		
		计算密集型任务：线程个数 ＝ CPU个数	（最高效）
		I/O密集型任务：线程个数 > CPU个数
		
* 当任务增加的时候能够动态的增加线程池中线程的数量直到一个阀值。
* 当任务执行完毕的时候，能够动态的销毁线程池中的线程。
* 该线程池的实现本质上也是生产者与消费模型的应用。生产者线程向任务队列中添加任务，一旦队列有任务到来，如果有等待线程就唤醒来执行任务，如果没有等待线程并线程数没有到达阀值，就创建新线程来执行任务。

#### 2.线程池实现结构体
	//任务结构体，将任务放入队列由线程池中的线程来执行
	typedef struct tast
	{
		void *(*run)(void *arg);	//任务回调函数
		void *arg;					//回调函数参数
		struct tast *next;
	}task_t;
	
	//线程池结构体
	typedef struct threadpool
	{
		condition_t ready;		//任务准备就绪或者线程池销毁通知
		tast_t 	   *first;	//任务队列头指针
		tast_t 	    *last;	//任务队列尾指针
		int       counter;		//线程池中当前线程数
		int			 idle;			//线程池中当前正在等待任务的线程数
		int   max_threads;		//线程池中最大容许的线程数
		int			 quit;			//销毁线程池的时候置1
	}threadpool_t;
	
	//初始化线程池
	void threadpool_init(threadpool_t *pool, int threads);
	
	//往线程池中添加任务
	void threadpool_add_task(threadpool_t *pool, void *(*run)(void *arg), void *arg);
	
	//销毁线程池
	void threadpool_destroy(threadpool_t *pool);
	
