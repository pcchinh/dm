

/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2011 Stephen Caudle <scaudle@doceme.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/timer.h>
#include <string.h>
#define debug
#define sizeofBuf 17
#define bit0 17
#define bit1 34

#define lednum 4
unsigned char uartBufbk[20];
unsigned char uartBuf[20]={'a','s','d','f','g','h','j','k','l','2'};
unsigned char ledBuf[96]={bit0,bit0,bit0,bit0,bit0,bit0,bit0,bit0,bit1,bit1,bit1,bit1,bit1,bit1,bit1,bit1,bit1,bit1,bit1,bit1,bit1,bit1,bit1,bit1};
//unsigned char green[3] ={0xff};
static bool ready =false;
static void decode(unsigned char* id,unsigned char* od)
{
unsigned char testbit;
for(unsigned char i=0; i<3;i++)
{
testbit=0x80;
for(unsigned char j=0;j<8;j++)
{
if((*(id+i)&testbit)==testbit)
*(od+j+8*i)=bit1; else *(od+j+8*i)=bit0;
testbit>>=1;
}
}
}
static void decode_led(unsigned char* indata,unsigned char* outdata,unsigned char nled)
{
for(unsigned char i=0;i<nled;i++)
{
decode(indata+i*3,outdata+i*24);
}
}

static void tim_setup(void)
{
//        timer_enable_irq(TIM1, TIM_DIER_CC1IE);
//nvic_disable_irq(NVIC_TIM1_CC_IRQ);
//	timer_set_dma_on_update_event(TIM1);
//	timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT,TIM_CR1_CMS_EDGE, TIM_CR1_DIR_DOWN);
//
//	/* Reset prescaler value. */
//	timer_set_prescaler(TIM1,8000);
//
//	/* Reset repetition counter value. */
//	timer_set_repetition_counter(TIM1, 0);
//
//	/* disable preload. */
//	timer_disable_preload(TIM1);
//
//	/* Continuous mode. */
//	timer_continuous_mode(TIM1);
//
//	/* Period (32kHz). */
//	timer_set_period(TIM1,65000);
//	timer_update_on_overflow(TIM1);
//	timer_enable_update_event(TIM1);
//	/* Configure break and deadtime. */
//	timer_set_deadtime(TIM1, 1);
//	timer_set_enabled_off_state_in_idle_mode(TIM1);
//	timer_set_enabled_off_state_in_run_mode(TIM1);
//	timer_disable_break(TIM1);
//	timer_set_break_polarity_high(TIM1);
//	timer_disable_break_automatic_output(TIM1);
//	timer_set_break_lock(TIM1, TIM_BDTR_LOCK_OFF);
//
//	/* -- OC1 and OC1N configuration -- */
//
//	/* Disable outputs. */
//	timer_disable_oc_output(TIM1, TIM_OC1);
//	timer_disable_oc_output(TIM3, TIM_OC4N);
//
//	/* Configure global mode of line 1. */
//	timer_disable_oc_clear(TIM1, TIM_OC1);
//	timer_disable_oc_preload(TIM1, TIM_OC1);
//	timer_set_oc_slow_mode(TIM1, TIM_OC1);
//	timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
	/* Configure OC1. */
//	timer_set_oc_polarity_low(TIM1, TIM_OC1N);
//	timer_set_oc_idle_state_unset(TIM1, TIM_OC1N);

	/* Configure OC1N. */
//	timer_set_oc_polarity_high(TIM1, TIM_OC1N);
//	timer_set_oc_idle_state_set(TIM1, TIM_OC1N);
//
//	/* Set the capture compare value for OC1. */
//	timer_set_oc_value(TIM1, TIM_OC1, 20000);
//	//timer_set_oc_polarity_high(TIM1,TIM_OC1N);
//	/* Reenable outputs. */
//	//mer_enable_oc_output(TIM1, TIM_OC1);
//	//time_set_oc_idle_state_unset(TIM1,TIM_OC1N);
//	//timer_disable_break_main_output(TIM3);
//	timer_enable_oc_output(TIM1, TIM_OC1N);
//	timer_enable_counter(TIM1);

	/* Enable commutation interrupt. */
	//mer_enable_irq(TIM1, TIM_DIER_COMIE);
TIM1_CR1 =0x4;
TIM1_CR2 =0;
TIM1_SMCR =0;
TIM1_DIER =0x100;
TIM1_EGR =0;
TIM1_CCMR1=0x60;
TIM1_CCMR2=0;
TIM1_CCER=0x4;
TIM1_PSC=0;
TIM1_RCR=0;
TIM1_BDTR=0;
TIM1_ARR =60;
TIM1_CCR1=bit1;
timer_disable_irq(TIM1, TIM_DIER_CC1IE);
nvic_enable_irq(NVIC_TIM1_CC_IRQ);
}
static void clock_setup(void)
{
	/* Enable GPIOC clock for LED & USARTs. */
	//rcc_periph_clock_enable(RCC_GPIOC);
	rcc_clock_setup_in_hse_8mhz_out_48mhz();
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_TIM1);
	/* Enable clocks for USART2. */
	rcc_periph_clock_enable(RCC_USART1);
	rcc_periph_clock_enable(RCC_DMA1);
	// rcc_periph_clock_enable(RCC_GPIOB);

}

static void dma_setup(void)
{
	dma_set_priority(DMA1,DMA_CHANNEL5,DMA_CCR_PL_HIGH);
	dma_set_priority(DMA1,DMA_CHANNEL3,DMA_CCR_PL_VERY_HIGH);
	dma_set_priority(DMA1,DMA_CHANNEL1,DMA_CCR_PL_HIGH);
	dma_set_memory_size(DMA1, DMA_CHANNEL3, DMA_CCR_MSIZE_32BIT);
	dma_set_memory_size(DMA1, DMA_CHANNEL5, DMA_CCR_MSIZE_8BIT);
	dma_set_memory_size(DMA1,DMA_CHANNEL1,DMA_CCR_MSIZE_32BIT);
	dma_set_peripheral_size(DMA1, DMA_CHANNEL3, DMA_CCR_PSIZE_32BIT);
	dma_set_peripheral_size(DMA1, DMA_CHANNEL5, DMA_CCR_PSIZE_16BIT);
	dma_set_peripheral_size(DMA1,DMA_CHANNEL1,DMA_CCR_PSIZE_32BIT);
	/*
	 * After every 32bits we have to increase the address because
	 * we use RAM.
	 */
	dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL3);
	dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL5);
	dma_enable_memory_increment_mode(DMA1,DMA_CHANNEL1);
	dma_enable_peripheral_increment_mode(DMA1, DMA_CHANNEL3);
	dma_disable_peripheral_increment_mode(DMA1, DMA_CHANNEL5);
	dma_enable_peripheral_increment_mode(DMA1,DMA_CHANNEL1);

	/* We define the source as peripheral. */
	dma_set_read_from_peripheral(DMA1, DMA_CHANNEL3);
	dma_set_read_from_memory(DMA1, DMA_CHANNEL5);
	dma_set_read_from_peripheral(DMA1,DMA_CHANNEL1);

	/* We want to transfer string s1. */
	dma_set_peripheral_address(DMA1, DMA_CHANNEL3,(uint32_t)uartBuf);
	dma_set_peripheral_address(DMA1, DMA_CHANNEL5, (uint32_t)0x40012C34);
	dma_set_peripheral_address(DMA1,DMA_CHANNEL1,(uint32_t)ledBuf);
	/* Destination should be string s2. */
	dma_set_memory_address(DMA1, DMA_CHANNEL3,(uint32_t)uartBufbk);
	dma_set_memory_address(DMA1, DMA_CHANNEL5, (uint32_t)ledBuf);

	/*
	 * Set number of DATA to transfer.
	 * Remember that this means not necessary bytes but MSIZE or PSIZE
	 * depending on your source device.
	 */
	dma_set_number_of_data(DMA1, DMA_CHANNEL3,5);
	dma_set_number_of_data(DMA1, DMA_CHANNEL5,lednum*24-1);
	dma_set_number_of_data(DMA1,DMA_CHANNEL1,6);
	dma_enable_mem2mem_mode(DMA1,DMA_CHANNEL3);
	dma_enable_mem2mem_mode(DMA1,DMA_CHANNEL1);
	/* Start DMA transfer. */
	dma_enable_transfer_complete_interrupt(DMA1,DMA_CHANNEL3);
	dma_enable_transfer_complete_interrupt(DMA1,DMA_CHANNEL5);
	dma_enable_transfer_complete_interrupt(DMA1,DMA_CHANNEL1);
	nvic_enable_irq(NVIC_DMA1_CHANNEL2_3_IRQ);
	nvic_enable_irq(NVIC_DMA1_CHANNEL4_5_IRQ);
//	nvic_enable_irq(NVIC_DMA1_CHANNEL1_IRQ);
	dma_disable_channel(DMA1,DMA_CHANNEL3);
	dma_enable_channel(DMA1,DMA_CHANNEL5);
	dma_disable_channel(DMA1,DMA_CHANNEL1);
}



static void usart_setup(void)
{

	/* Setup USART2 parameters. */
	usart_set_baudrate(USART1, 9600);
	usart_set_databits(USART1, 8);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_stopbits(USART1, USART_CR2_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX_RX);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
	//usart_enable_rx_dma(USART1);
	/* Finally enable the USART. */
	usart_enable_rx_interrupt(USART1);
	nvic_enable_irq(NVIC_USART1_IRQ);
	usart_enable(USART1);

}

static void gpio_setup(void)
{
	/* Setup GPIO pin GPIO8/9 on GPIO port C for LEDs. */
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
	//gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);
//gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO3);
	/* Setup GPIO pins for USART2 transmit. */
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3);
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO7);
	/* Setup USART1 TX pin as alternate function. */
	gpio_set_af(GPIOA, GPIO_AF2, GPIO7); //tim1_ch1n
	gpio_set_af(GPIOA, GPIO_AF1, GPIO2);
	gpio_set_af(GPIOA, GPIO_AF1, GPIO3);
	gpio_set_output_options(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_100MHZ,GPIO2);
	gpio_set_output_options(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_100MHZ,GPIO3);
	gpio_set_output_options(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_100MHZ,GPIO7);
}
#ifdef debug
static void debugu(unsigned short data)
{
usart_send_blocking(USART1,(unsigned char)((data/10000)%10+48));
usart_send_blocking(USART1,(unsigned char)((data/1000)%10+48));
usart_send_blocking(USART1,(unsigned char)((data/100)%10+48));
usart_send_blocking(USART1,(unsigned char)((data/10)%10+48));
usart_send_blocking(USART1,(unsigned char)(data%10+48));
usart_send_blocking(USART1, '\r');
usart_send_blocking(USART1, '\n');
}
#endif

int main(void)
{
#ifdef debug
	int i;
#endif
//	int j = 0, c = 0;
//unsigned short tim_1,tim_1_old=0;
//unsigned short tim1_cc;
	clock_setup();
	dma_setup();
	gpio_setup();
	usart_setup();
	tim_setup();
//nvic_set_priority(NVIC_USART1_IRQ,0);
//nvic_set_priority(NVIC_DMA1_CHANNEL4_5_IRQ,1);
//nvic_set_priority(NVIC_TIM1_CC_IRQ,2);
//TIM1_CR1 = TIM1_CR1|1;
//timer_enable_counter(TIM1);
//	decode_led(green,ledBuf,1);
//	TIM1_CR1 = TIM1_CR1|1;
//	for(unsigned char i=0;i<24;i++)
//{
//debugu(ledBuf[i]);
//}
uartBufbk[14]=0;uartBufbk[15]=0xff;uartBufbk[16]=0;ready=true;
	while (1) {
#ifdef debug
for(i=14;i<17;i++)
{
debugu(uartBufbk[i]);
//debugu(TIM1_CNT);debugu(TIM1_CCR1);
}
usart_send_blocking(USART1,'\r');
usart_send_blocking(USART1,'\n');
#endif



if(ready)
{
//#ifdef debug
//gpio_toggle(GPIOA,GPIO5);
//#endif
//debugu('o');debugu('k');debugu('\n');
decode_led(&uartBufbk[14],ledBuf,1);
ready=false;
for(i=1;i<lednum;i++)
{
dma_disable_channel(DMA1,DMA_CHANNEL1);
dma_set_number_of_data(DMA1,DMA_CHANNEL1,6);
dma_set_memory_address(DMA1,DMA_CHANNEL1,(uint32_t)&ledBuf[i*24]);
dma_enable_channel(DMA1,DMA_CHANNEL1);
while(!dma_get_interrupt_flag(DMA1,DMA_CHANNEL1,DMA_TCIF));
dma_clear_interrupt_flags(DMA1,DMA_CHANNEL1,DMA_TCIF);
}

TIM1_CCR1=ledBuf[0];
TIM1_BDTR=0x8000;
timer_enable_counter(TIM1);
//TIM1_CR1 = TIM1_CR1|1;
}
	//unsigned char temp= 'a';
//for (i=0;i<10;i++)
//{//temp = uartBuf[i];
//	usart_send_blocking (USART1,(uint16_t)uartBuf[i]);
//usart_send_blocking (USART1,13);
//}
//	usart_send_blocking(USART1, '\r');
//	usart_send_blocking(USART1, '\n');

//		for (i = 0; i < 10000000; i++) {	/* Wait a bit. */
//			__asm__("NOP");
//		}
	}

	return 0;
}
//unsigned char index=0;


void usart1_isr()
{
static unsigned char index=0;
static bool receive=false;
uartBuf[index]=(unsigned char)usart_recv(USART1);
if(!receive)
{
if(uartBuf[0]=='D'){index=1;receive=true;}else index=0;
}
else
{
if(index<sizeofBuf-1) index++;
else
{
index=0;receive =false;
if ((strncmp((const char*)uartBuf,"Data of LED: ",13)==0)&&!ready)
{
dma_disable_channel(DMA1,DMA_CHANNEL3);
dma_set_number_of_data(DMA1,DMA_CHANNEL3,5);
dma_enable_channel(DMA1,DMA_CHANNEL3);
}
}
}
}

void dma1_channel2_3_isr(void)
{
	//temp = uartBuf[i];
//	usart_send_blocking (USART1,(uint16_t)uartBuf[i]);
	dma_disable_channel(DMA1,DMA_CHANNEL3);
	dma_clear_interrupt_flags (DMA1,DMA_CHANNEL3,DMA_TCIF);
//	dma_set_number_of_data(DMA1, DMA_CHANNEL3,sizeofBuf);
//	(*(volatile uint32_t *)(0x4002000C))= sizeofBuf;
//	dma_enable_channel(DMA1,DMA_CHANNEL3);
	ready =true;
}
//void usart1_isr(void)
//{
//		static uint8_t data = 'A';

//	/* Check if we were called because of RXNE. */
//	if (((USART_CR1(USART1) & USART_CR1_RXNEIE) != 0) &&
//	    ((USART_ISR(USART1) & USART_ISR_RXNE) != 0)) {

//		lock =0;

		/* Retrieve the data from the peripheral. */
//		data = usart_recv(USART1);
//		usart_send_blocking (USART1,data);
//	}
//}
void dma1_channel4_5_isr(void)
{
//	timer_disable_counter(TIM1);
//	TIM1_CR1 = TIM1_CR1&0xfffe;
	timer_enable_irq(TIM1, TIM_DIER_CC1IE);
//	nvic_enable_irq(NVIC_TIM1_CC_IRQ);
        dma_clear_interrupt_flags (DMA1,DMA_CHANNEL5,DMA_TCIF);
//	usart_send_blocking(USART1,'o');
//	usart_send_blocking(USART1,'k');
//	usart_send_blocking(USART1, '\r');
//	usart_send_blocking(USART1, '\n');
      dma_disable_channel(DMA1,DMA_CHANNEL5);
//      dma_clear_interrupt_flags (DMA1,DMA_CHANNEL3,DMA_TCIF);
      dma_set_number_of_data(DMA1, DMA_CHANNEL5,lednum*24-1);
//      (*(volatile uint32_t *)(0x4002000C))= sizeofBuf;
      dma_enable_channel(DMA1,DMA_CHANNEL5);
}



void tim1_cc_isr()
{
	TIM1_BDTR=0;
	timer_disable_counter(TIM1);
//      TIM1_CR1 = TIM1_CR1&0xfffe;
//nvic_disable_irq(NVIC_TIM1_CC_IRQ);
	timer_disable_irq(TIM1, TIM_DIER_CC1IE);
	timer_clear_flag(TIM1,TIM_SR_CC1IF);
//        usart_send_blocking(USART1,'o');
//       usart_send_blocking(USART1,'k');
//       usart_send_blocking(USART1, '\r');
//        usart_send_blocking(USART1, '\n');
}
