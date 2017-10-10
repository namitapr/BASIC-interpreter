#include "ArithmeticExpression.h"

class BooleanExpression {
 public:
  BooleanExpression ();
  BooleanExpression (const BooleanExpression& old);
  virtual ~BooleanExpression();
  virtual void print (std::ostream & o) const = 0;
  BooleanExpression& operator=(const BooleanExpression& other);
};

class BinaryBoolExpression : public BooleanExpression {
public:
  BinaryBoolExpression (const BinaryBoolExpression& old);
  BinaryBoolExpression (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  virtual ~BinaryBoolExpression ();
  virtual void print (std::ostream & o) const = 0;
  BinaryBoolExpression& operator=(const BinaryBoolExpression& other);
protected:
  ArithmeticExpression *_ae1;
  ArithmeticExpression *_ae2;
};

class Equals : public BinaryBoolExpression {
public:
  Equals (const Equals& old);
  Equals(ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  virtual ~Equals ();
  virtual void print (std::ostream & o) const;
  Equals& operator=(const Equals& other);
};

class LessThan : public BinaryBoolExpression {
public:
  LessThan (const LessThan& old);
  LessThan(ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  virtual ~LessThan ();
  virtual void print (std::ostream & o) const;
  LessThan& operator=(const LessThan& other);
};

class GreaterThan : public BinaryBoolExpression {
public:
  GreaterThan (const GreaterThan& old);
  GreaterThan(ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  virtual ~GreaterThan ();
  virtual void print (std::ostream & o) const;
  GreaterThan& operator=(const GreaterThan& other);
};