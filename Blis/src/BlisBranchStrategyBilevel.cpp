/*===========================================================================*
 * This file is part of the BiCePS Linear Integer Solver (BLIS).             *
 *                                                                           *
 * BLIS is distributed under the Common Public License as part of the        *
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
 * Copyright (C) 2001-2009, Lehigh University, Yan Xu, and Ted Ralphs.       *
 * All Rights Reserved.                                                      *
 *===========================================================================*/

#include <algorithm>
#include <vector>

#include "CoinHelperFunctions.hpp"
#include "CoinSort.hpp"

#include "BlisBranchStrategyBilevel.h"
#include "BlisBranchObjectBilevel.h"

class doubleIntCompare {
public:
  /// Compare function
  inline bool operator()(const std::pair<double, int>& t1,
			 const std::pair<double, int>& t2) const
  { return t1.first < t2.first; }
};

//#############################################################################

// Copy constructor 
BlisBranchStrategyBilevel::BlisBranchStrategyBilevel (
    const BlisBranchStrategyBilevel & rhs)
    : BcpsBranchStrategy()
{
    bestChangeUp_ = rhs.bestChangeUp_;
    bestNumberUp_ = rhs.bestNumberUp_;
    bestChangeDown_ = rhs.bestChangeDown_;
    bestNumberDown_ = rhs.bestNumberDown_;
}

//#############################################################################

/** Create a set of candidate branching objects. */
int 
BlisBranchStrategyBilevel::createCandBranchObjects(int numPassesLeft)
{
    int i(0);
    std::deque<int> branchingSet;

    BlisModel *model = dynamic_cast<BlisModel *>(model_);
    OsiSolverInterface *solver = model->solver();

    int numCols = model->getNumCols();
    
    const double *redCosts = solver->getReducedCost();
    
    //Copied from CoinSort_2, which doesn;t seem to work for this case.

    std::vector< std::pair<double, int> > sortedRedCosts;

    for (i = 0; i < numCols; i++){
	sortedRedCosts.push_back(std::pair<double, int>(redCosts[i], i));
    }

    std::sort(sortedRedCosts.begin(), sortedRedCosts.end(), doubleIntCompare());
    
    // Start fixing variables to zero one by one until the threshold is 
    // exceeded

    double objVal;
    for (i = 0; i < numCols; i++){
	branchingSet.push_back(sortedRedCosts[i].second);
	solver->setColBounds(sortedRedCosts[i].second, 0.0, 0.0);
	solver->resolve();
	objVal = solver->getObjValue();
    }
    
    numBranchObjects_ = 1;
    branchObjects_ = new BcpsBranchObject* [1];
    branchObjects_[0] = new BlisBranchObjectBilevel(model_, branchingSet);
    
    return 0;
}

//#############################################################################

/** Compare branching object thisOne to bestSoFar. If thisOne is better 
    than bestObject, return branching direction(1 or -1), otherwise
    return 0. 
    If bestSoFar is NULL, then always return branching direction(1 or -1).
    This should not be called for this class.
*/
int
BlisBranchStrategyBilevel::betterBranchObject(BcpsBranchObject * thisOne,
					     BcpsBranchObject * bestSoFar)
{
    return 0;
}

//#############################################################################
