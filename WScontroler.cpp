#include <windows.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <conio.h> 
#include <process.h>
using namespace std;
/*
//��ȡ����̨������Ϣ  
GetConsoleScreenBufferInfo();  
  
//��ȡ����̨���ڱ���  
GetConsoleTitle();  
  
//����ָ����������С  
SetConsoleScreenBufferSize();  
  
//���ÿ���̨���ڱ���  
SetConsoleTitle();  
  
//���ÿ���̨������Ϣ  
SetConsoleWindowInfo();  

*/ 
/* 
�����ı����� 
FOREGROUND_BLUE ��ɫ 
FOREGROUND_GREEN ��ɫ 
FOREGROUND_RED ��ɫ 
FOREGROUND_INTENSITY ��ǿ 
BACKGROUND_BLUE ��ɫ���� 
BACKGROUND_GREEN ��ɫ���� 
BACKGROUND_RED ��ɫ���� 
BACKGROUND_INTENSITY ����ɫ��ǿ 
COMMON_LVB_REVERSE_VIDEO ��ɫ 
*/  
 /* 
���������      ֵ          ������ 
-----------------------------------------------------             
VK_BACK         0x08        �˸�� 
VK_TAB          0x09        Tab�� 
VK_RETURN       0x0D        �س��� 
VK_SHIFT        0x10        Shift�� 
VK_LSHIFT       0xA0        ��Shift�� 
VK_RSHIFT       0xA1        ��Shift�� 
VK_CONTROL      0x11        Ctrl�� 
VK_LCONTROL     0xA2        ��Ctrl�� 
VK_RCONTROL     0xA3        ��Ctrl�� 
VK_MENU         0x12        Alt�� 
VK_LMENU        0xA4        ��Alt�� 
VK_RMENU        0xA5        ��Alt�� 
VK_PAUSE        0x13        Pause�� 
VK_CAPITAL      0x14        Caps Lock�� 
VK_NUMLOCK      0x90        Num Lock�� 
VK_SCROLL       0x91        Scroll Lock�� 
VK_ESCAPE       0x1B        Esc�� 
VK_SPACE        0x20        �ո�� 
VK_PRIOR        0x21        Page Up�� 
VK_NEXT         0x22        Page Down�� 
VK_END          0x23        End�� 
VK_HOME         0x24        Home�� 
VK_LEFT         0x25        ����� 
VK_UP           0x26        �Ϸ���� 
VK_RIGHT        0x27        �ҷ���� 
VK_DOWN         0x28        �·���� 
VK_DELETE       0x2E        Delete�� 
VK_INSERT       0x2D        Insert�� 
'0'             0x30        0������С���̣� 
'1'             0x31        1������С���̣� 
'2'             0x32        2������С���̣� 
...             ...         ... 
'9'             0x39        9������С���̣� 
'A'             0x41        A�� 
'B'             0x42        B�� 
...             ...         ... 
'Z'             0x5A        Z�� 
VK_SLEEP        0x5F        Sleep�� 
VK_NUMPAD0      0x60        С����0�� 
VK_NUMPAD1      0x61        С����1�� 
VK_NUMPAD2      0x62        С����2�� 
...             ...         ... 
VK_NUMPAD9      0x69        С����9�� 
VK_MULTIPLY     0x6A        С���̳˼�* 
VK_ADD          0x6B        С���̼Ӽ�+ 
VK_SUBTRACT     0x6D        С���̼���- 
VK_DIVIDE       0x6F        С���̳���/ 
VK_DECIMAL      0x6E        С���̵��. 
VK_F1           0x70        F1�� 
VK_F2           0x71        F2�� 
...             ...         ... 
VK_F12          0x7B        F12�� 
VK_F13          0x7C        F13��      ע�������ң���Ҳ��֪��ʲô��������ô��� 
...             ...         ... 
VK_F24          0x87        F24�� 
VK_OEM_1        0xBA        ;:�� 
VK_OEM_2        0xBF        /?�� 
VK_OEM_3        0xC0        ��~�� 
VK_OEM_4        0xDB        [{�� 
VK_OEM_5        0xDC        \|�� 
VK_OEM_6        0xDD        ]}�� 
VK_OEM_7        0xDE        '"�� 
VK_OEM_PLUS     0xBB        =+�� 
VK_OEM_MINUS    0xBD        -_�� 
VK_OEM_COMMA    0xBC        ,<�� 
VK_OEM_PERIOD   0xBE        .>��  
*/   
#define  FORE_BLUE    FOREGROUND_BLUE          //��ɫ�ı�����  
#define  FORE_GREEN   FOREGROUND_GREEN          //��ɫ�ı�����  
#define  FORE_RED     FOREGROUND_RED            //��ɫ�ı�����  
#define  FORE_PURPLE  FORE_BLUE | FORE_RED      //��ɫ�ı�����  
#define  FORE_CYAN    FORE_BLUE | FORE_GREEN    //��ɫ�ı�����  
#define  FORE_YELLOW  FORE_RED | FORE_GREEN     //��ɫ�ı�����  
#define  FORE_GRAY    FOREGROUND_INTENSITY      //��ɫ�ı�����  
#define  BACK_BLUE    BACKGROUND_BLUE           //��ɫ��������  
#define  BACK_GREEN   BACKGROUND_GREEN          //��ɫ��������  
#define  BACK_RED     BACKGROUND_RED            //��ɫ��������  
#define  BACK_PURPLE  BACK_BLUE | BACK_RED      //��ɫ��������  
#define  BACK_CYAN    BACK_BLUE | BACK_GREEN    //��ɫ��������  
#define  BACK_YELLOW  BACK_RED | BACK_GREEN     //��ɫ��������  
#define  BACK_GRAY    BACKGROUND_INTENSITY      //��ɫ��������  
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
HANDLE getStdHandle(typeOfStdHandle w);//��ȡ��Ҫ�ľ�� 
char title[256];
SHORT BFwidth;
SHORT BFheight;
void getH_and_W(){this->BFwidth=this->screen_info.dwSize.X;this->BFheight=this->screen_info.dwSize.Y;}
COORD getNowPos(){return this->screen_info.dwCursorPosition;} //��ǰ���λ�� 
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

//���崰�ڻ�������Ϣ�ṹ��
CONSOLE_SCREEN_BUFFER_INFO screen_info;	
HANDLE Ohandle;//������
HANDLE Ihandle;//������
HANDLE Ehandle;//������


};

WScontroler::WScontroler()
{
if(!initHandle())
{
	cout<<"failed to init handle!"<<endl;
	return;
}
//��ȡ������Ϣ
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
	CloseHandle(Ohandle);    //�رձ�׼����豸��� 
	CloseHandle(Ihandle);    
	CloseHandle(Ehandle);    
}
/////////////////
HANDLE WScontroler::getStdHandle(typeOfStdHandle w)
{
/* 
StdHandle������ 
STD_INPUT_HANDLE    ��׼�����豸��� 
STD_OUTPUT_HANDLE   ��׼����豸��� 
STD_ERROR_HANDLE    ��׼�����豸��� 
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
	 CHAR_INFO chFill;       //��������ַ�
     chFill.Char.AsciiChar = ' ';  
     chFill.Attributes = screen_info.wAttributes; 
	 ScrollConsoleScreenBuffer(Ohandle, &scroll, NULL, pos, &chFill); //�ƶ��ı�
}
/////////////////////////
void WScontroler::addEventPromise()
{
	_beginthread(Eventthread, 0,NULL);
}
/////////////////////////////
void Eventthread(PVOID param)
{
    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);      //��ñ�׼�����豸���  
    INPUT_RECORD keyrec;        //���������¼��ṹ��  
    DWORD res;      //���巵�ؼ�¼  
    for (;;)  
    {  
        ReadConsoleInput(handle_in, &keyrec, 1, &res);      //��ȡ�����¼�  
        if (keyrec.EventType == KEY_EVENT)      //�����ǰ�¼��Ǽ����¼�  
        {  cout<<res;
          /*  if (keyrec.Event.KeyEvent.wVirtualKeyCode == 'A'  
                && keyrec.Event.KeyEvent.bKeyDown == true)   //��������ĸA��ʱ  
            {  
                if (keyrec.Event.KeyEvent.dwControlKeyState & SHIFT_PRESSED)    //Shift��Ϊ����״̬  
                {  
                    printf("Shift+");  
                }  
                if (keyrec.Event.KeyEvent.dwControlKeyState & CAPSLOCK_ON)  //��д����Ϊ��״̬  
                {  
                    printf("A ");  
                }  
                else        //��д�����ر�״̬  
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