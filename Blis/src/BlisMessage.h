/*===========================================================================*
 * This file is part of the BiCePS Linear Integer Solver (BLIS).             *
 *                                                                           *
 * BLIS is distributed under the Common Public License as part of the        *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors: Yan Xu, SAS Institute Inc.                                       *
 *          Ted Ralphs, Lehigh University                                    *
 *          Laszlo Ladanyi, IBM T.J. Watson Research Center                  *
 *          Matthew Saltzman, Clemson University                             *
 *                                                                           * 
 *                                                                           *
 * Copyright (C) 2001-2006, Lehigh University, Yan Xu, and Ted Ralphs.       *
 * All Rights Reserved.                                                      *
 *===========================================================================*/

#ifndef BlisMessage_H_
#define BlisMessage_H_

//#############################################################################
// This file is modified from SbbMessage.hpp
//#############################################################################

#if defined(_MSC_VER)
// Turn off compiler warning about long names
#  pragma warning(disable:4786)
#endif

/** This deals with Blis messages. */
#include "CoinMessageHandler.hpp"

enum BLIS_Message
{
    BLIS_S_VERSION,
    BLIS_PEAK_MEMORY,
    BLIS_DUMMY_END
};

class BlisMessage : public CoinMessages {

public:
    
    /**@name Constructors etc */
    //@{
    /** Constructor */
    BlisMessage(Language language=us_en);
    //@}
    
};

#endif
