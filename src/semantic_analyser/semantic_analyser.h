#ifndef COMPILER_H_VO9YQUZS
#define COMPILER_H_VO9YQUZS

/* simone includes */
#include <simone/ptr_interface.h>

/* forward declarations */
class Program;
class ScopeStackBuilder;

class SemanticAnalyser : public Simone::PtrInterface<SemanticAnalyser> {
public:
  typedef Simone::Ptr<const SemanticAnalyser> PtrConst;
  typedef Simone::Ptr<SemanticAnalyser> Ptr;

  static Ptr SemanticAnalyserNew(Simone::Ptr<Program> _program) {
    return new SemanticAnalyser(_program);
  }

private:
  SemanticAnalyser(Simone::Ptr<Program> _program);
  
  /* data members */
  Simone::Ptr<ScopeStackBuilder> sm_builder_;
};

#endif
