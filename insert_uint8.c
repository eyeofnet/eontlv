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


void tlv_insert_uint8(tlv_t *tlv,uint8_t v,int *err)
{
    int chk = 0;

    if (tlv) {
        uint8_t *ptr ;
        tlv_alloc_value(tlv,0,&chk);
	if (0 == chk) {
            ptr = (uint8_t *) &(tlv->value);
	    *ptr = v;
	    tlv->type = TLV_UINT8;
            tlv->len = 1;
            tlv_set_free_value_flag(tlv,0);
        }
    } else {
        chk = EINVAL;        
    }
    if (err) {
        *err = chk;
    }
}


