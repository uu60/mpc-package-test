#include "mpc_package/utils/Log.h"
#include "mpc_package/utils/Mpi.h"
#include "test_cases.h"
#include "cstring"

int main(int argc, char **argv) {
    Mpi::init(argc, argv);
    Log::i("Beginning...");

    std::string caseIdx;
    try {
        for (int i = 0; i < argc; i++) {
            if (strcmp("-case", argv[i]) == 0) {
                if (i + 1 >= argc) {
                    throw std::runtime_error("error");
                }
                caseIdx = argv[i + 1];
            }
        }
        switch (std::stoi(caseIdx)) {
            case 0:
                test_AdditionShareExecutor_0();
                break;
            case 1:
                test_RsaOtMultiplicationShareExecutor_1();
                break;
            case 2:
                test_FixedMultiplicationShareExecutor_2();
                break;
            case 3:
                test_RsaOtAndShareExecutor_3();
                break;
            case 4:
                test_ArrayAddition_4();
        }
    } catch (...) {
        Log::e("Wrong argument");
        Mpi::finalize();
        return 0;
    }

    Log::i("Done.");
    Mpi::finalize();
    return 0;
}

