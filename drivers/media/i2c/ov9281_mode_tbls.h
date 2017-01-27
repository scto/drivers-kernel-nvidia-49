/*
 * ov9281.c - ov9281 sensor driver
 *
 * Copyright (c) 2016-2017, NVIDIA CORPORATION, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <media/camera_common.h>

#ifndef __OV9281_I2C_TABLES__
#define __OV9281_I2C_TABLES__

#define OV9281_TABLE_WAIT_MS	0
#define OV9281_TABLE_END	1

#define ov9281_reg struct reg_8

enum {
	OV9281_MODE_1280X800,
	OV9281_MODE_1280X720,
	OV9281_MODE_640X400,
	OV9281_MODE_START_STREAM,
	OV9281_MODE_STOP_STREAM,
};

enum {
	OV9281_FSYNC_NONE,
	OV9281_FSYNC_MASTER,
	OV9281_FSYNC_SLAVE,
};

static const ov9281_reg ov9281_start[] = {
	{ 0x0100, 0x01 },
	{ OV9281_TABLE_END, 0x00 }
};

static const ov9281_reg ov9281_stop[] = {
	{ 0x0100, 0x00 },
	{ OV9281_TABLE_END, 0x00 }
};

static const ov9281_reg ov9281_fsync_master[] = {
	{0x3006, 0x02}, /* fsin pin out */
	{0x3823, 0x00},
	{OV9281_TABLE_WAIT_MS, 66},
	{OV9281_TABLE_END, 0x00}
};

static const ov9281_reg ov9281_fsync_slave[] = {
	{0x3006, 0x00}, /* fsin pin in */
	{0x3823, 0x30}, /* ext_vs_en, r_init_man */
	{OV9281_TABLE_WAIT_MS, 66},
	{OV9281_TABLE_END, 0x00}
};

static const ov9281_reg ov9281_mode_1280x800_26MhzMCLK[] = {
	/* PLL control */
	{ 0x0302, 0x32 },
	{ 0x030d, 0x50 },
	{ 0x030e, 0x02 },

	/* system control */
	{ 0x3001, 0x00 },
	{ 0x3004, 0x00 },
	{ 0x3005, 0x00 },
	{ 0x3006, 0x04 },
	{ 0x3011, 0x0a },
	{ 0x3013, 0x18 },
	{ 0x3022, 0x01 },
	{ 0x3030, 0x10 },
	{ 0x3039, 0x32 },
	{ 0x303a, 0x00 },

	/* manual AEC/AGC */
	{ 0x3500, 0x00 },
	{ 0x3501, 0x2a },
	{ 0x3502, 0x90 },
	{ 0x3503, 0x08 },
	{ 0x3505, 0x8c },
	{ 0x3507, 0x03 },
	{ 0x3508, 0x00 },
	{ 0x3509, 0x10 },

	/* analog control */
	{ 0x3610, 0x80 },
	{ 0x3611, 0xa0 },
	{ 0x3620, 0x6e },
	{ 0x3632, 0x56 },
	{ 0x3633, 0x78 },
	{ 0x3662, 0x05 },
	{ 0x3666, 0x00 },
	{ 0x366f, 0x5a },
	{ 0x3680, 0x84 },

	/* sensor control */
	{ 0x3712, 0x80 },
	{ 0x372d, 0x22 },
	{ 0x3731, 0x80 },
	{ 0x3732, 0x30 },
	{ 0x3778, 0x00 },
	{ 0x377d, 0x22 },
	{ 0x3788, 0x02 },
	{ 0x3789, 0xa4 },
	{ 0x378a, 0x00 },
	{ 0x378b, 0x4a },
	{ 0x3799, 0x20 },

	/* timing control */
	{ 0x3800, 0x00 },
	{ 0x3801, 0x00 },
	{ 0x3802, 0x00 },
	{ 0x3803, 0x00 },
	{ 0x3804, 0x05 },
	{ 0x3805, 0x0f },
	{ 0x3806, 0x03 },
	{ 0x3807, 0x2f },
	{ 0x3808, 0x05 },
	{ 0x3809, 0x00 },
	{ 0x380a, 0x03 },
	{ 0x380b, 0x20 },
	{ 0x380c, 0x02 },
	{ 0x380d, 0xd8 },
	{ 0x380e, 0x03 },
	{ 0x380f, 0x8e },
	{ 0x3810, 0x00 },
	{ 0x3811, 0x08 },
	{ 0x3812, 0x00 },
	{ 0x3813, 0x08 },
	{ 0x3814, 0x11 },
	{ 0x3815, 0x11 },
	{ 0x3820, 0x00 },
	{ 0x3821, 0x00 },
	{ 0x3881, 0x42 },
	{ 0x38a8, 0x02 },
	{ 0x38a9, 0x80 },
	{ 0x38b1, 0x00 },
	{ 0x38c4, 0x00 },
	{ 0x38c5, 0xc0 },
	{ 0x38c6, 0x04 },
	{ 0x38c7, 0x80 },

	/* PWM and strobe control */
	{ 0x3920, 0xff },

	/* BLC control */
	{ 0x4003, 0x40 },
	{ 0x4008, 0x04 },
	{ 0x4009, 0x0b },
	{ 0x400c, 0x00 },
	{ 0x400d, 0x07 },
	{ 0x4010, 0x40 },
	{ 0x4043, 0x40 },

	/* format control */
	{ 0x4307, 0x30 },
	{ 0x4317, 0x00 },

	/* ???? */
	{ 0x4501, 0x00 },
	{ 0x4507, 0x00 },
	{ 0x4509, 0x00 },
	{ 0x450a, 0x08 },

	/* VFIFO control */
	{ 0x4601, 0x04 },

	/* DVP control */
	{ 0x470f, 0x00 },

	/* low power mode control */
	{ 0x4f07, 0x00 },

	/* MIPI top control */
	{ 0x4800, 0x00 }, /* bit 5: discontinuous clk */

	/* ISP top control */
	{ 0x5000, 0x9f },
	{ 0x5001, 0x00 },
	{ 0x5e00, 0x00 },

	/* ???? */
	{ 0x5d00, 0x07 },
	{ 0x5d01, 0x00 },
	{ OV9281_TABLE_END, 0x00}
};

static const ov9281_reg ov9281_mode_1280x720_26MhzMCLK[] = {
	{ 0x0302, 0x32 },
	{ 0x030d, 0x50 },
	{ 0x030e, 0x02 },
	{ 0x3001, 0x00 },
	{ 0x3004, 0x00 },
	{ 0x3005, 0x00 },
	{ 0x3006, 0x04 },
	{ 0x3011, 0x0a },
	{ 0x3013, 0x18 },
	{ 0x3022, 0x01 },
	{ 0x3030, 0x10 },
	{ 0x3039, 0x32 },
	{ 0x303a, 0x00 },
	{ 0x3500, 0x00 },
	{ 0x3501, 0x2a },
	{ 0x3502, 0x90 },
	{ 0x3503, 0x08 },
	{ 0x3505, 0x8c },
	{ 0x3507, 0x03 },
	{ 0x3508, 0x00 },
	{ 0x3509, 0x10 },
	{ 0x3610, 0x80 },
	{ 0x3611, 0xa0 },
	{ 0x3620, 0x6e },
	{ 0x3632, 0x56 },
	{ 0x3633, 0x78 },
	{ 0x3662, 0x05 },
	{ 0x3666, 0x00 },
	{ 0x366f, 0x5a },
	{ 0x3680, 0x84 },
	{ 0x3712, 0x80 },
	{ 0x372d, 0x22 },
	{ 0x3731, 0x80 },
	{ 0x3732, 0x30 },
	{ 0x3778, 0x00 },
	{ 0x377d, 0x22 },
	{ 0x3788, 0x02 },
	{ 0x3789, 0xa4 },
	{ 0x378a, 0x00 },
	{ 0x378b, 0x4a },
	{ 0x3799, 0x20 },
	{ 0x3800, 0x00 },
	{ 0x3801, 0x00 },
	{ 0x3802, 0x00 },
	{ 0x3803, 0x28 },
	{ 0x3804, 0x05 },
	{ 0x3805, 0x0f },
	{ 0x3806, 0x03 },
	{ 0x3807, 0x07 },
	{ 0x3808, 0x05 },
	{ 0x3809, 0x00 },
	{ 0x380a, 0x02 },
	{ 0x380b, 0xd0 },
	{ 0x380c, 0x02 },
	{ 0x380d, 0xd8 },
	{ 0x380e, 0x03 },
	{ 0x380f, 0x8e },
	{ 0x3810, 0x00 },
	{ 0x3811, 0x08 },
	{ 0x3812, 0x00 },
	{ 0x3813, 0x08 },
	{ 0x3814, 0x11 },
	{ 0x3815, 0x11 },
	{ 0x3820, 0x00 },
	{ 0x3821, 0x00 },
	{ 0x3881, 0x42 },
	{ 0x38a8, 0x02 },
	{ 0x38a9, 0x80 },
	{ 0x38b1, 0x00 },
	{ 0x38c4, 0x00 },
	{ 0x38c5, 0xc0 },
	{ 0x38c6, 0x04 },
	{ 0x38c7, 0x80 },
	{ 0x3920, 0xff },
	{ 0x4003, 0x40 },
	{ 0x4008, 0x04 },
	{ 0x4009, 0x0b },
	{ 0x400c, 0x00 },
	{ 0x400d, 0x07 },
	{ 0x4010, 0x40 },
	{ 0x4043, 0x40 },
	{ 0x4307, 0x30 },
	{ 0x4317, 0x00 },
	{ 0x4501, 0x00 },
	{ 0x4507, 0x00 },
	{ 0x4509, 0x00 },
	{ 0x450a, 0x08 },
	{ 0x4601, 0x04 },
	{ 0x470f, 0x00 },
	{ 0x4f07, 0x00 },
	{ 0x4800, 0x00 },
	{ 0x5000, 0x9f },
	{ 0x5001, 0x00 },
	{ 0x5e00, 0x00 },
	{ 0x5d00, 0x07 },
	{ 0x5d01, 0x00 },
	{ OV9281_TABLE_END, 0x00}
};

static const ov9281_reg ov9281_mode_640x400_26MhzMCLK[] = {
	{ 0x0302, 0x32 },
	{ 0x030d, 0x50 },
	{ 0x030e, 0x02 },
	{ 0x3001, 0x00 },
	{ 0x3004, 0x00 },
	{ 0x3005, 0x00 },
	{ 0x3006, 0x04 },
	{ 0x3011, 0x0a },
	{ 0x3013, 0x18 },
	{ 0x3022, 0x01 },
	{ 0x3030, 0x10 },
	{ 0x3039, 0x32 },
	{ 0x303a, 0x00 },
	{ 0x3500, 0x00 },
	{ 0x3501, 0x01 },
	{ 0x3502, 0xf4 },
	{ 0x3503, 0x08 },
	{ 0x3505, 0x8c },
	{ 0x3507, 0x03 },
	{ 0x3508, 0x00 },
	{ 0x3509, 0x10 },
	{ 0x3610, 0x80 },
	{ 0x3611, 0xa0 },
	{ 0x3620, 0x6e },
	{ 0x3632, 0x56 },
	{ 0x3633, 0x78 },
	{ 0x3662, 0x05 },
	{ 0x3666, 0x00 },
	{ 0x366f, 0x5a },
	{ 0x3680, 0x84 },
	{ 0x3712, 0x80 },
	{ 0x372d, 0x22 },
	{ 0x3731, 0x80 },
	{ 0x3732, 0x30 },
	{ 0x3778, 0x10 },
	{ 0x377d, 0x22 },
	{ 0x3788, 0x02 },
	{ 0x3789, 0xa4 },
	{ 0x378a, 0x00 },
	{ 0x378b, 0x4a },
	{ 0x3799, 0x20 },
	{ 0x3800, 0x00 },
	{ 0x3801, 0x00 },
	{ 0x3802, 0x00 },
	{ 0x3803, 0x00 },
	{ 0x3804, 0x05 },
	{ 0x3805, 0x0f },
	{ 0x3806, 0x03 },
	{ 0x3807, 0x2f },
	{ 0x3808, 0x02 },
	{ 0x3809, 0x80 },
	{ 0x380a, 0x01 },
	{ 0x380b, 0x90 },
	{ 0x380c, 0x02 },
	{ 0x380d, 0xd8 },
	{ 0x380e, 0x02 },
	{ 0x380f, 0x08 },
	{ 0x3810, 0x00 },
	{ 0x3811, 0x04 },
	{ 0x3812, 0x00 },
	{ 0x3813, 0x04 },
	{ 0x3814, 0x31 },
	{ 0x3815, 0x22 },
	{ 0x3820, 0x20 },
	{ 0x3821, 0x01 },
	{ 0x3881, 0x42 },
	{ 0x38a8, 0x02 },
	{ 0x38a9, 0x80 },
	{ 0x38b1, 0x00 },
	{ 0x38c4, 0x00 },
	{ 0x38c5, 0xc0 },
	{ 0x38c6, 0x04 },
	{ 0x38c7, 0x80 },
	{ 0x3920, 0xff },
	{ 0x4003, 0x40 },
	{ 0x4008, 0x02 },
	{ 0x4009, 0x05 },
	{ 0x400c, 0x00 },
	{ 0x400d, 0x03 },
	{ 0x4010, 0x40 },
	{ 0x4043, 0x40 },
	{ 0x4307, 0x30 },
	{ 0x4317, 0x00 },
	{ 0x4501, 0x00 },
	{ 0x4507, 0x03 },
	{ 0x4509, 0x80 },
	{ 0x450a, 0x08 },
	{ 0x4601, 0x04 },
	{ 0x470f, 0x00 },
	{ 0x4f07, 0x00 },
	{ 0x4800, 0x00 },
	{ 0x5000, 0x9f },
	{ 0x5001, 0x00 },
	{ 0x5e00, 0x00 },
	{ 0x5d00, 0x07 },
	{ 0x5d01, 0x00 },
	{ OV9281_TABLE_END, 0x00 }
};

static const ov9281_reg *ov9281_mode_table[] = {
	[OV9281_MODE_1280X800] = ov9281_mode_1280x800_26MhzMCLK,
	[OV9281_MODE_1280X720] = ov9281_mode_1280x720_26MhzMCLK,
	[OV9281_MODE_640X400] = ov9281_mode_640x400_26MhzMCLK,
	[OV9281_MODE_START_STREAM] = ov9281_start,
	[OV9281_MODE_STOP_STREAM] = ov9281_stop,
};

static const ov9281_reg *ov9281_fsync_table[] = {
	[OV9281_FSYNC_NONE] = NULL,
	[OV9281_FSYNC_MASTER] = ov9281_fsync_master,
	[OV9281_FSYNC_SLAVE] = ov9281_fsync_slave,
};

static const int ov9281_120fps[] = {
	120,
};

static const struct camera_common_frmfmt ov9281_frmfmt[] = {
	{ { 1280, 800 }, ov9281_120fps, ARRAY_SIZE(ov9281_120fps), 0,
	  OV9281_MODE_1280X800 },
	{ { 1280, 720 }, ov9281_120fps, ARRAY_SIZE(ov9281_120fps), 0,
	  OV9281_MODE_1280X720 },
	{ { 640, 400 }, ov9281_120fps, ARRAY_SIZE(ov9281_120fps), 0,
	  OV9281_MODE_640X400 },
};

#endif  /* __OV9281_I2C_TABLES__ */
