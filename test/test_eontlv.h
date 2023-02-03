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

#ifndef _TEST_EONTLV_H_20230125_
#define _TEST_EONTLV_H_20230125_

#include "eontest.h"


int test_date(test_node_t *rec);
int test_datetime(test_node_t *rec);
int test_int8(test_node_t *rec);
int test_int16(test_node_t *rec);
int test_int32(test_node_t *rec);
int test_time(test_node_t *rec);
int test_uint8(test_node_t *rec);
int test_uint16(test_node_t *rec);
int test_uint32(test_node_t *rec);
int test_uuid(test_node_t *rec);

#endif /* _TEST_EONTLV_H_20230125_ */


