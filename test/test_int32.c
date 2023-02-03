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
#include "eontlv.h"
#include "test_eontlv.h"

int test_int32(test_node_t *rec)
{
    int rv = 0;
    int err;
    int line;
    int test_value_idx = 0;
    int line_number_idx = 0;
    int32_t chk;
    int32_t test_values[] = {-2147483648,-80000000,-7654321,-1999999,-100000,-1,1,100000,1999999,7654321,200000000,2147483647};
    tlv_t *tlv;

    if (!rec) {
        rv = EINVAL;
        goto out;
    }

    test_node_set_name(rec,__func__);

    tlv = create_tlv();
    if (tlv) {
        for (test_value_idx=0;test_value_idx<(sizeof(test_values)/sizeof(int32_t));test_value_idx++) {
            tlv_insert_int32(tlv,test_values[test_value_idx],&err); 
            if (err) {
                rv = err;
                goto out;
	    }
            chk = tlv_extract_int32(tlv,&err);
	    line = __LINE__ - 1;
            if (err) {
                rv = err;
                goto out;
	    }
            if (test_values[test_value_idx] == chk) {
                ++(rec->passed_test_count);
	    } else {
                ++(rec->failed_test_count);
                if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                    rec->failed_test_lines[line_number_idx++] = line;
                }
            }
        }
        destroy_tlv(tlv);
    } else {
        rv = ENOMEM; 
    }
out:
    return rv;
}

