#include "../header_files/StudyProgram.h"

BachelorsProgram::BachelorsProgram() {
    name = EMPTY_STRING;
    abbreviation = EMPTY_STRING;
    fieldOfStudy = EMPTY_STRING;
    educationalLevel = Bachelor;
    profileSubjects = EMPTY_VECTOR;
    minimumPercentileOfMathExam = DUMMY_NUM;
    maxGrade = DUMMY_NUM;
}

BachelorsProgram::BachelorsProgram(std::string name,
             std::string abbreviation,
             std::string fieldOfStudy,
             std::vector<std::string> profileSubjects,
             float minimumPercentileOfMathExam,
             int numberOfPlannedAdmissions,
             int maxGrade)
            : StudyProgram(std::move(name),std::move(abbreviation), std::move(fieldOfStudy), numberOfPlannedAdmissions),
              profileSubjects(std::move(profileSubjects)),
              minimumPercentileOfMathExam(minimumPercentileOfMathExam), maxGrade(maxGrade) {}

MastersProgram::MastersProgram() {
    name = EMPTY_STRING;
    abbreviation = EMPTY_STRING;
    fieldOfStudy = EMPTY_STRING;
    numberOfPlannedAdmissions = DUMMY_NUM;
    educationalLevel = Master;
    requiredBachelorsProgram = EMPTY_VECTOR;
    maxGPA = DUMMY_NUM;
    minimumEntranceExamScore = DUMMY_NUM;
    maximumAverageOfStateExams = DUMMY_NUM;
}

MastersProgram::MastersProgram(std::string name,
    std::string abbreviation,
    std::string fieldOfStudy,
    std::vector<std::string> requiredBachelorsProgram,
    float maxGPA,
    float minimumEntranceExamScore,
    float maximumAverageOfStateExams,
    int numberOfPlannedAdmissions)
        : StudyProgram(std::move(name),std::move(abbreviation), std::move(fieldOfStudy), numberOfPlannedAdmissions),
          requiredBachelorsProgram(std::move(requiredBachelorsProgram)),
          maxGPA(maxGPA),
          minimumEntranceExamScore(minimumEntranceExamScore),
          maximumAverageOfStateExams(maximumAverageOfStateExams) {}