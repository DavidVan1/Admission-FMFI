#include <iostream>
#include "gtest/gtest.h"
#include <typeinfo>

#include "../header_files/Applicants.h"
#include "../header_files/Evaluator.h"
#include "../header_files/Admit.h"

using namespace ::testing;


TEST(Test3, loadBachelorApplicants) {
  MasaterApplicants applicants;
  applicants.loadBachelorApplicants("../bachelorapplicants.txt");
  ASSERT_EQ(202, applicants.bachelorApplicants.size());
}