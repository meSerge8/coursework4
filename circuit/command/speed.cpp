#include <string>
#include <iostream>
#include <filesystem>

#include "circuit.h"
#include "timer.h"

using namespace std;
namespace fs = filesystem;

string GetName(string filePath);

void Test_BDD(string filePath);
void Test_DNF_from_BDD(string filePath);
void Test_DNF_from_BDD_only_DNF(string filePath);
void Test_DNF(string filePath);

const string benchmarkPath = "../benchmarks/",
             dotDir = "dot/";

int main()
{
    Test_BDD(benchmarkPath);
    Test_DNF_from_BDD(benchmarkPath);
    Test_DNF_from_BDD_only_DNF(benchmarkPath);
    Test_DNF(benchmarkPath);
}

string GetName(string filePath)
{
    auto pos = filePath.find(benchmarkPath) + benchmarkPath.size();
    auto name = filePath.substr(pos);
    name.resize(name.size() - 4);
    return name;
}

void Test_BDD(string benchmarkPath)
{
    cout << "BDD speed test" << endl
         << endl;

    for (const auto &entry : fs::directory_iterator(benchmarkPath))
    {
        string filePath = entry.path();
        timer timer;
        circuit c;
        c.ImportBenchmark(filePath);

        cout << GetName(filePath) << "\t"
             << c.CountInputs() << "\t"
             << c.CountOutputs() << "\t"
             << c.CountTriggers() << "\t"
             << c.CountGates() << "\t";

        timer.Start();
        c.ExportBDD();
        double t = timer.Finish();

        printf("%.4f\t", t);
        cout << endl;
    }
    cout << endl;
}

void Test_DNF_from_BDD(string benchmarkPath)
{
    cout << "DNF from BDD speed test" << endl
         << endl;

    for (const auto &entry : fs::directory_iterator(benchmarkPath))
    {
        string filePath = entry.path();
        timer timer;
        circuit c;
        c.ImportBenchmark(filePath);

        cout << GetName(filePath) << "\t"
             << c.CountInputs() << "\t"
             << c.CountOutputs() << "\t"
             << c.CountTriggers() << "\t"
             << c.CountGates() << "\t";

        timer.Start();
        bdd b = c.ExportBDD();
        b.ExportDNF();
        double t = timer.Finish();

        printf("%.4f\t", t);
        cout << endl;
    }
    cout << endl;
}

void Test_DNF_from_BDD_only_DNF(string benchmarkPath)
{
    cout << "DNF from BDD (only DNF) speed test" << endl
         << endl;

    for (const auto &entry : fs::directory_iterator(benchmarkPath))
    {
        string filePath = entry.path();
        timer timer;
        circuit c;
        c.ImportBenchmark(filePath);

        cout << GetName(filePath) << "\t"
             << c.CountInputs() << "\t"
             << c.CountOutputs() << "\t"
             << c.CountTriggers() << "\t"
             << c.CountGates() << "\t";

        bdd b = c.ExportBDD();

        timer.Start();
        b.ExportDNF();
        double t = timer.Finish();

        printf("%.4f\t", t);
        cout << endl;
    }
    cout << endl;
}

void Test_DNF(string benchmarkPath)
{
    cout << "DNF speed test" << endl
         << endl;

    for (const auto &entry : fs::directory_iterator(benchmarkPath))
    {
        string filePath = entry.path();
        timer timer;
        circuit c;
        c.ImportBenchmark(filePath);

        cout << GetName(filePath) << "\t"
             << c.CountInputs() << "\t"
             << c.CountOutputs() << "\t"
             << c.CountTriggers() << "\t"
             << c.CountGates() << "\t";

        timer.Start();
        c.ExportDNF();
        double t = timer.Finish();

        printf("%.4f\t", t);
        cout << endl;
    }
    cout << endl;
}
