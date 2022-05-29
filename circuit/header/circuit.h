#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <exception>
#include <regex>

#include "bdd.h"
#include "dnf.h"
#include "gate.h"

using namespace std;

class circuit
{
public:
    list<gate *> gates,
        outputs,
        inputs;

    // Amount of input gates
    u_int inGates = 0;

    // Amount of output gates
    u_int outGates = 0;

    // Amount of trigger gates
    u_int triggerGates = 0;

public:
    // Constructors
    circuit();
    ~circuit();

    // Import Benchmark
    void ImportBenchmark(string);

    // Export circuit
    void ExportCircuit(string);

    u_int CountInputs();
    u_int CountOutputs();
    u_int CountOPGates();
    u_int CountTriggers();
    u_int CountGates();
    u_int CountMemory();

    // Export as BDD
    bdd ExportBDD();

    // Export as DNF
    list<dnf> ExportDNF();

    // Print
    friend ostream &operator<<(ostream &, circuit &);

private:
    // ImportBenchmark
    void ProcessLine(string);
    void ClearDFFs();
    void CheckForNONE();
    void AddInput(string);
    void AddOutput(string);
    void AddOP(smatch);
    void AddDFF(smatch);
    list<gate *> ParceGatesArgs(string);
    gate *AddGate(string);
    gateType GetType(string);

    // Export circuit
    map<string, u_int> *BuildNameIdxMap();
    void WriteFirstLine(ofstream &);
    void WriteSecondLine(ofstream &);
    void WriteThirdLine(ofstream &, map<string, u_int> *);
    void WriteLastLines(ofstream &, map<string, u_int> *);

    // Printer
    list<string> GetOutNames();

    // Export as BDD
    map<string, vertex *> MakeBasicMap();
    vertex *MakeVertex(gate *, map<string, vertex *> *, bdd_manager *);
    vertex *PerformOperation(gate *, list<vertex *>, bdd_manager *);
    // void AddInputs(map<string, vertex *> *map);

    // Export as DNF
    void buildInputGates();
    vector<string> GetInputNames();
    dnf BuildDNF(gate *);
    dnf BuildInputDNF(gate *);
    dnf apply(dnf &, dnf &, gateType);

    // Printer
    // void PrintGate(gate, ostream &outStream);
    void PrintMap(map<string, u_int> *);

    // Support
    gate *Find(list<gate *>, string);
};