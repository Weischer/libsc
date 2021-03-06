/*
  This file is part of the SC Library.
  The SC Library provides support for parallel scientific applications.

  Copyright (C) 2010 The University of Texas System

  The SC Library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  The SC Library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with the SC Library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
*/

#include "boat.h"
#include "vehicle.h"

const char         *boat_type = "boat";

static int
is_type_fn (sc_object_t * o, sc_object_t * m, const char *type)
{
  SC_LDEBUG ("boat is_type\n");

  return !strcmp (type, boat_type) || !strcmp (type, vehicle_type);
}

static void
copy_fn (sc_object_t * o, sc_object_t * m, sc_object_t * c)
{
  const Boat         *boat_o = boat_get_data (o);
  Boat               *boat_c = boat_register_data (c);

  SC_LDEBUG ("boat copy\n");

  memcpy (boat_c, boat_o, sizeof (Boat));
}

static void
initialize_fn (sc_object_t * o, sc_object_t * m, sc_keyvalue_t * args)
{
  Boat               *boat = boat_register_data (o);

  SC_LDEBUG ("boat initialize\n");

  boat->speed = 0;
  boat->name = "<undefined>";

  if (args != NULL) {
    boat->name = sc_keyvalue_get_string (args, "name", NULL);
    SC_ASSERT (boat->name != NULL);
  }
}

static void
write_fn (sc_object_t * o, sc_object_t * m, FILE * out)
{
  Boat               *boat = boat_get_data (o);

  fprintf (out, "Boat \"%s\" speeds at %f km/h\n", boat->name, boat->speed);
}

static void
accelerate_fn (sc_object_t * o, sc_object_t * m)
{
  Boat               *boat = boat_get_data (o);

  SC_LDEBUG ("boat accelerate\n");

  boat->speed += 6;
}

sc_object_t        *
boat_klass_new (sc_object_t * d)
{
  int                 a1, a2, a3, a4, a5;
  sc_object_t        *o;

  SC_ASSERT (d != NULL);
  SC_ASSERT (sc_object_is_type (d, sc_object_type));

  o = sc_object_alloc ();
  sc_object_delegate_push (o, d);

  a1 = sc_object_method_register (o, (sc_object_method_t) sc_object_is_type,
                                  (sc_object_method_t) is_type_fn);
  a2 = sc_object_method_register (o, (sc_object_method_t) sc_object_copy,
                                  (sc_object_method_t) copy_fn);
  a3 =
    sc_object_method_register (o, (sc_object_method_t) sc_object_initialize,
                               (sc_object_method_t) initialize_fn);
  a4 =
    sc_object_method_register (o, (sc_object_method_t) sc_object_write,
                               (sc_object_method_t) write_fn);
  a5 =
    sc_object_method_register (o, (sc_object_method_t) vehicle_accelerate,
                               (sc_object_method_t) accelerate_fn);
  SC_ASSERT (a1 && a2 && a3 && a4 && a5);

  sc_object_initialize (o, NULL);

  return o;
}

sc_object_t        *
boat_new (sc_object_t * d, const char *name)
{
  return sc_object_new_from_klassf (d, "s:name", name, NULL);
}

Boat               *
boat_register_data (sc_object_t * o)
{
  SC_ASSERT (sc_object_is_type (o, boat_type));

  return (Boat *) sc_object_data_register (o, (sc_object_method_t)
                                           boat_get_data, sizeof (Boat));
}

Boat               *
boat_get_data (sc_object_t * o)
{
  SC_ASSERT (sc_object_is_type (o, boat_type));

  return (Boat *) sc_object_data_lookup (o, (sc_object_method_t)
                                         boat_get_data);
}
