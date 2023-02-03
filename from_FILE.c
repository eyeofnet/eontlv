/***************************************************************************
 *  EONTLV is a C-language library that provides access to 
 *  TLV (type, length, value) structures.
 *  Copyright (C) 2023 Winslow Williams 
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <errno.h>
#include <stdlib.h>
#include "eontlv.h"


tlv_t *tlv_from_FILE(FILE *fptr,int *err)
{
    tlv_t *rv = NULL;
    int error = 0;
    int buf_idx = 0;
    uint8_t buf[4];
    uint32_t typ;
    uint32_t len;
    size_t bytes_read;

    bytes_read = fread(buf,1,sizeof(buf),fptr);
    if (sizeof(buf) != bytes_read) {
        error = errno;
	goto set_error;
    }

    typ = (buf[buf_idx++] << 8);
    typ |= buf[buf_idx++];

    len = (buf[buf_idx++] << 8);
    len |= buf[buf_idx++];

    rv = create_tlv();
    if (rv) {
        rv->type = typ;
	if (len > 0) {
            rv->value = calloc(1,len);
            if (rv->value) {
                bytes_read = fread(rv->value,1,len,fptr);
                if (bytes_read == len) { 
                    rv->len = len;
                } else {
                    error = errno;
		}
            } else {
                error = ENOMEM;
            }
        }
    } else {
        error = ENOMEM;
    }
set_error:
    if (err) {
        *err = error;
    }
    return rv;
}


