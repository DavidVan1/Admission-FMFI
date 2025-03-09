#pragma once

#include "Evaluator.h"

class Admit {
 public:
    template <typename Applicant, typename Program>
    static void admitApplicants(vector<Applicant> &applicants,
                                vector<Program> &programs, unordered_map<string,
                                unordered_map<string, bool>> &programApplicants) {

        unordered_map<string, int> programMap;
        for (Program &program : programs) {
            programMap[program.abbreviation] = program.numberOfPlannedAdmissions;
        }

        for (Applicant &applicant : applicants) {

            if (applicant.getStatus() == REJECTED_DUE_CRITERIA) { continue; }

            bool admitted = false;

            for (const auto &preference : applicant.getPreferences()) {
                bool meetsCriteria = programApplicants[applicant.getUniqueID()][preference];

                if (meetsCriteria && programMap[preference] > 0) {
                    applicant.setFinalAdmission(preference);
                    applicant.setStatus(ACCEPTED);
                    programMap[preference]--;
                    admitted = true;
                    break;
                }
            }

            if (!admitted) {
                applicant.setStatus(REJECTED_DUE_CAPACITY);
            }
        }
    }
};