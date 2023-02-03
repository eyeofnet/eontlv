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



int32_t tlv_extract_int32(tlv_t *tlv,int *err)
{
    int32_t rv = 0;
    int error = 0;

    if (tlv) {
        uint8_t *ptr = (uint8_t *) &(tlv->value);
        if (TLV_INT32_BE == tlv->type) {
            rv = ((int32_t) *ptr++) << 24;
            rv |= ((int32_t) *ptr++) << 16;
            rv |= ((int32_t) *ptr++) << 8;
            rv |= (int32_t) *ptr;
        } else if (TLV_INT32_LE == tlv->type) {
            rv = (int32_t) *ptr++;
            rv |= ((int32_t) *ptr) << 8;
            rv |= ((int32_t) *ptr) << 16;
            rv |= ((int32_t) *ptr) << 24;
	} else {
            error = TLV_ERR_INVALID_TYPE; 
        }
    } else {
        error = EINVAL;
    }
    if (err) {
        *err = error;
    }
    return rv;
}


