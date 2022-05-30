/* module3.c: Based on Mazidi etal book. 
 * Initialize and display "EEE212" on the first row 
 * Display the number a on the second raw as decimal and hexadecimal 
 * using 8-bit data mode.
 * Data pins use Port D, control pins use Port A.
 * Then wait until a key pressed and display the typed keys on the f
 * first row after clearing screen
 * The LCD�s data pins are connected to PORTD of the microcontroller.
 * The LCD�s RS pin is connected to Pin 2 of PORTA of the microcontroller.
 * The LCD�s R/W pin is connected to Pin 4 of PORTA of the microcontroller.
 * The LCD�s E pin is connected to Pin 5 of PORTA of the microcontroller.
 * Polling of the busy bit of the LCD status bit is used for timing.
 * Raws of the keypad are connected to PORTC 0-3, Columns are connected to PORTC4-7.
  * pull-ups are enabled
 */

#include <MKL25Z4.H>
#include <stdio.h>


#define RS 0x04     /* PTA2 mask */ 
#define RW 0x10     /* PTA4 mask */ 
#define EN 0x20     /* PTA5 mask */

void Delay(volatile unsigned int time_del);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
void LCD_ready(void);
void keypad_init(void);
uint32_t keypad_getkey(void);

int main(void)
{
  uint32_t a=123456;
	uint32_t key;
	uint8_t equ=0;
  char opone[6]={0,0,0,0,0,0};
	char optwo[6]={0,0,0,0,0,0};
	uint32_t p=0x80;
	int n=0;
	int64_t opo;
	int64_t opt;
	uint8_t s=0;
	int64_t res;
	char result[20];
	uint8_t i=5;
	uint8_t j=5;
	char temp, temp2;
	int k,m,kk,mm;
	char buffer[20];
	char lookup[]= {'1','2','3','+','4','5','6','-','7','8','9','x',' ','0','=','/'};
  int l,length_hex, length_dec;
	LCD_init();
	LCD_command(0x80);      /* set cursor at first line */
	LCD_data('B');          /* write the word on LCD */
	LCD_data('L');
	LCD_data('O');
	LCD_data('C');
	LCD_data('K');
	LCD_data('C');
	LCD_data('H');
	LCD_data('A');
	LCD_data('I');
	LCD_data('N');			
	keypad_init();
    while(keypad_getkey() == 0)
    {
		}
    LCD_command(0x01);
		while(1)
		{
		int c=1;
		while(c!=0)
			{
			c=keypad_getkey();
			}
		Delay(300000);	
		key=keypad_getkey();
		if(key != 0)
		{	
			if (s==0)
			{
			switch(lookup[key-1])
			{
				case '1':
				LCD_data(lookup[key-1]);
				opone[i]= 1;
				++p;
				++n;
				--i;
				Delay(300000);
				key =0;
				break;
				case '2':
				LCD_data(lookup[key-1]);
				opone[i]= 2;
				++p;
				++n;				
				--i;
				Delay(300000);
				key =0;
				break;
				case '3':
				LCD_data(lookup[key-1]);
				opone[i]= 3;
				++p;
				++n;
				--i;
				Delay(300000);
				key =0;
				break;
				case '+':
				LCD_data(lookup[key-1]);
				++p;
				++n;
				s='+';
				Delay(300000);
				key =0;
				break;
				case '4':
				LCD_data(lookup[key-1]);
				opone[i]= 4;
				++p;
				++n;
				--i;
				Delay(300000);
				key =0;
				break;
				case '5':
				LCD_data(lookup[key-1]);
				opone[i]= 5;
				++p;
				++n;
				--i;
				Delay(300000);
				key =0;
				break;
				case '6':
				LCD_data(lookup[key-1]);
				opone[i]= 6;
				++p;
				++n;
				--i;
				Delay(300000);
				key =0;
				break;
				case '-':
				LCD_data(lookup[key-1]);
				++p;
				++n;
				s='-';
				Delay(300000);
				key =0;
				break;
				case '7':
				LCD_data(lookup[key-1]);
				opone[i]= 7;
				++p;
				++n;
				--i;
				Delay(300000);
				key =0;
				break;
				case '8':
				LCD_data(lookup[key-1]);
				opone[i]= 8;
				++p;
				++n;
				--i;
				Delay(300000);
				key =0;
				break;	
				case '9':
				LCD_data(lookup[key-1]);
				opone[i]= 9;
				++p;
				++n;
				--i;
				Delay(300000);
				key =0;
				break;				
				case 'x':
				LCD_data(lookup[key-1]);
				++p;
				++n;
				s='x';
				Delay(300000);
				key =0;
				break;				
				case ' ':
				opone[n-1]= '\0';
				LCD_command(p-1);
				LCD_data(' ');
				LCD_command(p-1);
				p-=1;
				i++;
				opone[i]=0;
				Delay(300000);
				key =0;
				break;				
				case '0':
				LCD_data(lookup[key-1]);
				opone[i]= 0;
				++p;
				++n;
				--i;
				Delay(300000);
				key =0;
				break;
				case '=':
				Delay(300000);
				key =0;
				break;				
				case '/':
				LCD_data(lookup[key-1]);
				++p;
				++n;
				s='/';
				Delay(300000);
				key =0;
				break;				
					
			}
		}
		else if (equ==0 && s!=0)
		{
			switch(lookup[key-1])
			{
				case '1':
				LCD_data(lookup[key-1]);
				optwo[j]= 1;
				++p;
				++n;
				--j;
				Delay(300000);
				key =0;
				break;
				case '2':
				LCD_data(lookup[key-1]);
				optwo[j]= 2;
				++p;
				++n;
				--j;
				Delay(300000);
				key =0;
				break;
				case '3':
				LCD_data(lookup[key-1]);
				optwo[j]= 3;
				++p;
				++n;
				--j;
				Delay(300000);
				key =0;
				break;
				case '+':
				Delay(300000);
				key =0;
				break;
				case '4':
				LCD_data(lookup[key-1]);
				optwo[j]= 4;
				++p;
				++n;
				--j;
				Delay(300000);
				key =0;
				break;
				case '5':
				LCD_data(lookup[key-1]);
				optwo[j]= 5;
				++p;
				++n;
				--j;
				Delay(300000);
				key =0;
				break;
				case '6':
				LCD_data(lookup[key-1]);
				optwo[j]= 6;
				++p;
				++n;
				--j;
				Delay(300000);
				key =0;
				break;
				case '-':
				Delay(300000);
				key =0;
				break;				
				case '7':
				LCD_data(lookup[key-1]);
				optwo[j]= 7;
				++p;
				++n;
				--j;
				Delay(300000);
				key =0;
				break;
				case '8':
				LCD_data(lookup[key-1]);
				optwo[j]= 8;
				++p;
				++n;
				--j;
				Delay(300000);
				key =0;
				break;	
				case '9':
				LCD_data(lookup[key-1]);
				optwo[j]= 9;
				++p;
				++n;
				--j;
				Delay(300000);
				key =0;
				break;	
				case 'x':
				Delay(300000);
				key =0;
				break;	
				case ' ':
				if(optwo[5]==0)	{
				LCD_command(p-1);
				LCD_data(' ');
				LCD_command(p-1);
				p-=1;
				s=0;
				}
				else {
				LCD_command(p-1);
				LCD_data(' ');
				LCD_command(p-1);
				p-=1;
				j++;
				optwo[j]=0;
				}
				Delay(300000);
				key =0;
				break;
				case '0':
				LCD_data(lookup[key-1]);
				optwo[j]= 0;
				++p;
				++n;
				--j;
				Delay(300000);
				key =0;
				break;
				case '=':
				LCD_data(lookup[key-1]);
				equ=1;
				for (kk=0;kk<i+1;kk++)
					{
					temp=opone[0];
					for(k=0;k<6;k++)
						{
						opone[k] = opone[k+1];  
						}
					opone[5] = temp;  
					}
				if(opone[5]!=0)
				{
					temp=opone[0];
					for(k=0;k<6;k++)
						{
						opone[k] = opone[k+1];  
						}
					opone[5] = temp;
					temp=opone[0];
					for(k=0;k<6;k++)
						{
						opone[k] = opone[k+1];  
						}
					opone[5] = temp;
				}
				for (mm=0;mm<j+1;mm++)
					{
					temp2=optwo[0];
					for(m=0;m<6;m++)
						{
						optwo[m] = optwo[m+1];  
						}
					optwo[5] = temp2;  
					}
					if(optwo[5]!=0)
				{
					temp=optwo[0];
					for(m=0;m<6;m++)
						{
						optwo[m] = optwo[m+1];  
						}
					optwo[5] = temp;
					temp=optwo[0];
					for(m=0;m<6;m++)
						{
						optwo[m] = optwo[m+1];  
						}
					optwo[5] = temp;
				}
				opo = opone[0]+10*opone[1]+100*opone[2]+1000*opone[3]+10000*opone[4]+100000*opone[5];
				opt = optwo[0]+10*optwo[1]+100*optwo[2]+1000*optwo[3]+10000*optwo[4]+100000*optwo[5];
				LCD_command(0xC0);
				switch(s)
				{
					case '+':
					res = opo + opt;
					length_dec = sprintf(result,"%d",res);
					for(l=0;l<length_dec;++l)
					{
					LCD_data(result[l]);
					}
					break;
					case '-':
					res = opo - opt;
					length_dec = sprintf(result,"%d",res);
					for(l=0;l<length_dec;++l)
					{
					LCD_data(result[l]);
					}
					break;
					case 'x':
					res = opo * opt;
					length_dec = sprintf(result,"%lld",res);
					for(l=0;l<length_dec;++l)
					{
					LCD_data(result[l]);
					}
					break;
					case '/':
					res = opo / opt;
					length_dec = sprintf(result,"%d",res);
					for(l=0;l<length_dec;++l)
					{
					LCD_data(result[l]);
					}
					break;
				}
				Delay(300000);
				key =0;
				break;
			}
		}	
		}
	}
}

void LCD_init(void)
{
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */ 
    PORTD->PCR[0] = 0x100;      /* make PTD0 pin as GPIO */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PORTD->PCR[2] = 0x100;      /* make PTD2 pin as GPIO */
    PORTD->PCR[3] = 0x100;      /* make PTD3 pin as GPIO */
    PORTD->PCR[4] = 0x100;      /* make PTD4 pin as GPIO */
    PORTD->PCR[5] = 0x100;      /* make PTD5 pin as GPIO */
    PORTD->PCR[6] = 0x100;      /* make PTD6 pin as GPIO */
    PORTD->PCR[7] = 0x100;      /* make PTD7 pin as GPIO */
    PTD->PDDR = 0xFF;           /* make PTD7-0 as output pins */
    
    SIM->SCGC5 |= 0x0200;       /* enable clock to Port A */ 
    PORTA->PCR[2] = 0x100;      /* make PTA2 pin as GPIO */
    PORTA->PCR[4] = 0x100;      /* make PTA4 pin as GPIO */
    PORTA->PCR[5] = 0x100;      /* make PTA5 pin as GPIO */
    PTA->PDDR |= 0x34;          /* make PTA5, 4, 2 as output pins */
    
    LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x01);      /* clear screen, move cursor to home */
    LCD_command(0x0F);      /* turn on display, cursor blinking */
}

/* This function waits until LCD controller is ready to
 * accept a new command/data before returns.
 */
void LCD_ready(void)
{
    uint32_t status;
    
    PTD->PDDR = 0x00;          /* PortD input */
    PTA->PCOR = RS;         /* RS = 0 for status */
    PTA->PSOR = RW;         /* R/W = 1, LCD output */
    
    do {    /* stay in the loop until it is not busy */
			  PTA->PCOR = EN;
			  Delay(500);
        PTA->PSOR = EN;     /* raise E */
        Delay(500);
        status = PTD->PDIR; /* read status register */
        PTA->PCOR = EN;
        Delay(500);			/* clear E */
    } while (status & 0x80UL);    /* check busy bit */
    
    PTA->PCOR = RW;         /* R/W = 0, LCD input */
    PTD->PDDR = 0xFF;       /* PortD output */
}

void LCD_command(unsigned char command)
{
    LCD_ready();			/* wait until LCD is ready */
    PTA->PCOR = RS | RW;    /* RS = 0, R/W = 0 */
    PTD->PDOR = command;
    PTA->PSOR = EN;         /* pulse E */
    Delay(500);
    PTA->PCOR = EN;
}

void LCD_data(unsigned char data)
{
    LCD_ready();			/* wait until LCD is ready */
    PTA->PSOR = RS;         /* RS = 1, R/W = 0 */
    PTA->PCOR = RW;
    PTD->PDOR = data;
    PTA->PSOR = EN;         /* pulse E */
    Delay(500);
    PTA->PCOR = EN;
}

/* Delay n milliseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */

/* delay n microseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */


void Delay(volatile unsigned int time_del) {
  while (time_del--) 
		{
  }
}


void keypad_init(void)
{
    SIM->SCGC5 |= 0x0800;       /* enable clock to Port C */ 
    PORTC->PCR[0] = 0x103;      /* make PTC0 pin as GPIO and enable pullup*/
    PORTC->PCR[1] = 0x103;      /* make PTC1 pin as GPIO and enable pullup*/
    PORTC->PCR[2] = 0x103;      /* make PTC2 pin as GPIO and enable pullup*/
    PORTC->PCR[3] = 0x103;      /* make PTC3 pin as GPIO and enable pullup*/
    PORTC->PCR[4] = 0x103;      /* make PTC4 pin as GPIO and enable pullup*/
    PORTC->PCR[5] = 0x103;      /* make PTC5 pin as GPIO and enable pullup*/
    PORTC->PCR[6] = 0x103;      /* make PTC6 pin as GPIO and enable pullup*/
    PORTC->PCR[7] = 0x103;      /* make PTC7 pin as GPIO and enable pullup*/
    PTC->PDDR = 0x00;         /* make PTC7-0 as input pins */
}




uint32_t keypad_getkey(void)
{
    uint32_t row, col;
    const char row_select[] = {0x01, 0x02, 0x04, 0x08}; /* one row is active */

    /* check to see any key pressed */
    PTC->PDDR |= 0x0F;          /* rows output */
    PTC->PCOR = 0x0F;               /* ground rows */
    Delay(500);                 /* wait for signal return */
    col =  PTC->PDIR & 0xF0UL;     /* read all columns */
    PTC->PDDR = 0;              /*  rows input */
    if (col == 0xF0UL)
        return 0;               /* no key pressed */

    /* If a key is pressed, it gets here to find out which key.
     * It activates one row at a time and read the input to see
     * which column is active. */
    for (row = 0; row < 4; row++)
		
    {
        PTC->PDDR = 0;                  /* disable all rows */
        PTC->PDDR |= row_select[row];   /* enable one row */
        PTC->PCOR = row_select[row];    /* drive the active row low */
        Delay(500);                     /* wait for signal to settle */
        col = PTC->PDIR & 0xF0UL;         /* read all columns */
        if (col != 0xF0UL) break;         /* if one of the input is low, some key is pressed. */
    }
    PTC->PDDR = 0;                      /* disable all rows */
    if (row == 4) 
        return 0;                       /* if we get here, no key is pressed */
 
    /* gets here when one of the rows has key pressed, check which column it is */
    if (col == 0xE0UL) return row * 4 + 1;    /* key in column 0 */
    if (col == 0xD0UL) return row * 4 + 2;    /* key in column 1 */
    if (col == 0xB0UL) return row * 4 + 3;    /* key in column 2 */
    if (col == 0x70UL) return row * 4 + 4;    /* key in column 3 */

    return 0;   /* just to be safe */
}