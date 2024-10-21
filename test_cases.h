//
// Created by 杜建璋 on 2024/8/29.
//

#ifndef DEMO_TEST_CASES_H
#define DEMO_TEST_CASES_H

#include "mpc_package/utils/Log.h"
#include "mpc_package/utils/Mpi.h"
#include "mpc_package/utils/Math.h"
#include "mpc_package/arithmetic/addition/AdditionShareExecutor.h"
#include "mpc_package/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.h"
#include "mpc_package/arithmetic/multiplication/FixedMultiplicationShareExecutor.h"
#include "mpc_package/comparison/ComparisonExecutor.h"
#include "mpc_package/boolean/and/RsaOtAndShareExecutor.h"
#include "mpc_package/api/IntSecret.h"

using namespace std;

void test_AdditionShareExecutor_0() {
    int x, y;
    if (!Mpi::isServer()) {
        x = Math::rand32(-100, 100);
        y = Math::rand32(-100, 100);
        Log::i("Addend: " + std::to_string(x) + " and " + std::to_string(y));
    }
    AdditionShareExecutor<int32_t> e(x, y);
    e.benchmark(Executor<int>::BenchmarkLevel::DETAILED)->logBenchmark(true)->execute(true);
    if (!Mpi::isServer()) {
        Log::i(std::to_string((e.result())));
    }
}

void test_RsaOtMultiplicationShareExecutor_1() {
    int x, y;
    if (!Mpi::isServer()) {
        x = Math::rand32(-100, 100);
        y = Math::rand32(-100, 100);
        Log::i("Multiplier: " + std::to_string(x) + " and " + std::to_string(y));
    }
    RsaOtMultiplicationShareExecutor<int32_t> e(x, y);
    e.benchmark(Executor<int>::BenchmarkLevel::DETAILED)->logBenchmark(true)->execute(true);
    if (!Mpi::isServer()) {
        Log::i(std::to_string((e.result())));
    }
}

void test_FixedMultiplicationShareExecutor_2() {
    int x, y;
    if (!Mpi::isServer()) {
        x = Math::rand32(-100, 100);
        y = Math::rand32(-100, 100);
        Log::i("Multiplier: " + std::to_string(x) + " and " + std::to_string(y));
    }
    FixedMultiplicationShareExecutor<int32_t> e(x, y);
    e.benchmark(Executor<int>::BenchmarkLevel::DETAILED)->logBenchmark(true)->execute(true);
    if (!Mpi::isServer()) {
        Log::i(std::to_string((e.result())));
    }
}

void test_RsaOtAndShareExecutor_3() {
    bool x, y;
    if (!Mpi::isServer()) {
        x = Math::rand32(0, 1);
        y = Math::rand32(0, 1);
        Log::i("Boolean: " + std::to_string(x) + " and " + std::to_string(y));
    }
    RsaOtAndShareExecutor e(x, y);
    e.execute(true);
    if (!Mpi::isServer()) {
        Log::i(std::to_string((e.result())));
    }
}

void test_comparison_4() {
    int x, y;
    if (Mpi::isClient()) {
        x = Math::rand32(-100, 100);
        y = Math::rand32(-100, 100);
        Log::i("x: " + std::to_string(x) + " y " + std::to_string(y));
    }
    ComparisonExecutor<int8_t> e(x, y);
    e.benchmark(Executor<int8_t>::BenchmarkLevel::DETAILED)->logBenchmark(true)->execute(true);
    if (!Mpi::isServer()) {
        Log::i(std::to_string((e.result())));
    }
}

void test_convert_arith_5() {
    int z0 = Math::rand32(-100, 100);
    int z1 = Math::rand32(-100, 100);
    if (Mpi::isServer()) {
        Log::i("original zi = " + std::to_string(Mpi::rank() == 0 ? z0 : z1));
    }
    int zi = Mpi::rank() == 0 ? z0 : z1;
    int zi1 = IntShareExecutor<int>().zi(zi)->convertZiToBool()->convertZiToArithmetic()->zi();
    if (Mpi::isServer()) {
        Log::i("zi = " + std::to_string(zi1));
    }
}

#endif //DEMO_TEST_CASES_H
