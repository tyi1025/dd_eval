// A simple test file using googletest to ensure DDSIM is working properly

#include "CircuitSimulator.hpp"

#include <gtest/gtest.h>
#include <memory>

TEST(DDSIMSimpleTest, SimpleTest) {
  using namespace qc::literals;

  // Create a simple circuit
  auto qc = std::make_unique<qc::QuantumComputation>(2U);
  qc->h(0U);
  qc->x(1U, 0_pc);

  auto       sim     = CircuitSimulator(std::move(qc));
  const auto results = sim.simulate(1024U);
  EXPECT_EQ(results.count("01"), 0U);
  EXPECT_EQ(results.count("10"), 0U);
}
