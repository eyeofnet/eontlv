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


tlv_t *create_tlv(void)
{
    tlv_t *rv = calloc(1,sizeof(tlv_t));
    return rv;
}

void tlv_free_value(tlv_t *tlv,int *err)
{
    int chk = 0;
    if (tlv) {
        if (tlv->value && !tlv_is_value_no_alloc(tlv)) {
            free(tlv->value);
	}
        tlv->value = NULL;
        tlv->len = 0;
	tlv->type = TLV_NULL;
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
}

void destroy_tlv(tlv_t *tlv)
{
    if (tlv) {
        tlv_free_value(tlv,NULL);
        free(tlv);
    }
}

