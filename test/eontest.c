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

#include <stdlib.h>
#include <string.h>

#include "eontest.h"



test_node_t *create_test_node(void)
{
    test_node_t *rv;

    rv = calloc(1,sizeof(test_node_t));
    return rv;
}

void destroy_test_node(test_node_t *v)
{
    if (v) {
        if (v->name) {
            free(v->name);
        }
        free(v);
    }
}

void test_node_set_name(test_node_t *nd,const char *name)
{
   if (nd) {
       if (nd->name) {
           free(nd->name);
       }
       nd->name = strdup(name);
   }
}
