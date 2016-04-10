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
