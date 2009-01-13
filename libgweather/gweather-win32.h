/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* gweather-win32.h - Win32 portability
 *
 * Copyright 2008, Novell, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef __GWEATHER_WIN32_H__
#define __GWEATHER_WIN32_H__

G_BEGIN_DECLS

#ifdef G_OS_WIN32

#define localtime_r(t,tmp) (localtime (t) ? ((*tmp) = *localtime (t), tmp) : NULL)

#undef GNOMELOCALEDIR
#define GNOMELOCALEDIR _gweather_win32_get_locale_dir ()

#undef ZONEINFO_DIR
#define ZONEINFO_DIR _gweather_win32_get_zoneinfo_dir ()

char *_gweather_win32_get_locale_dir (void);
char *_gweather_win32_get_zoneinfo_dir (void);

#endif

G_END_DECLS

#endif /* __GWEATHER_WIN32_H__ */