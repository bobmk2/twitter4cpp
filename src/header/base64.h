/* base64.h -- Encode binary data using printable characters.
   Copyright (C) 2004, 2005, 2006 Free Software Foundation, Inc.
   Written by Simon Josefsson.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

#ifndef BASE64_H
# define BASE64_H

/* Get size_t. */
# include <stddef.h>

/* Get bool. */
# include <stdbool.h>


/* Get malloc. */
#include <stdlib.h>

/* Get UCHAR_MAX. */
#include <limits.h>


/* This uses that the expression (n+(k-1))/k means the smallest
   integer >= n/k, i.e., the ceiling of n/k.  */
# define BASE64_LENGTH(inlen) ((((inlen) + 2) / 3) * 4)

bool isbase64 (char ch);

static inline unsigned char to_uchar (char ch){ return ch;}

void base64_encode (const char* in, size_t inlen,
			   char* out, size_t outlen){
	  static const char b64str[65] =
	    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	  while (inlen && outlen)
	    {
	      *out++ = b64str[(to_uchar (in[0]) >> 2) & 0x3f];
	      if (!--outlen)
		break;
	      *out++ = b64str[((to_uchar (in[0]) << 4)
			       + (--inlen ? to_uchar (in[1]) >> 4 : 0))
			      & 0x3f];
	      if (!--outlen)
		break;
	      *out++ =
		(inlen
		 ? b64str[((to_uchar (in[1]) << 2)
			   + (--inlen ? to_uchar (in[2]) >> 6 : 0))
			  & 0x3f]
		 : '=');
	      if (!--outlen)
		break;
	      *out++ = inlen ? b64str[to_uchar (in[2]) & 0x3f] : '=';
	      if (!--outlen)
		break;
	      if (inlen)
		inlen--;
	      if (inlen)
		in += 3;
	    }

	  if (outlen)
	    *out = '\0';
	}

#endif /* BASE64_H */
