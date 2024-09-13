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
#include "mpc_package/data/IntSecret.h"

using namespace std;

void test_AdditionShareExecutor_0() {
    int x, y;
    if (!Mpi::isCalculator()) {
        x = Math::rand32(0, 100);
        y = Math::rand32(0, 100);
        Log::i("Addend: " + std::to_string(x) + " and " + std::to_string(y));
    }
    AdditionShareExecutor e(x, y, 32);
    e.benchmark(AbstractExecutor::BenchmarkLevel::DETAILED)->logBenchmark(true)->execute(true);
    if (!Mpi::isCalculator()) {
        Log::i(std::to_string((e.result())));
    }
}

void test_RsaOtMultiplicationShareExecutor_1() {
    int x, y;
    if (!Mpi::isCalculator()) {
        x = Math::rand32();
        y = Math::rand32();
        Log::i("Multiplier: " + std::to_string(x) + " and " + std::to_string(y));
    }
    RsaOtMultiplicationShareExecutor e(x, y, 32);
    e.benchmark(AbstractExecutor::BenchmarkLevel::DETAILED)->logBenchmark(true)->execute(true);
    if (!Mpi::isCalculator()) {
        Log::i(std::to_string((e.result())));
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
    e.benchmark(AbstractExecutor::BenchmarkLevel::DETAILED)->logBenchmark(true)->execute(true);
    if (!Mpi::isCalculator()) {
        Log::i(std::to_string((e.result())));
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
    e.benchmark(AbstractExecutor::BenchmarkLevel::DETAILED)->logBenchmark(true)->execute(true);
    if (!Mpi::isCalculator()) {
        Log::i(std::to_string((e.result())));
    }
}

void test_ArrayAddition_4() {
    std::vector<int64_t> v;
    for (int i = 0; i < 3; i++) {
        v.push_back(Math::rand32(0, 100));
    }
    if (Mpi::isCalculator()) {
        Log::i("[" + std::to_string(v[0]) + ", " + std::to_string(v[1]) + ", " + std::to_string(v[2]) + "]");
    }
    int64_t res = AdditionShareExecutor(v, 32).benchmark(AbstractExecutor::BenchmarkLevel::DETAILED)->logBenchmark(true)->execute(
            true)->result();
    if (Mpi::isDataHolder()) {
        Log::i(std::to_string(res));
    }
}

void test_Operators_5() {
    int a = Math::rand32(0, 100);
    if (Mpi::isDataHolder()) {
        Log::i("Origin: " + to_string(a));
    }
    int64_t res = IntSecret(a, 32).share().add(15).add(-15).reconstruct().get();
    if (Mpi::isDataHolder()) {
        Log::i("Reconstruct result: " + to_string(res));
    }

    int m0 = Math::rand32();
    int m1 = Math::rand32();
    if (Mpi::isDataHolder()) {
        Log::i("m0: " + to_string(m0));
        Log::i("m1: " + to_string(m1));
    }
    int64_t res1 = IntSecret(m0, 32).share().multiply(IntSecret(m1, 32).share().get()).reconstruct().get();
    if (Mpi::isDataHolder()) {
        Log::i("Multiplication result: " + to_string(res1));
    }
}

#endif //DEMO_TEST_CASES_H
