//#include <iomanip>

#include "../header_files/Applicants.h"
#include <typeinfo>

bool BachelorApplicants::loadBachelorApplicants(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, nameStr, percentileStr, gradesStr, subjectsStr, preferenceStr;

        if (getline(ss, id, COMMA_DELIMITER) &&
            getline(ss, nameStr, COMMA_DELIMITER) &&
            getline(ss, percentileStr, COMMA_DELIMITER) &&
            getline(ss, gradesStr, COMMA_DELIMITER) &&
            getline(ss, subjectsStr, COMMA_DELIMITER) &&
            getline(ss, preferenceStr, COMMA_DELIMITER)) {

            float percentile = stof(percentileStr);

            unordered_map<string, vector<int>> grades;
            stringstream gradesStream(gradesStr);
            string sub;
            while (getline(gradesStream, sub, SEMICOLON_DELIMITER)) {
                string subject, marksStr;
                stringstream subjectStream(sub);
                if (getline(subjectStream, subject, COLON_DELIMITER)) {
                    vector<int> marks;
                    while (getline(subjectStream, marksStr, SPACE_DELIMETER)) {
                        if (!marksStr.empty()) {
                            marks.push_back(stoi(marksStr));
                        }
                    }
                    grades[subject] = marks;
                }
            }

            vector<string> stateExamSubjects;
            stringstream subjectsStream(subjectsStr);
            string subjectToken; // Temporary variable
            while (getline(subjectsStream, subjectToken, SEMICOLON_DELIMITER)) {
                stateExamSubjects.push_back(trim(subjectToken));
            }

            vector<string> preferences0;
            stringstream preferenceStream(preferenceStr);
            string pref;
            while (getline(preferenceStream, pref, SEMICOLON_DELIMITER)) {
                pref = trim(pref);
                if (!pref.empty()) {
                    preferences0.push_back(pref);
                }
            }

            BachelorApplicant newBachelorApplicant = BachelorApplicant(
                id, nameStr, preferences0, percentile, grades, stateExamSubjects);
            bachelorApplicants.push_back(newBachelorApplicant);
        }
    }
    file.close();
    return true;
}

void BachelorApplicants::printApplicants(const vector<BachelorApplicant>& applicants) {
    for (const auto& applicant : applicants) {
        cout << "ID: " << applicant.getUniqueID() << ", Name: " << applicant.getName()
             << ", TotalScore: " << applicant.getTotalScore()
             << ", Status: " << StatusType[applicant.getStatus()] <<endl;

        cout << "Percentile of Math exam: " << applicant.getPercentileOfMathExam() << endl;
        cout << "Admitted to: " << applicant.getFinalAdmission() << endl;
        cout << "Grades:\n";
        for (const auto& [subject, marks] : applicant.getGrades()) {
            cout << "  " << subject << ": ";
            for (int mark : marks) {
                cout << mark << " ";
            }
            cout << endl;
        }
        cout << "----------------------\n";
    }
}
