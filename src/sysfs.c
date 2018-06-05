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

#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "common.h"

#define PCI_DEVICE_DIR "/sys/bus/pci/devices/%04u:%02u:%02u.%u/"
#define PCI_DEVICE_RES "/sys/bus/pci/devices/%04u:%02u:%02u.%u/resource%d"
#define PCI_DEVICE_EN "/sys/bus/pci/devices/%04u:%02u:%02u.%u/enable"

int enet_sysfs_is_device_exit(struct enet_dev *dev)
{
	char path[100];
	struct stat sb;

	sprintf(path, PCI_DEVICE_DIR, dev->domain,
		dev->bus, dev->dev, dev->func);

	if (!stat(path, &sb))
		return 1;

	return 0;
}

int enet_sysfs_is_device_enabled(struct enet_dev *dev)
{
	char path[100];
	char val;
	int fd;

	pr_info("%s Called\n", __func__);
	sprintf(path, PCI_DEVICE_EN, dev->domain,
		dev->bus, dev->dev, dev->func);

	fd = open(path, O_RDONLY);
	if (!fd) {
		pr_err("Failed to open %s\n", path);
		return -1;
	}

	read(fd, &val, 1);

	return val == '1' ? 1 : 0;
}

int enet_sysfs_enable_device(struct enet_dev *dev)
{
	char path[100];
	int fd;

	pr_info("%s Called\n", __func__);
	sprintf(path, PCI_DEVICE_EN, dev->domain,
		dev->bus, dev->dev, dev->func);

	fd = open(path, O_RDWR);
	if (!fd) {
		pr_err("Failed to open %s\n", path);
		return -1;
	}

	write(fd, "1", 1);
	close(fd);

	return 0;
}

int enet_sysfs_open_resources(struct enet_dev *dev)
{
	char path[100];
	struct stat st;
	int i;


	for (i = 0; i < PCI_MAX_BARS; i++) {
		sprintf(path, PCI_DEVICE_RES, dev->domain,
			dev->bus, dev->dev, dev->func, i);
		if (!stat(path, &st)) {

			dev->bar[i].fd = open(path, O_RDWR);
			if (!dev->bar[i].fd) {
				pr_err("Failed to open resource %s\n", path);
				return 1;
			}

			if(fstat(dev->bar[i].fd, &st)) {
				pr_err("Failed to get size of resource %s\n",
				       path);
				return 1;
			}

			dev->bar[i].size = st.st_size;
		}
	}

	return 0;
}

void enet_sysfs_close_resources(struct enet_dev *dev)
{
	int i;

	for (i = 0; i < PCI_MAX_BARS; i++) {
		if (dev->bar[i].fd)
			close(dev->bar[i].fd);
	}
}

int enet_sysfs_mmap_resources(struct enet_dev *dev)
{
	void *base;
	int i;

	for(i = 0; i < PCI_MAX_BARS; i++) {
		if (dev->bar[i].fd) {
			base = mmap(NULL, dev->bar[i].size,
				    PROT_READ | PROT_WRITE,
				    MAP_FILE | MAP_SHARED,
				    dev->bar[i].fd, 0);
			if (base == (void *)-1) {
				pr_err("Failed to mmap bar %d\n", i);
				return 1;
			}

			dev->bar[i].base = base;
		}
	}

	return 0;
}

void enet_sysfs_unmap_resources(struct enet_dev *dev)
{
	int i;

	for (i = 0; i < PCI_MAX_BARS; i++) {
		if (dev->bar[i].base) {
			munmap(dev->bar[i].base, dev->bar[i].size);
		}
	}
}
