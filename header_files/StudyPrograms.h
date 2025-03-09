#pragma once

#include "StudyProgram.h"
#include <fstream>
#include <sstream>

const string CONVERSION_PROGRAM_STRING = "/k";
const char COMMA_DELIMITER = ',';
const char COLON_DELIMITER = ':';
const char SEMICOLON_DELIMITER = ';';
const char SPACE_DELIMETER = ' ';

class StudyPrograms {
  public:
    std::vector<BachelorsProgram> bachelorsPrograms;
    std::vector<MastersProgram> mastersPrograms;

    template <typename T>
    static T* getStudyProgram(std::vector<T>& programs, const std::string& abbreviation) {
        for (auto& program : programs) {
            if (program.abbreviation == abbreviation) {
                return &program;
            }
        }
        return nullptr;
    }

    template <typename T>
    static bool removeStudyProgram(std::vector<T> &programs, const std::string& abbreviation, bool removeConversionProgram = true) {

        T *program = getStudyProgram<T>(programs, abbreviation);
        if (program == nullptr) {
            return false;
        }

        if (removeConversionProgram) {
            std::string conversion = abbreviation + CONVERSION_PROGRAM_STRING;

            for (int i = 0; i < programs.size(); i++) {
                if (programs[i].abbreviation == conversion) {
                    programs.erase(programs.begin() + i);
                    break;
                }
            }
        }

        for (int i = 0; i < programs.size(); i++) {
            if (programs[i].abbreviation == abbreviation) {
                programs.erase(programs.begin() + i);
                return true;
            }
        }

        return false;
    };

    template <typename T>
    static bool changeNumberOfPlannedAdmissions(std::vector<T> &programs, const std::string &abbreviation, int newNumber) {

        if (newNumber < 1) {
            return false;
        }

        T *program = getStudyProgram(programs, abbreviation);

        if (program == nullptr) {
            return false;
        }

        program->numberOfPlannedAdmissions = newNumber;
        return true;

    }

    template <typename T>
    static int getNumberOfPlannedAdmissions(std::vector<T> &programs, const std::string &abbreviation) {
        T *program = getStudyProgram(programs, abbreviation);

        if (program == nullptr) {
            return NON_EXISTENT_NUM;
        }
        return program->numberOfPlannedAdmissions;
    }

    virtual ~StudyPrograms() = default;
};


class BachelorsPrograms: public StudyPrograms {
  public:
    bool loadPrograms(const std::string &filename);
    bool savePrograms(const std::string &filename);
    bool addStudyProgram(const std::string &name, const std::string &abbreviation, const std::string &field,
                         const std::vector<std::string> &profileSubjects=EMPTY_VECTOR, float percentile=-1, int numberOfPlannedAdmissions=1, int maxGrade=1);
    bool removeStudyProgram(const std::string &abbreviation, bool removeConversionProgram = true) {
        return StudyPrograms::removeStudyProgram<BachelorsProgram>(bachelorsPrograms, abbreviation, removeConversionProgram);
    }
    bool changeNumberOfPlannedAdmissions(const std::string &abbreviation, int newNumber) {
        return StudyPrograms::changeNumberOfPlannedAdmissions<BachelorsProgram>(bachelorsPrograms, abbreviation, newNumber);
    }
    BachelorsProgram *getStudyProgram(const std::string &abbreviation) {
        return StudyPrograms::getStudyProgram(bachelorsPrograms, abbreviation);
    }
    bool addProfileSubject(const std::string &abbreviation, const std::string &subject);
    bool removeProfileSubject(const std::string &abbreviation, const std::string &subject);
    bool changeRequiredPercentile(const std::string &abbreviation, float newPercentile);
    int getNumberOfPlannedAdmissions(const std::string &abbreviation) {
        return StudyPrograms::getNumberOfPlannedAdmissions<BachelorsProgram>(bachelorsPrograms, abbreviation);
    }
    float getMinimumPercentileOfMathExam(const std::string &abbreviation);
    std::vector<std::string> getProfileSubjects(const std::string &abbreviation);
};


class MastersPrograms: public StudyPrograms {
    public:
        bool loadPrograms(const std::string &filename);
        bool savePrograms(const std::string &filename);
        bool addStudyProgram(const std::string &name, const std::string &abbreviation, const std::string &field,
                         const std::vector<std::string> &programs=EMPTY_VECTOR, float gpa=-1, float score=-1, float average=-1,int numberOfPlannedAdmissions=1);
        bool removeStudyProgram(const std::string &abbreviation, bool removeConversionProgram = true) {
            return StudyPrograms::removeStudyProgram(mastersPrograms, abbreviation, removeConversionProgram);
        }
        bool changeNumberOfPlannedAdmissions(const std::string &abbreviation, int newNumber) {
            return StudyPrograms::changeNumberOfPlannedAdmissions<MastersProgram>(mastersPrograms, abbreviation, newNumber);
        }
        MastersProgram *getStudyProgram(const std::string &abbreviation) {
            return StudyPrograms::getStudyProgram(mastersPrograms, abbreviation);
        }
        bool changeMaxGPA(const std::string &abbreviation, float newGPA);
        bool changeMinimumEntranceExamScore(const std::string &abbreviation, float newEntrance);
        bool changeMaximumAverageOfStateExams(const std::string &abbreviation, float newMaximumAverage);
        int getNumberOfPlannedAdmissions(const std::string &abbreviation) {
            return StudyPrograms::getNumberOfPlannedAdmissions<MastersProgram>(mastersPrograms, abbreviation);
        }
        float getGPA(const std::string &abbreviation);
        float getMinimumEntranceExamScore(const std::string &abbreviation);
        float getMaximumAverageOfStateExams(const std::string &abbreviation);
        std::vector<std::string> getRequiredBachelorsProgram(const std::string &abbreviation);
};