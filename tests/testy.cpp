#include <iostream>
#include "gtest/gtest.h"
#include <typeinfo>

#include "../header_files/Applicants.h"
#include "../header_files/Evaluator.h"
#include "../header_files/Admit.h"

using namespace ::testing;

TEST(Test1, loadBachelor) {
    BachelorsPrograms programs;
    ASSERT_EQ(1, programs.loadPrograms("../csv_files/bachelorsprograms.csv"));
    ASSERT_EQ(27, programs.bachelorsPrograms.size());
}

TEST(Test1, saveBachelor) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    programs.savePrograms("../csv_files/new.csv");
    BachelorsPrograms savedPrograms;
    ASSERT_EQ(1, savedPrograms.loadPrograms("../csv_files/new.csv"));
    ASSERT_EQ(27, savedPrograms.bachelorsPrograms.size());
}

TEST(Test1, addStudy) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    std::vector<std::string> subjects = {"matematika"};
    ASSERT_EQ(1,programs.addStudyProgram("Aplikovaná algebra", "ALG", "matematika", subjects, 80, 20));
    ASSERT_EQ(28, programs.bachelorsPrograms.size());
    programs.addStudyProgram("Aplikovaná analýza", "ANA", "matematika", subjects, 80, 20);
    programs.addStudyProgram("Aplikované matematicko-stochastické metódy", "MSM", "matematika", subjects, 80, 10);
    ASSERT_EQ(30, programs.bachelorsPrograms.size());
}

TEST(Test1, getStudyProgram) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    BachelorsProgram *physics = programs.getStudyProgram("FYZ");
    ASSERT_EQ("Fyzika", physics->name);
    BachelorsProgram *physicsConversion = programs.getStudyProgram("FYZ/k");
    ASSERT_EQ("Fyzika konverzný program", physicsConversion->name);
    BachelorsProgram *nothing = programs.getStudyProgram("KKK");
    ASSERT_EQ(nullptr, nothing);
}


TEST(Test1, failedAddStudy) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    std::vector<std::string> subjects = {"matematika"};
    ASSERT_EQ(0,programs.addStudyProgram("Dátová veda", "DAV", "matematika", subjects, 80, 30));
    ASSERT_EQ(27,programs.bachelorsPrograms.size());
    ASSERT_EQ(0, programs.addStudyProgram("Aplikovaná analýza", "ANA", "matematika", subjects, 105, 30));
    ASSERT_EQ(27,programs.bachelorsPrograms.size());
}

TEST(Test1, removeProgram) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    ASSERT_EQ(1, programs.removeStudyProgram("DAV", false));
    ASSERT_EQ(1, programs.removeStudyProgram("MAT", false));
    ASSERT_EQ(25, programs.bachelorsPrograms.size());
    ASSERT_EQ(0, programs.removeStudyProgram("DAV", true));
    ASSERT_EQ(1, programs.removeStudyProgram("DAV/k", false));
    ASSERT_EQ(24, programs.bachelorsPrograms.size());
}

TEST(Test1, removeWithConversion) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    ASSERT_EQ(1, programs.removeStudyProgram("DAV"));
    ASSERT_EQ(25, programs.bachelorsPrograms.size());
    programs.removeStudyProgram("BIN");
    programs.removeStudyProgram("TEF", true);
    ASSERT_EQ(21, programs.bachelorsPrograms.size());
}

TEST(Test1, failedRemoval) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    programs.removeStudyProgram("DAV", false);
    programs.removeStudyProgram("MAT", false);
    programs.removeStudyProgram("BIN", true);
    ASSERT_EQ(0, programs.removeStudyProgram("BIN"));
    ASSERT_EQ(0, programs.removeStudyProgram("DDD", true));
    programs.removeStudyProgram("TEFFF", true);
    programs.removeStudyProgram("MAT", true);
    programs.removeStudyProgram("DAV", true);
    ASSERT_EQ(23, programs.bachelorsPrograms.size());
}

TEST(Test1, changeNumberOfAdmission) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    BachelorsProgram *mathematics = programs.getStudyProgram("MAT");
    ASSERT_EQ(40, mathematics->numberOfPlannedAdmissions);
    programs.changeNumberOfPlannedAdmissions("MAT", 20);
    ASSERT_EQ(20, mathematics->numberOfPlannedAdmissions);
    programs.changeNumberOfPlannedAdmissions("MAT", 10);
    ASSERT_EQ(10, mathematics->numberOfPlannedAdmissions);
}

TEST(Test1, failedChangeOfAdmissions) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    BachelorsProgram *bioinformatics = programs.getStudyProgram("BIN");
    programs.changeNumberOfPlannedAdmissions("BIN", -10);
    ASSERT_EQ(15, bioinformatics->numberOfPlannedAdmissions);
    programs.changeNumberOfPlannedAdmissions("upMADG", 10);
    ASSERT_EQ(10, programs.getNumberOfPlannedAdmissions("upMADG"));
}

TEST(Test1, addProfileSubject) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    programs.addProfileSubject("DAV", "chémia");
    std::vector<std::string> subjects = {"informatika", "matematika", "chémia"};
    ASSERT_EQ(subjects.size(), programs.getProfileSubjects("DAV").size());
    ASSERT_EQ(0, programs.addProfileSubject("DAV", "informatika"));
    ASSERT_EQ(3, programs.getProfileSubjects("DAV").size());
}

TEST(Test1, removeProfileSubjcet) {
    BachelorsPrograms programs;
    programs.loadPrograms("../csv_files/bachelorsprograms.csv");
    programs.removeProfileSubject("BIN", "informatika");
    programs.removeProfileSubject("BIN", "chémia");
    ASSERT_EQ(2, programs.getProfileSubjects("BIN").size());
    ASSERT_EQ(0, programs.removeProfileSubject("BIN", "chémia"));
    ASSERT_EQ(0, programs.removeProfileSubject("DAV", "chémia"));
}

TEST(Test2, loadMastersAndSave) {
    MastersPrograms programs;
    ASSERT_EQ(1,programs.loadPrograms("../csv_files/mastersprograms.csv"));
    ASSERT_EQ(31, programs.mastersPrograms.size());
    programs.savePrograms("../csv_files/newMastersprograms.csv");
    MastersPrograms newPrograms;
    newPrograms.loadPrograms("../csv_files/newMastersprograms.csv");
    ASSERT_EQ(31, newPrograms.mastersPrograms.size());
    MastersProgram *teachingProgram = newPrograms.getStudyProgram("muMAIN");
    ASSERT_EQ(20, teachingProgram->numberOfPlannedAdmissions);
}

TEST(Test2, addMasterProgram) {
    MastersPrograms programs;
    programs.loadPrograms("../csv_files/mastersprograms.csv");
    std::vector<std::string> bachelor = {"matematika"};
    programs.addStudyProgram("Aplikovaná štatistika", "APŠ", "matematika", bachelor);
    ASSERT_EQ(32, programs.mastersPrograms.size());
    MastersProgram *appliedStatistics = programs.getStudyProgram("APŠ");
    ASSERT_EQ("Aplikovaná štatistika", appliedStatistics->name);
    ASSERT_EQ(1, appliedStatistics->numberOfPlannedAdmissions);
    programs.addStudyProgram("Aplikovaná analýza", "ALA", "matematika", bachelor, 1.5, -1, 1.5, 20);
    MastersProgram *appliedAnalysis = programs.getStudyProgram("ALA");
    ASSERT_EQ("Aplikovaná analýza", appliedAnalysis->name);
    ASSERT_EQ(20, appliedAnalysis->numberOfPlannedAdmissions);
    ASSERT_EQ(1.5, appliedAnalysis->maxGPA);
    programs.savePrograms("../csv_files/newMastersprograms.csv");
    MastersPrograms newPrograms;
    newPrograms.loadPrograms("../csv_files/newMastersprograms.csv");
    ASSERT_EQ(33, newPrograms.mastersPrograms.size());
}

TEST(Test2, removeMasterProgram) {
    MastersPrograms programs;
    programs.loadPrograms("../csv_files/mastersprograms.csv");
    programs.removeStudyProgram("mPMS");
    MastersProgram *deleted = programs.getStudyProgram("mPMS");
    ASSERT_EQ(nullptr, deleted);
    ASSERT_EQ(30, programs.mastersPrograms.size());
    programs.removeStudyProgram("mINF");
    MastersProgram *deleted2 = programs.getStudyProgram("mINF/k");
    ASSERT_EQ(nullptr, deleted2);
    ASSERT_EQ(28, programs.mastersPrograms.size());
    ASSERT_EQ(0,programs.removeStudyProgram("mINF/k"));
    programs.removeStudyProgram("mAIN", false);
    MastersProgram *appliedConversion = programs.getStudyProgram("mAIN/k");
    ASSERT_EQ("Aplikovaná informatika konverzný program", appliedConversion->name);
}

TEST(Test2, testRequirements) {
    MastersPrograms programs;
    programs.loadPrograms("../csv_files/mastersprograms.csv");
    ASSERT_EQ(1.5, programs.getGPA("mMAT"));
    programs.changeMaxGPA("mMAT", 1.3);
    float gpa = 1.3;
    ASSERT_EQ(gpa, programs.getGPA("mMAT"));
    programs.changeMaxGPA("mPMS", 5);
    float gpa2 = 2.25;
    ASSERT_EQ(gpa2, programs.getGPA("mPMS"));
    ASSERT_EQ(0, programs.changeMaxGPA("mINF", 0.4));
    ASSERT_EQ(0, programs.changeMaxGPA("mINF", 0));
    float gpa3 = 1.75;
    ASSERT_EQ(gpa3, programs.getGPA("mINF"));
    programs.changeMaximumAverageOfStateExams("mINF", 0);
    ASSERT_EQ(gpa3, programs.getGPA("mINF"));
    programs.changeMaximumAverageOfStateExams("mEMM", 4.3);
    float gpa4 = 1.5;
    ASSERT_EQ(gpa4, programs.getMaximumAverageOfStateExams("mEMM"));
    programs.changeMaximumAverageOfStateExams("mEMM", gpa3);
    ASSERT_EQ(gpa3, programs.getMaximumAverageOfStateExams("mEMM"));
}

TEST(Test2, saveNew) {
    MastersPrograms programs;
    programs.loadPrograms("../csv_files/mastersprograms.csv");
    std::vector<std::string> bachelor = {"matematika"};
    programs.addStudyProgram("Aplikovaná stochastika", "mAST", "matematika", bachelor, 1.5, -1, 1.5, 20);
    programs.removeStudyProgram("mPMS");
    programs.removeStudyProgram("mINF");
    programs.removeStudyProgram("mAIN",false);
    programs.addStudyProgram("Štatistika", "mŠTA", "matematika", bachelor);
    programs.changeMaxGPA("mŠTA", 1.5);
    programs.changeMaxGPA("mŠTA", 5);
    programs.changeMaximumAverageOfStateExams("mŠTA", 1.7);
    programs.changeMaximumAverageOfStateExams("mFBM", 1.5);
    programs.changeMinimumEntranceExamScore("mFAA", 15);
    ASSERT_EQ(1,programs.savePrograms("../csv_files/newmasters2.csv"));
    MastersPrograms newPrograms;
    newPrograms.loadPrograms("../csv_files/newmasters2.csv");
    ASSERT_EQ(29,newPrograms.mastersPrograms.size());
    float avg = 1.7;
    ASSERT_EQ(avg, newPrograms.getMaximumAverageOfStateExams("mŠTA"));
    ASSERT_EQ(15,newPrograms.getMinimumEntranceExamScore("mFAA"));
    MastersProgram *deleted = programs.getStudyProgram("mINF/k");
    ASSERT_EQ(nullptr, deleted);
}
