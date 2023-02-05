#include <errno.h>
#include <string.h>

#include "eontlv.h"

void tlv_extract_cstr_string(tlv_t *tlv,char *str,uint32_t strlen,int *err)
{
    uint32_t i;
    int chk = 0;
    if (tlv && str) {
        if ((TLV_CSTR_STRING == tlv->type) && (strlen >= (tlv->len+1))) {
            for (i=0;i<(tlv->len+1);i++) {
	        str[i] = tlv->value[i];
	    }
	} else if (TLV_CSTR_STRING_FIRST == tlv->type) {
            uint32_t total_len = 0;
            tlv_t *ptr = tlv;
            while (ptr) {
                if (NULL == ptr->next) {
                    if (TLV_CSTR_STRING_LAST != tlv->type) {
                        chk = EINVAL;
                        goto out;
                    }
		} else if (total_len > 0) {
                    if (TLV_CSTR_STRING != tlv->type) {
                        chk = EINVAL;
                        goto out;
                    }
                }
                total_len += ptr->len;
                ptr = ptr->next;
            }
            if (strlen >= (total_len+1)) {
                uint32_t sidx;
                ptr = tlv;
                while (ptr) {
                    for (i=0,sidx=0;i<ptr->len;i++,sidx++) {
	                str[sidx] = tlv->value[i];
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




