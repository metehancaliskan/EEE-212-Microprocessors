#include <MKL25Z4.H>
#include <stdio.h>
#include <math.h>


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
void timer_1(uint32_t F1,uint32_t D1);
void timer_2(uint32_t F2,uint32_t D2);

int main(void)
{
		uint32_t key;
		char arrayf1[3];
		char arrayf2[3];
		char arrayd1[2];
		char arrayd2[2];
		uint16_t F1=0;
    uint16_t F2=0;
    uint16_t D1=0;
    uint16_t D2=0;
		uint16_t c=0;	
		char lookup[]= {'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
    LCD_init();
		keypad_init();
    while(keypad_getkey() == 0)
    { 

    }
    LCD_command(0x01);
		while(1)
		{
		Delay(300000);	
		key=keypad_getkey();
		if(key != 0)
		{	
			if(c==0)
			{
				LCD_data('F');
				LCD_data('1');
				LCD_data(':');
			}
			if(c<3)
			    {
				    LCD_data(lookup[key-1]);
						arrayf1[c]=lookup[key-1]-0x30;
						c++;
						Delay(300000);
				    key =0;
					}
			  if(c==3)
			{
				LCD_data('H');
        LCD_data('z');
        LCD_data(' ');
				LCD_data('D');
				LCD_data('1');
				LCD_data(':');
				LCD_data('%');
				c++;
				}
			if(c>3 && c<6&& key!=0)
			    {
						LCD_data(lookup[key-1]);
						arrayd1[c-4]=lookup[key-1]-0x30;
						c++;
						Delay(300000);
				    key =0;
						}
					if(c==6)
			{
				LCD_command(0xC0);
				LCD_data('F');
				LCD_data('2');
				LCD_data(':');
				c++;
				}
			if(c>6 && c<10 && key!=0)
			    {
						LCD_data(lookup[key-1]);
						arrayf2[c-7]=lookup[key-1]-0x30;
						c++;
						Delay(300000);
				    key =0;
						}
			     if(c==10)
			{
				LCD_data('H');
        LCD_data('z');
        LCD_data(' ');
				LCD_data('D');
				LCD_data('2');
				LCD_data(':');
				LCD_data('%');
				c++;
				}
			if(c>10&&c<13&& key!=0)
			    { 
						LCD_data(lookup[key-1]);
						arrayd2[c-11]=lookup[key-1]-0x30;
						c++;	
						Delay(300000);
				    key =0;
						}
					D1=arrayd1[1]+arrayd1[0]*10;
					F1=arrayf1[2]+arrayf1[1]*10+arrayf1[0]*100;
					D2=arrayd2[1]+arrayd2[0]*10;
					F2=arrayf2[2]+arrayf2[1]*10+arrayf2[0]*100;
					
				if (lookup[key-1]=='*')
           {
              arrayd1[0]=1+arrayd1[0];
							arrayd2[0]=1+arrayd2[0];
							Delay(300000);
					}
				if (lookup[key-1]=='#')
           {
							arrayf1[0]=2*arrayf1[0];
							arrayf1[1]=2*arrayf1[1];
							arrayf1[2]=2*arrayf1[2];
							arrayf2[0]=2*arrayf2[0];
							arrayf2[1]=2*arrayf2[1];
							arrayf2[2]=2*arrayf2[2];
							Delay(300000);
						 
                    }  			 
			timer_1(F1,D1);
			timer_2(F2,D2);		
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
void timer_1(uint32_t F1,uint32_t D1)
{
	  uint32_t M1= (10488000/(128*F1)); 
    uint32_t du1= ((D1*M1)/100);
    SIM->SCGC5 |= (1UL << 13); 
    PORTE->PCR[21] = 0x0300; 
    SIM->SCGC6 |= (1UL << 25); 
    SIM->SOPT2 |= 0x01000000; 
    TPM1->SC = 0; /* disable timer */
    TPM1->CONTROLS[1].CnSC = 0x20 | 0x08; 
    TPM1->MOD = M1; 
    TPM1->CONTROLS[1].CnV = du1;
    TPM1->SC = 0x0F | 0x20;
}
void timer_2(uint32_t F2,uint32_t D2)
{
		uint32_t M2= (10488000/(128*F2));
    uint32_t du2= ((D2*M2)/100);
    SIM->SCGC5 |= 0x2000; 
    PORTE->PCR[31] = 0x0300; 
    SIM->SCGC6 |= 0X01000000; 
    SIM->SOPT2 |= 0x01000000; 
    TPM0->SC = 0; /* disable timer */
    TPM0->CONTROLS[4].CnSC = 0x20 | 0x08; 
    TPM0->MOD = M2;
    TPM0->CONTROLS[4].CnV = du2; 
    TPM0->SC = 0x0F | 0x20;	
}
