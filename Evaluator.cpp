#include "../header_files/Evaluator.h"
#include <unordered_map>
#include <typeinfo>

bool Evaluator::checkGrades(const vector<string> &profileSubjects, const int &maxGrade, const unordered_map <string, vector<int>> &grades) {
    bool hasGradeAboveMax = false;
    for (const auto &profileSubject : profileSubjects) {
        auto it = grades.find(profileSubject);
        if (it == grades.end()) {
            continue;
        }
        for (const auto &grade : it->second) {
            if (grade > maxGrade) {
                hasGradeAboveMax = true;
                break;
            }
        }
        if (!hasGradeAboveMax) {
            return true;
        }
        hasGradeAboveMax = false;
    }
    return false;
}


bool Evaluator::checkPercentile(const float &percentile, const float &requiredPercentile) {
    return percentile >= requiredPercentile;
}

float countGPA(const unordered_map <string, vector<int>> &grades) {
    float counter = 0.0;
    float total = 0.0;

    for (const auto &subject: grades) {
        for (const auto &grade: subject.second) {
            total += grade;
            counter++;
        }
    }
    return total / counter;
}

float Evaluator::evaluateBachelorApplicant(const BachelorApplicant& applicant) {
    return percentileWeight*applicant.getPercentileOfMathExam() + gpaWeightBachelor*(WORST_GPA - countGPA(applicant.getGrades()));
}

bool Evaluator::checkSubjects(const vector<string> &subjects, const vector<string> &profileSubjects) {
    return any_of(profileSubjects.begin(), profileSubjects.end(),[&](const std::string &profileSubject) {
                  return std::find(subjects.begin(), subjects.end(), profileSubject) != subjects.end();
                 });
}


void Evaluator::evaluateBachelorApplicants(vector<BachelorApplicant> &applicants, vector<BachelorsProgram> &bachelorsPrograms) {

    unordered_map<string, BachelorsProgram> programMap;
    for (const auto &program: bachelorsPrograms) {
        programMap[program.abbreviation] = program;
    }

    for (auto &applicant: applicants) {
        bool meetsCriteria = false;


        for (auto &preference : applicant.getPreferences()) {
            bool meetsCriteriaForPreference = false;
            bool criteriaMet = (programMap[preference].fieldOfStudy == "učiteľstvo")
                                ? checkSubjects(applicant.getStateExamSubjects(),
                                                programMap[preference].profileSubjects)
                                : (checkPercentile(applicant.getPercentileOfMathExam(),
                                    programMap[preference].minimumPercentileOfMathExam) ||
                                   checkGrades(programMap[preference].profileSubjects, programMap[preference].maxGrade, applicant.getGrades()));

            if (criteriaMet) {
                meetsCriteria = meetsCriteriaForPreference = true;
            }


            programApplicants[applicant.getUniqueID()][preference] = meetsCriteriaForPreference;

        }
        if (!meetsCriteria) {
            applicant.setTotalScore(DUMMY_NUM);
            applicant.setStatus(REJECTED_DUE_CRITERIA);
        } else {
            applicant.setTotalScore(evaluateBachelorApplicant(applicant));
        }
    }
}


bool Evaluator::checkGPA(const float &gpa, const float &requiredGPA) {
    return gpa <= requiredGPA;
}

bool Evaluator::checkEntranceExamScore(const float &entranceExamScore, const float &requiredEntranceExamScore) {
    return entranceExamScore >= requiredEntranceExamScore;
}

bool Evaluator::checkAverageOfStateExams(const float &averageOfStateExams, const float &requiredAverageOfStateExams) {
    return averageOfStateExams <= requiredAverageOfStateExams;
}


bool Evaluator::checkOnlyRequiresCompleted(const float &gpa, const float &entranceExamScore, const float &averageOfStateExams) {
    return gpa  == DUMMY_FLOAT && entranceExamScore == DUMMY_FLOAT && averageOfStateExams == DUMMY_FLOAT;
}

bool Evaluator::checkCompletedProgramme(const string &programme, const vector<string> &requiredBachelorsProgram) {
    return any_of(requiredBachelorsProgram.begin(), requiredBachelorsProgram.end(),[&](const std::string &requiredProgram){
        return programme == requiredProgram;
    });
}

bool Evaluator::checkCriteria(const float &gpa, const float &requiredGPA, const float &entranceExamScore, const float &requiredEntranceExamScore,
                   const float &averageOfStateExams, const float &requiredAverageOfStateExams,
                   const string &programme, const vector<string> &requiredBachelorsProgram) {
    return checkCompletedProgramme(programme, requiredBachelorsProgram) || (
           checkGPA(gpa, requiredGPA) ||
           checkEntranceExamScore(entranceExamScore, requiredEntranceExamScore) ||
           checkAverageOfStateExams(averageOfStateExams, requiredAverageOfStateExams));
}

float Evaluator::evaluateMasterApplicant(const MasterApplicant& applicant) {
    return gpaWeightMaster*(WORST_GPA - applicant.getGPA()) + averageWeight*(WORST_GPA - applicant.getAverageOfStateExams());
}

void Evaluator::evaluateMasterApplicants(std::vector<MasterApplicant> &applicants, vector<MastersProgram> &mastersPrograms, vector<BachelorsProgram> &bachelorsPrograms) {
    unordered_map<string, MastersProgram> programMap;
    unordered_map<string, BachelorsProgram> bachelorsProgramMap;
    for (const auto &program: mastersPrograms) {
        programMap[program.abbreviation] = program;
    }

    for (const auto &program: bachelorsPrograms) {
        bachelorsProgramMap[program.abbreviation] = program;
    }

    for (auto &applicant: applicants) {
        bool meetsCriteria = false;
        for (auto &preference : applicant.getPreferences()) {
            bool meetsCriteriaForPreference = false;
            bool criteriaMet = checkOnlyRequiresCompleted(
                        programMap[preference].maxGPA,
                        programMap[preference].minimumEntranceExamScore,
                        programMap[preference].maximumAverageOfStateExams)
                    ? checkCompletedProgramme(
                        bachelorsProgramMap[applicant.getCompletedBachelorProgram()].fieldOfStudy,
                        programMap[preference].requiredBachelorsProgram)
                    : checkCriteria(
                        applicant.getGPA(),
                        programMap[preference].maxGPA,
                        applicant.getEntranceExamScore(),
                        programMap[preference].minimumEntranceExamScore,
                        applicant.getAverageOfStateExams(),
                        programMap[preference].maximumAverageOfStateExams,
                        bachelorsProgramMap[applicant.getCompletedBachelorProgram()].name,
                        programMap[preference].requiredBachelorsProgram);

            if (criteriaMet) {
                meetsCriteria = meetsCriteriaForPreference = true;
            }

            programApplicants[applicant.getUniqueID()][preference] = meetsCriteriaForPreference;

        }
        if (!meetsCriteria) {
            applicant.setTotalScore(DUMMY_NUM);
            applicant.setStatus(REJECTED_DUE_CRITERIA);
        }
    }
}



