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

#include "eontlv.h"


void tlv_to_buffer(tlv_t *tlv,uint8_t *buf,uint32_t buflen,int *err)
{
    int rv = 0;
    if (tlv && buf) {
        int buf_idx = 0;
        int tlv_idx = 0;
        if (buflen >= (tlv->len + 4)) {
            buf[buf_idx++] = ((tlv->type & 0xff00) >> 8);
            buf[buf_idx++] = (tlv->type & 0x00ff);
            buf[buf_idx++] = ((tlv->len & 0xff00) >> 8);
            buf[buf_idx++] = (tlv->len & 0x00ff);
	    for (tlv_idx=0;tlv_idx<tlv->len;tlv_idx++) {
                buf[buf_idx++] = tlv->value[tlv_idx];
	    }
	} else {
            rv = ENOBUFS;
        }
    } else {
        rv = EINVAL;
    }
    if (err) {
        *err = rv;
    }
}


