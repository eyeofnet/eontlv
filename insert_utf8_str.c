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

void tlv_insert_utf8_string(tlv_t *tlv,const uint8_t *str,uint32_t len,int *err)
{
    int chk = 0;
    if (tlv && str) {
        uint32_t i;
        tlv_t *tail;
        tlv_t *new_tlv;
        if (len < 0x00010000) {
            tlv_alloc_value(tlv,len,&chk);
            if (0 == chk) {
                for (i=0;i<len;i++) {
                    tlv->value[i] = *str++;
                }
                tlv->type = TLV_UTF8_STRING;
                tlv->next = NULL;
            } else {
                goto out;
            }
        } else {
            uint32_t chunk_len = 0x0000ffff;
            tlv_alloc_value(tlv,chunk_len,&chk);
            if (0 == chk) {
                uint32_t i;
                for (i=0;i<chunk_len;i++) {
                    tlv->value[i] = (uint8_t) *str++;
                }
                tlv->type = TLV_UTF8_STRING_FIRST;
                tail = tlv;
            } else {
                goto out;
            }
            len -= chunk_len;
            while (len >= 0x00010000) {
                new_tlv = create_tlv();
                if (new_tlv) {
                    tlv_alloc_value(new_tlv,chunk_len,&chk);
                    if (0 == chk) {
                        uint32_t i;
                        for (i=0;i<chunk_len;i++) {
                            new_tlv->value[i] = (uint8_t) *str++;
                        }
                    } else {
                        goto out;
                    }
                    len -= chunk_len;
                    if (0 == len) {
                        new_tlv->type = TLV_UTF8_STRING_LAST;
                    } else {
                        new_tlv->type = TLV_UTF8_STRING;
                    }
                    tail->next = new_tlv;
                    tail = new_tlv;
		} else {
                    chk = ENOMEM;
                    goto destroy_chain;
                }
            }
            if (len > 0) {
                uint32_t chunk_len = len;
                new_tlv = create_tlv();
                if (new_tlv) {
                    tlv_alloc_value(new_tlv,chunk_len,&chk);
                    if (0 == chk) {
                        uint32_t i;
                        for (i=0;i<chunk_len;i++) {
                            new_tlv->value[i] = (uint8_t) *str++;
                        }
                        new_tlv->type = TLV_UTF8_STRING_LAST;
                        tail->next = new_tlv;
                    }
                } else {
                    chk = ENOMEM;
                    goto destroy_chain;
                }
            }
        }
        goto out;
    } else {
        chk = EINVAL;
    }
destroy_chain:
    destroy_tlv_list(tlv->next);
out:
    if (err) {
        *err = chk;
    }
}

