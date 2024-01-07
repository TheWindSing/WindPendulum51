#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

uchar time,count=100,flag=1;//低电平的占空

sbit PWM1=P2^0;		//PWM 通道 1，反转脉冲
sbit PWM2=P2^1;		//PWM 通道 2，正转脉冲
sbit PWM3=P2^2;		//PWM 通道 3，反转脉冲
sbit PWM4=P2^3;		//PWM 通道 4，正转脉冲
sbit key_turn=P3^7; //电机换向


void delayxms(uint z);
void Motor_turn(void);
void timer0_init(void);

void main(void)
{
	timer0_init();
	while(1)
	{
		 Motor_turn();
	}
}

void delayxms(uint z)//延时xms程序
{
    uint x,y;
    for(y=z;x>0;x--)
          for(y=110;y>0;y--);
}

void Motor_turn(void)	//电机换向控制
{
	if(key_turn==0)
	 {
	    // delayxms(2);//此处可有可无，但是时间不能太长，否者会的中断产生冲突
	    if(key_turn==0)flag=~flag;
	    while(!key_turn);
	 }
}

void timer0_init(void)	//定时器0初始化
{
	TMOD=0x01; //定时器0工作于方式1
	TH0=(65536-10)/256;
	TL0=(65536-10)%256;
	TR0=1;
	ET0=1;
	EA=1;
}

void timer0_int(void) interrupt 1	//定时器0中断函数
{
	TR0=0;//设置定时器初值期间，关闭定时器
	TH0=(65536-10)/256;
	TL0=(65536-10)%256;
	TR0=1;

	if(flag==1)//电机正转
	{
		PWM1=0;
		PWM3=0;
		time++;
		if(time<count)PWM2=1;
		else  PWM2=0;
		
		if(time>=100)time=0;
	}

	else //电机反转
	{
		PWM2=0;
		PWM4=0;
		time++;
		if(time<count) PWM1=1;
		else PWM1=0;
		
		if(time>=100)time=0;
	}
}