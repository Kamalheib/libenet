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


/* SPI Control Register masks */

#define SPI_REG_SPICR_LOOP_MASK			(1 << 0) /* Loopback enable */
#define SPI_REG_SPICR_SPE_MASK			(1 << 1) /* System enable */
#define SPI_REG_SPICR_MASTER_MASK		(1 << 2) /* Master enable */
#define SPI_REG_SPICR_CPOL_MASK			(1 << 3) /* Clock polarity */
#define SPI_REG_SPICR_CPHA_MASK			(1 << 4) /* Clock phase */
#define SPI_REG_SPICR_TX_FIFO_RESET_MASK	(1 << 5) /* Reset TX register/FIFO */
#define SPI_REG_SPICR_RX_FIFO_RESET_MASK	(1 << 6) /* Reset RX register/FIFO */
#define SPI_REG_SPICR_MANUAL_SS_MASK		(1 << 7) /* Manual slave select */
#define SPI_REG_SPICR_INHIBIT_MASK		(1 << 8) /* Master transaction inhibit */
#define SPI_REG_SPICR_LSB_FIRST_MASK		(1 << 9) /* LSB fist data format */


int spi_read_reg(struct enet_dev *dev, uint32_t addr, uint32_t *data);
int spi_write_reg(struct enet_dev *dev, uint32_t addr, uint32_t data);

#endif /* _SPI_H_ */
