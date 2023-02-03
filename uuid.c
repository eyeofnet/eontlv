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
#include <string.h>

#include "eontlv.h"

#define UUID_STR_LEN         36

static const uint8_t g_valid_chars[] = 
{0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x61,0x62,0x63,0x64,0x65,0x66}; 

static uint8_t tlv_convert_ascii_pair_to_byte(const char *v,int *err)
{
    uint8_t rv = 0;
    int i1;
    int i2;
    int chk = 0;
    char *cptr;
   
    cptr = strchr((const char *) g_valid_chars,v[0]);
    if (cptr) {
        i1 = cptr - (const char *) g_valid_chars;
        cptr = strchr((const char *) g_valid_chars,v[1]);
        if (cptr) {
            i2 = cptr - (const char *) g_valid_chars;
            if (i1 < 10) {
                rv = ((int) g_valid_chars[i1] - 0x30) << 4;
            } else {
                rv = ((int) g_valid_chars[i1] - 0x61 + 10) << 4;
            }
            if (i2 < 10) {
                rv |= g_valid_chars[i2] - 0x30;
            } else {
                rv |= g_valid_chars[i2] - 0x61 + 10;
            }
        } else {
            chk = EINVAL;
        }
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
    return rv;
}

static void tlv_convert_uuid_string_to_bytes(const char *str,uint8_t *buf,uint32_t buflen,int *err)
{
    int i;
    int chk = 0;
    int buf_idx = 0;
    char *cptr;
    uint8_t x;

    if (str && buf) {
        if ((UUID_STR_LEN != strlen(str)) || (buflen < UUID_LEN)) {
            chk = EINVAL;
            goto out;
        }

	/* first group (8 characters) */
        cptr = strchr(str,'-');
        if (!cptr) {
            chk = EINVAL;
	    goto out;
        }
        if (8 != (cptr - str)) {
            chk = EINVAL;
	    goto out;
        }
        while (str != cptr) {
            x = tlv_convert_ascii_pair_to_byte(str,&chk);
            if (0 != chk) {
                goto out;
	    }
            buf[buf_idx++] = x;
            str += 2;
        }
	++str;

	/* next three groups (4 characters) */
        for (i=0;i<3;i++) {
            cptr = strchr(str,'-');
            if (!cptr) {
                chk = EINVAL;
	        goto out;
            }
            if (4 != (cptr - str)) {
                chk = EINVAL;
	        goto out;
            }
            while (str != cptr) {
                x = tlv_convert_ascii_pair_to_byte(str,&chk);
                if (0 != chk) {
                    goto out;
	        }
                buf[buf_idx++] = x;
                str += 2;
            }
	    ++str;
	}

	/* last group (12 characters) */
        cptr = strchr(str,'\0');
        if (!cptr) {
            chk = EINVAL;
	    goto out;
        }
        if (12 != (cptr - str)) {
            chk = EINVAL;
	    goto out;
        }
        while (str != cptr) {
            x = tlv_convert_ascii_pair_to_byte(str,&chk);
            if (0 != chk) {
                goto out;
	    }
            buf[buf_idx++] = x;
            str += 2;
        }
    } else {
        chk = EINVAL;
    }
out:
    if (err) {
        *err = chk;
    }
}

void tlv_insert_uuid_string(tlv_t *tlv,const char *str,int *err)
{
    int chk = 0;
    if (tlv) {
        tlv_alloc_value(tlv,UUID_LEN,&chk);
        if (0 == chk) {
            tlv_convert_uuid_string_to_bytes(str,tlv->value,UUID_LEN,&chk); 
            if (0 == chk) {
                tlv->type = TLV_UUID;
            }    
        }
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
}

static const char g_chars[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

void tlv_extract_uuid_string(tlv_t *tlv,char *str,uint32_t strlen,int *err)
{
    int chk = 0;
    if (tlv && str && (strlen >= UUID_STR_LEN)) {
        if (tlv->type == TLV_UUID) { 
            int di = 0;
            int si = 0;
            int ci;
            for (di=0;di<UUID_LEN;di++) {
                ci = (tlv->value[di] & 0xf0) >> 4;
                str[si++] = g_chars[ci];
                ci = (tlv->value[di] & 0x0f);
                str[si++] = g_chars[ci];
		switch(si) {
                    case 8:
                    case 13:
                    case 18:
                    case 23:
                        str[si++] = '-';
		        break;
                    default:
                        break;
		}
            }
	    str[si++] = '\0';
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



