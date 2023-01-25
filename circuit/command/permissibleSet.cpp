#include <iostream>
#include <vector>

#include "Circuit.h"
#include "Importer.h"
#include "PermissibleSetBuilder.h"
#include "TestabilityFooBuilder.h"
#include "Timer.h"

using namespace std;

double CountPercentPoles(Circuit*);
Gate* Table1(Circuit*);
void Table2(Gate*, Circuit*);
double CountPercentage(TestabilityFooBuilder*, Circuit*);

string benchPath = "../benchmarks/",
       filename;

double limit;

int main(int argc, char** argv) {
    filename = argv[1];
    limit = stod(argv[2]);
    Importer imp;
    Circuit c = imp.Import(benchPath + filename);
    auto minPole = Table1(&c);
    Table2(minPole, &c);
}

double CountPercentPoles(Circuit* c) {
    int countGates_P = 0;

    for (Gate* pole : c->GetGates()) {
        TestabilityFooBuilder testFooBuilder(pole, c);
        double observability = CountPercentage(&testFooBuilder, c);
        if (observability > limit) {
            continue;
        }
        if (observability == 0) {
            continue;
        }

        cout << observability << endl;
        countGates_P++;
    }

    return double(countGates_P) / c->CountGates();
}

Gate* Table1(Circuit* c) {
    Gate* minObservabilityPole;

    int countGates_P = 0,
        countZeroObservability = 0;

    double
        minObservability = 1,
        maxReduce = 0,
        middleReduce = 0,
        time1 = 0,
        time2 = 0,
        minTime1 = 0,
        minTime2 = 0;

    for (Gate* pole : c->GetGates()) {
        Timer t;
        t.Start();

        TestabilityFooBuilder testFooBuilder(pole, c);
        double observability = CountPercentage(&testFooBuilder, c);
        if (observability > limit) {
            continue;
        }
        if (observability == 0) {
            countZeroObservability++;
            continue;
        }

        dnf D0 = testFooBuilder.GetD0();
        dnf D1 = testFooBuilder.GetD1();

        double tFinish1 = t.Finish() * 1000;

        t.Start();
        PermissibleSetBuilder permSetBuilder;
        permSetBuilder.BuildSets(D0, D1, testFooBuilder.GetInputs());
        double tFinish2 = t.Finish() * 1000;

        auto minSet = permSetBuilder.GetMinSet();
        double reduce = 1 - (double(minSet.size()) / c->CountInputs());

        countGates_P++;
        middleReduce += reduce;
        time1 += tFinish1;
        time2 += tFinish2;

        if (reduce > maxReduce) {
            maxReduce = reduce;
        }

        if (observability < minObservability) {
            minObservability = observability;
            minObservabilityPole = pole;
            minTime1 = tFinish1;
            minTime2 = tFinish2;
        }
    }

    cout << "\tТАБЛИЦА 1" << endl
         << "Name: " << filename << endl
         << "Порог: " << limit << endl
         << "Полюсов больше порога: " << double(countGates_P) / c->CountGates() << endl
         << "Полюсов с нулевой наблюдаемостью: " << double(countZeroObservability) / c->CountGates() << endl
         << "Максимальное сокращение: " << maxReduce << endl
         << "Среднее сокращение: " << middleReduce / countGates_P << endl
         << "Среднее время построения тестовых функций милиСек: " << time1 / countGates_P << endl
         << "Среднее время получения достаточных множеств милиСек: " << time2 / countGates_P << endl

         << "2. Время построения тестовых функций милиСек: " << minTime1 << endl
         << "2. время получения достаточных множеств милиСек: " << minTime2 << endl;

    return minObservabilityPole;
}

void Table2(Gate* pole, Circuit* c) {
    cout << *pole << endl;

    Timer t;
    double time1 = 0,
           time2 = 0;
    t.Start();

    TestabilityFooBuilder testFooBuilder(pole, c);
    double observability = CountPercentage(&testFooBuilder, c);
    dnf D0 = testFooBuilder.GetD0();
    dnf D1 = testFooBuilder.GetD1();
    time1 = t.Finish() * 1000;

    t.Start();
    PermissibleSetBuilder permSetBuilder;
    permSetBuilder.BuildSets(D0, D1, testFooBuilder.GetInputs());
    time2 = t.Finish() * 1000;

    cout << "\tТАБЛИЦА 2" << endl
         << "Name: " << filename << endl
         << "Наблюдаемость: " << observability << endl
         << "Число безызбыточных множеств: " << permSetBuilder.GetSets().size() << endl
         << "Сокращение для минимального множества: " << 1 - (double(permSetBuilder.GetMinSet().size()) / c->CountInputs()) << endl
         << "Время построения тестовых функций микроСек: " << time1 << endl
         << "Время получения достаточных множеств микроСек: " << time2 << endl;
}

double CountPercentage(TestabilityFooBuilder* tb, Circuit* c) {
    dnf B = tb->GetB();

    if (B.IsConstant()) {
        return B.GetConstant() ? 1 : 0;
    }

    auto MB = GetM(B);
    double mb_size = MB->size();
    delete MB;
    double pow64 = powf64(2, c->CountInputs());
    return mb_size / pow64;
}