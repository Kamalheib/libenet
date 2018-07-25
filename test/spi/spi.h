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

#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>
#include "enet.h"

#define SPI_BASE_ADDR		0xB000

#define SPI_REG_DGIER		0x1c /* Device global in terrupt enable register */
#define SPI_REG_IPISR		0x20 /* IP interrupt status register */
#define SPI_REG_IPIER		0x28 /* IP interrupt enable register */

#define SPI_REG_SRR		0x40 /* Software reset register */
#define SPI_REG_SPICR		0x60 /* SPI control register */
#define SPI_REG_SPISR		0x64 /* SPI status register */
#define SPI_REG_DTR		0x68 /* SPI data transmit register/FIFO */
#define SPI_REG_DRR		0x6c /* SPI data receive register/FIFO */
#define SPI_REG_SPISSR		0x70 /* SPI Slave select register */
#define SPI_REG_TFO		0x74 /* Transmit FIFO occupancy register */
#define SPI_REG_RFO		0x78 /* Receive FIFO occupancy register */

#define SPI_SRR_RESET		0x0000000a /* SPI Software Reset mask */
#define SPI_SR_RESET		0x5 /* Default TX/RX empty */
#define SPI_SPICR_RESET		0x180 /* Default control register */

int spi_read_reg(struct enet_dev *dev, uint32_t addr, uint32_t *data);
int spi_write_reg(struct enet_dev *dev, uint32_t addr, uint32_t data);

#endif /* _SPI_H_ */
