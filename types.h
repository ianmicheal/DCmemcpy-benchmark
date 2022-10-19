/*
** Nofrendo (c) 1998-2000 Matthew Conte (matt@conte.com)
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of version 2 of the GNU Library General 
** Public License as published by the Free Software Foundation.
**
** This program is distributed in the hope that it will be useful, 
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
** Library General Public License for more details.  To obtain a 
** copy of the GNU Library General Public License, write to the Free 
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
**
**
** types.h
**
** Data type definitions
** types.h,v 1.3 2002/03/17 17:16:53 tekezo Exp
*/

/* 
** NesterDC by Ken Friece
** Any changes that I made to the original source, by Mathew Conte, are 
** marked with in the following way:
** KF DD/MM/YYYY <description of the change> 
*/

#ifndef _TYPES_H_
#define _TYPES_H_

/* Define this if running on little-endian (x86, Dreamcast) systems */
#define  HOST_LITTLE_ENDIAN

#ifndef __DREAMCAST__
/* These should be changed depending on the platform */
typedef unsigned long uint32; // KF 05/31/2001 changed the typedef for Dreamcast
typedef unsigned short uint16; // KF 05/31/2001 changed the typedef for Dreamcast
//typedef unsigned char uint8;
typedef signed long int32; // KF 05/31/2001 changed the typedef for Dreamcast
typedef signed short int16; // KF 05/31/2001 changed the typedef for Dreamcast
//typedef signed char int8; // KF 05/31/2001 changed the typedef for Dreamcast
#else
#include <kos.h>
#endif
typedef uint8 boolean;

#ifndef  TRUE
#define  TRUE     1
#endif
#ifndef  FALSE
#define  FALSE    0
#endif

#ifndef NULL
#define NULL 0
#endif

#endif /* _TYPES_H_ */


/*
** types.h,v
** Revision 1.3  2002/03/17 17:16:53  tekezo
** *** empty log message ***
**
** Revision 1.2  2002/01/29 19:14:37  tekezo
** *** empty log message ***
**
** Revision 1.1  2001/12/11 05:43:07  tekezo
** *** empty log message ***
**
** Revision 1.4  2001/09/23 10:53:54  tekezo
** now support SNSS
**
** Revision 1.3  2001/09/20 16:27:05  tekezo
** now pretty works on KOS
**
** Revision 1.2  2001/09/20 10:44:02  tekezo
** *** empty log message ***
**
** Revision 1.6  2000/06/09 15:12:25  matt
** initial revision
**
*/
