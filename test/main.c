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
#include <stdio.h>
#include "enet.h"

int main(int argc, char **argv)
{
	struct enet_dev *dev;

	puts("Start testing libenet...");
	dev = enet_open_dev(atoi(argv[1]), atoi(argv[2]),
			    atoi(argv[3]), atoi(argv[4]));
	if (!dev) {
		return 1;
	}
	enet_close_dev(dev);
	puts("End testing libenet...");
	return 0;
}
