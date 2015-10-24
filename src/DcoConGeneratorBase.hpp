#ifndef DcoConGeneratorBase_h_
#define DcoConGeneratorBase_h_

#include "Dco.hpp"
#include <string>

/**
   We will make DcoConGenerator an abstract base class. Then
   implement constraint generators, linear and conic ones.
   Both these generators assumed to generate linear cuts.
 **/

class BcpsConstraintPool;
class DcoModel;

class DcoConGeneratorBase {
protected:
  /** The client model. */
  DcoModel * model_;
  //------------------------------------------------------
  // CON CONTROL
  //------------------------------------------------------
  DcoCutStrategy strategy_;
  /** The frequency of calls to the cut generator. */
  int cutGenerationFrequency_;
  /** Name of generator. */
  std::string name_;
  /** Whether to call the generator in the normal place. */
  bool normal_;
  /** Whether to call the generator when a new solution is found. */
  bool atSolution_;
  /** Whether to call generator when a subproblem is found to be
      infeasible.*/
  bool whenInfeasible_;
  //------------------------------------------------------
  // CON STATISTICS
  //------------------------------------------------------
  /** Number of cons generated. */
  int numConsGenerated_;
  /** Number of cons used. */
  int numConsUsed_;
  /** Used CPU/User time. */
  double time_;
  /** The times of calling this generator. */
  int calls_;
  /** The times of calling this generator and no cons found. */
  int noConsCalls_;
public:
  /**@name Constructors and destructors */
  //@{
  /** Default constructor. */
  DcoConGeneratorBase()
    :
    model_(NULL),
    strategy_(DcoCutStrategyAuto),
    cutGenerationFrequency_(1),
    normal_(true),
    atSolution_(false),
    whenInfeasible_(false),
    numConsGenerated_(0),
    numConsUsed_(0),
    time_(0),
    calls_(0),
    noConsCalls_(0) { name_ = "UNKNOWN"; }
  /** Useful constructor. */
  DcoConGeneratorBase(DcoModel * model,
                      const char * name = NULL,
                      DcoCutStrategy strategy = DcoCutStrategyAuto,
                      int cutGenerationFrequency_ = 1,
                      bool normal = true,
                      bool atSolution = false,
                      bool infeasible = false);
  /** Copy constructor. */
  DcoConGeneratorBase (const DcoConGeneratorBase &);
  /** Assignment operator. */
  DcoConGeneratorBase & operator=(const DcoConGeneratorBase & rhs);
  /** Destructor. */
  virtual ~DcoConGeneratorBase() {}
  //@}
  /** \name Generate Constraints */
  //@{
  /** Generate cons for the client model.

      Evaluate the state of the client model and decide whether to
      generate cons. The generated cons are inserted into and returned
      in the collection of cons \p cs.

      The routine returns true if reoptimisation is needed (because the
      state of the solver interface has been modified).
  */
  virtual bool generateConstraints(BcpsConstraintPool &conPool) = 0;
  //@}
  /**@name Gets and sets */
  //@{
  /** Set the client model.
      In addition to setting the client model, refreshModel also calls
      the \c refreshSolver method of the CglCutGenerator object.
  */
  /** Get a pointer to the model */
  inline DcoModel *getModel() { return model_; }
  /** Set the model */
  inline void setModel(DcoModel *m) { model_ = m; }
  /** Refresh the model */
  void refreshModel(DcoModel * model);
  /** return name of generator. */
  void setName(const char *str) { name_ = str; }
  /** return name of generator. */
  inline std::string name() const { return name_; }
  /** Set the con generation strategy. */
  void setStrategy(DcoCutStrategy value) { strategy_ = value; }
  /** Get the con generation interval. */
  inline DcoCutStrategy strategy() const { return strategy_; }
  /** Set the con generation strategy. */
  void setCutGenerationFreq(int freq) { cutGenerationFrequency_ = freq; }
  /** Get the con generation interval. */
  inline int cutGenerationFreq() const { return cutGenerationFrequency_; }
  /** Get whether the con generator should be called in the normal place. */
  inline bool normal() const { return normal_; }
  /** Set whether the con generator should be called in the normal place. */
  inline void setNormal(bool value) { normal_ = value; }
  /** Get whether the con generator should be called when a solution
      is found. */
  inline bool atSolution() const { return atSolution_; }
  /** Set whether the con generator should be called when a solution
      is found. */
  inline void setAtSolution(bool value) { atSolution_ = value; }
  /** Get whether the con generator should be called when the subproblem is
      found to be infeasible. */
  inline bool whenInfeasible() const { return whenInfeasible_; }
  /** Set whether the con generator should be called when the subproblem is
      found to be infeasible. */
  inline void setWhenInfeasible(bool value) { whenInfeasible_ = value; }
  /** Get number of generated cons. */
  inline int numConsGenerated() { return numConsGenerated_; }
  /** Increase the number of generated cons. */
  inline void addNumConsGenerated(int n) { numConsGenerated_ += n; }
  /** Get number of used cons. */
  inline int numConsUsed() { return numConsUsed_; }
  /** Increase the number of generated cons. */
  inline void addNumConsUsed(int n) { numConsUsed_ += n; }
  /** Cpu time used. */
  inline double time() const { return time_; }
  /** Increase Cpu time used. */
  inline void addTime(double t) { time_ += t; }
  /** Number called. */
  inline int calls() const { return calls_; }
  /** Increase the number of called. */
  inline void addCalls(int n=1) { calls_ += n; }
  /** Number called and no cons found. */
  inline int noConsCalls() const { return noConsCalls_; }
  /** Increase the number of no cons called. */
  inline void addNoConsCalls(int n=1) { noConsCalls_ += n; }
  //@}
};

#endif