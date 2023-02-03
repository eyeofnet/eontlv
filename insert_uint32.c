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


void tlv_insert_uint32(tlv_t *tlv,uint32_t v,int *err)
{
    int chk = 0;

    if (tlv) {
        uint8_t *ptr ;
        tlv_alloc_value(tlv,0,&chk);
	if (0 == chk) {
            ptr = (uint8_t *) &(tlv->value);
	    *ptr++ = (uint8_t) ((v & 0xff000000) >> 24);
	    *ptr++ = (uint8_t) ((v & 0x00ff0000) >> 16);
	    *ptr++ = (uint8_t) ((v & 0xff00ff00) >> 8);
	    *ptr = (uint8_t) (v & 0x000000ff);
	    tlv->type = TLV_UINT32_BE;
            tlv->len = 4;
        }
    } else {
        chk = EINVAL;        
    }
    if (err) {
        *err = chk;
    }
}


