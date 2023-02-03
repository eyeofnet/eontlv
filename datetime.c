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


void tlv_insert_datetime(tlv_t *tlv,tlv_datetime_t *dt,int *err)
{
    int chk = 0;

    if (tlv && dt) {
        uint8_t *ptr ;

        tlv_alloc_value(tlv,8,&chk);
	if (0 == chk) {
            ptr = tlv->value;
	    *ptr++ = (uint8_t) ((dt->date.year & 0xff00) >> 8);
	    *ptr++ = (uint8_t) (dt->date.year & 0x00ff);
	    *ptr++ = (uint8_t) (dt->date.month & 0xff);
	    *ptr++ = (uint8_t) (dt->date.day & 0xff);
	    *ptr++ = dt->time.hour;
	    *ptr++ = dt->time.minute;
	    *ptr++ = dt->time.seconds;
	    *ptr = dt->time.gmt_offset;
	    tlv->type = TLV_DATETIME;
        }
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
}

void tlv_extract_datetime(tlv_t *tlv,tlv_datetime_t *dt,int *err)
{
    int chk = 0;

    if (tlv && dt) {
        if (TLV_DATETIME == tlv->type) {
            uint8_t *ptr = tlv->value;
            dt->date.year = (uint16_t ) ((*ptr++) << 8);
            dt->date.year |= (uint16_t) *ptr++;
            dt->date.month = (uint8_t) *ptr++;
            dt->date.day = (uint8_t) *ptr++;
            dt->time.hour = (uint8_t) *ptr++;
            dt->time.minute = (uint8_t) *ptr++;
            dt->time.seconds = (uint8_t) *ptr++;
            dt->time.gmt_offset = (uint8_t) *ptr++;
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


