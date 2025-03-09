#include <iostream>
#include "gtest/gtest.h"
#include <typeinfo>

#include "../header_files/Applicants.h"
#include "../header_files/Evaluator.h"
#include "../header_files/Admit.h"

using namespace ::testing;

TEST(Test3, loadBachelorApplicants) {
    BachelorApplicants applicants;
    applicants.loadBachelorApplicants("../csv_files//bachelorapplicants.txt");
    ASSERT_EQ(202, applicants.bachelorApplicants.size());
}

TEST(Test3, findApplicant) {
    BachelorApplicants applicants;
    applicants.loadBachelorApplicants("../csv_files//bachelorapplicants.txt");
    BachelorApplicant* smo = applicants.findBachelorApplicant("58");
    ASSERT_EQ("Peter Horváth", smo->getName());
    ASSERT_EQ("58", smo->getUniqueID());
    float n = 78.7;
    ASSERT_EQ(n, smo->getPercentileOfMathExam());
    ASSERT_EQ("DAV", smo->getPreferences()[0]);
}

TEST(Test3, evaluate) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    BachelorApplicants applicants;
    applicants.loadBachelorApplicants("../csv_files/bachelorapplicants.txt");
    Evaluator evaluator;
    evaluator.evaluateBachelorApplicants(applicants.bachelorApplicants, programs.bachelorsPrograms);
    BachelorApplicant* smo = applicants.findBachelorApplicant("201");
    BachelorApplicant* smo2 = applicants.findBachelorApplicant("58");
    ASSERT_EQ(REJECTED_DUE_CRITERIA, smo->getStatus());
    ASSERT_EQ(PENDING, smo2->getStatus());
}

TEST(Test3, sort) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    BachelorApplicants applicants;
    applicants.loadBachelorApplicants("../csv_files/bachelorapplicants.txt");
    Evaluator evaluator;
    evaluator.evaluateBachelorApplicants(applicants.bachelorApplicants, programs.bachelorsPrograms);
    evaluator.sortApplicantsByTotalScore(applicants.bachelorApplicants);
    ASSERT_EQ("202", applicants.bachelorApplicants[0].getUniqueID());
    ASSERT_EQ("201", applicants.bachelorApplicants[201].getUniqueID());
}

TEST(Test3, admit) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    BachelorApplicants applicants;
    applicants.loadBachelorApplicants("../csv_files/bachelorapplicants.txt");
    Evaluator evaluator;
    evaluator.evaluateBachelorApplicants(applicants.bachelorApplicants, programs.bachelorsPrograms);
    evaluator.sortApplicantsByTotalScore(applicants.bachelorApplicants);
    Admit admit;
    admit.admitApplicants(applicants.bachelorApplicants, programs.bachelorsPrograms, evaluator.programApplicants);
    BachelorApplicant* smo = applicants.findBachelorApplicant("58");
    BachelorApplicant* smo2 = applicants.findBachelorApplicant("202");
    BachelorApplicant* smo3 = applicants.findBachelorApplicant("201");
    ASSERT_EQ("upINCH", smo->getFinalAdmission());
    ASSERT_EQ("DAV", smo2->getFinalAdmission());
    ASSERT_EQ(EMPTY_STRING, smo3->getFinalAdmission());
}

TEST(Test3, admit2) {
    BachelorsProgram program("Dátová veda", "DAV", "matematika", {"matematika", "informatika"}, 80, 3, 2);
    BachelorsPrograms programs;
    programs.bachelorsPrograms.push_back(program);

    std::unordered_map<std::string, std::vector<int>> grades1 = {{"matematika", {1, 1, 1, 1}}, {"fyzika", {1, 1, 1, 1}}};
    std::unordered_map<std::string, std::vector<int>> grades2 = {{"matematika", {1, 1, 2, 1}}, {"informatika", {1, 3, 1, 1}}};
    BachelorApplicant applicant1("1", "Martin Horvath", {"DAV"}, 80, grades1, {"matematika", "fyzika"});
    BachelorApplicant applicant2("2", "Denis Kováč", {"DAV"}, 70, grades1, {"matematika", "informatika"});
    BachelorApplicant applicant3("3", "Peter Veľký", {"DAV"}, 75, grades1, {"matematika", "fyzika"});
    BachelorApplicant applicant4("4", "Adamnda Konečná", {"DAV"}, 62, grades2, {"informatika", "fyzika"});

    BachelorApplicants applicants;
    applicants.bachelorApplicants.push_back(applicant1);
    applicants.bachelorApplicants.push_back(applicant2);
    applicants.bachelorApplicants.push_back(applicant3);
    applicants.bachelorApplicants.push_back(applicant4);

    Evaluator evaluator;
    evaluator.evaluateBachelorApplicants(applicants.bachelorApplicants, programs.bachelorsPrograms);
    evaluator.sortApplicantsByTotalScore(applicants.bachelorApplicants);
    Admit admit;
    admit.admitApplicants(applicants.bachelorApplicants, programs.bachelorsPrograms, evaluator.programApplicants);
    BachelorApplicant* smo1 = applicants.findBachelorApplicant("1");
    BachelorApplicant* smo2 = applicants.findBachelorApplicant("4");
    ASSERT_EQ(ACCEPTED, smo1->getStatus());
    ASSERT_EQ(REJECTED_DUE_CAPACITY, smo2->getStatus());
}

TEST(Test3, changeWeight) {
    BachelorsProgram program("Dátová veda", "DAV", "matematika", {"matematika", "informatika"}, 80, 1, 2);
    BachelorsPrograms programs;
    programs.bachelorsPrograms.push_back(program);

    std::unordered_map<std::string, std::vector<int>> grades1 = {{"matematika", {1, 1, 1, 1}}, {"telesná", {1, 1, 1, 1}}};
    std::unordered_map<std::string, std::vector<int>> grades2 = {{"matematika", {1, 3, 4, 1}}, {"fyzika", {1, 1, 1, 1}}};
    BachelorApplicant applicant1("1", "Martin Horvath", {"DAV"}, 80, grades2, {"matematika", "fyzika"});
    BachelorApplicant applicant2("2", "Denis Kováč", {"DAV"}, 70, grades1, {"matematika", "informatika"});


    BachelorApplicants applicants;
    applicants.bachelorApplicants.push_back(applicant1);
    applicants.bachelorApplicants.push_back(applicant2);

    Evaluator evaluator;
    evaluator.evaluateBachelorApplicants(applicants.bachelorApplicants, programs.bachelorsPrograms);
    evaluator.sortApplicantsByTotalScore(applicants.bachelorApplicants);
    Admit admit;
    admit.admitApplicants(applicants.bachelorApplicants, programs.bachelorsPrograms, evaluator.programApplicants);

    BachelorApplicant* smo1 = applicants.findBachelorApplicant("1");
    BachelorApplicant* smo2 = applicants.findBachelorApplicant("2");

    ASSERT_EQ(ACCEPTED, smo1->getStatus());
    ASSERT_EQ(REJECTED_DUE_CAPACITY, smo2->getStatus());

    evaluator.changePercentileWeight(0);
    evaluator.evaluateBachelorApplicants(applicants.bachelorApplicants, programs.bachelorsPrograms);
    evaluator.sortApplicantsByTotalScore(applicants.bachelorApplicants);
    admit.admitApplicants(applicants.bachelorApplicants, programs.bachelorsPrograms, evaluator.programApplicants);

    BachelorApplicant* smo3 = applicants.findBachelorApplicant("1");
    BachelorApplicant* smo4 = applicants.findBachelorApplicant("2");
    ASSERT_EQ(REJECTED_DUE_CAPACITY, smo3->getStatus());
    ASSERT_EQ(ACCEPTED, smo4->getStatus());
}


TEST(Test4, loadMaster) {
    MasterApplicants applicants;
    applicants.loadMasterApplicants("../csv_files/masterapplicants.txt");
    ASSERT_EQ(200, applicants.masterApplicants.size());
}

TEST(Test4, findApplicant) {
    MasterApplicants applicants;
    applicants.loadMasterApplicants("../csv_files/masterapplicants.txt");
    MasterApplicant* smo1 = applicants.findMasterApplicant("1169");
    ASSERT_EQ("Alena Svoboda", smo1->getName());
}

TEST(Test4, admit) {
    BachelorsPrograms bcprograms;
    bcprograms.loadPrograms("../csv_files/bachelorsprograms.csv");

    MastersPrograms programs;
    programs.loadPrograms("../csv_files/mastersprograms.csv");

    MasterApplicants applicants;
    applicants.loadMasterApplicants("../csv_files/masterapplicants.txt");
    ASSERT_EQ(true, programs.mastersPrograms.size() > 0);

    Evaluator evaluator;
    evaluator.evaluateMasterApplicants(applicants.masterApplicants, programs.mastersPrograms, bcprograms.bachelorsPrograms);

    MasterApplicant* smo1 = applicants.findMasterApplicant("1082");
    float n = 3;
    ASSERT_EQ(n, smo1->getGPA());
    ASSERT_EQ(n, smo1->getAverageOfStateExams());
    ASSERT_EQ(REJECTED_DUE_CRITERIA, smo1->getStatus());

    MasterApplicant* smo2 = applicants.findMasterApplicant("1003");
    ASSERT_EQ(PENDING, smo2->getStatus());

    evaluator.sortApplicantsByTotalScore(applicants.masterApplicants);

    Admit admit;
    admit.admitApplicants(applicants.masterApplicants, programs.mastersPrograms, evaluator.programApplicants);
    applicants.exportMasterApplicants("../csv_files/admitedMaster.txt");
}
