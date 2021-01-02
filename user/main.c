#include <reg52.h>
typedef unsigned int uint;
typedef unsigned char uchar;

sbit key1=P1^0;
sbit key2=P1^1;
sbit key3=P1^2;
sbit key4=P1^3;
sbit key5=P1^4;

sbit led1 = P2^0;
sbit led2 = P2^1;
sbit led3 = P2^2;
sbit led4 = P2^3;
sbit led5 = P2^4;
sbit led6 = P2^5;
sbit led7 = P2^6;

void Init();
void delay(uint Time);
void test_v1(uchar key,uchar keycan_v);
void key_process(uchar key,uchar trg,uchar cont);
void keycan();
uchar oled_key = 0;
uchar new_key = 0;
uchar j,vl;

void main()
{
	Init();
	while(1)
	{
		keycan();
	}
}
								
void keycan()
{
	uint keycan_v;
	uchar i = 0,key;
	uchar keyCode;
 	P1 = 0x1f;
	if((P1&0x1f) != 0x1f)
	{
		if((P1&0x1f) != 0x1f)key = P1&0x1f;
		test_v1(key,0x3f);
	}
	else
	{
		keycan_v  = 0x1e;
		for(i=0;i<3;i++)
		{
// 			if(vl >= 20)vl = 0;
			P1 = keycan_v;
			if((P1&0x1f) != keycan_v)
			{
				key = P1&0x1f;
				keyCode = keycan_v;
				j = i;
				vl++;
			}
			else
			{
				key = keycan_v;
				keyCode = keycan_v;
			}
			test_v1(key,keyCode);
			keycan_v = ((keycan_v<<1)|0x01)&0x1f;
		}
		delay(50);
	}
}
/*******************************************************/
void test_v1(uchar key,uchar keycan_v)
{
 uchar databuf,trg,cont;
 uchar trigger_T,continue_T;
	switch(keycan_v)
	{
		case 0x1e:
			if(j == 0)
			{
				if(key == 0x0e||key == 0x16)
					databuf = key ^ 0x1f;
				else
					databuf = key ^ keycan_v;
		  }
			break;
		case 0x1d:
			if(j == 1)
			{
				if(key == 0x0d||key == 0x15)
					databuf = key ^ 0x1f;
				else
					databuf = key ^ keycan_v;
			}
			break;
		case 0x1b:
			if(j == 2)
			{
				if(key == 0x0b||key == 0x13)
					databuf = key ^ 0x1f;
				else
					databuf = key ^ keycan_v;
			}
			break;
		case 0x3f:
			if(key == 0x0f)
				databuf = key ^ 0x1f;
			break;
		default:
// 			databuf = 0;
		  break;
	}
	trg = databuf&(databuf^cont);
	cont = databuf;
	if((trg != 0) && (cont != 0))trigger_T = 1;
	else if((trg == 0) && (cont != 0)&&(vl == 10))continue_T = 1;
	else {trigger_T = 0;continue_T = 0;}
	key_process(key,trigger_T,continue_T);

}
/***************************************************/
void key_process(uchar key,uchar trg,uchar cont)
{
	static uchar flag1,flag2,flag3,flag4,flag5,flag6,flag7;
	
	if((key == 0x0f) && (trg == 1))
	{
		flag7++;
		
		if(flag7 == 1)
			led7 = 0;
		else
			led7 = 1;
		if(flag7 == 2)
				flag7 = 0;
	}
	if(((key == 0x0e) && (trg == 1)) || ((key == 0x0e) && (cont == 1)))
	{
		vl = 0;
		flag1++;
		
		if(flag1 == 1)
			led1 = 0;
		else
			led1 = 1;
		if(flag1 == 2)
			flag1 = 0;
	}
  if(((key == 0x16) && (trg == 1)) || ((key == 0x16) && (cont == 1)))
	{
		vl = 0;
		flag2++;
		
		if(flag2 == 1)
			led2 = 0;
		else
			led2 = 1;
		if(flag2 == 2)
				flag2 = 0;
	}
  if(((key == 0x0d) && (trg == 1)) || ((key == 0x0d) && (cont == 1)))		
	{
		vl = 0;
		flag3++;
		
		if(flag3 == 1)
			led3 = 0;
		else
			led3 = 1;
		if(flag3 == 2)
				flag3 = 0;
	}
  if(((key == 0x15) && (trg == 1)) || ((key == 0x15) && (cont == 1)))
	{
		vl = 0;
		flag4++;
		
		if(flag4 == 1)
			led4 = 0;
		else
			led4 = 1;
		if(flag4 == 2)
				flag4 = 0;
	}
	if(((key == 0x0b) && (trg == 1)) || ((key == 0x0b) && (cont == 1)))
	{
		vl = 0;
		flag5++;

		if(flag5 == 1)
			led5 = 0; 
		else
			led5 = 1;		
		if(flag5 == 2)
				flag5 = 0;
	}
	if(((key == 0x13) && (trg == 1)) || ((key == 0x13) && (cont == 1)))
	{
		vl = 0;
		flag6++;
		
		if(flag6 == 1)
			led6 = 0;
		else
			led6 = 1;
		if(flag6 == 2)
				flag6 = 0;
	}

}
void Init()
{
	key1 = 1;
  key2 = 1;
	key3 = 1;
	key4 = 1;
	key5 = 1;
	
	led1 = 1;
	led2 = 1;
	led3 = 1;
	led3 = 1;
	led5 = 1;
	led6 = 1;
	led7 = 1;
}

void delay(uint Time)
{
	uint x,y;
	for(x=Time;x>0;x--)
		for(y=110;y>0;y--);
}