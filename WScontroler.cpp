#include <windows.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <conio.h> 
#include <process.h>
using namespace std;
/*
//获取控制台窗口信息  
GetConsoleScreenBufferInfo();  
  
//获取控制台窗口标题  
GetConsoleTitle();  
  
//更改指定缓冲区大小  
SetConsoleScreenBufferSize();  
  
//设置控制台窗口标题  
SetConsoleTitle();  
  
//设置控制台窗口信息  
SetConsoleWindowInfo();  

*/ 
/* 
基本文本属性 
FOREGROUND_BLUE 蓝色 
FOREGROUND_GREEN 绿色 
FOREGROUND_RED 红色 
FOREGROUND_INTENSITY 加强 
BACKGROUND_BLUE 蓝色背景 
BACKGROUND_GREEN 绿色背景 
BACKGROUND_RED 红色背景 
BACKGROUND_INTENSITY 背景色加强 
COMMON_LVB_REVERSE_VIDEO 反色 
*/  
 /* 
虚拟键代码      值          键名称 
-----------------------------------------------------             
VK_BACK         0x08        退格键 
VK_TAB          0x09        Tab键 
VK_RETURN       0x0D        回车键 
VK_SHIFT        0x10        Shift键 
VK_LSHIFT       0xA0        左Shift键 
VK_RSHIFT       0xA1        右Shift键 
VK_CONTROL      0x11        Ctrl键 
VK_LCONTROL     0xA2        左Ctrl键 
VK_RCONTROL     0xA3        右Ctrl键 
VK_MENU         0x12        Alt键 
VK_LMENU        0xA4        左Alt键 
VK_RMENU        0xA5        右Alt键 
VK_PAUSE        0x13        Pause键 
VK_CAPITAL      0x14        Caps Lock键 
VK_NUMLOCK      0x90        Num Lock键 
VK_SCROLL       0x91        Scroll Lock键 
VK_ESCAPE       0x1B        Esc键 
VK_SPACE        0x20        空格键 
VK_PRIOR        0x21        Page Up键 
VK_NEXT         0x22        Page Down键 
VK_END          0x23        End键 
VK_HOME         0x24        Home键 
VK_LEFT         0x25        左方向键 
VK_UP           0x26        上方向键 
VK_RIGHT        0x27        右方向键 
VK_DOWN         0x28        下方向键 
VK_DELETE       0x2E        Delete键 
VK_INSERT       0x2D        Insert键 
'0'             0x30        0键（非小键盘） 
'1'             0x31        1键（非小键盘） 
'2'             0x32        2键（非小键盘） 
...             ...         ... 
'9'             0x39        9键（非小键盘） 
'A'             0x41        A键 
'B'             0x42        B键 
...             ...         ... 
'Z'             0x5A        Z键 
VK_SLEEP        0x5F        Sleep键 
VK_NUMPAD0      0x60        小键盘0键 
VK_NUMPAD1      0x61        小键盘1键 
VK_NUMPAD2      0x62        小键盘2键 
...             ...         ... 
VK_NUMPAD9      0x69        小键盘9键 
VK_MULTIPLY     0x6A        小键盘乘键* 
VK_ADD          0x6B        小键盘加键+ 
VK_SUBTRACT     0x6D        小键盘减键- 
VK_DIVIDE       0x6F        小键盘除键/ 
VK_DECIMAL      0x6E        小键盘点键. 
VK_F1           0x70        F1键 
VK_F2           0x71        F2键 
...             ...         ... 
VK_F12          0x7B        F12键 
VK_F13          0x7C        F13键      注：别问我，我也不知道什么电脑有这么多键 
...             ...         ... 
VK_F24          0x87        F24键 
VK_OEM_1        0xBA        ;:键 
VK_OEM_2        0xBF        /?键 
VK_OEM_3        0xC0        ·~键 
VK_OEM_4        0xDB        [{键 
VK_OEM_5        0xDC        \|键 
VK_OEM_6        0xDD        ]}键 
VK_OEM_7        0xDE        '"键 
VK_OEM_PLUS     0xBB        =+键 
VK_OEM_MINUS    0xBD        -_键 
VK_OEM_COMMA    0xBC        ,<键 
VK_OEM_PERIOD   0xBE        .>键  
*/   
#define  FORE_BLUE    FOREGROUND_BLUE          //蓝色文本属性  
#define  FORE_GREEN   FOREGROUND_GREEN          //绿色文本属性  
#define  FORE_RED     FOREGROUND_RED            //红色文本属性  
#define  FORE_PURPLE  FORE_BLUE | FORE_RED      //紫色文本属性  
#define  FORE_CYAN    FORE_BLUE | FORE_GREEN    //青色文本属性  
#define  FORE_YELLOW  FORE_RED | FORE_GREEN     //黄色文本属性  
#define  FORE_GRAY    FOREGROUND_INTENSITY      //灰色文本属性  
#define  BACK_BLUE    BACKGROUND_BLUE           //蓝色背景属性  
#define  BACK_GREEN   BACKGROUND_GREEN          //绿色背景属性  
#define  BACK_RED     BACKGROUND_RED            //绿色背景属性  
#define  BACK_PURPLE  BACK_BLUE | BACK_RED      //紫色背景属性  
#define  BACK_CYAN    BACK_BLUE | BACK_GREEN    //青色背景属性  
#define  BACK_YELLOW  BACK_RED | BACK_GREEN     //黄色背景属性  
#define  BACK_GRAY    BACKGROUND_INTENSITY      //灰色背景属性  
void Eventthread(PVOID param); 
enum typeOfStdHandle
{
STDOUTHANDLE,
STDINHANDLE,
STDERRORHANDLE
};
class WScontroler
{
public:
~WScontroler();
WScontroler();
HANDLE getStdHandle(typeOfStdHandle w);//获取想要的句柄 
char title[256];
SHORT BFwidth;
SHORT BFheight;
void getH_and_W(){this->BFwidth=this->screen_info.dwSize.X;this->BFheight=this->screen_info.dwSize.Y;}
COORD getNowPos(){return this->screen_info.dwCursorPosition;} //当前光标位置 
char* getTitle(char *s){GetConsoleTitle(s,255);return s;} 
void setTitle(char *s){SetConsoleTitle(s); strcpy(title,s); }
void setBFSize(COORD size){SetConsoleScreenBufferSize(Ohandle, size);}
void setScreenInfo(SMALL_RECT *rc){SetConsoleWindowInfo(Ohandle, 1, rc); } 
void setTextAttribute(WORD w){ SetConsoleTextAttribute(Ohandle,w);}
void MoveTextRect(SHORT left,SHORT top,SHORT width,SHORT height,SHORT posx,SHORT posy);
void gotoxy(SHORT x,SHORT y){ SetConsoleCursorPosition(Ohandle,(COORD){x,y});}
void addEventPromise();
private:
bool initHandle();

//定义窗口缓冲区信息结构体
CONSOLE_SCREEN_BUFFER_INFO screen_info;	
HANDLE Ohandle;//输出句柄
HANDLE Ihandle;//输入句柄
HANDLE Ehandle;//错误句柄


};

WScontroler::WScontroler()
{
if(!initHandle())
{
	cout<<"failed to init handle!"<<endl;
	return;
}
//获取窗口信息
if(!GetConsoleScreenBufferInfo(Ohandle, &screen_info))
{
	cout<<"faile to get screen info"<<endl;
	
	return;
}
getH_and_W();
char str[300]="hh222";
cout<<"init this"<<endl;
cout<<"this title:"<<getTitle(title)<<endl;
setTitle(str);
cout<<"now title:"<<title<<endl;
cout<<"BF width:"<<BFwidth<<endl<<"BF Height:"<<BFheight<<endl;
}
////////////////
WScontroler::~WScontroler()
{
	CloseHandle(Ohandle);    //关闭标准输出设备句柄 
	CloseHandle(Ihandle);    
	CloseHandle(Ehandle);    
}
/////////////////
HANDLE WScontroler::getStdHandle(typeOfStdHandle w)
{
/* 
StdHandle可以是 
STD_INPUT_HANDLE    标准输入设备句柄 
STD_OUTPUT_HANDLE   标准输出设备句柄 
STD_ERROR_HANDLE    标准错误设备句柄 
*/	
switch(w)
{
	case STDOUTHANDLE: return Ohandle; break;
	case STDINHANDLE:  return Ihandle; break;
	case STDERRORHANDLE: return Ehandle; break;
}
}

///////////////
bool WScontroler::initHandle()
{
	if(Ohandle= GetStdHandle(STD_OUTPUT_HANDLE))
	if(Ihandle= GetStdHandle(STD_INPUT_HANDLE))
	if(Ihandle= GetStdHandle(STD_ERROR_HANDLE))
	return true;
	return false;
}
////////////////
void WScontroler::MoveTextRect(SHORT left,SHORT top,SHORT width,SHORT height,SHORT posx,SHORT posy)
{	 COORD pos={posx,posy};
	 SMALL_RECT scroll={left,top,left+width-1,height+top-1};
	 CHAR_INFO chFill;       //定义填充字符
     chFill.Char.AsciiChar = ' ';  
     chFill.Attributes = screen_info.wAttributes; 
	 ScrollConsoleScreenBuffer(Ohandle, &scroll, NULL, pos, &chFill); //移动文本
}
/////////////////////////
void WScontroler::addEventPromise()
{
	_beginthread(Eventthread, 0,NULL);
}
/////////////////////////////
void Eventthread(PVOID param)
{
    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);      //获得标准输入设备句柄  
    INPUT_RECORD keyrec;        //定义输入事件结构体  
    DWORD res;      //定义返回记录  
    for (;;)  
    {  
        ReadConsoleInput(handle_in, &keyrec, 1, &res);      //读取输入事件  
        if (keyrec.EventType == KEY_EVENT)      //如果当前事件是键盘事件  
        {  cout<<res;
          /*  if (keyrec.Event.KeyEvent.wVirtualKeyCode == 'A'  
                && keyrec.Event.KeyEvent.bKeyDown == true)   //当按下字母A键时  
            {  
                if (keyrec.Event.KeyEvent.dwControlKeyState & SHIFT_PRESSED)    //Shift键为按下状态  
                {  
                    printf("Shift+");  
                }  
                if (keyrec.Event.KeyEvent.dwControlKeyState & CAPSLOCK_ON)  //大写锁定为打开状态  
                {  
                    printf("A ");  
                }  
                else        //大写锁定关闭状态  
                {  
                    printf("a ");  
                }  
            }  */
        }  
    }       
}
int main()
{
	WScontroler a;
	a.setTextAttribute(FORE_GRAY);
	//a.gotoxy(0,0);
	cout<<"dddddddddddddddddddddddddd\ndddddddddddddddddddddddddddd\ndddddddddddddddddddddddddddddd"<<endl;
    a.MoveTextRect(1,1,5,7,12,12);
    a.addEventPromise();
    Sleep(100000);

	return 0;
} 