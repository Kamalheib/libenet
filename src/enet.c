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

#include "common.h"
#include "sysfs.h"
#include "enet.h"

struct enet_dev *enet_open_dev(uint16_t domain, uint8_t bus,
			       uint8_t dev, uint8_t func)
{
	struct enet_dev *device;
	int enabled;

	device = malloc(sizeof(struct enet_dev));
	if (!device) {
		pr_err("Failed to allocate device\n");
		return NULL;
	}

	device->domain = domain;
	device->bus = bus;
	device->dev = dev;
	device->func = func;

	if (!enet_sysfs_is_device_exit(device)) {
		pr_err("Device not found\n");
		goto free_dev;
	}

	enabled = enet_sysfs_is_device_enabled(device);
	if (enabled == -1) {
		pr_err("Failed to open device\n");
		goto free_dev;
	}

	if (!enabled) {
		int rv = enet_sysfs_enable_device(device);

		if (rv == -1) {
			pr_err("Failed to enabled device\n");
			goto free_dev;
		}
	}


	if (enet_sysfs_open_resources(device)) {
		pr_err("Failed to open resources\n");
		goto close_res;
	}

	if (enet_sysfs_mmap_resources(device)) {
		pr_err("Failed to mmap resources\n");
		goto unmap;
	}

	return device;

unmap:
	enet_sysfs_unmap_resources(device);
close_res:
	enet_sysfs_close_resources(device);
free_dev:
	free(device);
	return NULL;
}

void enet_close_dev(struct enet_dev *dev)
{
	enet_sysfs_unmap_resources(dev);
	enet_sysfs_close_resources(dev);
	free(dev);
}

int enet_write_reg(struct enet_dev *dev, uint8_t bar, uint32_t addr,
		   uint32_t len, uint32_t *vals)
{
	void *virt_addr;
	int i;

	if (!dev->bar[bar].fd)
		return 1;

	virt_addr = dev->bar[bar].base + (addr & (dev->bar[bar].size - 1));

	for (i = 0; i < len; i++)
		*((uint32_t *)virt_addr) = vals[i];

	return 0;
}

int enet_read_reg(struct enet_dev *dev, uint8_t bar, uint32_t addr,
		  uint32_t len, uint32_t *data)
{
	void *virt_addr;
	int i;

	if (!dev->bar[bar].fd)
		return 1;

	virt_addr = dev->bar[bar].base + (addr & (dev->bar[bar].size - 1));

	for (i = 0; i < len; i++)
		data[i] = *((uint32_t *)virt_addr);

	return 0;
}
