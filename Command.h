#include "BooleanExpression.h"

class Command {
 public:
  Command ();
  Command (const Command& old);
  virtual ~Command();
  virtual void print (std::ostream & o) const = 0;
  Command& operator=(const Command& other);
};

class Print : public Command {
public:
  Print (const Print& old);
  Print(unsigned int line, ArithmeticExpression *ae);
  virtual ~Print ();
  virtual void print (std::ostream & o) const;
  Print& operator=(const Print& other);
private:
	unsigned int _line;
	ArithmeticExpression *_ae;
};

class Let : public Command {
public:
  Let (const Let& old);
  Let(unsigned int line, 
    ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  virtual ~Let ();
  virtual void print (std::ostream & o) const;
  Let& operator=(const Let& other);

private:
	unsigned int _line;
	ArithmeticExpression *_ae1;
  ArithmeticExpression *_ae2;
};

class Goto : public Command {
public:
  Goto (const Goto* old);
  Goto(unsigned int line, unsigned int lineJ);
  virtual ~Goto ();
  virtual void print (std::ostream & o) const;
  Goto& operator=(const Goto& other);
private:
	unsigned int _line;
	unsigned int _lineJ;
};

class IfStatement : public Command {
public:
  IfStatement (const IfStatement& old);
  IfStatement(unsigned int line, 
    BooleanExpression *be, unsigned int lineJ);
  virtual ~IfStatement ();
  virtual void print (std::ostream & o) const;
  IfStatement& operator=(const IfStatement& other);
private:
	unsigned int _line;
	BooleanExpression *_be;
	unsigned int _lineJ;
};

class GoSub : public Command {
public:
  GoSub (const GoSub& old);
  GoSub(unsigned int line, unsigned int lineJ);
  virtual ~GoSub ();
  virtual void print (std::ostream & o) const;
  int get_last_pos() const;
  GoSub& operator=(const GoSub& other);
private:
	unsigned int _line;
	unsigned int _lineJ;
};

class Return : public Command {
public:
  Return (const Return& old);
  Return(unsigned int line);
  virtual ~Return ();
  virtual void print (std::ostream & o) const;
  Return& operator=(const Return& other);
private:
	unsigned int _line;
};

class End : public Command {
public:
  End (const End& old);
  End(unsigned int line);
  virtual ~End ();
  virtual void print (std::ostream & o) const;
  End& operator=(const End& other);
private:
	unsigned int _line;
};