#define N 64 
#define READ   1   //查询用户信息
#define CHANGE 2   //修改用户信息
#define DELETE 3   //删除用户
#define ADD    4   //添加用户
#define LOAD   5   //用户申请登录
#define QUIT   6   //用户退出时发给服务器的通知消息
#define SUCCESS 7  //服务器操作成功
#define FAILED  8  //服务器操作失败

//user 用到的宏
#define STAFF  10
#define ADM    11

typedef struct
{
	int  type;//判断是否为管理员
	char name[N];
	char passwd[N];
	int  no;
}USER;

typedef struct
{
	char name[N];//姓名
	char addr[N];//地址 
	int  age;//年龄
	int  level;//评级
	int  no;//编号
	double  salary;//工资
	char phone[N];//手机号
	int type;//是否为管理员

}INFO;

typedef struct
{
	int  sign;//操作成功与否的标志位
	int  type;//判断操作类型 
	char name[N];//发送消息的用户
	INFO info;//员工信息结构体
	char passwd[N];//用户密码（只在第一次登录时使用）
	char data[N];//和客户端交流的信息
}MSG;

