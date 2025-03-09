#pragma once
#include "Applicant.h"

class Applicants {
  public:
    vector<BachelorApplicant> bachelorApplicants;
    vector<MasterApplicant> masterApplicants;

  template <typename Applicants>
  void exportAcceptedApplicants(const string &fileName, vector<Applicants> &applicants) {
    ofstream file(fileName);
    if (!file.is_open()) {
      cerr << "Error opening file " << fileName << endl;
    }

    for (const auto &applicant: applicants) {

      if (applicant.getStatus() != ACCEPTED) { continue; }
      std::stringstream lineStream;

      lineStream << applicant.getUniqueID() << COMMA_DELIMITER
                 << applicant.getName() << COMMA_DELIMITER
                 << applicant.getFinalAdmission();

      file << lineStream.str() << "\n";
    }
  }
  template <typename Applicants>
  Applicants* findApplicant(const string &id, vector<Applicants> &applicants) {
    for ( auto &applicant: applicants) {
      if (applicant.getUniqueID() == id) { return &applicant; }
    }
    return nullptr;
  }

  static inline std::string trim(const std::string &s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
      start++;
    }

    auto end = s.end();
    do {
      end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return string(start, end + 1);
  }

};

class BachelorApplicants : public Applicants {
  public:
    bool loadBachelorApplicants(const string &filename);
    static void printApplicants(const vector<BachelorApplicant> &applicants);
    void exportBachelorApplicants(const string &filename) { exportAcceptedApplicants(filename, bachelorApplicants); }
    BachelorApplicant* findBachelorApplicant(const string &id) { return findApplicant(id, bachelorApplicants); }
};

class MasterApplicants : public Applicants {
  public:
    bool loadMasterApplicants(const string &filename);
    void exportMasterApplicants(const string &filename) { exportAcceptedApplicants(filename, masterApplicants); }
    MasterApplicant* findMasterApplicant(const string &id) { return findApplicant(id, masterApplicants); }
};