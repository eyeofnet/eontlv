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

#include "eontlv.h"


/*
 * For numeric values 4 bytes or less in length, we don't allocate value, we use the pointer
 * as data space. This function lets us know to not free the value "pointer".
 */
int tlv_is_value_no_alloc(tlv_t *tlv)
{
    int rv = 0;

    if (tlv) {
        switch (tlv->type) {
            /* These all fall through */
            case TLV_INT8:
	    case TLV_UINT8:
	    case TLV_INT16_BE:
	    case TLV_UINT16_BE:
	    case TLV_INT32_BE: 
	    case TLV_UINT32_BE:
	    case TLV_INT16_LE:
	    case TLV_UINT16_LE:
	    case TLV_INT32_LE:
	    case TLV_UINT32_LE:
	    case TLV_DATE:
	    case TLV_TIME:
                rv = 1;
                break;
            default:
                break;
	}
    }
    return rv;
}


