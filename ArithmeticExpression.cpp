#include "ArithmeticExpression.h"

ArithmeticExpression::ArithmeticExpression() {}

ArithmeticExpression::ArithmeticExpression
(const ArithmeticExpression& old) {}

ArithmeticExpression::~ArithmeticExpression () {}

ArithmeticExpression& ArithmeticExpression::operator=
(const ArithmeticExpression& other) {
	return *this;
}

Variable::Variable (const Variable& old) {
	_var = old._var;
}

Variable::Variable (std::string var){
	_var = var;
}

Variable::~Variable () {}

void Variable::print(std::ostream & o) const {
	o << _var;
}

std::string Variable::get() const {
	return _var;
}

Variable& Variable::operator=(const Variable& other) {
	this->_var = other._var;
	return *this;
}

Constant::Constant (const Constant& old){
	_num = old._num;
}

Constant::Constant (int num){
	_num = num;
}

Constant::~Constant () {}

void Constant::print(std::ostream & o) const {
	o << _num;
}

std::string Constant::get() const {
	return std::to_string(_num);
}

Constant& Constant::operator=(const Constant& other) {
	this->_num = other._num;
	return *this;
}

Operator::Operator(std::string c){
	_c = c;
}

Operator::~Operator () {}

void Operator::print (std::ostream & o) const {
	o << _c;
}

std::string Operator::get() const {
	return _c;
}

Operator& Operator::operator=(const Operator& other) {
	this->_c = other._c;
	return *this;
}

BinaryArithExpression::BinaryArithExpression 
(const BinaryArithExpression& old) {
	_ae1 = old._ae1;
	_ae2 = old._ae2;
}

BinaryArithExpression::BinaryArithExpression 
(ArithmeticExpression *ae1, ArithmeticExpression *ae2) {
  _ae1 = ae1;
  _ae2 = ae2;
}

BinaryArithExpression::~BinaryArithExpression () {
  delete _ae1;
  delete _ae2;
}

std::string BinaryArithExpression::get() const {
	return "";
}

BinaryArithExpression& BinaryArithExpression::operator=
(const BinaryArithExpression& other) {
	this->_ae1 = other._ae1;
	this->_ae2 = other._ae2;
	return *this;
}

Addition::Addition (const Addition& old): BinaryArithExpression(old) {}

Addition::Addition(ArithmeticExpression *ae1, ArithmeticExpression *ae2) 
: BinaryArithExpression (ae1, ae2) {}

Addition::~Addition() {}

void Addition::print (std::ostream & o) const
{
  o << "(";
  _ae1->print (o);
  o << " + ";
  _ae2->print (o);
  o << ")";
}

std::string Addition::get() const {
	return ("(" + _ae1->get() + "+" + _ae2->get() + ")");
}

Addition& Addition::operator=(const Addition& other) {
	return *this;
}

Subtraction::Subtraction (const Subtraction& old) 
: BinaryArithExpression(old) {}

Subtraction::Subtraction (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
: BinaryArithExpression (ae1, ae2) {}

Subtraction::~Subtraction () {}

void Subtraction::print (std::ostream & o) const {
	o << "(";
	_ae1->print (o);
	o << " - ";
	_ae2->print (o);
	o << ")";
}

std::string Subtraction::get() const {
	return ("(" + _ae1->get() + "-" + _ae2->get() + ")");
}

Subtraction& Subtraction::operator=(const Subtraction& other){
	return *this;
}

Multiplication::Multiplication (const Multiplication& old)
: BinaryArithExpression(old) {}

Multiplication::Multiplication(ArithmeticExpression *ae1, ArithmeticExpression *ae2)
: BinaryArithExpression (ae1, ae2) {}

Multiplication::~Multiplication () {}

void Multiplication::print (std::ostream & o) const {
	o << "(";
	_ae1->print (o);
	o << " * ";
	_ae2->print (o);
	o << ")";
}

std::string Multiplication::get() const {
	return ("(" + _ae1->get() + "*" + _ae2->get() + ")");
}

Multiplication& Multiplication::operator=(const Multiplication& other) {
	return *this;
}

Division::Division(const Division &old)
: BinaryArithExpression(old) {}

Division::Division(ArithmeticExpression *ae1, ArithmeticExpression *ae2)
: BinaryArithExpression (ae1, ae2) {}

Division::~Division () {}

void Division::print (std::ostream & o) const {
	o << "(";
	_ae1->print (o);
	o << " / ";
	_ae2->print (o);
	o << ")";
}

std::string Division::get() const {
	return ("(" + _ae1->get() + "/" + _ae2->get() + ")");
}

Division& Division::operator=(const Division& other) {
	return *this;
}
