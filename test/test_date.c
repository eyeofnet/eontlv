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
#include <string.h>
#include <time.h>
#include "eontlv.h"
#include "test_eontlv.h"


int test_date(test_node_t *rec)
{
    int rv = 0;
    int err;
    int line;
    int line_number_idx = 0;
    tlv_t *tlv;

    if (!rec) {
        rv = EINVAL;
        goto out;
    }
    test_node_set_name(rec,__func__);

    tlv = create_tlv();
    if (tlv) {
        time_t tt;
	struct tm ttm;
        tlv_date_t iv;
        tlv_date_t ev;

        memset(&ev,0,sizeof(ev));
        memset(&iv,0,sizeof(iv));
	tt = time(NULL);
        localtime_r(&tt,&ttm);
	iv.year = ttm.tm_year + 1900;
	iv.month = ttm.tm_mon + 1;
	iv.day = ttm.tm_mday;
        tlv_insert_date(tlv,&iv,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tlv_extract_date(tlv,&ev,&err);
        line = __LINE__ + 1;
        if (iv.year == ev.year) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }
        line = __LINE__ + 1;
        if (iv.month == ev.month) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }
        line = __LINE__ + 1;
        if (iv.day == ev.day) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }
        destroy_tlv(tlv);
    } else {
        rv = ENOMEM; 
    }
out:
    return rv;
}


