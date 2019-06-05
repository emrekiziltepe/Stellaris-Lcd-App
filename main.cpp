//150201181 - Emre Kiziltepe

#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include <stdint.h>
#include "inc/lm4f120h5qr.h";

//Lcd fonksiyonlarýnda bu siteden yararlandým: http://www.mcu-turkey.com/stellaris-launchpad-16x2-lcd/

void EkranOlustur() {

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xFF);

	SysCtlDelay(50000);

	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0,  0x00 );

	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,  0x30 );
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
	SysCtlDelay(10);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);

	SysCtlDelay(50000);

	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,  0x30 );
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
	SysCtlDelay(10);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);

	SysCtlDelay(50000);

	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,  0x30 );
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
	SysCtlDelay(10);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);

	SysCtlDelay(50000);

	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,  0x20 );
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
	SysCtlDelay(10);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);

	SysCtlDelay(50000);

	EkranKomut(0x28);
	EkranKomut(0xC0);
	EkranKomut(0x06);
	EkranKomut(0x80);
	EkranKomut(0x28);
	EkranKomut(0x0f);
	EkranTemizle();

}

void EkranKomut(unsigned char c) {

	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, (c & 0xf0) );
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x00);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
	SysCtlDelay(50000);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);

	SysCtlDelay(50000);

	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, (c & 0x0f) << 4 );
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x00);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
	SysCtlDelay(10);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);

	SysCtlDelay(50000);

}

void KonumGit(char satir, char sutun){

	if(satir==1)
		EkranKomut(0x80+((sutun-1)%16));
	else
		EkranKomut(0xC0+((sutun-1)%16));
}

void KarakterEkle(unsigned char krktr) {

	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, (krktr & 0xf0) );
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x01);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
	SysCtlDelay(10);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);

	SysCtlDelay(50000);

	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, (krktr & 0x0f) << 4 );
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x01);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
	SysCtlDelay(10);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);

	SysCtlDelay(50000);

}

void StringEkle( char* kelime){

	while(*kelime)
		KarakterEkle(*kelime++);
}

void EkranTemizle(void){
	EkranKomut(0x01);
	SysCtlDelay(10);
}


void init_port_B() {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTB_DIR_R |= 0b00000100;
	GPIO_PORTB_AFSEL_R &= ~0b00000100;
	GPIO_PORTB_DEN_R |= 0b00000100;
}

void init_port_D() {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTD_DIR_R |= 0b01001100;
	GPIO_PORTD_AFSEL_R &= ~0b01001100;
	GPIO_PORTD_DEN_R |= 0b01001100;
}


int main(void) {

	init_port_B();
	init_port_D();


	char uni[16] = "Kocaeli Uni";
	char ad[16] = "Emre Kiziltepe";

	volatile unsigned long delay;

	SysCtlClockSet(
			SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ
			| SYSCTL_OSC_MAIN);

	while (1) {

		int durum = rand()%4+1;

		if(durum==1){
			GPIO_PORTD_DATA_R |= 0b00000100;
			EkranOlustur();
			KonumGit(1,1);
			StringEkle(uni);

			for(delay=0;delay<10000000;delay++)
				/*bos*/ ;



			KonumGit(2,1);
			StringEkle(ad);

			for(delay=0;delay<15000000;delay++)
				/* bos */ ;


			EkranTemizle();

			GPIO_PORTD_DATA_R &= ~0b00000100;

		}


		if(durum==2){
			GPIO_PORTD_DATA_R |= 0b00001000;
			EkranOlustur();
			KonumGit(2,1);
			StringEkle(ad);

			for(delay=0;delay<10000000;delay++)
				/* bos */ ;

			KonumGit(1,1);
			StringEkle(uni);

			for(delay=0;delay<15000000;delay++)
				/* bos */ ;

			EkranTemizle();
			GPIO_PORTD_DATA_R &= ~0b01000;

		}

		if(durum==3){
			GPIO_PORTD_DATA_R |= 0b01000000;
			EkranOlustur();
			for(int i=1;i<=11;i++){
				int deneme=1;
				KonumGit(1,i);
				for(int j=11-i;j<11;j++){
					KonumGit(1,deneme++);
					StringEkle(uni+j);
					if(i<6){
						for(delay=0;delay<320000;delay++)
							/*bos*/ ;
					}

				}


			}

			for(delay=0;delay<10000000;delay++)
				/*bos*/ ;

			for(int i=1;i<=14;i++){
				int deneme=1;
				KonumGit(2,i);
				for(int j=14-i;j<14;j++){
					KonumGit(2,deneme++);
					StringEkle(ad+j);
					if(i<8){
						for(delay=0;delay<320000;delay++)
							/*bos*/ ;
					}
				}
			}


			for(delay=0;delay<15000000;delay++)
				/* bos */ ;

			EkranTemizle();
			GPIO_PORTD_DATA_R &= ~0b01000000;


		}

		if(durum==4){
			GPIO_PORTB_DATA_R |= 0b00000100;
			EkranOlustur();
			for(int i=16;i>0;i--){
				KonumGit(1,i);
				StringEkle(uni);
				for(delay=0;delay<320000;delay++)
					/*bos*/ ;
				if(i==1){
					break;
				}
				EkranTemizle();

			}

			for(delay=0;delay<10000000;delay++)
								/*bos*/ ;

			for(int i=16;i>0;i--){
				KonumGit(1,1);
				StringEkle(uni);

				KonumGit(2,i);
				StringEkle(ad);
				for(delay=0;delay<320000;delay++)
					/*bos*/ ;
				if(i==1){
					break;
				}
				EkranTemizle();
			}

			for(delay=0;delay<15000000;delay++)
				/* bos */ ;

			EkranTemizle();
			GPIO_PORTB_DATA_R &= ~0b00000100;


		}

	}

}
