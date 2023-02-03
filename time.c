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


void tlv_insert_time(tlv_t *tlv,tlv_time_t *t,int *err)
{
    int chk = 0;

    if (tlv && t) {
        uint8_t *ptr ;

        tlv_alloc_value(tlv,0,&chk);
        if (0 == chk) {
            ptr = (uint8_t *) &(tlv->value);
	    *ptr++ = t->hour;
	    *ptr++ = t->minute;
	    *ptr++ = t->seconds;
	    *ptr = t->gmt_offset;
	    tlv->type = TLV_TIME;
            tlv->len = 4;
        }
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
}

void tlv_extract_time(tlv_t *tlv,tlv_time_t *t,int *err)
{
    int chk = 0;

    if (tlv && t) {
        if (TLV_TIME == tlv->type) {
            uint8_t *ptr = (uint8_t *) &(tlv->value);
            t->hour = *ptr++;
            t->minute = *ptr++;
            t->seconds = *ptr++;
            t->gmt_offset = *ptr++;
        } else {
            chk = TLV_ERR_INVALID_TYPE; 
        }
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
}


