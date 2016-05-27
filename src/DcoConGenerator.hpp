#ifndef DcoConGenerator_hpp_
#define DcoConGenerator_hpp_

#include "Dco.hpp"
#include <string>
#include <BcpsObjectPool.h>

/*!
   DcoConGenerator is an Abstract Base Class (ABC) for generating constraints.
   It provides an interface for constraint generation.
*/

class DcoModel;

class DcoConGeneratorStats {
  /// Number of constraints generated by this generator.
  int numConsGenerated_;
  /// Number of constraints that are actually used out of the generated.
  int numConsUsed_;
  /// CPU/User time this generator consumed.
  double time_;
  /// Number of times this generator is called.
  int numCalls_;
  /// Number of times this generator is called and did not yield any cuts.
  int numNoConsCalls_;
public:
  /// Default constructor
  DcoConGeneratorStats() { reset(); }
  // notes(aykut) No need to define copy constructor and copy assignment
  // operator, default values givenby the compiler will be enough since
  // this is a simple class.

  ///@name Get Statistics
  //@{
  /// Get number of constraints generated by this generator.
  int numConsGenerated() const { return numConsGenerated_; }
  /// Get number of constraints that are actually used out of the generated.
  int numConsUsed() const { return numConsUsed_; }
  /// Get CPU/User time this generator consumed.
  double time() const { return time_; }
  /// Get number of times this generator is called.
  int numCalls() const { return numCalls_; }
  /// Get number of times this generator is called and did not yield any cuts.
  int numNoConsCalls() const { return numNoConsCalls_; }
  //@}

  ///@name Update Statistics
  //@{
  /// Reset statistics.
  void reset();
  /// Increase the number of generated constraints.
  void addNumConsGenerated(int n) { numConsGenerated_ += n; }
  /// Increase the number of generated and used constraints.
  void addNumConsUsed(int n) { numConsUsed_ += n; }
  /// Increase Cpu time used.
  void addTime(double t) { time_ += t; }
  /// Increase the number of calls.
  void addNumCalls(int n=1) { numCalls_ += n; }
  /// Increase the number of calls and no constraints generated.
  void addNumNoConsCalls(int n=1) { numNoConsCalls_ += n; }
  //@}
};

class DcoConGenerator {
  ///@name Constraint generator info
  /// Name of generator.
  std::string name_;
  /// The client model.
  DcoModel * model_;
  /// Statistics of this generator.
  DcoConGeneratorStats stats_;
  //@}

  ///@name Constraint Generation Control
  //@{
  /// Constraint generation strategy.
  DcoCutStrategy strategy_;
  /// The frequency of calls to the cut generator.
  int frequency_;
  //@}

public:
  ///@name Constructors and Destructor
  //@{
  /// Constructor with usefull inputs.
  DcoConGenerator(DcoModel * model,
                  char const * name = NULL,
                  DcoCutStrategy strategy = DcoCutStrategyAuto,
                  int frequency = 1);
  /// Destructor.
  virtual ~DcoConGenerator();
  //@}

  ///@name Constraint generator functions
  //@{
  /// Generate constraints and add them to the pool.  return true if resolve is
  /// needed (because the state of the solver interface has been modified).
  virtual bool generateConstraints(BcpsConstraintPool & conPool) = 0;
  //@}

  // notes(aykut) We do not provide interface for all class fields. Updating
  // strategy and frequency does not make sense, since this will give false
  // info, stored statistics may be invalid, if this generator already
  // generated cuts with the previous strategy and frequency.

  /// Querry functions.
  //@{
  /// Get a pointer to the model.
  DcoModel * model() const { return model_; }
  /// Get the name of this generator.
  std::string name() const { return name_; }
  /// Get the constraint generation strategy.
  DcoCutStrategy strategy() const { return strategy_; }
  /// Get the frequency of calls to this cut generator.
  int frequency() const { return frequency_; }
  //@}

  /// Get mutable statistics
  DcoConGeneratorStats & stats() { return stats_; }

private:
  /// Disable default constructor.
  DcoConGenerator();
  /// Disable copy constructor.
  DcoConGenerator(DcoConGenerator const & other);
  /// Disable copy assignment operator.
  DcoConGenerator & operator=(DcoConGenerator const & rhs);
};

#endif
