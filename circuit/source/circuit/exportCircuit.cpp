#include "circuit.h"

void circuit::ExportCircuit(string fileName)
{
    ofstream res_file(fileName);

    if (not res_file)
        throw invalid_argument("File doesn't exist");

    auto nim = BuildNameIdxMap();
    WriteFirstLine(res_file);
    WriteSecondLine(res_file);
    WriteThirdLine(res_file, nim);
    WriteLastLines(res_file, nim);

    PrintMap(nim);

    res_file.close();
    delete nim;
}

map<string, u_int> *circuit::BuildNameIdxMap()
{
    auto res = new map<string, u_int>;
    u_int idx = 0;
    for (auto i : gates)
        (*res)[i->name] = idx++;
    return res;
}

void circuit::WriteFirstLine(ofstream &res_file)
{
    u_int counts[] = {CountInputs(), CountOutputs(), CountMemory(), CountOPGates()};

    for (auto i : counts)
        res_file << to_string(i) << " ";

    res_file << endl;
}

void circuit::WriteSecondLine(ofstream &res_file) {}

void circuit::WriteThirdLine(ofstream &res_file, map<string, u_int> *nim)
{
    for (auto i : outputs)
        res_file << to_string(nim->at(i->name)) << " ";

    res_file << endl;
}

void circuit::WriteLastLines(ofstream &res_file, map<string, u_int> *nim)
{
    for (auto itr : gates)
    {
        if (itr->type == INPUT or itr->type == DFF)
            continue;

        res_file << nim->at(itr->name) << " " << itr->type << " ";

        for (auto subg : itr->subGates)
            res_file << nim->at(subg->name) << " ";

        res_file << endl;
    }
}

u_int circuit::CountInputs()
{
    return inGates;
}

u_int circuit::CountOutputs()
{
    return outGates;
}

u_int circuit::CountOPGates()
{
    u_int count = 0;
    for (auto g : gates)
        if (g->type != INPUT)
            count++;

    return count;
}

u_int circuit::CountTriggers()
{
    return triggerGates;
}

u_int circuit::CountGates()
{
    return gates.size();
}

u_int circuit::CountMemory()
{
    return 0;
}