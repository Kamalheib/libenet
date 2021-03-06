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


#define prefix "libenet"
#define pr_err(fmt, ...) \
	fprintf(stderr, "%s error: " fmt, prefix, ## __VA_ARGS__);

static int debug_flags = 0;
#define pr_dbg(fmt, ...) do { \
	if (debug_flags) \
		fprintf(stdout, "%s debug: " fmt, prefix, ## __VA_ARGS__); \
} while (0) \

#define pr_info(fmt, ...) \
	fprintf(stdout, "%s info: " fmt, prefix, ## __VA_ARGS__);

#define PCI_MAX_BARS 6

struct enet_pci_bar {
	int fd;
	void *base;
	uint32_t size;
};

struct enet_dev {
	uint16_t domain;
	uint8_t bus;
	uint8_t dev;
	uint8_t func;

	struct enet_pci_bar bar[PCI_MAX_BARS];
};
