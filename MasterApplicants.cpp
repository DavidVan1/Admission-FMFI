#include "../header_files/Applicants.h"

bool MasterApplicants::loadMasterApplicants(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, completedBachelor, gpaStr, entranceExamStr, averageStr, preferenceStr;

        if (getline(ss, id, COMMA_DELIMITER) &&
            getline(ss, name, COMMA_DELIMITER) &&
            getline(ss, completedBachelor, COMMA_DELIMITER) &&
            getline(ss, gpaStr, COMMA_DELIMITER) &&
            getline(ss, entranceExamStr, COMMA_DELIMITER) &&
            getline(ss, averageStr, COMMA_DELIMITER) &&
            getline(ss, preferenceStr, COMMA_DELIMITER)) {

            float gpa = stof(gpaStr);
            float entrance = stof(entranceExamStr);
            float average = stof(averageStr);

            vector<string> preferences0;
            stringstream preferenceStream(preferenceStr);
            string pref;
            while (getline(preferenceStream, pref, SEMICOLON_DELIMITER)) {
                pref = trim(pref);
                if (!pref.empty()) {
                    preferences0.push_back(pref);
                }
            }

            MasterApplicant newMasterApplicant = MasterApplicant(id, name, preferences0, completedBachelor, gpa, entrance, average);
            masterApplicants.push_back(newMasterApplicant);
        }
    }
    return true;
}
