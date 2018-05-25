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
#include <stdio.h>

#include "common.h"
#include "enet.h"

struct enet_dev *enet_open_dev(uint16_t domain, uint8_t bus,
			       uint8_t dev, uint8_t func)
{
	pr_info("%s called\n", __func__);
	return NULL;
}

void enet_close_dev(struct enet_dev *dev)
{
	pr_info("%s called\n", __func__);
}

int enet_write_reg(struct enet_dev *dev, uint64_t addr, uint64_t val)
{
	pr_info("%s called\n", __func__);
	return -1;
}

int enet_read_reg(struct enet_dev *dev, uint64_t addr, uint64_t *data)
{
	pr_info("%s called\n", __func__);
	return -1;
}
