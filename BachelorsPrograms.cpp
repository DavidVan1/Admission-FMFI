#include "../header_files/StudyPrograms.h"

bool BachelorsPrograms::loadPrograms(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, abbreviation, field,subjectsStr, percentileStr, admissionsStr, maxGradeStr;

        if (std::getline(ss, name, COMMA_DELIMITER) &&
            std::getline(ss, abbreviation, COMMA_DELIMITER) &&
            std::getline(ss, field, COMMA_DELIMITER) &&
            std::getline(ss, subjectsStr, COMMA_DELIMITER) &&
            std::getline(ss, percentileStr, COMMA_DELIMITER) &&
            std::getline(ss, admissionsStr, COMMA_DELIMITER) &&
            std::getline(ss, maxGradeStr)) {

            std::vector<std::string> subjects;
            std::stringstream subjectsStream(subjectsStr);
            std::string subject;
            while (std::getline(subjectsStream, subject, SEMICOLON_DELIMITER)) {
                subjects.push_back(subject);
            }

            float percentile = std::stof(percentileStr);
            int plannedAdmissions = std::stoi(admissionsStr);
            int maxGrade0 = std::stoi(maxGradeStr);
            BachelorsProgram newStudyProgram = BachelorsProgram();

            newStudyProgram.name = name;
            newStudyProgram.abbreviation = abbreviation;
            newStudyProgram.fieldOfStudy = field;
            newStudyProgram.profileSubjects = subjects;
            newStudyProgram.minimumPercentileOfMathExam = percentile;
            newStudyProgram.numberOfPlannedAdmissions = plannedAdmissions;
            newStudyProgram.maxGrade = maxGrade0;

            bachelorsPrograms.emplace_back(newStudyProgram);
            }
    }

    file.close();
    return true;
}

bool BachelorsPrograms::savePrograms(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (const auto &program : bachelorsPrograms) {
        file << program.name << COMMA_DELIMITER
             << program.abbreviation << COMMA_DELIMITER
             << program.fieldOfStudy << COMMA_DELIMITER;

        for (size_t i = 0; i < program.profileSubjects.size(); ++i) {
            file << program.profileSubjects[i];
            if (i < program.profileSubjects.size() - 1) {
                file << SEMICOLON_DELIMITER;
            }
        }
        file << COMMA_DELIMITER << program.minimumPercentileOfMathExam;
        file << COMMA_DELIMITER << program.numberOfPlannedAdmissions;
        file << COMMA_DELIMITER << program.maxGrade << "\n";
    }

    file.close();
    return true;
}


bool BachelorsPrograms::addStudyProgram(const std::string &name, const std::string &abbreviation, const std::string &field,
                                    const std::vector<std::string> &profileSubjects, float percentile,int numberOfPlannedAdmissions, int maxGrade) {

    if (percentile < 0 || percentile > 100 || numberOfPlannedAdmissions < 0) {
        return false;
    }

    if (getStudyProgram(abbreviation) != nullptr) {
        return false;
    }

    BachelorsProgram newStudyProgram = BachelorsProgram(name, abbreviation, field,profileSubjects, percentile,numberOfPlannedAdmissions, maxGrade);
    bachelorsPrograms.emplace_back(newStudyProgram);
    return true;
}


bool BachelorsPrograms::addProfileSubject(const std::string &abbreviation, const std::string &subject) {

    BachelorsProgram *temp = getStudyProgram(abbreviation);

    for (auto &profileSubject : temp->profileSubjects) {
        if (subject == profileSubject) {
            return false;
        }
    }

    if (temp == nullptr) {
        return false;
    }

    temp->profileSubjects.push_back(subject);
    return true;
}


bool BachelorsPrograms::removeProfileSubject(const std::string &abbreviation, const std::string &subject) {
    BachelorsProgram *temp = getStudyProgram(abbreviation);

    if (temp == nullptr) {
        return false;
    }

    for (int i = 0; i < temp->profileSubjects.size(); ++i) {
        if (temp->profileSubjects[i] == subject) {
            temp->profileSubjects.erase(temp->profileSubjects.begin() + i);
            return true;
        }
    }

    return false;
}

bool BachelorsPrograms::changeRequiredPercentile(const std::string &abbreviation, float newPercentile) {

    if (newPercentile < -1 || newPercentile > 100 || newPercentile == 0) {
        return false;
    }

    BachelorsProgram *temp = getStudyProgram(abbreviation);
    if (temp == nullptr) {
        return false;
    }
    temp->minimumPercentileOfMathExam = newPercentile;
    return true;
}

float BachelorsPrograms::getMinimumPercentileOfMathExam(const std::string &abbreviation) {
    BachelorsProgram *temp = getStudyProgram(abbreviation);

    if (temp == nullptr) {
        return NON_EXISTENT_NUM;
    }
    return temp->minimumPercentileOfMathExam;
}

std::vector<std::string> BachelorsPrograms::getProfileSubjects(const std::string &abbreviation) {
    BachelorsProgram *temp = getStudyProgram(abbreviation);

    if (temp == nullptr) {
        return EMPTY_VECTOR;
    }
    return temp->profileSubjects;
}
