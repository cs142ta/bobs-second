#ifndef HELP_INSTANCE_H_
#define HELP_INSTANCE_H_

#include <sstream>
#include <string>
using namespace std;

class HelpInstance {
 private:
  static string currentDate;

  string enqueue;
  string dequeue;
  string wait;
  int duration;

  string date;
  string taName;
  string student;

 public:
  HelpInstance(string row) { parse(row); }
  void parse(string row) {
    string cell;
    istringstream line(row);

    getline(line, cell, ',');
    if (cell != "") currentDate = cell;
    addDate(currentDate);
    getline(line, cell, ',');
    addStudent(cell);
    getline(line, cell, ',');
    addTaName(cell);
    getline(line, cell, ',');
    addEnqueue(cell);
    getline(line, cell, ',');
    addDequeue(cell);
    getline(line, cell, ',');
    addWait(cell);
    getline(line, cell, ',');
    getline(line, cell, ',');
    addDuration(cell);
  }
  void addEnqueue(string enqueue) { this->enqueue = enqueue; }
  void addDequeue(string dequeue) { this->dequeue = dequeue; }
  void addWait(string wait) { this->wait = wait; }
  void addDuration(string duration) {
    if (duration != "None") {
      string minutes = duration.substr(0, 2);
      string seconds = duration.substr(3, 2);
      this->duration = (stoi(minutes) * 60) + stoi(seconds);
    } else {
      this->duration = 0;
    }
  }
  int getDuration() const { return duration; }

  void addDate(string date) { this->date = date; }
  void addTaName(string taName) { this->taName = taName; }
  void addStudent(string student) { this->student = student; }
  string getTaName() { return taName; }
  string getStudent() const { return student; }
};

string HelpInstance::currentDate = "";

#endif
