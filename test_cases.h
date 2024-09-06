//
// Created by 杜建璋 on 2024/8/29.
//

#ifndef DEMO_TEST_CASES_H
#define DEMO_TEST_CASES_H

#include "mpc_package/utils/Log.h"
#include "mpc_package/utils/Mpi.h"
#include "mpc_package/utils/Math.h"
#include "mpc_package/executor/share/arithmetic/addition/AdditionShareExecutor.h"
#include "mpc_package/executor/share/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.h"
#include "mpc_package/executor/share/arithmetic/multiplication/FixedMultiplicationShareExecutor.h"
#include "mpc_package/executor/share/boolean/and/RsaOtAndShareExecutor.h"

void test_AdditionShareExecutor_0() {
    int x, y;
    if (!Mpi::isCalculator()) {
        x = Math::rand32(0, 100);
        y = Math::rand32(0, 100);
        Log::i("Addend: " + std::to_string(x) + " and " + std::to_string(y));
    }
    AdditionShareExecutor e(x, y);
    e.setBenchmark(BenchmarkLevel::DETAILED);
    e.setLogBenchmark(true);
    e.compute();
    if (!Mpi::isCalculator()) {
        Log::i(std::to_string((e.getResult())));
    }
}

void test_RsaOtMultiplicationShareExecutor_1() {
    int x, y;
    if (!Mpi::isCalculator()) {
        x = Math::rand32(0, 100);
        y = Math::rand32(0, 100);
        Log::i("Multiplier: " + std::to_string(x) + " and " + std::to_string(y));
    }
    RsaOtMultiplicationShareExecutor e(x, y, 32);
    e.setBenchmark(BenchmarkLevel::DETAILED);
    e.setLogBenchmark(true);
    e.compute();
    if (!Mpi::isCalculator()) {
        Log::i(std::to_string((e.getResult())));
    }
}

void test_FixedMultiplicationShareExecutor_2() {
    int x, y;
    if (!Mpi::isCalculator()) {
        x = Math::rand32(0, 100);
        y = Math::rand32(0, 100);
        Log::i("Multiplier: " + std::to_string(x) + " and " + std::to_string(y));
    }
    FixedMultiplicationShareExecutor e(x, y, 32);
    e.setBenchmark(BenchmarkLevel::DETAILED);
    e.setLogBenchmark(true);
    e.compute();
    if (!Mpi::isCalculator()) {
        Log::i(std::to_string((e.getResult())));
    }
}

void test_RsaOtAndShareExecutor_3() {
    bool x, y;
    if (!Mpi::isCalculator()) {
        x = Math::rand32(0, 1);
        y = Math::rand32(0, 1);
        Log::i("Boolean: " + std::to_string(x) + " and " + std::to_string(y));
    }
    RsaOtAndShareExecutor e(x, y);
    e.setBenchmark(BenchmarkLevel::DETAILED);
    e.setLogBenchmark(true);
    e.compute();
    if (!Mpi::isCalculator()) {
        Log::i(std::to_string((e.getResult())));
    }
}

#endif //DEMO_TEST_CASES_H
