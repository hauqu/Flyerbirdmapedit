#include<graphics.h>
#include<fstream>
using namespace std;

const int MapSize = 32; //地图单位长度
const int MapHig = 15;  //地图纵向元素数
const int MapLen = 35; //地图横向元素数

const int ButtonSize = 32; //按钮半径
const int ButtonNum = 4; //按钮数量

const int WinL = MapSize * MapLen; //地图界面长
const int WinH = MapSize * MapHig; //地图界面高

int Map[MapLen][MapHig] = { 0 }; //初始化地图元素数组
int MapObjectValue = 1; //地图元素值,默认为 1
const int MapObjectValueMax = 5; //最大值
const int MapObjectValueMin = 0; //最小值，默认为空，且默认为0

IMAGE wall; //地图元素贴图 
IMAGE hole; //地图元素贴图
IMAGE box; //地图元素贴图
IMAGE blue; //地图元素贴图
IMAGE man; //地图元素贴图
IMAGE tank; //地图元素贴图

struct Point  //按钮结构体 ，点坐标
{
	int x;
	int y;
};

struct Point ButtonClear = {WinL+32*2,32*1}; //清除按钮
struct Point ButtonChoose = { WinL +32*2,32*5 }; //选择地图元素
struct Point ButtonHelp = { WinL + 32 * 2,32 * 7 };//帮助
struct Point ButtonSaveExit = { WinL + 32 * 2,32 * 3 };//保存并退出

void Button(int x, int y);//判断是哪一个按钮
//*****************************
//               按钮功能函数
void Button_help();
void Button_clear();
void Button_choose();
void Button_save_exit();
//****************************
void CreatMapDateText(); //将地图元素存储到map.txt中

void DrawLine(); //画出地图编辑器界面

bool CanEdit(int x, int y);//是否属于可编辑范围

int main()
{
	loadimage(&wall, "wall.jpg", 32, 32);
	loadimage(&hole, "hole.jpg",32,32);
	loadimage(&box, "box.jpg", 32, 32);
	loadimage(&blue, "blue.jpg", 32, 32);
	loadimage(&man, "man.jpg", 32, 32);
	loadimage(&tank, "tank.jpg", 32, 32);
	initgraph(WinL+32*4, WinH+32*2);
	DrawLine();
	MOUSEMSG click;
	while (1)
	{
		click = GetMouseMsg();
		if (click.mkRButton)
		{
			if(CanEdit(click.x, click.y))
			{
				Map[click.x / MapSize][click.y / MapSize] = MapObjectValueMin;
				putimage(click.x / MapSize * 32, click.y / MapSize * 32, &hole);
				rectangle(click.x / MapSize * 32,click.y / MapSize * 32,click.x / MapSize * 32 + 32,click.y / MapSize * 32 + 32
				);
			}
			else{	Button(click.x, click.y);}
		}
		if (click.mkMButton)
		{
			break;
		}
		if (click.mkLButton)
		{	
			if (CanEdit(click.x, click.y))
			{
				Map[click.x / MapSize][click.y / MapSize] = MapObjectValue;
				switch (MapObjectValue)
				{
				case 1:
					putimage(click.x / MapSize * 32, click.y / MapSize * 32, &wall);
					break;
				case 2:
					putimage(click.x / MapSize * 32, click.y / MapSize * 32, &box);
					break;
				case 3:
					putimage(click.x / MapSize * 32, click.y / MapSize * 32, &man);
					break;
				case 4:
					putimage(click.x / MapSize * 32, click.y / MapSize * 32, &blue);
					break;
				case 5:
					putimage(click.x / MapSize * 32, click.y / MapSize * 32, &tank);
					break;
				default:
					break;
				}
				
				rectangle(click.x / MapSize * 32,click.y / MapSize * 32,click.x / MapSize * 32 + 32,click.y / MapSize * 32 + 32);
			}
			else{Button(click.x, click.y);}		
		}
	}
	return 0;
}
void CreatMapDateText()
{
	ofstream mapdate; //纯元素
	ofstream maparraw; //数组
	maparraw.open("maparraw.txt");
	mapdate.open("mapdate.txt");
	for (int j = 0; j < MapHig; j++)
	{
		for (int i = 0; i < MapLen; i++)
		{
			mapdate << Map[i][j];
			maparraw << Map[i][j];
			maparraw << ",";
		}
		mapdate << endl;
		maparraw << endl;
	}
	mapdate.close();
	maparraw.close();
}
void DrawLine()
{
	for (int i = 0; i <= MapLen; i++)
	{
		for (int j = 0; j <= MapHig; j++)
		{
			line(i * 32, 0, i * 32, WinH);
			line(0, j * 32, WinL, j * 32);
		}
	}//画出格子
	for (int i = 0; i < MapLen;)
	{
		char numl[MapLen * 2 + 1] = { "01030507091112131517192123252729313335" };
		outtextxy(i * 32-7, WinH, numl[i]);
		outtextxy(i * 32-7 + 7, WinH, numl[i + 1]);
		i++;
		i++;
	}//标出行数
	for (int i = 0; i < MapHig;)
	{
		char numh[MapHig * 2 + 1] = { "010305070911131517" };
		outtextxy(WinL, i * 32-7, numh[i]);
		outtextxy(WinL+7 ,i * 32-7, numh[i + 1]);
		i++;
		i++;
	}//标出列数

	setfillcolor(RGB(128, 128, 64));
	fillcircle(ButtonChoose.x, ButtonChoose.y, 32);
	fillcircle(ButtonClear.x, ButtonClear.y, 32);
	fillcircle(ButtonSaveExit.x, ButtonSaveExit.y, 32);
	fillcircle(ButtonHelp.x, ButtonHelp.y, 32);

	putimage(ButtonHelp.x, ButtonHelp.y+32*2, &wall);

	setbkmode(TRANSPARENT);
	outtextxy(ButtonClear.x-12, ButtonClear.y-6, "清空");
	outtextxy(ButtonSaveExit.x-12, ButtonSaveExit.y-6, "完成");
	outtextxy(ButtonChoose.x-12, ButtonChoose.y-6, "切换");
	outtextxy(ButtonHelp.x-12, ButtonHelp.y-6, "帮助");
	setfillcolor(RGB(256, 256, 256));
	//画出圆形按钮
}
bool CanEdit(int x,int y)
{
	if (x>MapLen*MapSize-2)
	{
		return false;
	}
	
	if (y>MapHig*MapSize-2)
	{
		return false;
	}
	return true;
}
void Button(int x, int y)
{
	float distance[ButtonNum] = {
		sqrt((x - ButtonClear.x)*(x - ButtonClear.x) + (y - ButtonClear.y)*(y - ButtonClear.y)),
		sqrt((x - ButtonChoose.x)*(x - ButtonChoose.x) + (y - ButtonChoose.y)*(y - ButtonChoose.y)),
		sqrt((x - ButtonHelp.x)*(x - ButtonHelp.x) + (y - ButtonHelp.y)*(y - ButtonHelp.y)),
		sqrt((x - ButtonSaveExit.x)*(x - ButtonSaveExit.x) + (y - ButtonSaveExit.y)*(y - ButtonSaveExit.y))
	};
	int n = 0;
	for (int i = 0; i < ButtonNum; i++)
	{
		if(distance[i]<ButtonSize)
		{
			n = i;
			n++;
			switch (n)
			{
			case 1:
				Button_clear();
				break;
			case 2:
				Button_choose();
				break;
			case 3:
				Button_help();
				break;
			case 4:
				Button_save_exit();
				break;
			default:
				break;
			}
		}
	}
}
void Button_clear()
{
	cleardevice();
	MapObjectValue = 1;
	for (int i = 0; i <= MapLen; i++)
	{
		for (int j = 0; j <= MapHig; j++)
		{
			Map[i][j] = 0;
		}
	}
	DrawLine();

}
void Button_choose()
{

	if(++MapObjectValue==6)
	{
		MapObjectValue = 1;
	}
	switch (MapObjectValue)
	{
	case 1:
		putimage(ButtonHelp.x, ButtonHelp.y + 32 * 2, &wall);
		break;
	case 2:
		putimage(ButtonHelp.x, ButtonHelp.y + 32 * 2, &box);
		break;
	case 3:
		putimage(ButtonHelp.x, ButtonHelp.y + 32 * 2, &man);
		break;
	case 4:
		putimage(ButtonHelp.x, ButtonHelp.y + 32 * 2, &blue);
		break;
	case 5:
		putimage(ButtonHelp.x, ButtonHelp.y + 32 * 2, &tank);
		break;
	default:
		break;
	}
}
void Button_save_exit()
{
	CreatMapDateText();
	cleardevice();
	outtextxy(0, 50 * 4, "        地图保存在map.txt中，每次运行程序覆盖");
	outtextxy(0, 50 * 5, "                点击鼠标退出");
	Sleep(2000);

	while (true)
	{
		MOUSEMSG m = GetMouseMsg();
		if (m.mkCtrl || m.mkLButton || m.mkMButton || m.mkRButton)
		{
			
			break;
		}
	}
	
	closegraph();
	exit(-1);
}
void Button_help()
{
	cleardevice();
	settextstyle(30, 25, "宋体");
	outtext("鼠标左键填充，右键撤回，中键退出");
	outtextxy(0, 50, "清空-清空当前");
	outtextxy(0, 50*2, "完成-保存并退出");
	outtextxy(0, 50 * 3, "切换-切换填充元素");
	outtextxy(0, 50 * 4, "地图保存在map.txt中，每次运行程序覆盖");
	outtextxy(0, 50 * 5, "点击鼠标继续");
	MapObjectValue = 1;
	for (int i = 0; i <= MapLen; i++)
	{
		for (int j = 0; j <= MapHig; j++)
		{
			Map[i][j] = 0;
		}
	}
	
	while (true)
	{
		MOUSEMSG m = GetMouseMsg();
		if (m.mkCtrl||m.mkLButton||m.mkMButton||m.mkRButton)
		{
			settextstyle(15,10,"楷体");
			cleardevice();
			DrawLine();
			break;
		}
	}

}