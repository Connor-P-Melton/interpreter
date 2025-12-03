// Connor Melton
#include <iostream>
#include <string>
#include <vector>

#include "val.h"
using namespace std;

bool isNumericStr(string str) {
  // Edge case
  if (empty(str)) {
    return false;
  }

  for (char s : str) {
    if (!isdigit(s) && s != '.') {
      return false;
    }
  }
  return true;
}

// Multiply with support for numeric coersion (Perl allows "1" * 1 = 1)
Value Value::operator*(const Value& op) const {
  double thisValue = this->Ntemp;
  double opValue = op.Ntemp;

  // expects two numbers or string numbers
  if (!this->IsNum() && !isNumericStr(this->Stemp) ||
      !op.IsNum() && !isNumericStr(op.Stemp)) {
    return Value();  // error constructor
  }

  // Support for multipling numeric strings
  if (isNumericStr(this->Stemp)) {
    thisValue = stoi(this->Stemp);
  }
  if (isNumericStr(op.Stemp)) {
    opValue = stoi(op.Stemp);
  }

  // convert bc confusion between 0 and boolean for constructor
  return Value(static_cast<double>(thisValue * opValue));
}

// numeric less than
Value Value::operator<(const Value& op) const {
  double thisValue = this->Ntemp;
  double opValue = op.Ntemp;

  // expects two numbers or string numbers
  if (!this->IsNum() && !isNumericStr(this->Stemp) ||
      !op.IsNum() && !isNumericStr(op.Stemp)) {
    return Value();  // error constructor
  }

  // Support for multipling numeric strings
  if (isNumericStr(this->Stemp)) {
    thisValue = stoi(this->Stemp);
  }
  if (isNumericStr(op.Stemp)) {
    opValue = stoi(op.Stemp);
  }

  // convert bc confusion between 0 and boolean for constructor
  return Value(thisValue < opValue);
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
