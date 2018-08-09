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
#include <stdbool.h>
#include "spi.h"

static int spi_read_device_id(struct enet_dev *dev)
{
	uint32_t control_reg;
	uint32_t status_reg;
	uint32_t buffer[3];
	uint32_t val;
	int rc = 0;

	rc = spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_SPICR, &control_reg);
	if (rc) {
		printf("Failed to read control register\n");
		return 1;
	}

	control_reg |= 0x20 | 0x40 | 0x2 | 0x4;

	rc = spi_write_reg(dev, SPI_BASE_ADDR + SPI_REG_SPICR, control_reg);
	if (rc) {
		printf("Failed to write control register\n");
		return 1;
	}

	buffer[0] = 0x9f;
	buffer[1] = 0x00;
	buffer[2] = 0x00;

	rc = spi_write_reg(dev, SPI_BASE_ADDR + SPI_REG_DTR, buffer[0]);
	rc += spi_write_reg(dev, SPI_BASE_ADDR + SPI_REG_DTR, buffer[1]);
	rc += spi_write_reg(dev, SPI_BASE_ADDR + SPI_REG_DTR, buffer[2]);
	if (rc) {
		printf("Failed to write flash read command\n");
		return 1;
	}

	rc = spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_SPICR, &control_reg);
	if (rc) {
		printf("Failed to read control register\n");
		return 1;
	}

	control_reg &= ~0x100;

	rc = spi_write_reg(dev, SPI_BASE_ADDR + SPI_REG_SPICR, control_reg);
	if (rc) {
		printf("Failed to write control register\n");
		return 1;
	}

	rc = spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_SPICR, &control_reg);
	if (rc) {
		printf("Failed to read control register\n");
		return 1;
	}

	control_reg |= 0x100;

	rc = spi_write_reg(dev, SPI_BASE_ADDR + SPI_REG_SPICR, control_reg);
	if (rc) {
		printf("Failed to write control register\n");
		return 1;
	}

	rc = spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_SPISR, &status_reg);
	if (rc) {
		printf("Failed to read status register\n");
		return 1;
	}

	if (!(status_reg & 0x1)) {
		printf("We got data in RX\n");
		rc = spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_DRR, &val);
		if (rc) {
			printf("Failed to read data\n");
			return 1;
		}

		printf("val=%#x\n", val);
	}

	rc = spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_SPISR, &status_reg);
	if (rc) {
		printf("Failed to read status register\n");
		return 1;
	}

	if (!(status_reg & 0x1)) {
		printf("We got data in RX\n");
		rc = spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_DRR, &val);
		if (rc) {
			printf("Failed to read data\n");
			return 1;
		}

		printf("val=%#x\n", val);
	}

	rc = spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_SPISR, &status_reg);
	if (rc) {
		printf("Failed to read status register\n");
		return 1;
	}

	if (!(status_reg & 0x1)) {
		printf("We got data in RX\n");
		rc = spi_read_reg(dev, SPI_BASE_ADDR + SPI_REG_DRR, &val);
		if (rc) {
			printf("Failed to read data\n");
			return 1;
		}

		printf("val=%#x\n", val);
	}

	return 0;
}

int main(int argc, char **argv)
{
	struct enet_dev *dev;
	int rc = 0;

	dev = enet_open_dev(atoi(argv[1]), atoi(argv[2]),
			    atoi(argv[3]), atoi(argv[4]));
	if (!dev) {
		printf("Failed to open device");
		return 1;
	}

	rc = spi_read_device_id(dev);
	if (rc)
		goto out;

	return 0;

out:
	if (dev)
		enet_close_dev(dev);
	return rc;
}
