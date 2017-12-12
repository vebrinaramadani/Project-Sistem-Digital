/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.3 Standard
Automatic Program Generator
� Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 4/17/2016
Author  : regina
Company : rumah
Comments: 


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 16.001000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

#include <mega32.h>
#include <stdio.h>
#include <delay.h>

// Alphanumeric LCD Module functions
#include <alcd.h>

unsigned int jarak;
unsigned char us1,tam[33];
float data;

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Reinitialize Timer 0 value
TCNT0=0x98;
// Place your code here
jarak++;
}

#define ADC_VREF_TYPE 0x00

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}


void ultra_sonic1(void)
{
 TCNT0=0x98;
 jarak=0;
 PORTD.0 = 1;
 delay_us(10);
 PORTD.0 = 0;

 while (PIND.1==0) {;};

 TCCR0=0x02;

 while(PIND.1==1 && jarak!=240)    {;};
 TCCR0=0x00;
 us1 = jarak;
 delay_ms(5); 

 if (jarak < 10) {PORTD.2 = 1;}
 else if (jarak < 51) {PORTD.2 = 1; delay_ms(jarak*2);PORTD.2 = 0;}
 else PORTD.2 = 0;
}


void tegangan()
{
data=(float)read_adc(0)*55/1024;
}

// Declare your global variables here

void main(void)
{
bit a=0;
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
PORTB=0x80;
DDRB=0x80;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
PORTC=0x80;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
PORTD=0x00;
DDRD=0x05;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 16000,000 kHz
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x01;
TCNT0=0x98;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x01;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 1000,000 kHz
// ADC Voltage Reference: AREF pin
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x84;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

// Alphanumeric LCD initialization
// Connections specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTB Bit 0
// RD - PORTB Bit 1
// EN - PORTB Bit 2
// D4 - PORTB Bit 3
// D5 - PORTB Bit 4
// D6 - PORTB Bit 5
// D7 - PORTB Bit 6
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here
     
      if(PINC.7==0){a++;if(a>1){a=0;}}
     
      if (a==0)
        {
        ultra_sonic1();
        lcd_gotoxy(0,0);
        lcd_putsf("Alarm Parkir    ");
        lcd_gotoxy(0,1);
        sprintf(tam,"Jarak = %d cm ",jarak);
        lcd_puts(tam);
        }
     
      else
        {
        tegangan();
        lcd_gotoxy(0,0);
        lcd_putsf("Tegangan Supply  ");
        lcd_gotoxy(0,1);
        sprintf(tam,"V = %0.1f Volt ",data);
        lcd_puts(tam);
        }
       
      delay_ms(100);
      }
}

