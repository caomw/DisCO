/*===========================================================================*
 * This file is part of the BiCePS Linear Integer Solver (BLIS).             *
 *                                                                           *
 * BLIS is distributed under the Eclipse Public License as part of the       *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *                                                                           *
 * Conceptual Design:                                                        *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *          Laszlo Ladanyi, IBM T.J. Watson Research Center                  *
 *          Matthew Saltzman, Clemson University                             *
 *                                                                           * 
 *                                                                           *
 * Copyright (C) 2001-2015, Lehigh University, Yan Xu, and Ted Ralphs.       *
 * All Rights Reserved.                                                      *
 *===========================================================================*/

#include "DcoMessage.hpp"
#include <cstring>

//#############################################################################

typedef struct {
    DISCO_Message internalNumber;
    int externalNumber;              // or continuation
    char detail;
    const char * message;
} Dco_message;

//#############################################################################

static Dco_message us_english[]=
{
    {DISCO_CUTOFF_INC, 43, 1, "Objective coefficients are multiples of %g"},
    {DISCO_CUT_STAT_FINAL, 53, 1, "Called %s cut generator %d times, generated %d cuts, CPU time %.4f seconds, current strategy %d"},
    {DISCO_CUT_STAT_NODE, 55, 1, "Node %d, called %s cut generator %d times, generated %d cuts, CPU time %.4f seconds, current strategy %d"},
    {DISCO_GAP_NO, 57, 1, "Relative optimality gap is infinity because no solution was found"},
    {DISCO_GAP_YES, 58, 1, "Relative optimality gap is %.2f%%"},
    {DISCO_HEUR_BEFORE_ROOT, 60, 1, "%s heuristic found a solution; quality is %g"},
    {DISCO_HEUR_STAT_FINAL, 63, 1, "Called %s heuristic %d times, found %d solutions, CPU time %.4f seconds, current strategy %d"},
    {DISCO_HEUR_STAT_NODE, 65, 1, "Node %d, called %s heuristic %d times, found %d solutions, CPU time %.4f seconds, current strategy %d"},
    {DISCO_ROOT_PROCESS, 30, 1, "Processing the root node (%d rows, %d columns)"},
    {DISCO_ROOT_TIME, 35, 1, "Processing the first root relaxation took CPU time %.4f seconds"},
    {DISCO_W_LP, 20, 1, "WARNING: The Problem does not have integer variables"},
    {DISCO_DUMMY_END, 999999, 0, ""}
};

//#############################################################################

/* Constructor */
DcoMessage::DcoMessage(Language language) 
    :
    CoinMessages(sizeof(us_english) / sizeof(Dco_message))
{
    language_ = language;
    strcpy(source_, "Dco");
    Dco_message * message = us_english;

    while (message->internalNumber != DISCO_DUMMY_END) {
	CoinOneMessage oneMessage(message->externalNumber, message->detail,
				  message->message);
	addMessage(message->internalNumber, oneMessage);
	message++;
    }

    // now override any language ones

    switch (language) {

    default:
	message = NULL;
	break;
    }

    // replace if any found
    if (message) {
	while (message->internalNumber != DISCO_DUMMY_END) {
	    replaceMessage(message->internalNumber, message->message);
	    message++;
	}
    }
}