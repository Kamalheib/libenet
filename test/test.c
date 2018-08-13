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

int main(int argc, char **argv)
{
	struct enet_dev *dev;
	uint32_t val;
	int rc = 0;
	int i;

	dev = enet_open_dev(atoi(argv[1]), atoi(argv[2]),
			    atoi(argv[3]), atoi(argv[4]));
	if (!dev) {
		printf("Failed to open device");
		return 1;
	}

	for (i = 0xb000; i < 0xbfff; i++) {
		rc = enet_read_reg(dev, 0, i, 1, &val);
		if (rc) {
			printf("Failed to read from address %#x\n", i);
			goto out;
		}
		printf("val=%#x\n", val);
	}

out:
	if (dev)
		enet_close_dev(dev);
	return rc;
}
