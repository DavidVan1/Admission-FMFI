#pragma once
#include <iostream>
#include <vector>
using namespace std;

const std::vector<std::string> EMPTY_VECTOR;
const std::string EMPTY_STRING;
const int DUMMY_NUM = -1;
const int NON_EXISTENT_NUM = -2;
const float DUMMY_FLOAT = -1.0;

enum EducationalLevel {
    Bachelor,
    Master
};

class StudyProgram {
public:
    std::string name;
    std::string abbreviation;
    std::string fieldOfStudy;
    int numberOfPlannedAdmissions;
    StudyProgram()
    : name(EMPTY_STRING), abbreviation(EMPTY_STRING), fieldOfStudy(EMPTY_STRING), numberOfPlannedAdmissions(DUMMY_NUM) {}
    StudyProgram(std::string name, std::string abbreviation, std::string fieldOfStudy, int numberOfPlannedAdmissions)
        : name(std::move(name)),
          abbreviation(std::move(abbreviation)),
          fieldOfStudy(std::move(fieldOfStudy)),
          numberOfPlannedAdmissions(numberOfPlannedAdmissions){}
    virtual ~StudyProgram() = default;
};


class BachelorsProgram: public StudyProgram {
public:
    EducationalLevel educationalLevel = Bachelor;
    std::vector<std::string> profileSubjects;
    float minimumPercentileOfMathExam;
    int maxGrade;
    BachelorsProgram();
    BachelorsProgram(std::string name,
                      std::string abbreviation,
                      std::string fieldOfStudy,
                      std::vector<std::string> profileSubjects,
                      float minimumPercentileOfMathExam,
                      int numberOfPlannedAdmissions,
                      int maxGrade);
};


class MastersProgram: public StudyProgram {
public:
    EducationalLevel educationalLevel = Master;
    std::vector<std::string> requiredBachelorsProgram;
    float maxGPA;
    float minimumEntranceExamScore;
    float maximumAverageOfStateExams;
    MastersProgram();
    MastersProgram(std::string name,
                   std::string abbreviation,
                   std::string fieldOfStudy,
                   std::vector<std::string> requiredBachelorsProgram,
                   float maxGPA,
                   float minimumEntranceExamScore,
                   float maximumAverageOfStateExams,
                   int numberOfPlannedAdmissions);

};