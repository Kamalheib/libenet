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

#ifndef _ENET_H_
#define _ENET_H_

struct enet_dev;
struct enet_dev *enet_open_dev(uint16_t domain, uint8_t bus,
			       uint8_t dev, uint8_t func);
void enet_close_dev(struct enet_dev *dev);
void enet_write_reg(struct enet_dev *dev, uint8_t bar, uint32_t addr,
		   uint32_t len, uint32_t *vals);
void enet_read_reg(struct enet_dev *dev, uint8_t bar, uint32_t addr,
		  uint32_t len, uint32_t *data);

#endif /* _ENET_H_ */
