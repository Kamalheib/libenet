/*
 * libenet - Library for access enet's PCIe device.
 *
 * Copyright (c) 2018 Kamal Heib <kamalheib1@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "spi.h"

int main(int argc, char **argv)
{
	struct enet_dev *dev;
	uint32_t control_reg;
	uint32_t status_reg;
	uint32_t slave_select_reg;
	uint32_t tx_fifo;
	uint32_t rx_fifo;
	int rc = 0;

	dev = enet_open_dev(atoi(argv[1]), atoi(argv[2]),
			    atoi(argv[3]), atoi(argv[4]));
	if (!dev) {
		printf("Failed to open device");
		return 1;
	}

	if (spi_write_reg(dev, SPI_BASE_ADDR + SPI_REG_SRR, SPI_SRR_RESET)) {
		rc = 1;
		printf("Failed to reset device\n");
		goto out;
	}

	if (spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_SPICR, &control_reg)) {
		rc = 1;
		printf("Failed to read control register\n");
		goto out;
	}

	if (control_reg != SPI_SPICR_RESET) {
		rc = 1;
		printf("Invalid control register value\n");
		goto out;
	}

	printf("control register=%#x\n", control_reg);

	if (spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_SPISR, &status_reg)) {
		rc = 1;
		printf("Failed to read status register\n");
		goto out;
	}

	if ((status_reg & SPI_SR_RESET) != SPI_SR_RESET) {
		rc = 1;
		printf("Invalid status register value\n");
		goto out;
	}

	printf("status register=%#x\n", status_reg);

	if (spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_SPISSR, &slave_select_reg)) {
		rc = 1;
		printf("Failed to read slave select register\n");
		goto out;
	}

	printf("slave select register=%#x\n", slave_select_reg);

	if (spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_TFO, &tx_fifo)) {
		rc = 1;
		printf("Failed to read TX fifo occupancy\n");
		goto out;
	}

	if (spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_RFO, &rx_fifo)) {
		rc = 1;
		printf("Failed to read RX fifo occupancy\n");
		goto out;
	}

	printf("tx_fifo_occupancy=%#x rx_fifo_occupancy=%#x\n", tx_fifo, rx_fifo);

out:
	if (dev)
		enet_close_dev(dev);
	return rc;
}
