#pragma once

#include <unordered_map>

#include "StudyPrograms.h"

enum ApplicantStatus {PENDING, ACCEPTED, REJECTED_DUE_CRITERIA, REJECTED_DUE_CAPACITY};
const string StatusType[] = {"PENDING", "ACCEPTED", "REJECTED BY NOT MEETING CRITERIA", "REJECTUED DUE TO LACK OF CAPACITY"};
const unordered_map <string, vector<int>> EMPTY_MAP;

class Applicant {
    string uniqueID;
    string name;
    float totalScore = DUMMY_NUM;
    ApplicantStatus status = PENDING;
    vector<string> preferences;
    string finalAdmission = EMPTY_STRING;
 public:
    Applicant() : uniqueID(EMPTY_STRING), name(EMPTY_STRING), preferences(EMPTY_VECTOR) {};
    Applicant(string uniqueID, string name, vector<string> preferences)
             : uniqueID(move(uniqueID)), name(move(name)), preferences(move(preferences)) {};
    virtual ~Applicant() = default;

    [[nodiscard]] ApplicantStatus getStatus() const { return status; }
    [[nodiscard]] const string& getUniqueID() const { return uniqueID; }
    [[nodiscard]] const string& getName() const { return name; }
    [[nodiscard]] float getTotalScore() const { return totalScore; }
    [[nodiscard]] string getFinalAdmission() const { return finalAdmission; }
    void setStatus(ApplicantStatus status) { this->status = status; }
    void setTotalScore(float totalScore) { this->totalScore = totalScore; }
    [[nodiscard]] vector<string> getPreferences() const { return preferences; }
    void setFinalAdmission(const string &finalAdmission) { this->finalAdmission = finalAdmission; }
};


class BachelorApplicant : public Applicant {
    float percentileOfMathExam;
    unordered_map <string, vector<int>> grades;
    vector<string> stateExamSubjects;
 public:
    BachelorApplicant();
    BachelorApplicant(string uniqueID, string name, vector<string> preferences,float percentileOfMathExam, unordered_map <string, vector<int>> grades, vector<string> stateExamSubjects);
    [[nodiscard]] float getPercentileOfMathExam() const { return percentileOfMathExam; }
    [[nodiscard]] unordered_map <string, vector<int>> getGrades() const { return grades; }
    [[nodiscard]] vector<string> getStateExamSubjects() const { return stateExamSubjects; }
    bool operator==(const BachelorApplicant& other) const {
        return (getUniqueID() == other.getUniqueID()) && (getName() == other.getName());
    }
};


class MasterApplicant : public Applicant {
    string completedBachelorProgram;
    float GPA;
    float entranceExamScore;
    float averageOfStateExams;
 public:
    MasterApplicant();
    MasterApplicant(string uniqueID, string name, vector<string> preferences, string completedBachelorProgram,
                    float GPA, float entranceExamScore, float averageOfStateExams);
    [[nodiscard]] float getGPA() const { return GPA; }
    [[nodiscard]] float getEntranceExamScore() const { return entranceExamScore; }
    [[nodiscard]] float getAverageOfStateExams() const { return averageOfStateExams; }
    const string& getCompletedBachelorProgram() { return completedBachelorProgram; }
};