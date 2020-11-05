#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class GradingStatsWorker {
 private:
  class Event {
   public:
    std::string timeStamp;
    std::string eventType;
    std::string studentName;
    std::string labName;
    std::string taNetid;
    std::string lockType;

    Event(const std::string &row) {
      std::istringstream rowSS(row);
      std::getline(rowSS, timeStamp, ',');
      std::getline(rowSS, eventType, ',');
      std::getline(rowSS, studentName, ',');
      std::getline(rowSS, labName, ',');
      std::getline(rowSS, taNetid, ',');
      std::getline(rowSS, lockType, ',');
    }
    bool isLock() { return lockType == "LOCK"; }
  };

  std::vector<Event> events;

  struct StudentAssignment {
    std::string studentName;
    std::string labName;
    StudentAssignment(const std::string &s, const std::string &l)
        : studentName(s), labName(l) {}
    bool operator<(const StudentAssignment o) const {
      if (this->studentName == o.studentName) {
        return this->labName < o.labName;
      } else {
        return this->studentName < o.studentName;
      }
    }
  };

  std::map<StudentAssignment, std::vector<Event>> mappedEvents;
  std::map<std::string, int> taCounts;

  unsigned long long int secondsInYear(const std::string &timeStamp) {
    unsigned long long int yr = 0, mon = 0, day = 0, hr = 0, min = 0, sec = 0,
                           ms = 0;
    sscanf(timeStamp.c_str(), "%4llu-%2llu-%2lluT%2llu:%2llu:%2llu.%6llu", &yr,
           &mon, &day, &hr, &min, &sec, &ms);
    mon *= 31;
    day += mon;
    day *= 24;
    hr += day;
    hr *= 60;
    min += hr;
    min *= 60;
    sec += min;
    return sec;
  }

  std::string whoGradedThis(const std::vector<Event> &events) {
    std::vector<std::pair<std::string, unsigned long long int>> taSeconds;
    std::map<std::string, unsigned long long int> lockTimes;
    for (Event e : events) {
      if (e.isLock()) {
        lockTimes[e.taNetid] = secondsInYear(e.timeStamp);
      } else {
        if (lockTimes.count(e.taNetid) == 0 || lockTimes[e.taNetid] == 0) {
          // do nothing
        } else {
          taSeconds.push_back(std::make_pair(
              e.taNetid, secondsInYear(e.timeStamp) - lockTimes[e.taNetid]));
        }
      }
    }

    // taSeconds now holds the amount of time the assignment was unlocked by
    // each TA in order

    const int MIN_SECONDS_THRESHOLD = 15;
    std::vector<std::pair<std::string, unsigned long long int>>
        longEnoughTaSeconds;
    for (std::pair<std::string, unsigned long long int> count : taSeconds) {
      if (count.second > MIN_SECONDS_THRESHOLD) {
        longEnoughTaSeconds.push_back(count);
      }
    }

    if (longEnoughTaSeconds.empty()) {
      return "";
    } else {
      return longEnoughTaSeconds.front().first;
    }
  }

  void interpret() {
    for (Event e : events) {
      mappedEvents[StudentAssignment(e.studentName, e.labName)].push_back(e);
    }
    std::map<StudentAssignment, std::vector<Event>>::const_iterator it;
    for (it = mappedEvents.cbegin(); it != mappedEvents.cend(); ++it) {
      std::string taName = whoGradedThis(it->second);
      if (!taName.empty()) {
        taCounts[taName]++;
      }
    }
  }

 public:
  void readInStats(const std::string &fileName) {
    std::ifstream in(fileName);
    std::string row;
    while (std::getline(in, row)) {
      Event event = Event(row);
      if (event.eventType == "LAB") {
        events.push_back(Event(row));
      }
    }
    in.close();
    interpret();
  }
  void writeOutStats(const std::string &fileName) {
    std::ofstream out(fileName);
    for (std::map<std::string, int>::const_iterator it = taCounts.cbegin();
         it != taCounts.cend(); ++it) {
      out << it->first << ',' << it->second << '\n';
    }
    out.close();
  }
};
