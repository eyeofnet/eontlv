#include <errno.h>
#include <string.h>

#include "eontlv.h"

void tlv_extract_utf8_string(tlv_t *tlv,uint8_t *str,uint32_t strlen,int *err)
{
    int chk = 0;
    if (tlv && str) {
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
}




