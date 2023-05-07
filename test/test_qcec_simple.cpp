// A simple test file using googletest to ensure QCEC is working properly

#include "EquivalenceCheckingManager.hpp"

#include <gtest/gtest.h>

TEST(QCECSimpleTest, SimpleTest) {
  using namespace qc::literals;

  // Create a simple circuit
  auto qc = qc::QuantumComputation(2U);
  qc.h(0U);
  qc.x(1U, 0_pc);

  // check the circuit against itself
  auto ecm = ec::EquivalenceCheckingManager(qc, qc);
  ecm.run();
  EXPECT_TRUE(ecm.getResults().consideredEquivalent());
}
