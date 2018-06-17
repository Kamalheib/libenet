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
#include <time.h>
#include "enet.h"

#define TRANSFER_SIZE (8 * 1024)
#define RUNS 5000

int main(int argc, char **argv)
{
	struct enet_dev *dev;
	clock_t start, end;
	double ttime;
	char *ma;
	int i;

	puts("Start testing libenet...");
	dev = enet_open_dev(atoi(argv[1]), atoi(argv[2]),
			    atoi(argv[3]), atoi(argv[4]));
	if (!dev) {
		return 1;
	}

	ma = memalign(4 * 1024, 8 * 1024);
	if (!ma) {
		puts("Error: Failed to allocate memory aligned\n");
		enet_close_dev(dev);
		return 1;
	}

	start = clock();
	for (i = 0; i < RUNS; i++) {
		enet_read_reg(dev, 0, 0, TRANSFER_SIZE / 4, (uint32_t *)ma);
	}
	end = clock();

	ttime = ((double)(end - start) / CLOCKS_PER_SEC);

	printf("Total time %f seconds to execute\n", ttime);
	printf("Read bandwidth %.2f Mbyte/sec\n",
	       RUNS * (double) (TRANSFER_SIZE / 4) / ttime / 1000000.);


	start = clock();
	for (i = 0; i < RUNS; i++) {
		enet_write_reg(dev, 0, 0, TRANSFER_SIZE / 4, (uint32_t *)ma);
	}
	end = clock();

	ttime = ((double)(end - start) / CLOCKS_PER_SEC);

	printf("Total time %f seconds to execute\n", ttime);
	printf("Write bandwidth %.2f Mbyte/sec\n",
	       RUNS * (double) (TRANSFER_SIZE / 4) / ttime / 1000000.);


	free(ma);
	enet_close_dev(dev);
	puts("End testing libenet...");
	return 0;
}
