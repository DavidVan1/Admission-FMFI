#pragma once

#include "Applicants.h"
#include <algorithm>

const float WORST_GPA = 4.0;

class Evaluator {
  public:

    float gpaWeightBachelor = 0.3;
    float percentileWeight = 0.7;

    float gpaWeightMaster = 0.7;
    float averageWeight = 0.9;

    unordered_map<string, unordered_map<string, bool>> programApplicants;

    void changeGpaWeightBachelor(const float &gpaWeightBachelor) { this->gpaWeightBachelor = gpaWeightBachelor; }
    void changePercentileWeight(const float &percentileWeight) { this->percentileWeight = percentileWeight; }

    void changeGpaWeightMaster(const float &gpaWeightMaster) { this->gpaWeightMaster = gpaWeightMaster; }
    void changeAverageWeight(const float &averageWeight) { this->averageWeight = averageWeight; }

    static bool checkGrades(const vector<string> &profileSubjects, const int &maxGrade, const unordered_map <string, vector<int>> &grades);
    static bool checkPercentile(const float &percentile, const float &requiredPercentile);
    static bool checkSubjects(const vector<string> &subjects, const vector<string> &profileSubjects);

    static bool checkGPA(const float &gpa, const float &requiredGPA);
    static bool checkEntranceExamScore(const float &entranceExamScore, const float &requiredEntranceExamScore);
    static bool checkAverageOfStateExams(const float &averageOfStateExams, const float &requiredAverageOfStateExams);
    static bool checkOnlyRequiresCompleted(const float &gpa, const float &entranceExamScore, const float &averageOfStateExams);
    static bool checkCompletedProgramme(const string &programme, const vector<string> &requiredBachelorsProgram);
    static bool checkCriteria(const float &gpa, const float &requiredGPA, const float &entranceExamScore, const float &requiredEntranceExamScore,
        const float &averageOfStateExams, const float &requiredAverageOfStateExams,
        const string &programme, const vector<string> &requiredBachelorsProgram);

    float evaluateBachelorApplicant(const BachelorApplicant& applicant);
    float evaluateMasterApplicant(const MasterApplicant& applicant);

    void evaluateBachelorApplicants(vector<BachelorApplicant> &applicants, vector<BachelorsProgram> &bachelorsPrograms);
    void evaluateMasterApplicants(vector<MasterApplicant> &applicants, vector<MastersProgram> &mastersPrograms, vector<BachelorsProgram> &bachelorsPrograms);

    template <typename T>
    static void sortApplicantsByTotalScore(vector<T>& applicants) {
            std::sort(applicants.begin(), applicants.end(),
              [](const Applicant& a, const Applicant& b) {
                  return a.getTotalScore() > b.getTotalScore();
              });
    }

};