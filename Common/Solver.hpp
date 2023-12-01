#ifndef SOLVER_HPP
#define SOLVER_HPP

typedef const char* ConfigurationResource;

struct RETURN_CODE_TYPE
{
  enum Value
  {
    NO_ERROR,
    INVALID_PARAM,
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