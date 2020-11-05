#ifndef TEACHING_ASSISTANT_H_
#define TEACHING_ASSISTANT_H_

#include <sstream>
#include <string>

class TeachingAssistant {
 private:
  string name;
  vector<HelpInstance> helpInstances;

 public:
  TeachingAssistant(string name) { this->name = name; }
  void addHelpInstance(HelpInstance help) { helpInstances.push_back(help); }
  string getName() const { return name; }
  int getHelpInstanceTotal() const { return helpInstances.size(); }
  unsigned long long int getTotalHelpTime() const {
    unsigned long long int totalTime = 0;
    for (int i = 0; i < helpInstances.size(); i++) {
      totalTime += helpInstances.at(i).getDuration();
    }
    return totalTime;
  }

  string getAverageTimeStr() const {
    string res = minutesToString(getTotalHelpTime() / helpInstances.size());
    return res;
  }
  string getTotalHoursStr() const {
    return minutesToString(getTotalHelpTime());
  }
  static string minutesToString(unsigned long long int totalSeconds) {
    ostringstream out;
    double hours = (totalSeconds / 60.0 / 60.0);
    unsigned long long int timeLeft = (hours - (int)hours) * 3600;
    double minutes = (timeLeft / 60.0);
    unsigned int seconds = (minutes - (int)minutes) * 60;
    out << (int)hours << ":" << (int)minutes << ":" << seconds;
    return out.str();
  }

  bool operator<(const TeachingAssistant &comp) {
    return (this->getName() < comp.getName());
  }
};

#endif
