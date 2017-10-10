#include "Command.h"

Command::Command() {}

Command::Command (const Command& old){}

Command::~Command() {}

Command& Command::operator=(const Command& other) {
	return *this;
}

Print::Print(const Print& old){
	_line = old._line;
	_ae = old._ae;
}

Print::Print(unsigned int line, ArithmeticExpression *ae) {
	_line = line;
	_ae = ae;
}

Print::~Print () {}

void Print::print (std::ostream & o) const {
	o << _line << " PRINT ";
	_ae->print(o);
}

Print& Print::operator=(const Print& other) {
	this->_line = other._line;
	this->_ae = other._ae;
	return *this;
}

Let::Let(const Let& old) {
	_line = old._line;
	_ae1 = old._ae1;
	_ae2 = old._ae2;
}

Let::Let
(unsigned int line, ArithmeticExpression *ae1, ArithmeticExpression *ae2) {
	_line = line;
	_ae1 = ae1;
	_ae2 = ae2;
}

Let::~Let () {}

void Let::print (std::ostream & o) const {
	o << _line << " LET ";
	_ae1->print(o);
	o << " ";
	_ae2->print(o);
}

Let& Let::operator=(const Let& other) {
	this->_line = other._line;
	this->_ae1 = other._ae1;
	this->_ae2 = other._ae2;
	return *this;
}

Goto::Goto(unsigned int line, unsigned int lineJ) {
	_line = line;
	_lineJ = lineJ;
}

Goto::~Goto () {}

void Goto::print (std::ostream & o) const {
	o << _line << " GOTO <" << _lineJ << ">";
}

Goto& Goto::operator=(const Goto& other) {
	this->_line = other._line;
	this->_lineJ = other._lineJ;
	return *this;
}

IfStatement::IfStatement(const IfStatement& old) {
	_line = old._line;
	_be = old._be;
	_lineJ = old._lineJ;
}

IfStatement::IfStatement
(unsigned int line, BooleanExpression *be, unsigned int lineJ) {
	_line = line;
	_be = be;
	_lineJ = lineJ;
}

IfStatement::~IfStatement () {}

void IfStatement::print (std::ostream & o) const {
	o << _line;
	o << " IF ";
	_be->print(o);
	o << " THEN <";
	o << _lineJ;
	o << ">";
}

IfStatement& IfStatement::operator=(const IfStatement& other) {
	this->_line = other._line;
	this->_be = other._be;
	this->_lineJ = other._lineJ;
	return *this;
}

GoSub::GoSub(const GoSub& old) {
	_line = old._line;
	_lineJ = old._lineJ;
}

GoSub::GoSub(unsigned int line, unsigned int lineJ) {
	_line = line;
	_lineJ = lineJ;
}

GoSub::~GoSub () {}

void GoSub::print (std::ostream & o) const {
	o << _line << " GOSUB <" << _lineJ << ">";
}

int GoSub::get_last_pos() const {
	return _line;
}

GoSub& GoSub::operator=(const GoSub& other) {
	this->_line = other._line;
	this->_lineJ = other._lineJ;
	return *this;
}

Return::Return(const Return& old) {
	_line = old._line;
}

Return::Return(unsigned int line) {
	_line = line;
}

Return::~Return () {}

void Return::print (std::ostream & o) const {
	o << _line << " RETURN";
}

Return& Return::operator=(const Return& other) {
	this->_line = other._line;
	return *this;
}

End::End(const End& old) {
	_line = old._line;
}

End::End(unsigned int line) {
	_line = line;
}

End::~End () {}

void End::print (std::ostream & o) const {
	o << _line << " END";
}


End& End::operator=(const End& other) {
	this->_line = other._line;
	return *this;
}