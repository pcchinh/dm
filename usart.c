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
#include <libopencm3/stm32/spi.h>
#include <libopencm3/cm3/nvic.h>

static void spi_setup(void)
{
	spi_disable_crc(SPI1);
	spi_reset(SPI1);
	spi_disable(SPI1);
	spi_set_full_duplex_mode(SPI1);
	spi_set_standard_mode(SPI1,0);
	spi_disable_software_slave_management(SPI1);
	spi_set_nss_high (SPI1);
	spi_send_msb_first (SPI1);
//	spi_set_baudrate_prescaler(SPI_CR1_BR_FPCLK_DIV_2);
	spi_set_slave_mode (SPI1);
//	spi_set_clock_polarity_0(SPI1);
//	spi_set_clock_phase_0(SPI1);
	spi_disable_tx_buffer_empty_interrupt (SPI1);
	spi_enable_rx_buffer_not_empty_interrupt (SPI1);
	spi_set_crcl_8bit(SPI1);
	spi_set_data_size(SPI1,SPI_CR2_DS_8BIT);
	nvic_enable_irq(NVIC_SPI1_IRQ);
	spi_enable(SPI1);
}

static void clock_setup(void)
{
	/* Enable GPIOC clock for LED & USARTs. */
	//rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_clock_setup_in_hse_8mhz_out_48mhz();
	/* Enable clocks for USART2. */
	rcc_periph_clock_enable(RCC_USART1);
	rcc_periph_clock_enable(RCC_SPI1);
}

static void usart_setup(void)
{
	/* Setup USART2 parameters. */
	usart_set_baudrate(USART1, 38400);
	usart_set_databits(USART1, 8);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_stopbits(USART1, USART_CR2_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART1);
}

static void gpio_setup(void)
{
	/* Setup GPIO pin GPIO8/9 on GPIO port C for LEDs. */
	//gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8 | GPIO9);
gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO4);
gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO5);
gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6);
gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO7);
	/* Setup GPIO pins for USART2 transmit. */
//	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);
gpio_set_af(GPIOA, GPIO_AF1, GPIO2);
gpio_set_af(GPIOA, GPIO_AF0, GPIO4);
gpio_set_af(GPIOA, GPIO_AF0, GPIO5);
gpio_set_af(GPIOA, GPIO_AF0, GPIO6);
gpio_set_af(GPIOA, GPIO_AF0, GPIO7);
	/* Setup USART1 TX pin as alternate function. */
//	gpio_set_af(GPIOA, GPIO_AF1, GPIO9);
gpio_set_output_options(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_100MHZ,GPIO2);
gpio_set_output_options(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_100MHZ,GPIO4);
gpio_set_output_options(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_100MHZ,GPIO5);
gpio_set_output_options(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_100MHZ,GPIO6);
gpio_set_output_options(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_100MHZ,GPIO7);
}



int main(void)
{
	//int i, j = 0, c = 0;
int i;
	clock_setup();
	gpio_setup();
	usart_setup();
	spi_setup();
	/* Blink the LED (PD12) on the board with every transmitted byte. */
	while (1) {
/*		gpio_toggle(GPIOC, GPIO8);
		usart_send_blocking(USART1, c + '0');
		c = (c == 9) ? 0 : c + 1;
		if ((j++ % 80) == 0) {
			usart_send_blocking(USART1, '\r');
			usart_send_blocking(USART1, '\n');
		}
*/
		for (i = 0; i < 10000000; i++) {
			__asm__("NOP");
		}

	usart_send_blocking(USART1,'p');
	usart_send_blocking(USART1,spi_read8(SPI1));
	usart_send_blocking(USART1, '\r');
	usart_send_blocking(USART1, '\n');
	}

	return 0;
}

void spi1_isr()
{
	usart_send_blocking(USART1,'i');
	usart_send_blocking(USART1, '\r');
	usart_send_blocking(USART1, '\n');	
}