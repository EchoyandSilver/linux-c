##Linux系统编程课程介绍
* Linux系统编程围绕Linux操作系统的三大抽象展开讲解（文件、虚拟存储、进程）。并配合一个小型的Shell程序minishell作为教学项目。
* Linux系统编程之文件篇
* Linux系统编程之进程篇
* Linux系统编程之信号与管道篇
* Linux系统编程之时间篇
* Linux系统编程之实战篇（minishell实现）

## 1章 Linux系统编程之文件篇

### 01 文件与IO(一)
#### 本章目标
* 什么是I/O
* 文件描述符
* 文件系统调用

#### 1.什么是I/O
* 输入／输出是内存和外部设备之间拷贝数据的过程

		设备－>内存（输入操作）
		内存－>设备（输出操作）

* 高级I/O

		ANSI C提供的标准I/O库称为高级I/O，通常也称为带缓冲的I/O.
		
* 低级I/O

		通常也称为不带缓冲的I/O.
		
#### 2.文件描述符
* 对于Linux而言，所有对设备或文件的操作都是通过文件描述符进行的。
* 当打开或者创建一个文件的时候，内核向进程返回一个文件描述符（非负整数）。后续对文件的操作只需要通过该文件描述符。内核纪录有关这个打开文件的信息。
* 一个进程启动时，默认打开3个文件，标准输入、标准输出、标准错误，对应的文件描述符是0(STDIN_FILENO),1(STD_FILENO),2(STDERR_FILENO),这些常量定义在unistd.h头文件中。

#### 3.文件描述符与文件指针转换
* fileno:将文件指针转换为文件描述符
* fdopen:将文件描述符转换为文件指针

#### 4.文件系统调用
* open系统调用
* close系统调用
* creat系统调用
* read系统调用
* write系统调用

#### 4-1.open系统调用2-1
* 有几种方法可以获得容许访问文件的文件描述符。最常用的是使用open()(打开)系统调用。
* 函数原型

		int open(const char *path, int flags);
		参数
		path:文件的名称，可以包含（绝对和相对）路径
		flags:文件打开模式
		返回值:打开成功，返回文件描述符；打开失败返回－1.
		
#### 4-2.open系统调用2-2
* 函数原型

		int open(const char *path, int flags);
		参数
		path:文件的名称，可以包含（绝对和相对）路径
		flags:文件打开模式
		mode:用来规定对该文件的所有者，文件的用户组及系统中其他用户的访问权限。
		返回值:打开成功，返回文件描述符；打开失败返回－1。

#### 5.打开文件的方式
	O_RDONLY		打开一个供读取的文件
	O_WRONLY		打开一个供写入的文件
	O_RDWR			打开一个可供读写的文件
	O_APPEND		写入的所有数据将被追加到文件的末尾
	O_CREAT		打开文件，如果文件不存在则建立文件
	O_EXCL			如果已经置O_CREAT且文件存在，则强制open()失败
	O_TRUNC		在open()时，将文件的内容清空
	
	所有这些标志值的符号名称可以通过＃include <fcntl.h>访问。
	
#### 6.close系统调用
* 为了重新利用文件描述符，用close()系统调用释放打开的文件描述符。

		函数原型：int close(int fd);
		函数参数：
		－fd:要关闭的文件描述符
		返回值：如果出现错误，返回－1，如果调用成功返回0.
		
#### 7.creat系统调用2-1
* 为了维持与早期的unix系统的向后兼容性，Linux也提供可选的创建文件的系统调用，它称为creat().
* 函数原型

		int creat(const char *path, mode_t mode);
		参数
		path：文件的名称，可以包含（绝对和相对）路径
		mode：用来规定对文件的所有者，文件的用户组及系统中其他用户的访问权限。	
		返回值：打开成功，返回文件描述符，打开失败，返回－1.
		
#### 8.creat系统调用2-2
* 在UNIX的早期版本中，open()系统调用仅仅存在两个参数形式，如果文件不存在就不能打开这些文件，文件的创建则是由单独的系统调用creat()完成。在Linux及所有UNIX的近代版本中，creat()系统调用是多余的。
* creat()调用

		fd = creat(file, mode);
		完全等价于近代的open()调用
		fd = open(file, O_WRONLY|O_CREAT|O_TRUNC, mode);
		
### 02 文件与IO(二)
#### 本章目标
* read、write
* lseek
* 目录访问（opendir、readdir、closedir）
* rmdir、mkdir
* chmod、fchmod
* chown、fchown

#### 1.read系统调用
* 一旦有了与一个打开文件描述相连的文件描述符，只要改文件是用O_RDONLY或O_WRONLY标志打开的，就可以用read()系统调用从该文件中读取字节。
*  函数原型：

		ssize_t read(int fd, void *buf, size_t count);
		参数:
		fd:想要读的文件的文件描述符
		buf:指向内存块的指针，从文件中读取来的字节放到这个内存块中
		count:从该文件复制到buf中的字节个数
		返回值：
		如果出现错误，返回－1；读文件结束，返回0；
		否则返回从该文件复制到规定的缓冲区中的字节数
		
#### 2.write系统调用
* 用write()系统调用将数据写到一个文件中
* 函数原型

		ssize_t write(int fd, const void *buf, size_t count);
		函数参数：
		fd:要写入的文件的文件描述符
		buf:指向内存块的指针，从这个内存块中读取数据写入到文件中
		count:从该文件复制到buf中的字节个数
		返回值：
		如果出现错误，返回－1，
		如果写入成功，则返回写入到文件中的字节个数。
		
#### 3.1lseek系统调用1
* 功能说明：通过指定相对于开始位置、当前位置或末尾位置的字节数来重定位cup，这取决于lseek()函数中指定的位置
* 原型：

		off_t lseek(int fd, off_t offset, int base);
		fd:需要设置的文件表示符
		offset:偏移量
		base:搜索的起始位置
		
		返回值：返回新的文件偏移值。
		
#### 3.2lseek系统调用2
* base表示搜索的起始位置，有以下几个位置：（这些值定义在< unistd.h >）

		base				文件位置
		SEEK_SET			从文件开始处计算偏移
		SEEK_CUR			从当前文件的偏移值计算偏移
		SEEK_END			从文件的结束处计算偏移
		
#### 4.1目录访问
* 功能说明：打开一个目录
* 原型： DIR＊ opendir(char*pathname);
* 返回值：打开成功，返回一个目录指针；打开失败，则返回0。

#### 4.2目录访问
* 功能说明：访问指定目录中下一个连接的细节
* 原型：struct dirent* readdir(DIR *dirptr);
* 返回值：返回一个指向dirent结构的指针，它包含指定目录中下一个连接的细节；没有更多连接时，返回0。

#### 4.3目录访问
* 功能说明：关闭一个已经打开的目录
* 原型： int closedir(DIR *dirptr);
* 返回值：调用成功返回0，失败返回－1。
* 目录信息结构体

		struct dirent
		{
			long	d_ino;		/*inode number*/
			off_t	d_off;		/*offset to this dirent*/
			unsigned short d_reclen;	/*lenth of this d_name*/
			char d_name[NAME_MAX + 1];	/*file name(null-terminated)*/
		}
		
#### 5.mkdir系统调用
* 功能说明：用来创建一个称为pathname的新目录，它的权限位设置为mode。
* 原型： int mkdir(char*pathname,mode_t mode);
* 返回值：调用成功返回0，失败返回－1。

#### 6.rmdir系统调用
* 功能说明：删除一个空目录。
* 原型： int rmdir(char*pathname);
* 返回值：调用成功返回0，失败返回－1。

#### 7.chmod和fchmod系统调用
* 功能说明：用来改变给定路径名pathname的文件的权限位
* 原型：

		int chmod(char*pathname,mode_t mode);
		
		int fchmod(int fd,mode_t mode);
		
* 返回值：调用成功返回0，失败返回－1。

#### 8.chown和fchown系统调用
* 功能说明：用来改变文件所有者的识别号（owner id）或者它的用户组识别号（group ID）。
* 原型：

		int chown(char*pathname,uid_t owner,gid_t group);
		
		int fchown(int fd,uid_t owner,gid_t group);
		
* 返回值：调用成功返回0，失败返回－1。


### 03 文件与IO(三)
#### 本章目标
* stat
* stat结构体
* stat实例

#### 01stat
* 功能：读取文件元数据

		(1)int stat(const char *path, struct stat *buf);
		(2)int fstat(int fd, struct stat *buf);
		(3)int lstat(const char *path, struct *buf);
		
#### 02stat结构体
	struct stat{
		dev_t st_dev; /*ID of device containing file*/
		ino_t st_ino; /*inode number*/
		mode_t st_mode; /*protection*/
		nlink_t st_nlink; /*number of hard links*/
		uid_t st_uid; /*user ID of owner*/
		gid_t st_gid; /*group ID of owner*/
		dev_t st_rdev; /*device ID of owner*/
		off_t st_size; /*total size, in bytes*/
		blksize_t st_blksize; /*blocksize for file system I/O*/
		blkcnt_t st_blocks; /*number of 512B blocks allocated*/
		time_t st_atime; /*time of last access*/		time_t st_mtime; /*time of last modification*/		time_t st_ctime; /*time of last status change*/
	}
	
#### 03实现ls -l功能
* lstat
* getpwuid
* getgrgid
* readlink


### 04 文件与IO(四)
#### 本章目标
* 文件共享
		
		1.打开文件内核数据结构	
		2.一个进程两次打开同一个文件
		3.两个进程打开同一个文件
		(见代码io_04/01fileshare.c)
		
* 复制文件描述符（dup、dup2、fcntl）(见代码io_04/02dup.c)

#### 1.复制文件描述符
* 复制文件描述符有三种方法：
		
		1.dup 2.dup2 3.fcntl
		
* fcntl(fd, F_DUPFD, fd _start);


### 05 文件与IO（五）
#### 本章目标
* fcntl函数
* fcntl常用操作
* 文件锁

#### 1.fcntl
* 功能：操纵文件描述符，改变已打开的文件的属性

		int fcntl(fd, int cmd, ... /* arg */);
		
#### 2.fcntl常用操作
* 复制文件描述符：

		F_DUPFD(long)
		int fcntl(fd, F_DUPFD, ... /* arg */);
		arg:表示从指定的位置开始搜索空闲的文件描述符。
		
* 文件描述符标志：

		F_GETFD(void)
		F_SETFD(long)
		
* 文件状态标志

		F_GETFL(void)
		F_SETFL(long)
		
* 文件锁

		F_GETLK
		F_SETLK,F_SETLKW
		
#### 3.文件锁结构体

	struct flock{
	...
	short l_type;		/* Type of lock: F_RDLCK
							F_WRLCK, F_UNLCK*/
	short l_whence;	/* How to interpret l_start:
							SEEK_SET,SEEK_CUR,SEEK_END */
	off_t l_start;	/* Starting offset for lock */
	off_t l_len;		/* Number of process blocking our lock */
	pid_t l_pid;		/* PID of process blocking our lock 
							(F_GETLK only) */
	...
	};
	
## 2章 Linux系统编程之进程篇

### 01 进程（一）
#### 本章目标
* 什么是程序
* 什么事进程
* 进程数据结构
* 进程与程序区别与联系

#### 1.什么是程序
* 程序是完成特定任务的一系列指令集合

#### 2.什么是进程
* 从用户的角度来看进程是程序的一次执行过程
* 从操作系统的核心来看进程是操作系统分配的内存、CPU时间片等资源的基本单位。
* 进程是资源分配的最小单位
* 每一个进程都有自己独立的地址空间与执行状态。
* 像UNIX这样的多任务系统能够让许多程序同时运行，每一个运行着的程序就构成了一个进程。

#### 3.进程数据结构
* 我们进程的静态描述：由三部分组成：PCB、有关程序段和该程序段对其操作的数据结构集。
* 进程控制块：用于描述进程情况及控制进程运行所需的全部信息。
* 代码段：是进程中能被进程调度程序在CPU上执行的程序代码段。
* 数据段：一个进程的数据段，可以是进程对应的程序加工处理的原始数据，也可以是程序执行后产生的中间或最终数据。

		程序：代码段 ＋ 数据段
		只读数据段 常量
		已初始化数据段  全局变量 静态变量
		未初始化数据段 （0初始化段）未初始化全局变量 静态变量 bass
		
		进程：代码段 ＋ 数据段＋ 堆栈段 ＋ PCB（进程控制块）
		
#### 4.进程与程序
* 进程是动态的，程序是静态的。
* 进程的生命周期是相对短暂的，而程序是永久的。
* 进程数据结构。
* 一个进程只能对应一个程序，一个程序可以对应多个进程。


### 02 进程（二）
#### 本章目标
* 进程状态变迁
* 进程控制块
* 进程创建
* 进程撤销
* 终止进程的五种方法

#### 01 进程状态变迁
* 就绪（所有资源都满足，只差cpu）
* 等待（发生等待事件）
* 运行（所有资源都满足）

		创建进程：就绪态---->运行态-------->等待态----->就绪态
					  调度      发生等待事件    等待结束
					  
* 运行状态（TASK_RUNNING）
* 可中断睡眠状态（TASK_INTERRUPTIBLE）
* 不可中断睡眠状态（TASK_UNINTERRUPTIBLE）
* 暂停状态（TASK_STOPPED）
* 僵死状态（TASK_ZOMBIE）

#### 02 进程控制块
* 进程描述信息

		进程表示符用于唯一的标识一个进程
		
* 进程控制信息

		进程当前状态
		进程优先级
		程序开始地址
		各种计时信息
		通信信息
		
* 资源信息

		占用内存大小及管理用数据结构指针
		交换区相关信息
		I/O设备号、缓冲、设备相关的数结构
		文件系统相关指针
		
* 现场保护信息

		寄存器
		PC
		程序状态字PSW
		栈指针
		
#### 03 进程标识
* 每个进程都会被分配到一个独一无二的数字编号，我们称之为“进程标识”或者直接叫它PID
* 是一个正整数，取值范围从2到32768
* 当一个进程被启动时，它会顺序挑选下一个未使用的编号数字作为自己的PID
* 数字1一般为特殊进程init（用户进程）保留的 。／sbin／init

#### 04 进程创建
* 不同的操作系统所提供的进程创建原语的名称和格式不尽相同，但执行创建原语后，操作系统所做的工作却大致相同，都包括以下几点：
* 给新创建的进程分配一个内部标识，在内核中建立进程结构。
* 复制父进程的环境。
* 为进程分配资源，包括进程映像所需要的所有元素（程序、数据、用户栈等）。
* 复制父进程地址空间的内容到该进程地址空间中。
* 值该进程的状态为就绪，插入就绪队列。

#### 05 进程撤销
* 进程终止时操作系统做以下工作：
* 关闭软中断：因为进程即将终止而不再处理任何软中断信号；
* 回收资源：释放进程分配的所有资源，如关闭所有已打开文件，释放进程相应的数据结构等；
* 写记帐本信息：将进程在运行过程中所产生的记账数据（其中包括进程运行时的各种统计信息）纪录到一个全局记账文件中；
* 置该进程为僵死状态：向父进程发送子进程死的软中断信号，将终止信息status送到指定的存储单元中；
* 转进程调度：因为此时CPU已经被释放，需要由进程调度进行CPU再分配。

#### 06 终止进程的五种方法
* 从main函数返回 （return）
* 调用exit （C函数库）
* 调用_exit（系统调用）
* 调用abort （SIGABRT信号）
* 由信号终止（ctrl + c相当于发送一个SIGINT信号）


### 03 进程（三）
#### 本章目标
* 复制进程映像
* fork系统调用
* 孤儿进程、僵尸进程
* 写时复制

#### 1.复制一个进程映像fork
* 使用fork函数得到的子进程从父进程的继承了整个进程的地址空间，包括：进程上下文、进程堆栈、内存信息、打开的文件描述符、信号控制设置、进程优先级、进程组号、当前工作目录、根目录、资源限制、控制终端等。
* 子进程与父进程的区别在于：

		1.父进程设置的锁，子进程不继承
		2.各自的进程ID和父进程ID不同
		3.子进程的未决告警被清除
		4.子进程的未决信号集设置为空集
		
#### 2.fork系统调用
* 包含头文件< sys/types.h >和< unistd.h >
* 函数功能：创建一个子进程
* 函数原型：pid_t fork(void);
* 参数：无参数。
* 返回值：

		1.如果成功创建一个子进程，对于父进程来说返回子进程ID。
		2.如果成功创建一个子进程，对于子进程来说返回值为0。
		3.如果为－1表示创建失败。
		
#### 3.fork系统调用注意点
* fork系统调用之后，父子进程将交替执行。
* 如果父进程先退出，子进程还没退出那么子进程的父进程将变为init进程。（任何一个进程必须有父进程）。
* 如果子进程先退出，父进程还没退出，那么子进程必须等到父进程捕获到子进程的退出状态才真正结束，否则这个时候子进程就成为僵尸进程。

		fork一次调用两次返回；
		fork成功意味着创建一个进程副本，两个进程；
		是在各自的进程地址空间中返回的。
		
		孤儿进程:托孤给1号进程
		僵尸进程:子进程先退出，父进程尚未查询子进程的退出状态，子进程就处于僵尸状态
		
#### 4.写实复制copy on write（以页为单位复制） 
* 如果多个进程要读取它们自己的那部分资源的副本，那么复制是不必要的。
* 每个进程只保存一个指向这个资源的指针就可以了。
* 如果一个进程要修改自己的那份资源的”副本“，那么就会复制那份资源。这就是写实复制的含义。

### 04 进程（四）
#### 本章目标
* fork之后父子进程共享文件
* fork与vfork
* exit与_exit
* atexit
* execve替换进程映像（加载程序）

#### 01.fork与vfork
* 在fork还没实现copy on write 之前。Unix设计者很关心fork之后立刻执行exec所造成的地址空间浪费，所以引入vfork系统调用。
* vfork有个限制，子进程必须立刻执行_exit或者exec函数。
* 即使fork实现了copy on write,效率也没有vfork高，但是我们不推荐使用vfork的实现，都或多或少存在一定的问题。

#### 02.进程的五种终止方式
* 正常退出

		从main函数返回
		调用exit
		调用_exit
		
* 异常退出

		调用abort
		由信号终止
		
		_exit 系统调用(直接操纵内核) （不会清除I/O缓冲区）
		exit C库中一个函数 可以调用终止处理函数 （清除I/O缓冲区）
		输出加上 "/n" 可以清除缓冲区，
		
#### 03.atexit(C库函数)
* atexit可以注册终止处理程序，ANSI C规定最多注册32个终止程序。
* 终止处理程序的调用与注册次序相反

		int atexit(void (*function)(void));
		
#### 04.execve(替换进程映像)（系统调用）

	int execve(const char *filename, char *const argv[], char *const envp[]);
	
	
### 05 进程（五）
#### 本章目标
* exec替换进程映像
* exec关联函数组（execl、execlp、execle、execv、execvp)(C库函数)

#### 01.exec替换进程映像
* 在进程的创建上Unix采用了一个独特的方法，它将进程创建与加载一个新进程映像分离。这样的好处是有更多的余地对两种操作进行管理。
* 当我们创建了一个进程后，通常将子进程替换成新的进程映像，这可以用exec系列的函数来进行。当然，exec系列的函数也可以将当前进程替换掉。

#### 02.exec关联函数组
* 包含头文件<unistd.h>
* 功能：用exec函数可以把当前进程替换为一个新进程。exec名下是由多个关联函数组成的一个完整系列，头文件<unistd.h>
* 原型：

		int execl(const char *path, const char *arg, ...);
		int execlp(const char *file, const char *arg, ...);
		int execle(const char *path, const char *arg, ..., char* const envp[]);
		...
		int execv(const char *path, const char *argv[]);
		int execvp(const char *file, const char *argv[]);
		
* 参数
* path参数表示你要启动程序的名称包括路径名。
* arg参数表示启动程序所带的参数。
* 返回值：成功返回0，失败返回－1。
* 名字最后一个字母是“p”的函数会搜索PATH环境变量去查找新程序的可执行文件。如果可执行文件不在PATH定义的路径上，就必须把包括子目录在内的绝对文件名作为一个参数传递给这些函数。


### 06 进程 （六）
#### 本章目标
* SIGCHLD
* wait
* waitpid
* 僵进程
* system

#### 01.SIGCHLD
* 当子进程退出的时候，内核会向父进程发送SIGCHLD信号，子进程的退出是个异步事件(子进程可以在父进程运行的任何时刻退出)
* 在进程退出时，内核将子进程置为僵尸态，这个进程称为僵尸进程，他只是保留一些内核数据结构，以便父进程查询子进程的退出状态。
* 父进程查询子进程的退出状态可以用wait/waitpid函数。

#### 02.wait
* 头文件<sys/types.h>和<sys/wait.pid>
* 函数功能：当我们用fork启动一个进程时，子进程就有了自己的的生命，并将独立地运行。有时，我们需要知道某个子进程是否已经结束，我们可以通过wait安排父进程在子进程结束之后。
* 函数原型

		pid_t wait(int *status);
	
* 函数参数

		status:该参数可以获得你等待子进程的信息。
		
* 返回值：成功等待子进程函数返回等待子进程的ID。
* 以下这些宏在sys/wait.h头文件里定义：

	|          宏定义         |           描述          
	| :--------------------- | :---------------------- |
	|  WIFEXITED(Sstatus)    | 如果子进程正常结束，返回一个非零值     
	|  WEXITSTAUS(status)    | 如果WEXITSTATUS非零，返回子进程退出码
	|  WIFSIGNALED(status)   | 子进程因为捕获信号而终止，返回非零值
	|  WTERMSIG(status)      | 如果WIFSIGNALED非零，返回信号代码
	|  WIFSTOPPED(status)    | 如果子进程被暂停，返回一个非零值
	|  WSTOPSIG(status)      | 如果WIFSTOPPED非零，返回一个信号代码
	
#### 03.waitpid
* 函数功能：用来等待某个特定进程的结束
* 函数原型：

		pid_t waitpid(pid_t pid, int *status, int options);
		
* 参数：

		1.status:如果不是空，会把状态信息写到它指向的位置；
		2.options:容许改变waitpid的行为，最有用的一个选项是WNOHANG，它的作用是防止waitpid把调用者的执行挂起；
		3.返回值：如果成功返回等待子进程的ID，失败返回－1.
		
		wait(&status); <==> waitpid(-1, &status, 0);
		
#### 04.wait和waitpid的区别
* 在一个子进程终止前，wait使其调用者阻塞，而wait有一个选项，可使调用者不阻塞。
* waitpid并不等待第一个终止的子进程－它有若干个选择项，可以控制它所等待的特定进程。
* 实际上wait函数是waitpid函数的特例。

#### 05.僵进程
* 当一个子进程结束运行时，它与父进程之间的关联还会保持到父进程也正常的结束运行或者父进程调用了wait才告终止。
* 进程表中代表子进程的数据项是不会立刻释放的，虽然不再活跃了，可子进程还停留在系统里，因为它的退出码还需要保存起来以备父进程中后续的wait调用使用。它将称为一个“僵进程”。

#### 06.如何避免僵进程
* 调用wait或者waitpid函数查询子进程退出状态，此方法父进程会被挂起。
* 如果不想让父进程挂起，可以在父进程中加入一条语句：signal(SIGCHLD,SIG_IGN);表示父进程忽略SIGCHLD信号，该信号是子进程退出的时候向父进程发送的。

#### 07.system
* 功能：system()函数调用“/bin/sh -c command”执行特定的命令，阻挡当前进程直到command命令执行完毕。
* 原型：

		int system(const char *command);
		
* 返回值：如果无法启动shell运行命令，system将返回127；出现不能执行system调用的其他错误时返回－1。如果system能够顺利执行，返回那个命令的退出码。
* system函数执行时，会调用fork,execve,waitpid等函数。

### 07 进程（七）
#### 本章目标
* 什么是守护进程
* 守护进程的创建步骤
* daemon

#### 01.什么是守护进程
* 守护进程是在后台运行不受控制的进程，通常情况下守护进程在系统启动时自动运行。
* 守护进程的名称通常以d结尾，比如ssh、xinetd、crond等。

#### 02.创建守护进程步骤
* 调用fork(),创建新进程，它会是将来的守护进程
* 在父进程中调用exit，保证子进程不是进程组组长
* 调用setsid创建新的会话期
* 将当前目录改为根目录
* 将标准输入、标准输出、标准错误重定向到 /dev/null

#### 03.daemon
* 功能：创建一个守护进程。
* 参数：

		1.nochdir: =0将当前目录更改至“／”
		2.noclose: =0将标准输入、标准输出、标准错误重定向至“/dev/nul”
		
		int daemon(int nochdir, int noclose);
		

## 3章 Linux系统编程之信号篇
### 01 信号（一）
#### 本章目标
* 中断
* 信号
* 信号与中断
* signal

#### 01.中断
* 中断是系统对于异步事件的响应
* 中断信号
* 中断源
* 现场信息
* 中断处理程序
* 中断向量表

		中断过程：中断源－>中断屏蔽－>保护现场->中断处理程序->恢复现场
		中断个数固定的
		中断向量表:保存固定个数的中断处理程序入口地址
		中断处理程序保存在中断向量表

#### 02.中断分类
 * 硬件中断（外部中断）

 		外部中断是指由外部设备通过硬件请求的方式产生的中断，也称为硬件中断。
 		
 * 软件中断（内部中断）

 		内部中断是由CPU运行程序错误或执行内部程序调用引起的一种中断，也称软件中断。
 		
#### 03.信号
* 信号是UNIX系统响应某些状况而产生的事件，进程在接收到信号时会采取相应的行动。
* 信号是因为某些错误条件而产生的，比如内存段冲突、浮点处理器或者非法指令等。
* 信号是在软件层次上对中断的一种模拟，所以通常把它称为软中断。

#### 04.信号与中断
* 信号与中断的相似点：

		1.采用了相同的异步通信方式；
		2.当检测出有信号或中断请求时，都暂停正在执行的程序而转去执行相应的处理程序；
		3.都在处理完毕后返回到原来的断电；
		4.对信号或中断都可以进行屏蔽。
		
* 信号与中断的区别

		1.中断有优先级，而信号没有优先级，所有信号都是平等的；
		2.信号处理程序是在用户状态下运行的，而中断处理程序是在核心态下进行的；
		3.中断响应是及时的，而信号响应通常都有较大的时间延误。
		

#### 05.进程对信号的三种响应
* 忽略信号

		不采取任何操作、有两个信号不能被忽略:SIGKILL和SIHSTOP。
		
* 捕捉并处理信号

		内核中断正在执行的代码，转过去执行先前注册过的处理程序。
		
* 执行默认的操作

		默认操作通常是终止进程，这取决于被发送的信号。
		
#### 06.signal
 * typedef void(*_sighandler_t)(int);
 
 		#define SIG_ERR((__sighandler_t)-1)
 		
 		#define SIG_DFL((__sighandler_t)0)
 		
 		#define SIG_IGN((__sighandler_t)0)
 		
 * 函数原型：

 		__sighandler_t signal(int signum,__sighandler_t handler);
 		
 * 参数：

 		1.signal是一个带signum和handler两个参数的函数，准备捕捉或屏蔽的信号由参数signum给出，接收指定信号时将要调用的函数由handler给出；
 		2.handler这个函数必须有一个int类型的参数（即接收到的信号代码），它本身类型是void；
 		3.handler也可以是下面两个特殊值：
 		SIG_IGN		屏蔽该信号
 		SIG_DFL		恢复该信号
 		
 		
### 02 信号 （二）
#### 本章目标
* 信号分类
* 可靠信号与不可靠信号
* 信号发送
* pause

#### 01.信号分类
* 可靠信号
* 不可靠信号
* 实时信号
* 非实时信号

#### 02.不可靠信号
* linux信号机制基本上是从unix系统中继承过来的。早期unix系统中的信号机制比较简单和原始，后来的实践中暴露出一些问题：

		1.进程每次处理信号后，就将对信号的响应设置为默认动作。在某些情况下，将导致对信号的错误处理；因此，用户不希望这样的操作，那么就要在信号处理函数结尾再一次调用signal()，重新安装该信号。
		2.早期的不可靠信号主要指的是进程可能对信号做出错误的反应以及信号可能丢失。
		3.Linux支持不可靠信号，但是对不可靠信号机制做了改进：在调用完信号处理函数后，不必重新调用调用该信号的安装函数（信号安装函数是在可靠机制上的实现）。因此，Linux下的不可靠问题主要是指信号可能丢失。
	
#### 03.可靠信号
* 随着时间发展，实践证明了有必要对信号的原始机制加以改进和扩充。所以，后来出现的各种unix版本分别在这方面进行了研究，力图实现“可靠信号”。由于原来定义的信号已有许多应用，不好做改动，最终只好又新增了一些信号，并在一开始就把它们定义为可靠信号，这些信号支持排队，不会丢失。
* 同时，信号的发送和安装也出现了新版本：信号发送函数sigqueue()及信号安装函数sigaction()。

#### 04.实时信号(可靠信号）
* 早期Unix系统只定义了32种信号,Ret hat7.2支持64种信号，编号0~63(SIGRTMIN=31,SIGRTMAX=63)。前32种信号已经有了预定义值，每个信号有了确定的用途及含义，并且每种信号都有各自的缺省动作。后32个信号没有确定的用途，完全由用户自己决定。
* 非实时信号都不支持排队，都是不可靠信号；实时信号都支持排队，都是可靠信号。

#### 05.信号发送
* kill

		竞态
		向pid进程发送9号信号（kill -9）
		
		kill(pid, sig);
		pid>0: 信号sig发送给进程号=pid的进程
		pid=0: 信号sig将被发送给调用者所在组中的每一个进程
		pid=-1:信号sig将被发送给调用者进程有权限发送的每一个进程，除了1号进程与自身之外
		pid<-1:信号sig将发送给进程组＝－pid中的每一个进程
		
* raise:

		给自己发送信号。raise(sig)等价于kill(getpid(),sig);

* killpg:

		给进程组发送信号。killpg(pgrp, sig)等价于kill(-pgrp, sig);

* sigqueue

		给进程发送信号，支持排队，可以附带信息。
		
#### 06.pause
* 将进程置为可中断睡眠状态。然后它调用schedule(),使linux进程调度器找到另一个进程来运行。
* pause使调用者进程挂起，直到一个信号被捕获。


### 03 信号（三）
#### 本章目标
* 更多信号发送函数
* 可重入入函数与不可重入函数
* 不可重入函数示例

#### 01.更多信号发送函数
* alarm
* setitimer
* abort

		alarm函数可以发送 SIGALRM信号
		setitimer可以发送 SIGALRM、SIGVTALRM、SIGPROF信号
		abort可以发送 SIGABRT信号
			
#### 02.可重入函数
* 为了增强程序的稳定性，在信号处理函数中应使用可重入函数。
* 所谓可重入函数是指一个可以被多个任务调用的过程，任务在调用时不必担心数据会出错。因为进程在收到信号后，就将跳转到信号处理函数去接着执行。如果信号处理函数中使用了不可重入函数，那么信号处理函数可能会修改不应该被修改的部分，出现不可预料的后果。不可再入函数在信号处理函数中被视为不安全函数。
* 满足下列函数多数是不可重入的：(1)使用静态的数据结构，如getlogin(),gmtime(),getgrgid(),getrnam(),getwuid(),getpwnam()等等；(2)函数实现时，调用了malloc()或者free()函数；(3)实现时使用了标准I/O函数的。**(不可重入函数，见代码reetrant.c)**


### 04 信号（四）
#### 本章目标
* 信号在内核中的表示
* 信号阻塞与未央
* 信号集操作函数
* sigprocmask
