/**
 * File name: bitfield-io.h
 * Project name: bitfield, a bit array manipulation library written in C
 * URL: https://github.com/ciubotaru/bitfield
 * Author: Vitalie Ciubotaru <vitalie at ciubotaru dot tk>
 * License: General Public License, version 3 or later
 * Copyright 2016
**/

#include <stdint.h>

#ifndef HAVE_BITFIELD_IO_H
#define HAVE_BITFIELD_IO_H
#ifndef HAVE_BITFIELD_H
#include <bitfield.h>
#endif

int bfwrite(const struct bitfield *input, const char *filename, char **errmsg);  /* write a bitfield to file */

struct bitfield *bfread(const char *filename, char **errmsg);  /* write a bitfield to file */

#endif
