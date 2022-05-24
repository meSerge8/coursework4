#include <string>
#include <iostream>
#include <filesystem>

#include "circuit.h"
#include "timer.h"

using namespace std;
namespace fs = filesystem;

void MeasureTime(string filePath);
void MeasureTime2(string filePath);

string GetName(string filePath);

const string path = "../benchmarks/",
             dotDir = "dot/";

int main()
{
    for (const auto &entry : fs::directory_iterator(path))
    {
        string filePath = entry.path();
        // cout << "For " + filePath << endl;

        try
        {
            MeasureTime2(filePath);
        }
        catch (const exception &e)
        {
            cout << endl
                 << e.what() << endl;
        }
        cout << endl;
    }
}

void MeasureTime(string filePath)
{
    timer t;
    circuit c;

    cout << "Importing bench...\t";
    t.Start();
    c.ImportBenchmark(filePath);
    cout << t.Finish() << endl;

    cout << "Exporting BDD...\t";
    t.Start();
    auto b = c.ExportBDD();
    cout << t.Finish() << endl;

    // cout << "Exporting DNF...\t";
    // t.Start();
    // auto d = b.ExportDNF();
    // cout << t.Finish() << endl;

    // string name = GetName(filePath);
    // b.ExportGV(name);
}

void MeasureTime2(string filePath)
{
    timer timerBDD, timerDNF;
    circuit c;
    c.ImportBenchmark(filePath);

    timerBDD.Start();
    timerDNF.Start();
    auto b = c.ExportBDD();
    double tBDD = timerBDD.Finish();
    // auto d = b.ExportDNF();
    double tDNF = timerDNF.Finish();

    cout << GetName(filePath) << "\t"
         << c.CountInputs() << "\t"
         << c.CountOutputs() << "\t"
         << c.CountTriggers() << "\t"
         << c.CountGates() << "\t";
         printf("%.4f\t",tBDD);
         printf("%.4f\t",tDNF);
}

string GetName(string filePath)
{
    auto pos = filePath.find(path) + path.size();
    auto name = filePath.substr(pos);
    name.resize(name.size() - 4);
    return name;
}
