#include	<REGX51.H>
#define		choncotcao  	1
#define		choncotthap 	0
//1 lan quet tinh toan duoc 0.0175s
//su dung hoan toan mo phong
#define 	counter1s			52  //60 <-> 1.10492079s
#define		off_speed			6   // 4 <-> delta = 0.0702s

unsigned char hextable[] = //Ma quet LED ma trix
{
0x00,0x00,  0x01,0x80,  0x03,0xC0,  0x07,0xE0,
0x0F,0xF0,  0x1F,0xF8,  0x3F,0xFC,  0x7F,0xFE,
0xFF,0xFF,  0xFF,0xFF,  0xFF,0xFF,  0xFF,0xFF, 
0xFF,0xFF,  0xFE,0x7F,  0x7C,0x3E,  0x00,0x00
};

unsigned char ledcount[] =					//So luong LED sang
{
 5,5 , 7,7 , 8,8 , 8,8 , 8,8 , 8,8 , 8,8 , 
 7,7  , 6,6  ,5,5 , 4,4 , 3,3 , 2,2  ,1,1 ,

};

unsigned char hextable_copy[33] ; 	// Backup gia tri Hex

volatile unsigned char xdata cotcao _at_ 0x1000;
volatile unsigned char xdata cotthap _at_ 0x1F00;
volatile unsigned char xdata hangcao _at_ 0x4000;
volatile unsigned char xdata hangthap _at_ 0x9000;

unsigned char 	 	counter_led;			// bien dem so led con lai
unsigned char			led_valuex;				// thay doi HEX de LED tat
unsigned char			delta_led ;				// luong led tat <=> luong b.i.t dich
unsigned char			pter;							// bien vong lap dich b.i.t 

int 					pointer_quet, mode;		//con tro quet HEX, MODE(0-29)
int						cop;									// bien vong lap copy HEX table
int						x,y = 0;							// bien vong lap thoi gian hien thi


void 	quetmatran(unsigned char m);
int 	ledoff(int n);


void delay_ms (int time) {						//Ham Delay ms
	int j, k;
	for(j = 0; j < time; j++) {
		for (k = 0; k <115 ; k++)
		{}
	}
}

void quetmatran(unsigned char m) {	 //Ham chon cot - quet
	
	unsigned char choncot	= 0x01;
	int i;
	for( i = 0; i < 8; i++) {
		if( m == choncotthap) {
			cotthap = choncot;
		}
		else {
			cotcao = choncot;
		}
		
		hangcao = hextable[pointer_quet] ;
		pointer_quet++;
		hangthap = hextable[pointer_quet] ;
		pointer_quet++;
		delay_ms(1);
		
		choncot = choncot * 2;
	}
	
	choncot = 0;
	if( m == choncotthap) {
			cotthap = choncot;
		}
		else {
			cotcao = choncot;
		}
}	

void tatled(){

	 counter_led = ledcount[mode];				//Lay so LED tu` trong bang
	 led_valuex = ledoff(mode);						//Lay HEX thay doi tu` SWITCH
	
	if(mode%2==0) {
	delta_led = ledcount[mode+1] - counter_led;		//So LED con lai
	}
	else {
	delta_led = ledcount[mode-1] - counter_led;		
	}
	
	for(pter = 0; pter < delta_led ; pter++) {
		led_valuex = led_valuex * 2;							// value LED <=> Dich b.i.t
	}
	hextable[29-mode] = hextable[29-mode] & (~led_valuex);	//Doi HEX
	ledcount[mode] = ledcount[mode] - 1;					
	if ( ledcount[mode] == 255 ) {
	
		if(mode%2 == 0) {	
			ledcount[mode] = ledcount[mode+1];	//  5<->5 , 7<->7 
		}
		else {
			ledcount[mode] = ledcount[mode-1];	//	Doi xung, tu backup
		}
		mode = mode + 1;											// Kich MODE
		x = off_speed - 1;																// Bo qua 0.1s khi chuyen MODE
	}
}

	//0x02,0x04,0x01,0x02,0x01,0x01,0x01,
	//0x01,0x01,0x01,0x01,0x01,0x01,0x01,
	//0x02,0x01,0x04,0x01,0x08,0x01,0x10,
	//0x01,0x20,0x01,0x40,0x01,0x80,0x01

int ledoff(int n)	{								//Khong du RAM => SWTICHCASE thay TABLE
	int value_off;
	switch(n) {
		case 0 :   value_off = 0x02;
						 	 break;
		case 1 :   value_off = 0x04;
							 break;
		case 2 :   value_off = 0x01;
							 break;
		case 3 :   value_off = 0x02;
							 break;
		case 4 :   value_off = 0x01;
							 break;
		case 5 :   value_off = 0x01;
							 break;
		case 6 :   value_off = 0x01;
						 	 break;
		case 7 :   value_off = 0x01;
							 break;
		case 8 :   value_off = 0x01;
							 break;
		case 9 :   value_off = 0x01;
							 break;
		case 10 :  value_off = 0x01;
							 break;
		case 11 :  value_off = 0x01;
							 break;
		case 12 :  value_off = 0x01;
							 break;
		case 13 :  value_off = 0x01;
							 break;
		case 14 :  value_off = 0x02;
							 break;
		case 15 :  value_off = 0x01;
							 break;
		case 16 :  value_off = 0x04;
							 break;
		case 17 :  value_off = 0x01;
							 break;
		case 18 :  value_off = 0x08;
							 break;
		case 19 :  value_off = 0x01;
							 break;
		case 20 :  value_off = 0x10;
							 break;
		case 21 :  value_off = 0x01;
							 break;
		case 22 :  value_off = 0x20;
							 break;
		case 23 :  value_off = 0x01;
							 break;
		case 24 :  value_off = 0x40;
							 break;
		case 25 :  value_off = 0x01;
							 break;
		case 26 :  value_off = 0x80;
							 break;
		case 27 :  value_off = 0x01;
							 break;
		default: 	 value_off = 0;
							 break;
	}
	return value_off;
}

void reset (void)	{				//Tat het LED thi Reset

	for(cop = 0 ; cop < 32 ; cop++){
		hextable[cop] = hextable_copy[cop];	//BACKUP
	}	
	
	((void (code *) (void)) 0x0000) ();		//Ve dau ch.trinh
}


//void ngattimer0 (void) interrupt 1
//{
//}

void main () {

	mode = 0;
	for(cop = 0 ; cop < 32 ; cop++) {
		hextable_copy[cop] = hextable[cop];
	}	
	
	while(1) {
	
		pointer_quet = 0;
		quetmatran(choncotthap);
		quetmatran(choncotcao);
		
		y++;
		if(y == counter1s	) {			
			y = counter1s	- 1;	//Neu Y dem du lan thi` truot qua Y
			x++;
			if(x == off_speed) {
				x = 0;
				tatled();
				if (mode == 28) {
					reset();
				}		
			}
		}
	}
}


