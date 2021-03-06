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

#ifndef SC_GETOPT_H
#define SC_GETOPT_H

#include <sc.h>

#ifdef SC_PROVIDE_GETOPT
#ifdef _GETOPT_H
#error "getopt.h is included.  Include sc.h first or use --without-getopt".
#endif
#include "sc_builtin/getopt.h"
#else
#include <getopt.h>
#endif

#endif /* !SC_GETOPT_H */
