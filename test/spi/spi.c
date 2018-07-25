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

#include "spi.h"

int spi_read_reg(struct enet_dev *dev, uint32_t addr, uint32_t *data)
{
	return enet_read_reg(dev, 0, addr, 1, data);
}

int spi_write_reg(struct enet_dev *dev, uint32_t addr, uint32_t data)
{
	return enet_write_reg(dev, 0, addr, 1, &data);
}
