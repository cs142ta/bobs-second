#ifndef GRADE_INSTANCE_H_
#define GRADE_INSTANCE_H_

#include <sstream>
#include <string>

#include "Instance.h"

class GradeInstance : public Instance {
 private:
  string assignment;
  string before;
  string after;
  string current;

 public:
  GradeInstance(string row) { parse(row); }
  void parse(string row) {
    string cell;
    string assignment;
    istringstream line(row);

    string date;
    getline(line, cell, ',');
    date += cell;
    getline(line, cell, ',');
    date += cell;
    addDate(date);

    getline(line, cell, ',');  // anonymous
    getline(line, cell, ',');
    addStudent(cell);
    getline(line, cell, ',');
    addTaName(cell);
    getline(line, assignment, ',');
    addAssignment(assignment);
    getline(line, cell, ',');
    addBefore(cell);
    getline(line, cell, ',');
    addAfter(cell);
    getline(line, cell, ',');
    addCurrent(cell);
  }
  void addAssignment(string assignment) { this->assignment = assignment; }
  string getAssignment() const { return assignment; }
  void addBefore(string before) { this->before = before; }
  void addAfter(string after) { this->after = after; }
  void addCurrent(string current) { this->current = current; }
};

#endif
