#include <iostream>

class ArithmeticExpression {
 public:
  ArithmeticExpression();
  ArithmeticExpression(const ArithmeticExpression& old);
  virtual ~ArithmeticExpression();
  virtual void print (std::ostream & o) const = 0;
  virtual std::string get() const = 0;
  ArithmeticExpression& operator= (const ArithmeticExpression& other);
};

class Variable : public ArithmeticExpression {
public:
  Variable(const Variable& old);
  Variable (std::string var);
  virtual ~Variable ();
  virtual void print (std::ostream & o) const;
  virtual std::string get() const;
  Variable& operator= (const Variable& other);
protected:
  std::string _var;
};

class Constant : public ArithmeticExpression {
public:
  Constant (const Constant& old);
  Constant (int num);
  virtual ~Constant ();
  virtual void print (std::ostream & o) const;
  virtual std::string get() const;
  Constant& operator= (const Constant& other);
protected:
  int _num;
};

class Operator : public ArithmeticExpression {
public:
  Operator (const Operator* old);
  Operator(std::string c);
  virtual ~Operator();
  virtual void print (std::ostream & o) const;
  virtual std::string get() const;
  Operator& operator= (const Operator& other);
protected:
  std::string _c;
};

class BinaryArithExpression : public ArithmeticExpression {
public:
  BinaryArithExpression (const BinaryArithExpression& old);
  BinaryArithExpression (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  virtual ~BinaryArithExpression ();
  virtual void print (std::ostream & o) const = 0;
  virtual std::string get() const;
  BinaryArithExpression& operator= (const BinaryArithExpression& other);
protected:
  ArithmeticExpression *_ae1;
  ArithmeticExpression *_ae2;
};

class Addition : public BinaryArithExpression {
 public:
  Addition (const Addition& old);
  Addition (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  virtual ~Addition ();
  virtual void print (std::ostream & o) const;
  virtual std::string get() const;  
  Addition& operator= (const Addition& other);
};

class Subtraction : public BinaryArithExpression {
public:
  Subtraction (const Subtraction& old);
  Subtraction (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  virtual ~Subtraction ();
  virtual void print (std::ostream & o) const;
  virtual std::string get() const;
  Subtraction& operator= (const Subtraction& other);
};

class Multiplication : public BinaryArithExpression {
public:
  Multiplication (const Multiplication& old);
  Multiplication (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  virtual ~Multiplication ();
  virtual void print (std::ostream & o) const;
  virtual std::string get() const;
  Multiplication& operator= (const Multiplication& other);
};

class Division : public BinaryArithExpression {
public:
  Division (const Division& old); 
  Division (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  virtual ~Division ();
  virtual void print (std::ostream & o) const;
  virtual std::string get() const;
  Division& operator= (const Division& other);
};