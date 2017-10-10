#include "BooleanExpression.h"

BooleanExpression::BooleanExpression () {}

BooleanExpression::BooleanExpression (const BooleanExpression& old) {}

BooleanExpression::~BooleanExpression() {}

BooleanExpression& BooleanExpression::operator=
(const BooleanExpression& other) {
	return *this;
}

BinaryBoolExpression::BinaryBoolExpression 
(const BinaryBoolExpression& old) {
	_ae1 = old._ae1;
	_ae2 = old._ae2;
}

BinaryBoolExpression::BinaryBoolExpression 
(ArithmeticExpression *ae1, ArithmeticExpression *ae2) {
	_ae1 = ae1;
	_ae2 = ae2;
}

BinaryBoolExpression::~BinaryBoolExpression () {
	delete _ae1;
	delete _ae2;
}

BinaryBoolExpression& BinaryBoolExpression::operator=
(const BinaryBoolExpression& other) {
	this->_ae1 = other._ae1;
	this->_ae2 = other._ae2;
	return *this;
}

Equals::Equals (const Equals& old) : BinaryBoolExpression (old) {}

Equals::Equals(ArithmeticExpression *ae1, ArithmeticExpression *ae2)
: BinaryBoolExpression(ae1, ae2) {}

Equals::~Equals () {}

void Equals::print (std::ostream & o) const {
	o << "[";
	_ae1->print (o);
	o << " = ";
	_ae2->print (o);
	o << "]";  
}

Equals& Equals::operator=(const Equals& other) {
	return *this;
}

LessThan::LessThan (const LessThan& old)
: BinaryBoolExpression (old) {}

LessThan::LessThan(ArithmeticExpression *ae1, ArithmeticExpression *ae2)
: BinaryBoolExpression(ae1, ae2) {}

LessThan::~LessThan () {}

void LessThan::print (std::ostream & o) const {
	o << "[";
	_ae1->print (o);
	o << " < ";
	_ae2->print (o);
	o << "]";
}

LessThan& LessThan::operator=(const LessThan& other) {
	return *this;
}

GreaterThan::GreaterThan (const GreaterThan& old)
: BinaryBoolExpression (old) {}

GreaterThan::GreaterThan(ArithmeticExpression *ae1, ArithmeticExpression *ae2)
: BinaryBoolExpression(ae1, ae2) {}

GreaterThan::~GreaterThan () {}

void GreaterThan::print (std::ostream & o) const {
	o << "[";
	_ae2->print (o);
	o << " < ";
	_ae1->print (o);
	o << "]";
}

GreaterThan& GreaterThan::operator=(const GreaterThan& other) {
	return *this;
}