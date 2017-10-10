#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stack>
#include <cctype>
#include "Command.h"

using namespace std;

void ParseAE(string dump, stack<ArithmeticExpression*>& sa);
void ParseBE(string dump, stack<ArithmeticExpression*>& sa, stack<BooleanExpression*>& sb);
bool isInt(char s);
bool isArr(string s);
bool isGrouping(char c);

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide an input file." << endl;
    return 1;
  }
  ifstream input(argv[1]);

  stack<ArithmeticExpression*> sa;
  stack<BooleanExpression*> sb;

  string curr; // the current line
  Command* c;

  //loop to read all lines of the program
  while(getline(input, curr)) {
    stringstream ss;
    ss << curr;
    string command; // the command
    unsigned int line;  // the line number
    
    ss >> line;
    ss >> command;
    if (command == "PRINT") {
      string dump;
      getline(ss, dump);
      ParseAE(dump, sa);
      ArithmeticExpression* top = sa.top();
      sa.pop();
      c = new Print(line, top);
      c->print(cout);
      cout << endl;
      delete c;
      delete top;
    }
    else if (command == "LET") {
      string dump;
      getline(ss, dump);
      ParseAE(dump, sa);
      ArithmeticExpression* second = sa.top();
      sa.pop();
      ArithmeticExpression* first = sa.top();
      sa.pop();
      c = new Let(line, first, second);
      c->print(cout);
      cout << endl;
      delete c;
      delete first;
      delete second;
    }
    else if (command == "GOTO") {
      int lineJ;
      ss >> lineJ;
      c = new Goto(line, lineJ);
      c->print(cout);
      cout << endl;
      delete c;
    }
    else if (command == "IF") {
      string dump;
      int lineJ;
      getline(ss, dump, 'T'); // dump now contains only bool expression
      ParseBE(dump, sa, sb);
      getline(ss, dump, 'N'); // removes the word "THEN" from dump
      ss >> lineJ;
      BooleanExpression* top = sb.top();
      sb.pop();
      c = new IfStatement(line, top, lineJ);
      c->print(cout);
      cout << endl; 
      delete c;
      delete top;
    }
    else if (command == "GOSUB") {
      int lineJ;
      ss >> lineJ;
      Command* c = new GoSub(line, lineJ);
      c->print(cout);
      cout << endl;
      delete c;
    }
    else if (command == "RETURN") {
      c = new Return(line);
      c->print(cout);
      cout << endl;
      delete c;
    }
    else if (command == "END") {
      c = new End(line);
      c->print(cout);
      cout << endl;
      delete c;
    }
    else {
      cerr << "Error! Invalid Command." << endl;
      return -1;
    }
  }

  return 0;
}

void ParseAE(string dump, stack<ArithmeticExpression*>& sa){
  ArithmeticExpression *ae, *op;
  bool operated = false;
  stringstream parse;
  parse << dump;
  char c;
  int n;
  string trash = "";

  while (parse >> c){
    if (c != ')' && c != ']'){
      if (c == '+') {
        op = new Operator("+");
        sa.push(op);
        operated = true;
      }
      else if (c == '-'){
        // accounting for negative ints here too
        c = parse.peek();
        if (isInt(c) && !operated){
          string nums;
          nums.push_back('-');
          while(isInt(c)){
            char q;
            parse >> q;
            nums.push_back(q);
            c = parse.peek();
          }
          n = stoi(nums);
          ae = new Constant(n);
          sa.push(ae);
        }
        else if (operated){
          string nums;
          nums.push_back('-');
          while(isInt(c)){
            char q;
            parse >> q;
            nums.push_back(q);
            c = parse.peek();
          }
          n = stoi(nums);
          ae = new Constant(n);
          sa.push(ae);
        }
        else {
        op = new Operator("-");
        sa.push(op);
        operated = true;
        }
      }
      else if (c == '*'){
        op = new Operator("*");
        sa.push(op);
        operated = true;
      }
      else if (c == '/'){
        op = new Operator("/");
        sa.push(op);
        operated = true;
      }
      else if (isInt(c)){
        string nums;
        nums.push_back(c);
        c = parse.peek();
        while(isInt(c)){
          char q;
          parse >> q;
          nums.push_back(q);
          c = parse.peek();
        }
        n = stoi(nums);
        ae = new Constant(n);
        sa.push(ae);
      }
      else if (isGrouping(c)) {
        string s;
        s.push_back(c);
        ae = new Variable(s);
        sa.push(ae);
      }
      else {
        string s;
        s.push_back(c);
        c = parse.peek();
        while(isalpha(c)){
          parse  >> c;
          s.push_back(c);
          c = parse.peek();
        }
        ae = new Variable(s);
        sa.push(ae);
      }
    }
    else {
      stack<ArithmeticExpression*> temp;
      trash = "";
      string marker;
      if(c == ')'){
        marker = "(";
      } else if (c == ']') {
        marker = "[";
      }
      while( trash != marker){
        ArithmeticExpression *aex, *aexp1, *aexp2;
        aex = sa.top();
        sa.pop();
        if (aex->get() == marker){
          aexp1 = temp.top();
          temp.pop();
          if(temp.size()>0){
            op = temp.top();
            temp.pop();
            aexp2 = temp.top();
            temp.pop();
          }
          if(marker == "[") {
            // executes if dealing with array index;
            ArithmeticExpression *forArr = sa.top(); 
            sa.pop();
            string arrVar = forArr->get() + "[" + aexp1->get() + "]";
            ArithmeticExpression *arithexp = new Variable(arrVar); 
            sa.push(arithexp);
            trash = aex->get();
            delete aex;
            delete aexp1;
            delete forArr;
          }
          else if (op->get() == "+"){
            ArithmeticExpression *binexp = new Addition(aexp1, aexp2);
            sa.push(binexp);
            trash = aex->get();
            delete op;
            delete aex;
          }
          else if (op->get() == "-") {
            ArithmeticExpression *binexp = new Subtraction(aexp1, aexp2);
            sa.push(binexp);
            trash = aex->get();
            delete op;
            delete aex;
          }
          else if (op->get() == "*") {
            ArithmeticExpression *binexp = new Multiplication(aexp1, aexp2);
            sa.push(binexp);
            trash = aex->get();
            delete op;
            delete aex;
          }
          else if (op->get() == "/") {
            ArithmeticExpression *binexp = new Division(aexp1, aexp2);
            sa.push(binexp);
            trash = aex->get();
            delete op;
            delete aex;
          }
        }
        else {
          temp.push(aex);
          trash = aex->get();
        }
      }
      while(!temp.empty()){
        ArithmeticExpression* to_delete = temp.top();
        delete to_delete;
        temp.pop();
      }
    }
  }
}

void ParseBE(string dump, stack<ArithmeticExpression*>& sa, stack<BooleanExpression*>& sb) {
  BooleanExpression* be;
  string interDump1, interDump2, comparison;
  int operation, end;
  // isolating two AEs in Boolean Expression
  end = dump.find('H');
  operation = dump.find('=');
  if(operation > -1){
    comparison = "=";
    interDump1 = dump.substr(0, operation);
    interDump2 = dump.substr(operation+1, end);
    ParseAE(interDump1, sa);
    ParseAE(interDump2, sa);
  }

  operation = dump.find('<');
  if(operation > -1){
    comparison = "<";
    interDump1 = dump.substr(0, operation);
    interDump2 = dump.substr(operation+1, end);
    ParseAE(interDump1, sa);
    ParseAE(interDump2, sa);
  }
  operation = dump.find('>');
  if(operation > -1){
    comparison = ">";
    interDump1 = dump.substr(0, operation);
    interDump2 = dump.substr(operation+1, end);    
    ParseAE(interDump1, sa);
    ParseAE(interDump2, sa);
  }
  ArithmeticExpression* second = sa.top();
  sa.pop();

  if(comparison == "="){
    be = new Equals(sa.top(), second);
  }
  else if(comparison == "<"){
    be = new LessThan(sa.top(), second);
  }
  else if (comparison == ">") {
    be = new GreaterThan(sa.top(), second);
  }
  sb.push(be);

}

bool isInt(char c) {
  string s;
  s.push_back(c);
  return s.find_first_not_of("0123456789") == string::npos;
}

bool isArr(string s){
  for(unsigned int i=0; i<s.length(); i++){
    if(s[i] == '[' || s[i] == ']'){
      return true;
    }
  }
  return false;
}

bool isGrouping(char c){
  if(c == '(' || c == ')' || c == '[' || c == ']'){
    return true;
  }
  return false;
}