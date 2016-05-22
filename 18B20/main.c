#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"


__IO uint32_t delay_count=0;
GPIO_InitTypeDef GPIO_Init_LED;
uint8_t read_bit=0;
uint16_t DS_temp=0;
uint16_t Th=0;
uint16_t Tl=0;
uint16_t Config=0;
uint16_t Rswd_1=0;
uint16_t Rswd_2=0;
uint16_t Rswd_3=0;
uint16_t DS_CRC=0;

uint8_t DS_temp_1=0;


uint8_t  bit_0=0;
uint8_t  bit_1=0;
uint8_t  bit_2=0;
uint8_t  bit_3=0;
uint8_t  bit_4=0;
uint8_t  bit_5=0;
uint8_t  bit_6=0;
uint8_t  bit_7=0;
uint8_t  bit_8=0;
uint8_t  bit_9=0;
uint8_t  bit_10=0;
uint8_t  bit_11=0;
uint8_t  bit_12=0;
uint8_t  bit_13=0;
uint8_t  bit_14=0;
uint8_t  bit_15=0;



void SysTick_Handler (void)  //вызывается каждую 1 мкс
{
	if(delay_count>0)
	{
		delay_count--;
	}
}


void delay_ms(uint32_t delay_temp)
{
	delay_count=delay_temp;
	while(delay_count){}
}

void DS18B20_Reset (void)
{
	GPIO_Init_LED.GPIO_Mode =  GPIO_Mode_Out_PP;
	    	GPIO_Init(GPIOB, &GPIO_Init_LED);
	    	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	    	delay_ms(500);
	    	GPIO_Init_LED.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
	    	GPIO_Init(GPIOB, &GPIO_Init_LED);
}

void DS18B20_0 (void)
{
	delay_ms(2);
	GPIO_Init_LED.GPIO_Mode =  GPIO_Mode_Out_PP;
	    	GPIO_Init(GPIOB, &GPIO_Init_LED);
	    	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	    	delay_ms(70);
	    	GPIO_Init_LED.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
	    	GPIO_Init(GPIOB, &GPIO_Init_LED);
}

void DS18B20_1 (void)
{
	delay_ms(2);
	GPIO_Init_LED.GPIO_Mode =  GPIO_Mode_Out_PP;
	    	GPIO_Init(GPIOB, &GPIO_Init_LED);
	    	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	    	delay_ms(10);
	    	GPIO_Init_LED.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
	    	GPIO_Init(GPIOB, &GPIO_Init_LED);
	    	delay_ms(60);
}


void DS18B20_read (void)
{
	delay_ms(2);
	GPIO_Init_LED.GPIO_Mode =  GPIO_Mode_Out_PP;
	    	GPIO_Init(GPIOB, &GPIO_Init_LED);
	    	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	    	delay_ms(3);
	    	GPIO_Init_LED.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
	    	GPIO_Init(GPIOB, &GPIO_Init_LED);
	    	delay_ms(5);
	    	read_bit = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
	    	delay_ms(60);

}




uint32_t i=0;

int main(void)
{


	SysTick_Config(SystemCoreClock/1000000); //1ms



		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

		GPIO_Init_LED.GPIO_Pin = GPIO_Pin_12;
		GPIO_Init_LED.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
		GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;

		GPIO_Init(GPIOB, &GPIO_Init_LED);

    while(1)
    {


    	delay_ms(1000000);

    	DS18B20_Reset ();
        	delay_ms(500);


    	//Skip Rom
    	DS18B20_0 ();
       	DS18B20_0 ();
    	DS18B20_1 ();
    	DS18B20_1 ();
    	DS18B20_0 ();
    	DS18B20_0 ();
    	DS18B20_1 ();
    	DS18B20_1 ();


    	//Convert T
    	DS18B20_0 ();
       	DS18B20_0 ();
    	DS18B20_1 ();
    	DS18B20_0 ();
    	DS18B20_0 ();
    	DS18B20_0 ();
    	DS18B20_1 ();
    	DS18B20_0 ();



  	GPIO_SetBits(GPIOB,GPIO_Pin_12);
    	GPIO_Init_LED.GPIO_Mode =  GPIO_Mode_Out_PP;
        	    	GPIO_Init(GPIOB, &GPIO_Init_LED);

    	delay_ms(750000);



      	DS18B20_Reset ();
       	delay_ms(200);



    	//Skip Rom
    	DS18B20_0 ();
       	DS18B20_0 ();
    	DS18B20_1 ();
    	DS18B20_1 ();
    	DS18B20_0 ();
    	DS18B20_0 ();
    	DS18B20_1 ();
    	DS18B20_1 ();

// Read book
    	DS18B20_0 ();
       	DS18B20_1 ();
    	DS18B20_1 ();
    	DS18B20_1 ();
    	DS18B20_1 ();
    	DS18B20_1 ();
    	DS18B20_0 ();
    	DS18B20_1 ();


  //  	delay_ms(500);


    	DS18B20_read ();

    	if (read_bit==1) {bit_0=1;DS_temp=DS_temp+0x0001;}

    	DS18B20_read ();

    	if (read_bit==1) {bit_1=1;DS_temp=DS_temp+0x0002;}

    	DS18B20_read ();

    	if (read_bit==1) {bit_2=1;DS_temp=DS_temp+0x0004;}

    	DS18B20_read ();

    	if (read_bit==1) {bit_3=1;DS_temp=DS_temp+0x0008;}

    	DS18B20_read ();

    	if (read_bit==1) {bit_4=1;DS_temp=DS_temp+0x0010;}

    	DS18B20_read ();


    	if (read_bit==1) {bit_5=1;DS_temp=DS_temp+0x0020;}

    	DS18B20_read ();

    	if (read_bit==1) {bit_6=1;DS_temp=DS_temp+0x0040;}

    	DS18B20_read ();

    	if (read_bit==1) {bit_7=1;DS_temp=DS_temp+0x0080;}




    	DS18B20_read ();

    	if (read_bit==1) {bit_8=1;DS_temp=DS_temp+0x0100;}

    	DS18B20_read ();

    	if (read_bit==1) {bit_9=1;DS_temp=DS_temp+0x0200;}

    	DS18B20_read ();

    	if (read_bit==1) {bit_10=1;DS_temp=DS_temp+0x0400;}

    	DS18B20_read ();

    	if (read_bit==1) {bit_11=1;DS_temp=DS_temp+0x0800;}

    	DS18B20_read ();


    	if (read_bit==1) {bit_12=1;DS_temp=DS_temp+0x1000;}

    	DS18B20_read ();

    	if (read_bit==1) {bit_13=1;DS_temp=DS_temp+2000;}

    	DS18B20_read ();

    	if (read_bit==1) {bit_14=1;DS_temp=DS_temp+4000;}

    	DS18B20_read ();

        	if (read_bit==1) {bit_15=1;DS_temp=DS_temp+8000;}



       //Th


        	DS18B20_read ();

            	if (read_bit==1) {Th=Th+0x0001;}

            	DS18B20_read ();

            	if (read_bit==1) {Th=Th+0x0002;}

            	DS18B20_read ();

            	if (read_bit==1) {Th=Th+0x0004;}

            	DS18B20_read ();

            	if (read_bit==1) {Th=Th+0x0008;}

            	DS18B20_read ();

            	if (read_bit==1) {Th=Th+0x0010;}

            	DS18B20_read ();


            	if (read_bit==1) {Th=Th+0x0020;}

            	DS18B20_read ();

            	if (read_bit==1) {Th=Th+0x0040;}

            	DS18B20_read ();

            	if (read_bit==1) {Th=Th+0x0080;}


                //Tl


                 	DS18B20_read ();

                     	if (read_bit==1) {Tl=Tl+0x0001;}

                     	DS18B20_read ();

                     	if (read_bit==1) {Tl=Tl+0x0002;}

                     	DS18B20_read ();

                     	if (read_bit==1) {Tl=Tl+0x0004;}

                     	DS18B20_read ();

                     	if (read_bit==1) {Tl=Tl+0x0008;}

                     	DS18B20_read ();

                     	if (read_bit==1) {Tl=Tl+0x0010;}

                     	DS18B20_read ();


                     	if (read_bit==1) {Tl=Tl+0x0020;}

                     	DS18B20_read ();

                     	if (read_bit==1) {Tl=Tl+0x0040;}

                     	DS18B20_read ();

                     	if (read_bit==1) {Tl=Tl+0x0080;}



                        //Config


                         	DS18B20_read ();

                             	if (read_bit==1) {Config=Config+0x01;}

                             	DS18B20_read ();

                             	if (read_bit==1) {Config=Config+0x02;}

                             	DS18B20_read ();

                             	if (read_bit==1) {Config=Config+0x04;}

                             	DS18B20_read ();

                             	if (read_bit==1) {Config=Config+0x08;}

                             	DS18B20_read ();

                             	if (read_bit==1) {Config=Config+0x10;}

                             	DS18B20_read ();


                             	if (read_bit==1) {Config=Config+0x20;}

                             	DS18B20_read ();

                             	if (read_bit==1) {Config=Config+0x40;}

                             	DS18B20_read ();

                             	if (read_bit==1) {Config=Config+0x80;}



                                //Rswd_1


                                 	DS18B20_read ();

                                     	if (read_bit==1) {Rswd_1=Rswd_1+0x0001;}

                                     	DS18B20_read ();

                                     	if (read_bit==1) {Rswd_1=Rswd_1+0x0002;}

                                     	DS18B20_read ();

                                     	if (read_bit==1) {Rswd_1=Rswd_1+0x0004;}

                                     	DS18B20_read ();

                                     	if (read_bit==1) {Rswd_1=Rswd_1+0x0008;}

                                     	DS18B20_read ();

                                     	if (read_bit==1) {Rswd_1=Rswd_1+0x0010;}

                                     	DS18B20_read ();


                                     	if (read_bit==1) {Rswd_1=Rswd_1+0x0020;}

                                     	DS18B20_read ();

                                     	if (read_bit==1) {Rswd_1=Rswd_1+0x0040;}

                                     	DS18B20_read ();

                                     	if (read_bit==1) {Rswd_1=Rswd_1+0x0080;}





                                        //Rswd_2


                                         	DS18B20_read ();

                                             	if (read_bit==1) {Rswd_2=Rswd_2+0x0001;}

                                             	DS18B20_read ();

                                             	if (read_bit==1) {Rswd_2=Rswd_2+0x0002;}

                                             	DS18B20_read ();

                                             	if (read_bit==1) {Rswd_2=Rswd_2+0x0004;}

                                             	DS18B20_read ();

                                             	if (read_bit==1) {Rswd_2=Rswd_2+0x0008;}

                                             	DS18B20_read ();

                                             	if (read_bit==1) {Rswd_2=Rswd_2+0x0010;}

                                             	DS18B20_read ();


                                             	if (read_bit==1) {Rswd_2=Rswd_2+0x0020;}

                                             	DS18B20_read ();

                                             	if (read_bit==1) {Rswd_2=Rswd_2+0x0040;}

                                             	DS18B20_read ();

                                             	if (read_bit==1) {Rswd_2=Rswd_2+0x0080;}






                                                //Rswd_3


                                                 	DS18B20_read ();

                                                     	if (read_bit==1) {Rswd_3=Rswd_3+0x0001;}

                                                     	DS18B20_read ();

                                                     	if (read_bit==1) {Rswd_3=Rswd_3+0x0002;}

                                                     	DS18B20_read ();

                                                     	if (read_bit==1) {Rswd_3=Rswd_3+0x0004;}

                                                     	DS18B20_read ();

                                                     	if (read_bit==1) {Rswd_3=Rswd_3+0x0008;}

                                                     	DS18B20_read ();

                                                     	if (read_bit==1) {Rswd_3=Rswd_3+0x0010;}

                                                     	DS18B20_read ();


                                                     	if (read_bit==1) {Rswd_3=Rswd_3+0x0020;}

                                                     	DS18B20_read ();

                                                     	if (read_bit==1) {Rswd_3=Rswd_3+0x0040;}

                                                     	DS18B20_read ();

                                                     	if (read_bit==1) {Rswd_3=Rswd_3+0x0080;}




                                       //DS_CRC


                                             	DS18B20_read ();

                                             	if (read_bit==1) {DS_CRC=DS_CRC+0x0001;}

                                             	DS18B20_read ();

                                             	if (read_bit==1) {DS_CRC=DS_CRC+0x0002;}

                                             	DS18B20_read ();

                                             	if (read_bit==1) {DS_CRC=DS_CRC+0x0004;}

                                             	DS18B20_read ();

                                             	if (read_bit==1) {DS_CRC=DS_CRC+0x0008;}

                                             	DS18B20_read ();

                                             	if (read_bit==1) {DS_CRC=DS_CRC+0x0010;}

                                             	DS18B20_read ();


                                             	if (read_bit==1) {DS_CRC=DS_CRC+0x0020;}

                                             	DS18B20_read ();

                                             	if (read_bit==1) {DS_CRC=DS_CRC+0x0040;}

                                             	DS18B20_read ();

                                             	if (read_bit==1) {DS_CRC=DS_CRC+0x0080;}





        	  Th=0;
        	  Tl=0;
        	  Config=0;
        	  Rswd_1=0;
        	  Rswd_2=0;
        	  Rswd_3=0;
        	  DS_CRC=0;




        	  bit_0=0;
        	  bit_1=0;
        	  bit_2=0;
        	  bit_3=0;
        	  bit_4=0;
        	  bit_5=0;
        	  bit_6=0;
        	  bit_7=0;
        	  bit_8=0;
        	  bit_9=0;
        	  bit_10=0;
        	  bit_11=0;
        	  bit_12=0;
        	  bit_13=0;
        	  bit_14=0;
        	  bit_15=0;
        	  DS_temp=0;

    }
}
