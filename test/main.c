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

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "enet.h"

static int read_indirect(struct enet_dev *dev, uint32_t addr, uint32_t *val)
{
	uint32_t write_val;
	uint32_t high;
	uint32_t low;

	write_val = addr & 0xffff;

	if (enet_write_reg(dev, 0, 0x4, 1, &write_val)) {
		printf("Failed to write low addr\n");
		return 1;
	}

	if (enet_read_reg(dev, 0, 0x8, 1, &low)) {
		printf("Failed to read low addr\n");
		return 1;
	}

	write_val = addr + 2;

	if (enet_write_reg(dev, 0, 0x4, 1, &write_val)) {
		printf("Failed to write high addr\n");
		return 1;
	}

	if (enet_read_reg(dev, 0, 0x8, 1, &high)) {
		printf("Failed to read high addr\n");
		return 1;
	}

	*(val) = ((uint32_t)(high << 16) | low);

	return 0;
}

static int write_indirect(struct enet_dev *dev, uint32_t addr, uint32_t val)
{
	uint32_t write_val;

	write_val = ((uint32_t)((val & 0xffff) << 16) | (addr & 0xffff));

	if (enet_write_reg(dev, 0, 0x0, 1, &write_val)) {
		printf("Failed to write low addr and val\n");
		return 1;
	}

	write_val = ((uint32_t)(val & 0xffff0000) | (addr + 2));

	if (enet_write_reg(dev, 0, 0x0, 1, &write_val)) {
		printf("Failed to write high addr and val\n");
		return 1;
	}

	return 0;
}

int main(int argc, char **argv)
{
	struct enet_dev *dev;
	uint32_t addr = 0xc0;
	uint32_t write_val = 0x12345678;
	uint32_t reset_val = 0x8888aaaa;
	uint32_t val;

	dev = enet_open_dev(atoi(argv[1]), atoi(argv[2]),
			    atoi(argv[3]), atoi(argv[4]));
	if (!dev) {
		printf("Failed to open device");
		return 1;
	}

	if (read_indirect(dev, addr, &val)) {
		printf("Failed to read indirect\n");
		return 1;
	}

	printf("Before write val=%#x\n", val);

	if (write_indirect(dev, addr, write_val)) {
		printf("Failed to write indirect\n");
		return 1;
	}

	if (read_indirect(dev, addr, &val)) {
		printf("Failed to read indirect\n");
		return 1;
	}

	printf("After write val=%#x\n", val);

	if (write_indirect(dev, addr, reset_val)) {
		printf("Failed to write indirect\n");
		return 1;
	}

	if (dev)
		enet_close_dev(dev);
	return 0;
}
