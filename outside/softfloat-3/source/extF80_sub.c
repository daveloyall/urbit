
/*============================================================================

This C source file is part of the SoftFloat IEEE Floating-Point Arithmetic
Package, Release 3, by John R. Hauser.

Copyright 2011, 2012, 2013, 2014 The Regents of the University of California
(Regents).  All Rights Reserved.  Redistribution and use in source and binary
forms, with or without modification, are permitted provided that the following
conditions are met:

Redistributions of source code must retain the above copyright notice,
this list of conditions, and the following two paragraphs of disclaimer.
Redistributions in binary form must reproduce the above copyright notice,
this list of conditions, and the following two paragraphs of disclaimer in the
documentation and/or other materials provided with the distribution.  Neither
the name of the Regents nor the names of its contributors may be used to
endorse or promote products derived from this software without specific prior
written permission.

IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING
OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS
BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED
HEREUNDER IS PROVIDED "AS IS".  REGENTS HAS NO OBLIGATION TO PROVIDE
MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

=============================================================================*/

#include <stdbool.h>
#include <stdint.h>
#include "platform.h"
#include "internals.h"
#include "softfloat.h"

extFloat80_t extF80_sub( extFloat80_t a, extFloat80_t b )
{
    union { struct extFloat80M s; extFloat80_t f; } uA;
    uint_fast16_t uiA64;
    uint_fast64_t uiA0;
    bool signA;
    union { struct extFloat80M s; extFloat80_t f; } uB;
    uint_fast16_t uiB64;
    uint_fast64_t uiB0;
    bool signB;
#if ! defined INLINE_LEVEL || (INLINE_LEVEL < 2)
    extFloat80_t
        (*magsFuncPtr)(
            uint_fast16_t, uint_fast64_t, uint_fast16_t, uint_fast64_t, bool );
#endif

    uA.f = a;
    uiA64 = uA.s.signExp;
    uiA0  = uA.s.signif;
    signA = signExtF80UI64( uiA64 );
    uB.f = b;
    uiB64 = uB.s.signExp;
    uiB0  = uB.s.signif;
    signB = signExtF80UI64( uiB64 );
#if defined INLINE_LEVEL && (2 <= INLINE_LEVEL)
    if ( signA == signB ) {
        return softfloat_subMagsExtF80( uiA64, uiA0, uiB64, uiB0, signA );
    } else {
        return softfloat_addMagsExtF80( uiA64, uiA0, uiB64, uiB0, signA );
    }
#else
    magsFuncPtr =
        (signA == signB) ? softfloat_subMagsExtF80 : softfloat_addMagsExtF80;
    return (*magsFuncPtr)( uiA64, uiA0, uiB64, uiB0, signA );
#endif

}

