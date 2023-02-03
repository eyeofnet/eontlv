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

const char *g_error_msgs[] = 
{
    "Unknown TLV error",
    "Invalid TLV type",
};

int tlv_is_valid_error_code(int code)
{
    int rv = 0;
    if ((code > TLV_ERR_BASE) && (code <= TLV_ERR_LAST_ERROR)) {
        rv = 1;
    }
    return rv;
}

const char *tlv_get_error_string(int code)
{
    const char *rv = g_error_msgs[0];
    if (tlv_is_valid_error_code(code)) {
        rv = g_error_msgs[code - TLV_ERR_BASE];
    }
    return rv;
}



