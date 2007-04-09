/*===========================================================================*
 * This file is part of a solver for the Vehicle Routing Problem             *
 * developed using the BiCePS Linear Integer Solver (BLIS).                  *
 *                                                                           *
 * This solver is distributed under the Common Public License as part of     * 
 * the COIN-OR repository (http://www.coin-or.org).                          *
 *                                                                           *
 * Authors: Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *                                                                           *
 * Copyright (C) 2007 Yan Xu and Ted Ralphs.                                 *
 * All Rights Reserved.                                                      *
 *===========================================================================*/

#ifndef VrpSolution_h_
#define VrpSolution_h_

#include "Alps.h"
#include "BlisSolution.h"

//#############################################################################
/** This class contains a vrp solution */
//#############################################################################

class VrpSolution : public BlisSolution {

protected:

public:
    
    /** Default constructor. */
    VrpSolution() 
	: 
	BlisSolution()
	{}

    /** Useful constructor. */
    VrpSolution(int s, const double *values, double objValue)
	:
	BlisSolution(s, values, objValue)
	{}

    /** Destructor. */
    virtual ~VrpSolution() { }
    
    /** Print the solution.*/
    virtual void print(std::ostream& os) const {};
    
    /** The method that encodes the solution into a encoded object. */
    virtual AlpsEncoded* encode() const {
	//AlpsEncoded* encoded = new AlpsEncoded("ALPS_SOLUTION");
	//encodeBcps(encoded);
	// Nothing to do for Vrp part.
	return encoded;
    }
  
    /** The method that decodes the solution from a encoded object. */
    virtual AlpsKnowledge* decode(AlpsEncoded& encoded) const {
	//VrpSolution * sol = new VrpSolution();
	//sol->decodeBcps(encoded);
	return sol;
    }
    
};

//#############################################################################
//#############################################################################

#endif