#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <string>

typedef std::string ConfigurationResource;

struct RETURN_CODE_TYPE
{
  enum Value
  {
    NO_ERROR,
    INVALID_PARAM,
    MEMORY_EXCEEDED,
  };
};

class Solver
{
  public:
  Solver(){};
  ~Solver(){};
  virtual void Initialize(RETURN_CODE_TYPE::Value& return_code) = 0;
  virtual void Configure(const ConfigurationResource configuration_resource,
                         RETURN_CODE_TYPE::Value& return_code)  = 0;
  virtual void Solve(RETURN_CODE_TYPE::Value& return_code)      = 0;
  virtual void Finalize(RETURN_CODE_TYPE::Value& return_code)   = 0;
};

#endif // SOLVER_HPP