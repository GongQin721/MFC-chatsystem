#define MAXNICKNAMELENGTH				32						/// 昵称长度
#define HISTORYPATH						"history"				/// 聊天记录的文件夹
#define SENDFILES_CONFIG_SUB			"cfg"					/// 传输文件的配置文件的后缀

typedef struct tagUser											/// 用户结构体	
{
	int									nFace;					/// 用户头像
	char								strName[ MAXNICKNAMELENGTH + 1 ];				
																/// 用户名
	char								strIP[ 16 ];			/// 用户IP
	BOOL								bHasCamera;				/// 是否有摄像头
} USER;

typedef struct tabChatRoomMessageInfo								/// 聊天室消息结构体
{
	char								szSrcIP[ 16 ];			/// 消息发送的IP
	char								szTime[ 10 ];			/// 消息发送的时间
} CHATROOMMESSAGEINFO;

enum CONTROLCOMMAND												/// 命令
{
	REQUEST_ADD,												/// 请求加为好友
	REQUEST_DENY,												/// 请求被拒绝
	REQUEST_ALLOW,												/// 请求被通过
	REQUEST_KEEPCONNECT,										/// 请求保持接连
	RESPONSE_KEEPCONNECT,										/// 回应保持接连
	OFFLINE,													/// 下线通知
	CHATROOM_SERVER_CLOSED,										/// 聊天室服务器关闭
	CHATROOM_ADDREQUEST,										/// 服务器向客户端发起请求
	CHATROOM_ADDREQUEST_DENY,									/// 客户端拒绝加入聊天室服务器
	CHATROOM_ADDREQUEST_ALLOW,									/// 客户端允许加入聊天室服务器
	CHATROOM_CLIENT_CLOSED,										/// 客户端关闭聊天室
	CHATROOM_CLIENT_KICKED,										/// 客户端被踢
	CHATROOM_CLIENT_ADDUSER,									/// 向客户端添加用户
	CHATROOM_CLIENT_DELDUSER,									/// 从客户端删除用户
	CHATROOM_TEXT,												/// 聊天室文本消息
	CHAT_PREPARE_MESSAGE,										/// 聊天发送的消息信息
	CHAT_MESSAGE,												/// 聊天发送的消息
	CHAT_RECEIVE,												/// 开始接收聊天消息的命令
	SENDFILES_NOTIFY,											/// 在文件传过来的通知
	SENDFILES_CONNECT,											/// 向文件传输服务器发起连接
	SENDFILES_DENY,												/// 拒绝接收文件
	SENDFILES_REQUEST,											/// 请求接收数据
	SENDFILES_RESPONSE,											/// 发送数据给请求者
	SENDFIELS_DONE,												/// 接收数据完毕
	SENDFILES_FILEINFO,											/// 接收者向发送发送接收的文件信息
	SENDFILES_BEGIN, 											/// 通知接收者开始发送接收消息
	SHARESCREEN_SERVER_CLOSED,									/// 共享屏幕服务器关闭
	SHARESCREEN_ADDREQUEST,										/// 共享屏幕添加请求
	SHARESCREEN_ADDREQUEST_DENY,								/// 共享屏幕拒绝添加
	SHARESCREEN_ADDREQUEST_ALLOW,								/// 共享屏幕允许添加
	SHARESCREEN_CLIENT_CLOSED,									/// 共享屏幕客户端关闭
	SHARESCREEN_CLIENT_KICKED,									/// 共享屏幕客户端被踢
	SHARESCREEN_SERVER_SCREEN_DIM,								/// 共享屏幕服务器的尺寸
	SHARESCREEN_SERVER_SCREEN,									/// 共享屏幕服务器的屏幕数据
	WHITEBOARD_ADDREQUEST,										/// 白板添加用户请求
	WHITEBOARD_ADDREQUEST_DENY,									/// 白板拒绝添加请求
	WHITEBOARD_ADDREQUEST_ALLOW,								/// 白板允许添加请求
	WHITEBOARD_SERVER_CLOSED,									/// 白板服务器关闭
	WHITEBOARD_CLIENT_COLSED,									/// 白板客户端关闭
	WHITEBOARD_CLIENT_KICKED,									/// 白板客户端被踢
	WHITEBOARD_DRAWINFO,										/// 画图信息
	VIDEOCHAT_VIDEO_ADDREQUEST,									/// 视频请求
	VIDEOCHAT_VIDEO_ADDREQUEST_DENY,							/// 拒绝视频聊天
	VIDEOCHAT_VIDEO_ADDREQUEST_ALLOW,							/// 允许视频聊天
	VIDEOCHAT_VIDEO_PICTURE_START,								/// 将要发送视频数据
	VIDEOCHAT_VIEDO_PICTURE_REQUEST,							/// 请求发送视频数据
	VIDEOCHAT_VIDEO_PICTURE,									/// 视频画面数据
	VIDEOCHAT_VIDEO_DISCONNECT,									/// 断开连接
	VIDEOCHAT_AUDIO_DATA,										/// 音频数据
	VIDEOCHAT_VIDEO_RECEIVE_FINISHED							/// 数据接收完毕
};

typedef struct tagDataPacket									/// 数据包的结构体
{
	CONTROLCOMMAND command;										/// 命令
	BYTE * pData;												/// 数据的指针
	DWORD dwLength;												/// 数据的长度
} DATAPACKET;

typedef struct tagChatPacketInfo								/// 聊天传输消息结构
{
	int									nCurrent;				/// 当前包序号
	int									nTotal;					/// 包的总数
	int									nLength;				/// 当前包的长度
} CHATPACKETINFO;

typedef struct tagSendFilesList									/// 文件发送框的结构
{	
	int									nIndex;					/// 序号
	char								szFilePath[ MAX_PATH ];	/// 文件路径
	DWORD								dwLength;				/// 大小
	DWORD								dwSended;				/// 已完成
	int									nPercent;				/// 进度
	char								strName[ MAXNICKNAMELENGTH + 1 ];				
																/// 接收用户名
	char								strIP[ 16 ];			/// 接收IP		
} SENDFILESLIST;

enum TOOL														/// 工具
{
	ERASER,														/// 橡皮擦
	PENCIL,														/// 画笔
	LINE,														/// 直线
	RECTANGLE_EMPTY,											/// 空心矩形
	RECTANGLE,													/// 实心矩形
	ELLIPSE_EMPTY,												/// 空心椭圆
	ELLIPSE														/// 实心椭圆
};

typedef struct tagDrawInfo										/// 画图的信息
{
	TOOL								tool;					/// 工具
	int									nWidth;					/// 线宽
	COLORREF							color;					/// 颜色
	CPoint								ptStart;				/// 开始点
	CPoint								ptEnd;					/// 结束点
} DRAWINFO;

#define TIMER_CONNECT					1						/// 保持连接的timer号
#define TIMER_TRAYSHOW					2						/// 托盘动态图标的显示timer号
#define TIMER_SENDFILES_REFRESH			3						/// 发送文件更新列表框
#define TIMER_SHARESCREEN				4						/// 共享屏幕的timer号
#define TIMER_VIDEOCHAT					5						/// 视频聊天的timer号

#define SHARESCREEN_BITCOUNT			8						/// 分享屏幕时颜色的位数

#define DEFAULT_WHITEBOARD_CANVAS_COLOR	RGB( 255, 255, 255 )	/// 默认白板画布颜色
#define DEFAULT_WHITEBOARD_TOOL_COLOR	RGB( 255, 0, 0 )		/// 默认白板工具颜色
#define WHITEBOARD_WIDTH_1				1						/// 白板线宽一
#define WHITEBOARD_WIDTH_2				( WHITEBOARD_WIDTH_1 + 6)
																/// 白板线宽二
#define WHITEBOARD_WIDTH_3				( WHITEBOARD_WIDTH_2 + 6)
																/// 白板线宽三
#define WHITEBOARD_WIDTH_4				( WHITEBOARD_WIDTH_3 + 6)
																/// 白板线宽四
#define WHITEBOARD_MIN_WIDTH			300						/// 白板窗口最小宽度
#define WHITEBOARD_MIN_HEIGHT			450						/// 白板窗口最小高度

#define VIDEOCHAT_VIDEO_WIDTH			320						/// 视频的宽
#define VIDEOCHAT_VIDEO_HEIGHT			240						/// 视频的长
#define VIDEOCHAT_VIDEOWND_WIDTH		( 320 + 2 * 2 )			/// 视频窗口的宽
#define VIDEOCHAT_VIDEOWND_HEIGHT		( 240 + 2 * 2 )			/// 视频窗口的长

#define AUDIO_BUFFER_SIZE				16384					/// 音频缓冲区长度
#define AUDIO_BUFFER_BLOCK				5						/// 接收音频数据的缓冲区数

#define MAXCHATLENGTH					512						/// 聊天发送消息每次的最大长度

#define DEFAULT_REFRESH_TIME			( 1000 * 5 )			/// 刷新联系人列表的时间,单位毫秒
#define DEFAULT_SHARESCREEN_REFRESH		( 200 )					/// 共享屏幕刷新的时间
#define DEFALUT_VIDEOCHAT_REFRESH		( 2000 )				/// 视频聊天刷新			

#define MAXDATAPACKETLENGTH				( 38 + 512 )			/// 数据包的最大长度

#define WM_SHELLNOTIFY					WM_USER+1				/// 托盘消息
#define TM_SENDVIDEO_RECEIVE			WM_USER+2				/// 发送视频数据线程的接收数据消息
#define TM_SENDVIDEO_UPDATEPICTURE		WM_USER+3				/// 发送视频数据线程的更新视频画面的消息
#define TM_SENDVIDEO_DELUSER			WM_USER+4				/// 发送视频数据线程的删除用户的消息
#define TM_SENDVIDEO_SENDAUDIO			WM_USER+5				/// 发送视频数据线程的发送音频数据的消息
#define TM_SENDVIDEO_EXIT				WM_USER+6				/// 发送视频数据线程的退出消息
#define TM_RECEIVEVIDEO_RECEIVE			WM_USER+7				/// 接收视频数据线程的接收数据消息
#define TM_RECEIVEVIDEO_DELUSER			WM_USER+8				/// 接收视频数据线程的删除用户的消息
#define TM_RECEIVEVIDEO_EXIT			WM_USER+9				/// 接收视频数据线程的退出消息

#define CONFIG_FILE						"conf.ini"				/// 配置文件名称

#define	DEFAULT_VIRTUALKEYCODE			'Z'						/// 默认热键虚拟键码
#define	DEFAULT_MODIFIERS				MOD_CONTROL | \
										MOD_ALT					/// 默认热键修正符标志
#define DEFAULT_AUTOADDFRIENDS			0						/// 默认自动加为好友

#define STATE_ONLINE					0						/// 在线状态
#define STATE_OFFLINE					1						/// 下线状态

#define DEFAULT_FACE					0						/// 默认头像
#define DEFAULT_STATE					STATE_ONLINE			/// 默认状态
#define DEFAULT_NICKNAME				"无名"					/// 默认昵称
#define MAXHISTORYFRIENDS				10						/// 联系人历史记录最大值
#define MAXFACES						83						/// 最大头像数

#define IDHOTKEY						100						/// 热键的ID
#define	FACEBGCOLOR						RGB( 0, 128, 128 )		/// 头像背景颜色

#define DEFAULT_FRIENDSLIST_HEIGHT		( 32 + 5 + 5 )			/// 默认用户列表的高度

#define DEFALUT_FRIENDSLIST_NAMECOLOR	RGB( 0, 0, 0 )			/// 用户列表用户名的颜色
#define DEFALUT_FRIENDSLIST_IPCOLOR		RGB( 128, 128, 128 )	/// 用户列表用户IP的颜色
#define DEFAULT_FRIENDSLIST_NORMALCOLOR	RGB( 255, 255, 255 )	/// 用户列表正常的背景色
#define DEFAULT_FRIENDSLIST_SELCOLOR	RGB( 252, 234, 162 )	/// 用户列表选中的背景色
#define DEFAULT_FRIENDSLIST_HOVERCOLOR	RGB( 197, 227, 247 )	/// 用户列表鼠标滑过的颜色
#define DEFAULT_FRIENDSLIST_FONT		100						/// 用户列表用户和IP的字体大小

#define DEFAULT_PORT					8000					/// 默认端口号
#define CHATROOM_SERVER_PORT			( DEFAULT_PORT + 1 )	/// 聊天室服务器端口号
#define CHATROOM_CLIENT_PORT			( DEFAULT_PORT + 2 )	/// 聊天室客户端端口号
#define SENDFILESSERVER_PORT			( DEFAULT_PORT + 3 )	/// 发送文件服务器的端口号
#define SHARESCREENSERVER_PORT			( DEFAULT_PORT + 4 )	/// 共享屏幕服务器端口号
#define SHARESCREENCLIENT_PORT			( DEFAULT_PORT + 5 )	/// 共享屏幕客户端端口号
#define WHITEBOARD_SERVER_PORT			( DEFAULT_PORT + 6 )	/// 白板服务器端口号
#define WHITEBOARD_CLIENT_PORT			( DEFAULT_PORT + 7 )	/// 白板客户端端口号
#define VIDEOCHAT_PORT					( DEFAULT_PORT + 8 )	/// 视频聊天端口号
