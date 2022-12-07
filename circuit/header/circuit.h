#pragma once

#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <regex>
#include <string>

#include "bdd.h"
#include "bddExporter.h"
#include "dnf.h"
#include "gate.h"

using namespace std;

class circuit {
    list<gate *> gates,
        outputs,
        inputs;

    u_int inGates = 0,
          outGates = 0,
          triggerGates = 0;

   public:
    circuit();
    ~circuit();

    void ImportBenchmark(string);
    void ExportCircuit(string);
    bdd ExportBDD();
    list<dnf> ExportDNF();

    u_int CountInputs();
    u_int CountOutputs();
    u_int CountOPGates();
    u_int CountTriggers();
    u_int CountGates();
    u_int CountMemory();

    IBddExporter *GetBddExporter(BddExporterType);

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