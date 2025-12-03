#include <iostream>
#include <string>
#include <vector>

#include "val.h"
using namespace std;

bool isNumericStr(string str) {
  for (char s : str) {
    if (!isdigit(s) && s != '.') {
      return false;
    }
  }
  return true;
}

// numeric multiply
Value Value::operator*(const Value& op) const {
  int opValue = 0;
  int thisValue = 0;

  // expects two numbers or string numbers
  if (!this->IsNum() && !isNumericStr(this->Stemp) ||
      !op.IsNum() && !isNumericStr(op.Stemp)) {
    return Value();  // error constructor
  }

  // Multiply the numeric strings, otherwise just numeric values
  if (isNumericStr(this->Stemp)) {
    thisValue = stoi(this->Stemp);
  } else if (isNumericStr(op.Stemp)) {
    opValue = stoi(op.Stemp);
  } else {
    thisValue = this->Ntemp;
    opValue = op.Ntemp;
  }
  // convert bc weird 0 and boolean issue
  return Value(static_cast<double>(thisValue * opValue));
}

// numeric less than
Value Value::operator<(const Value& op) const {
  // expects two numbers
  if (!this->IsNum() || !op.IsNum()) {
    return Value();
  }
  return Value(this->Ntemp < op.Ntemp);
}

// string equality (-eq)
Value Value::SEQ(const Value& oper) const {
  // expects numbers and/or string
  if ((!this->IsNum() && !this->IsString()) ||
      (!oper.IsNum() && !oper.IsString())) {
    return Value();
  }
  return Value(this->Ntemp == oper.Ntemp);
}

// string concatenation
Value Value::Catenate(const Value& oper) const {
  // expects numbers and/or string
  if ((!this->IsNum() && !this->IsString()) ||
      (!oper.IsNum() && !oper.IsString())) {
    return Value();
  }
  return Value(this->Stemp + oper.Stemp);
}

// string repetition
// Repeat the LHS a RHS # of times
Value Value::Repeat(const Value& oper) const {
  // expects lhs number/string and rhs number only
  if ((!this->IsNum() && !this->IsString()) || !oper.IsNum()) {
    return Value();
  }

  string curr = "";
  for (int i = 0; i < oper.Ntemp; i++) {
    curr += oper.Stemp;
  }

  return Value(curr);
}
