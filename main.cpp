#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

#include "HelpInstance.h"
#include "TeachingAssistant.h"
#include "GradingStatsWorker.h"

int index(const vector<TeachingAssistant> &teachingAssistants, string name) {
  for (int i = 0; i < teachingAssistants.size(); ++i) {
    if (teachingAssistants.at(i).getName() == name) {
      return i;
    }
  }
  return -1;
}

void writeInLabResults(vector<TeachingAssistant> teachingAssistants) {
  std::sort(teachingAssistants.begin(), teachingAssistants.end());
  ofstream file;
  file.open("help-results.csv");


  file << "Name";
  file << ',' << "Total Time";
  file << ',' << "Helped";
  file << endl;
	
  for (TeachingAssistant& ta : teachingAssistants) {
    if (ta.getName() != "Themselves") {
      file << ta.getName();
      file << ',' << ta.getTotalHoursStr();
      file << ',' << ta.getHelpInstanceTotal();
      file << '\n';
    }
  }
  file.close();
}

vector<HelpInstance> extractInLabFile(string fileloc) {
  vector<HelpInstance> inLab;
  ifstream inLabFile;
  string row;

  inLabFile.open(fileloc);

  while (inLabFile.good()) {
    getline(inLabFile, row);
    if (row != ",,,,,,," && row != "") {
      inLab.push_back(HelpInstance(row));
    }
  }

  inLabFile.close();

  return inLab;
}

vector<TeachingAssistant> assignInstancesToTA(vector<HelpInstance> instances) {
  vector<TeachingAssistant> teachingAssistants;
  for (HelpInstance inst : instances) {
    int thisTA = index(teachingAssistants, inst.getTaName());

    if (thisTA == -1) {
      teachingAssistants.push_back(TeachingAssistant(inst.getTaName()));
      teachingAssistants.back().addHelpInstance(inst);
    } else {
      teachingAssistants.at(thisTA).addHelpInstance(inst);
    }
  }

  return teachingAssistants;
}



int main(int argc, char *argv[]) {

  string inLabFileLoc = "help-data.csv";
  string gradingFileLoc = "grade-data.csv";

  writeInLabResults(assignInstancesToTA(extractInLabFile(inLabFileLoc)));

  GradingStatsWorker gradeWorker;
  gradeWorker.readInStats(gradingFileLoc);
  gradeWorker.writeOutStats("grade-results.csv");
}
