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
#include <errno.h>
#include <string.h>

#include "eontlv.h"

void tlv_extract_cstr_string(tlv_t *tlv,char *str,uint32_t len,int *err)
{
    uint32_t i;
    int chk = 0;
    if (tlv && str) {
        if ((TLV_CSTR_STRING == tlv->type) && (len >= (tlv->len+1))) {
            for (i=0;i<(tlv->len+1);i++) {
	        str[i] = tlv->value[i];
	    }
	} else if (TLV_CSTR_STRING_FIRST == tlv->type) {
            uint32_t total_len = 0;
            tlv_t *ptr = tlv;
            while (ptr) {
                if (NULL == ptr->next) {
                    if (TLV_CSTR_STRING_LAST != ptr->type) {
                        chk = EINVAL;
                        goto out;
                    }
		} else if (total_len > 0) {
                    if (TLV_CSTR_STRING != ptr->type) {
                        chk = EINVAL;
                        goto out;
                    }
                }
                total_len += ptr->len;
                ptr = ptr->next;
            }
            if (len >= (total_len)) {
                uint32_t sidx = 0;
                ptr = tlv;
                while (ptr) {
                    for (i=0;i<ptr->len;i++,sidx++) {
	                str[sidx] = ptr->value[i];
	            }
                    ptr = ptr->next;
                }
                str[sidx] = '\0';
            } else {
                chk = ENOBUFS;
                goto out;
            }
        } else {
            chk = TLV_ERR_INVALID_TYPE;
        }
    } else {
        chk = EINVAL;
    }
out:
    if (err) {
        *err = chk;
    }
}




