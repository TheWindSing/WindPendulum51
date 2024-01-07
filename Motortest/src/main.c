#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

uchar time,count=100,flag=1;//�͵�ƽ��ռ��

sbit PWM1=P2^0;		//PWM ͨ�� 1����ת����
sbit PWM2=P2^1;		//PWM ͨ�� 2����ת����
sbit PWM3=P2^2;		//PWM ͨ�� 3����ת����
sbit PWM4=P2^3;		//PWM ͨ�� 4����ת����
sbit key_turn=P3^7; //�������


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

void delayxms(uint z)//��ʱxms����
{
    uint x,y;
    for(y=z;x>0;x--)
          for(y=110;y>0;y--);
}

void Motor_turn(void)	//����������
{
	if(key_turn==0)
	 {
	    // delayxms(2);//�˴����п��ޣ�����ʱ�䲻��̫�������߻���жϲ�����ͻ
	    if(key_turn==0)flag=~flag;
	    while(!key_turn);
	 }
}

void timer0_init(void)	//��ʱ��0��ʼ��
{
	TMOD=0x01; //��ʱ��0�����ڷ�ʽ1
	TH0=(65536-10)/256;
	TL0=(65536-10)%256;
	TR0=1;
	ET0=1;
	EA=1;
}

void timer0_int(void) interrupt 1	//��ʱ��0�жϺ���
{
	TR0=0;//���ö�ʱ����ֵ�ڼ䣬�رն�ʱ��
	TH0=(65536-10)/256;
	TL0=(65536-10)%256;
	TR0=1;

	if(flag==1)//�����ת
	{
		PWM1=0;
		PWM3=0;
		time++;
		if(time<count)PWM2=1;
		else  PWM2=0;
		
		if(time>=100)time=0;
	}

	else //�����ת
	{
		PWM2=0;
		PWM4=0;
		time++;
		if(time<count) PWM1=1;
		else PWM1=0;
		
		if(time>=100)time=0;
	}
}