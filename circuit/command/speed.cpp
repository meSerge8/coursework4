#include <string>
#include <iostream>
#include <filesystem>

#include "circuit.h"
#include "timer.h"

using namespace std;
namespace fs = filesystem;

void MeasureTimeDNF(string filePath);
void MeasureTimeBDD(string filePath);
string GetName(string filePath);

const string benchmarkPath = "../benchmarks/",
             dotDir = "dot/";

int main()
{
    cout << "BDD speed test" << endl;
    MeasureTimeBDD(benchmarkPath);

    cout << endl
         << "DNF speed test" << endl;
    MeasureTimeDNF(benchmarkPath);
}

void MeasureTimeDNF(string benchmarkPath)
{
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
}

void MeasureTimeBDD(string benchmarkPath)
{
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
}

string GetName(string filePath)
{
    auto pos = filePath.find(benchmarkPath) + benchmarkPath.size();
    auto name = filePath.substr(pos);
    name.resize(name.size() - 4);
    return name;
}
