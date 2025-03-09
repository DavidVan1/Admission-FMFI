#include "../header_files/Applicant.h"

BachelorApplicant::BachelorApplicant()
    : Applicant(), percentileOfMathExam(DUMMY_NUM), grades(EMPTY_MAP), stateExamSubjects(EMPTY_VECTOR) {}

BachelorApplicant::BachelorApplicant(string uniqueID,
    string name,
    vector<string> preferences,
    float percentileOfMathExam,
    unordered_map<string, vector<int> > grades,
    vector<string>stateExamSubjects)
    : Applicant(move(uniqueID), move(name), move(preferences)),
      percentileOfMathExam(percentileOfMathExam),
      grades(move(grades)),
      stateExamSubjects(move(stateExamSubjects)){}


MasterApplicant::MasterApplicant()
: Applicant(), completedBachelorProgram(EMPTY_STRING), GPA(DUMMY_NUM), entranceExamScore(DUMMY_NUM), averageOfStateExams(DUMMY_NUM) {}

MasterApplicant::MasterApplicant(string uniqueID,
    string name,
    vector<string> preferences,
    string completedBachelorProgram,
    float GPA,
    float entranceExamScore,
    float averageOfStateExams)
    : Applicant(move(uniqueID), move(name), move(preferences)),
      completedBachelorProgram(move(completedBachelorProgram)),
      GPA(GPA), entranceExamScore(entranceExamScore),
      averageOfStateExams(averageOfStateExams)  {}

