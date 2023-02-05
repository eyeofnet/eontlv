#include <errno.h>
#include <string.h>

#include "eontlv.h"

void tlv_insert_utf8_string(tlv_t *tlv,const uint8_t *str,int *err)
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

