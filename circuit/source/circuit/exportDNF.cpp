#include "circuit.h"

// list<dnf> circuit::ExportDNF()
// {
//     list<dnf> dnfs;

//     auto vars = GetInputNames();

//     for (auto outGate : outputs)
//     {
//         dnf res_dnf = BuildDNF(outGate, vars);
//         dnfs.push_back(res_dnf);
//     }

//     return dnfs;
// }

// dnf circuit::BuildDNF(gate *g, vector<string> vars)
// {
//     if (g->type == INPUT)
//         return BuildInputDNF(g, vars);

//     int capacity = vars.size();
//     dnf resDNF(capacity);

//     for (auto subgate : g->subGates)
//     {
//         dnf subDNF = BuildDNF(subgate, vars);
//         // BuildFromSubGatesDNF(subgate, GetInputNames());
//     }

//     return resDNF;
// }

vector<string> circuit::GetInputNames()
{
    vector<string> inputNames;

    for (auto gate : gates)
        if (gate->type == INPUT)
            inputNames.push_back(gate->name);

    return inputNames;
}
    
// dnf circuit::BuildInputDNF(gate *g, vector<string> vars)
// {
//     auto it = find(vars.begin(), vars.end(), g->name);
//     int index = distance(vars.begin(), it);

//     int capacity = vars.size();
//     conjunction cnj(capacity);

//     cnj.insert(cnj.begin() + index, pos);

//     dnf resDNF(capacity);
//     resDNF.AddConjunction(cnj);

//     return resDNF;
// }