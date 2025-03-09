#include "../header_files/StudyPrograms.h"

bool MastersPrograms::loadPrograms(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, abbreviation, field, programsStr, gpaStr, scoreStr, averageStr, admissionsStr;

        if (std::getline(ss, name, COMMA_DELIMITER) &&
            std::getline(ss, abbreviation, COMMA_DELIMITER) &&
            std::getline(ss, field, COMMA_DELIMITER) &&
            std::getline(ss, programsStr, COMMA_DELIMITER) &&
            std::getline(ss, gpaStr, COMMA_DELIMITER) &&
            std::getline(ss, scoreStr, COMMA_DELIMITER) &&
            std::getline(ss, averageStr, COMMA_DELIMITER) &&
            std::getline(ss, admissionsStr, COMMA_DELIMITER)) {

            std::vector<std::string> programs;
            std::stringstream programsStream(programsStr);
            std::string program;
            while (std::getline(programsStream, program, SEMICOLON_DELIMITER)) {
                programs.push_back(program);
            }

            float gpa = std::stof(gpaStr);
            float score = std::stof(scoreStr);
            float average = std::stof(averageStr);
            int admissions = std::stoi(admissionsStr);
            MastersProgram newStudyProgram = MastersProgram();

            newStudyProgram.name = name;
            newStudyProgram.abbreviation = abbreviation;
            newStudyProgram.fieldOfStudy = field;
            newStudyProgram.requiredBachelorsProgram = programs;
            newStudyProgram.maxGPA = gpa;
            newStudyProgram.minimumEntranceExamScore = score;
            newStudyProgram.maximumAverageOfStateExams = average;
            newStudyProgram.numberOfPlannedAdmissions = admissions;

            mastersPrograms.emplace_back(newStudyProgram);
            }
    }

    file.close();
    return true;
}


bool MastersPrograms::savePrograms(const std::string &fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& program : mastersPrograms) {
        std::stringstream lineStream;

        lineStream << program.name << COMMA_DELIMITER
                   << program.abbreviation << COMMA_DELIMITER
                   << program.fieldOfStudy << COMMA_DELIMITER;

        for (size_t i = 0; i < program.requiredBachelorsProgram.size(); ++i) {
            lineStream << program.requiredBachelorsProgram[i];
            if (i != program.requiredBachelorsProgram.size() - 1) {
                lineStream << SEMICOLON_DELIMITER;
            }
        }
        lineStream << COMMA_DELIMITER;

        lineStream << program.maxGPA << COMMA_DELIMITER
                   << program.minimumEntranceExamScore << COMMA_DELIMITER
                   << program.maximumAverageOfStateExams << COMMA_DELIMITER
                   << program.numberOfPlannedAdmissions;

        file << lineStream.str() << "\n";
    }

    file.close();
    return true;
}

bool MastersPrograms::addStudyProgram(const std::string &name, const std::string &abbreviation, const std::string &field,
                         const std::vector<std::string> &programs, float gpa, float score, float average,int numberOfPlannedAdmissions) {

    if (getStudyProgram(abbreviation) != nullptr) {
        return false;
    }

    if (field.empty() || numberOfPlannedAdmissions <= 0) {
        return false;
    }

    MastersProgram newStudyProgram = MastersProgram(name, abbreviation, field, programs, gpa, score, average, numberOfPlannedAdmissions);
    mastersPrograms.emplace_back(newStudyProgram);
    return true;
}

bool MastersPrograms::changeMaxGPA(const std::string &abbreviation, float newGPA) {

    if (newGPA < -1 || !(newGPA >= 1 && newGPA <= 4)) {
        return false;
    }

    MastersProgram *temp = getStudyProgram(abbreviation);
    if (temp == nullptr) {
        return false;
    }
    temp->maxGPA = newGPA;
    return true;
}


bool MastersPrograms::changeMinimumEntranceExamScore(const std::string &abbreviation, float newEntrance) {

    if (newEntrance < -1 || newEntrance == 0) {
        return false;
    }

    MastersProgram *temp = getStudyProgram(abbreviation);
    if (temp == nullptr) {
        return false;
    }
    temp->minimumEntranceExamScore = newEntrance;
    return true;
}

bool MastersPrograms::changeMaximumAverageOfStateExams(const std::string &abbreviation, float newMaximumAverage) {

    if (newMaximumAverage < -1 || !(newMaximumAverage >= 1 && newMaximumAverage <= 4)) {
        return false;
    }

    MastersProgram *temp = getStudyProgram(abbreviation);
    if (temp == nullptr) {
        return false;
    }
    temp->maximumAverageOfStateExams = newMaximumAverage;
    return true;
}


float MastersPrograms::getGPA(const std::string &abbreviation) {
    MastersProgram *temp = getStudyProgram(abbreviation);
    if (temp == nullptr) {
        return NON_EXISTENT_NUM;
    }
    return temp->maxGPA;

}
float MastersPrograms::getMinimumEntranceExamScore(const std::string &abbreviation) {
    MastersProgram *temp = getStudyProgram(abbreviation);
    if (temp == nullptr) {
        return NON_EXISTENT_NUM;
    }
    return temp->minimumEntranceExamScore;
}
float MastersPrograms::getMaximumAverageOfStateExams(const std::string &abbreviation) {
    MastersProgram *temp = getStudyProgram(abbreviation);
    if (temp == nullptr) {
        return NON_EXISTENT_NUM;
    }
    return temp->maximumAverageOfStateExams;
}

std::vector<std::string> MastersPrograms::getRequiredBachelorsProgram(const std::string &abbreviation) {
    MastersProgram *temp = getStudyProgram(abbreviation);
    if (temp == nullptr) {
        return EMPTY_VECTOR;
    }
    return temp->requiredBachelorsProgram;
}