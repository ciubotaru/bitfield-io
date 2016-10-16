/**
 * File name: bitfield-io.c
 * Project name: bitfield, a bit array manipulation library written in C
 * URL: https://github.com/ciubotaru/bitfield
 * Author: Vitalie Ciubotaru <vitalie at ciubotaru dot tk>
 * License: General Public License, version 3 or later
 * Copyright 2016
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <endian.h>
#include <bitfield.h>
#include "bitfield-io.h"
#include "bitfield-io-internals.h"

int bfwrite(const struct bitfield *input, const char *filename, char **errmsg)
{
	int retcode = 0;
	char *msg;
	if (strlen(filename) > NAME_MAX) {
		msg = "Filename is too long";
		retcode = 0;
		goto error;
	}

	FILE *outfile;
	outfile = fopen(filename, "wb+");

	uint16_t size = htole16((uint16_t) bfsize(input));
	if (bfsize(input) > UINT_MAX) {
		msg = "Bit array is too long";
		retcode = 0;
		fclose(outfile);
		goto error;
	}
	int written = 0;
	/* write size into the first 16 bit */
	written += fwrite(&size, 1, 2, outfile);
	/* write bit array */
	int chars = (size - 1) / 8 + 1;
	fseek(outfile, 0, SEEK_CUR);
	written += fwrite(input->field, 1, chars, outfile);
	fclose(outfile);

	return written;
 error:
	if (errmsg) {
		*errmsg = malloc(strlen(msg) + 1);
		memcpy(*errmsg, msg, strlen(msg) + 1);
	}
	return retcode;
}

struct bitfield *bfread(const char *filename, char **errmsg)
{
	char *msg;
	FILE *infile;
	infile = fopen(filename, "r");
	if (infile == NULL) {
		msg = "Could not open file";
		fclose(infile);
		goto error;
	}
	uint16_t size = 0;
	int read = 0;
	read = fread(&size, 1, 2, infile);
	if (read != 2) {
		msg = "Could not read file";
		fclose(infile);
		goto error;
	}
	struct bitfield *output = bfnew((int) le16toh(size));
	int chars = (size - 1) / 8 + 1;
	read = fread(output->field, 1, chars, infile);
	if (read != chars) {
		msg = "Could not read file";
		fclose(infile);
		goto error;
	}
	fclose(infile);
	return output;
 error:
	if (errmsg) {
		*errmsg = malloc(strlen(msg) + 1);
		memcpy(*errmsg, msg, strlen(msg) + 1);
	}
	return NULL;
}
