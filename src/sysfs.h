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

#ifndef _SYSFS_H_
#define _SYSFS_H_

int enet_sysfs_is_device_exit(struct enet_dev *dev);
int enet_sysfs_open_resources(struct enet_dev *dev);
void enet_sysfs_close_resources(struct enet_dev *dev);
int enet_sysfs_mmap_resources(struct enet_dev *dev);
void enet_sysfs_unmap_resources(struct enet_dev *dev);
int enet_sysfs_is_device_enabled(struct enet_dev *dev);
int enet_sysfs_enable_device(struct enet_dev *dev);

#endif /* _SYSFS_H_ */
