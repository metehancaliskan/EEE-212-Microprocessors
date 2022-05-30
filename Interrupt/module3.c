#include <MKL25Z4.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include "switches.h"
#include "gpio_defs.h"
void DAC0_init(void);
void ADC0_init(void);
void init_switch(void);
void PORTD_IRQHandler(void);
void Delay(volatile unsigned int time_del);
volatile unsigned int count = 0;
#define squarel 174
#define triangularl 141
#define sinel 150
int squareWave[squarel];
int sineWave[sinel];
int triangleWave[triangularl];
float rad;
const float pi = 3.14;

int main (void) 
{
		init_switch();
		PORTD_IRQHandler();
		short int result;
		ADC0_init(); /* Configure ADC0 */
	while (1) {
		ADC0->SC1[0] = 0; /* start conversion on channel 0 */
		while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
		result = ADC0->R[0]; /* read conversion result and clear COCO flag */
		int i;
		int l;
	if (count%3==0)
	{
		rad = ((2 * pi) / sinel);
        for (l = 0; l < sinel; l++) 
    {    
		sineWave[l] = 2047 * (sinf(rad * l) + 1);
    }
		DAC0_init(); /* Configure DAC0 */
		while (1) {
			if(count%3!=0) {
			for (i = 0; i < sinel; i++) {
				/* write value to DAC0 */
				ADC0->SC1[0] = 0; /* start conversion on channel 0 */
				while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
				result = ADC0->R[0]; /* read conversion result and clear COCO flag */
				DAC0->DAT[0].DATL = result*sineWave[i]/3724 & 0xff; /* write low byte */
				DAC0->DAT[0].DATH = (result*sineWave[i]/3724 >> 8) & 0x0f;/* write high byte */
			}
		}
				else 
				{
					break;
				}
			}
		}
	Delay(10000);

	int j;
	int m;
	if (count%3==1)
	{
		for(m=0; m<squarel; m++)
			{
			if(m<87)
			{
			squareWave[m] = 0;
			}
			else
			{
			squareWave[m]=1;
			}
			}
		DAC0_init(); /* Configure DAC0 */
		while (1) {
			if (count%3==1){
			for (j = 0; j < squarel; j++) {
				ADC0->SC1[0] = 0; /* start conversion on channel 0 */
				while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
				result = ADC0->R[0]; /* read conversion result and clear COCO flag */
				/* write value to DAC0 */
				DAC0->DAT[0].DATL = result*squareWave[j] & 0xff; /* write low byte */
				DAC0->DAT[0].DATH = (result*squareWave[j] >> 8) & 0x0f;/* write high byte */
				Delay(1);
			}
		}
				else
				{
					break;
				}
			}
		}
		Delay(1000);

	int k;
	int n;
	if (count%3==2)
	{
		for(n=0;n<triangularl;n++)
		{
		triangleWave[n]=2*n;
		}		
		DAC0_init(); 
		while (1) {
			if (count%3==2){
			for (k = 0; k < triangularl; k++) {
				/* write value to DAC0 */
				ADC0->SC1[0] = 0; /* start conversion on channel 0 */
				while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
				result = ADC0->R[0]; /* read conversion result and clear COCO flag */
				DAC0->DAT[0].DATL = result*triangleWave[k]/(2*triangularl) & 0xff; /* write low byte */
				DAC0->DAT[0].DATH = (result*triangleWave[k]/(2*triangularl) >> 8) & 0x0f;/* write high byte */
				Delay(1); /* delay 1ms */
			}
		}
				else
				{
					break;
				}
			}
		}
		Delay(1000);
	}
}
	

void DAC0_init(void) 
{
	SIM->SCGC6 |= 0x80000000; /* clock to DAC module */
	DAC0->C1 = 0; /* disable the use of buffer */
	DAC0->C0 = 0x80 | 0x20; /* enable DAC and use software trigger */
}

void Delay(volatile unsigned int time_del) {
  while (time_del--) 
		{
  }
}
	
void ADC0_init(void)
{
	SIM->SCGC5 |= 0x2000; /* clock to PORTE */
	PORTE->PCR[20] = 0; /* PTE20 analog input */
	SIM->SCGC6 |= 0x8000000; /* clock to ADC0 */
	ADC0->SC2 &= ~0x40; /* software trigger */
	/* clock div by 4, long sample time, single ended 12 bit, bus clock */
	ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00;
}

void init_switch(void) {
	SIM->SCGC5 |=  SIM_SCGC5_PORTD_MASK; /* enable clock for port D */

	/* Select GPIO and enable pull-up resistors and interrupts 
		on falling edges for pins connected to switches */
	
	/* Set port D switch bit to inputs */
	PTD->PDDR &= ~(1UL << (6));
		PORTD->PCR[SW_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);

	/* Enable Interrupts */
	NVIC_SetPriority(PORTD_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTD_IRQn); 
	NVIC_EnableIRQ(PORTD_IRQn);
}

void PORTD_IRQHandler(void) {  
	if (count==2){
	count=0;
	}
		else {
		count++;
		}
		Delay(10);

	PORTD->ISFR = 0xffffffff;
}
