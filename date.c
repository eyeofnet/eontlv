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


void tlv_insert_date(tlv_t *tlv,tlv_date_t *d,int *err)
{
    int chk = 0;

    if (tlv && d) {
        uint8_t *ptr ;

        tlv_alloc_value(tlv,0,&chk);
        if (0 == chk) {
            ptr = (uint8_t *) &(tlv->value);
	    *ptr++ = (uint8_t) ((d->year & 0xff00) >> 8);
	    *ptr++ = (uint8_t) (d->year & 0x00ff);
	    *ptr++ = (uint8_t) (d->month & 0xff);
	    *ptr = (uint8_t) (d->day & 0xff);
	    tlv->type = TLV_DATE;
            tlv->len = 4;
        }
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
}

void tlv_extract_date(tlv_t *tlv,tlv_date_t *d,int *err)
{
    int chk = 0;

    if (tlv && d) {
        if (TLV_DATE == tlv->type) {
            uint8_t *ptr = (uint8_t *) &(tlv->value);
            d->year = (uint16_t ) ((*ptr++) << 8);
            d->year |= (uint16_t) *ptr++;
            d->month = (uint8_t) *ptr++;
            d->day = (uint8_t) *ptr++;
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


