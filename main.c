#include "TM4C123.h"                    // Device header

#define LCD_PORT GPIOB 
#define RS 1    /* BIT0 mask */ 
#define RW 2    /* BIT1 mask */ 
#define EN 4    /* BIT2 mask */

void delayMs(int n);
void delayUs(int n);
void LCD_nibble_write(unsigned char data, unsigned char control);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
void LCD_string(const char *buffer);
void LCD_blink(uint32_t  number);
void LCD_msg1(void);
void LCD_msg2(void);
int main(void)
{
    LCD_init();
   for(;;)
    {
        LCD_command(1);       /* clear display */
        LCD_command(0x80);    /* LCD cursor location */

        delayMs(200);
			  LCD_msg1();
			  LCD_msg2();
			
//	      LCD_string("CORTEX-M.COM");
//			   delayUs(1);
//			  LCD_command(0xC0);
//	     // LCD_command(0xC0);          //move to line2
//			  LCD_string("VISIT OUR SITE.");
//			  LCD_blink(7);
//			  LCD_command(0x01);        //clear screen
//			  LCD_string("CORTEX-M");
//			  delayUs(1);
//			  LCD_command(0xC0);
//			  LCD_string("LIKE US ON FB");
//			  LCD_blink(7);
//			  LCD_command(0x01);
			
     //LCD_data('H');
//	     delayUs(20);
//        LCD_data('E');
//     	delayUs(20);
//        LCD_data('L');
//	    delayUs(20);
//        LCD_data('L');
//	    delayMs(20);
//        LCD_data('O');
//        delayMs(500);
    }
}

void LCD_init(void)
{
    SYSCTL->RCGCGPIO |= 0x02;   /* enable clock to GPIOB */ 
    LCD_PORT->DIR = 0xFF;       /* set all PORTB pins as output */
    LCD_PORT->DEN = 0xFF;       /* set all PORTB pins as digital pins */


    LCD_command(0x28);          /* set 4-bit data, 2-line, 5x7 font */
    LCD_command(0x06);          /* move cursor right */
    LCD_command(0x01);          /* clear screen, move cursor to home */
    LCD_command(0x0F);          /* turn on display, cursor blinking */
}

void LCD_nibble_write(unsigned char data, unsigned char control)
{
    data &= 0xF0;       /* clear lower nibble for control */
    control &= 0x0F;    /* clear upper nibble for data */
    LCD_PORT->DATA = data | control;       /* RS = 0, R/W = 0 */
    LCD_PORT->DATA = data | control | EN;  /* pulse E */
    delayUs(0);
    LCD_PORT->DATA = data;
    LCD_PORT->DATA = 0;
}

void LCD_command(unsigned char command)
{
    LCD_nibble_write(command & 0xF0, 0);   /* upper nibble first */
    LCD_nibble_write(command << 4, 0);     /* then lower nibble */
    
    if (command < 4)
        delayMs(2);         /* commands 1 and 2 need up to 1.64ms */
    else
        delayUs(40);        /* all others 40 us */
}

void LCD_data(unsigned char data)
{
    LCD_nibble_write(data & 0xF0, RS);    /* upper nibble first */
    LCD_nibble_write(data << 4, RS);      /* then lower nibble  */
    
    delayUs(40);
}

void LCD_string(const char  *buffer){
	while(*buffer)
	{
		delayMs(1);
		LCD_data(*buffer);
		
		buffer++;
		
	}
}
void LCD_msg1(void)
{
	 LCD_string("CORTEX-M.COM");
			   delayUs(1);
			  LCD_command(0xC0);
	               //move to line2
			  LCD_string("VISIT OUR SITE.");
			  LCD_blink(7);
			  LCD_command(0x01);        //clear screen
}
void LCD_msg2(void)
{
	LCD_string("CORTEX-M");
			  delayUs(1);
			  LCD_command(0xC0);
			  LCD_string("LIKE US ON FB");
			  LCD_blink(7);
			  LCD_command(0x01);
}
void LCD_blink(uint32_t number)
	
{
	int n;
	for(n=0;n<number;n++){
	LCD_command(0x0C);
	delayMs(1000);
	LCD_command(0x08);
	delayMs(1000);
	}
}
/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3180; j++)
            {}  /* do nothing for 1 ms */
}
/* delay n microseconds (16 MHz CPU clock) */
void delayUs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3; j++)
            {}  /* do nothing for 1 us */
}

