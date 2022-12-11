#include "circuit.h"

const regex INPUT_R("INPUT\\((\\w+\\.?\\w*)\\)"),
    OUTPUT_R("OUTPUT\\((\\w+\\.?\\w*)\\)"),
    COMMENT_R("#.*"),
    EMPTY_R("\\s*"),
    GATE_R("(\\w+\\.?\\w*)=(\\w+\\.?\\w*)\\((.*)\\)"),
    DFF_R("(\\w+\\.?\\w*)=DFF\\((.*)\\)");

void circuit::ImportBenchmark(string fileName) {
    if (gates.size() != 0) {
        throw logic_error("benchmark is already imported");
    }

    ifstream bench(fileName);
    if (not bench)
        throw invalid_argument("File doesn't exist");

    string one;
    while (getline(bench, one)) {
        auto noSpaces = regex_replace(one, regex("\\s"), "");
        ProcessLine(noSpaces);
    }
    bench.close();

    ClearDFFs();
    CheckForNONE();
}

void circuit::ProcessLine(string line) {
    smatch m;

    if (regex_match(line, m, INPUT_R)) {
        AddInput(m[1]);
    }

    else if (regex_match(line, m, OUTPUT_R)) {
        AddOutput(m[1]);
    }

    else if (regex_match(line, m, COMMENT_R)) {
        return;
    }

    else if (regex_match(line, m, EMPTY_R)) {
        return;
    }

    else if (regex_match(line, m, DFF_R)) {
        AddDFF(m);
    }

    else if (regex_match(line, m, GATE_R)) {
        AddOP(m);
    }

    else
        throw invalid_argument("Unknown command");
}

void circuit::ClearDFFs() {
    for (auto &&g : gates)
        if (g->type == DFF)
            g->subGates.clear();
}

void circuit::CheckForNONE() {
    for (auto g : gates)
        if (g->type == NONE)
            throw logic_error("No init for " + g->name);
}

void circuit::AddInput(string name) {
    auto one = AddGate(name);
    if (one->type == NONE)
        one->type = INPUT;

    else if (one->type != INPUT) {
        auto er_str = "Attempt to re-init " + name + " as input gate";
        throw logic_error(er_str);
    }

    inGates++;
}

void circuit::AddOutput(string name) {
    auto one = AddGate(name);
    outputs.push_back(one);

    outGates++;
}

void circuit::AddOP(smatch m) {
    string name = m[1];
    auto gate = AddGate(name);

    if (gate->type != NONE) {
        auto er_str = "Attempt to re-init " + name + " as operator gate";
        throw logic_error(er_str);
    }

    gate->subGates = ParceGatesArgs(m[3]);
    gate->type = GetType(m[2]);
}

void circuit::AddDFF(smatch m) {
    AddInput(m[1]);
    AddOutput(m[2]);

    triggerGates++;
    inGates--;
    outGates--;
}

list<gate *> circuit::ParceGatesArgs(string args) {
    list<gate *> res;
    regex argR("\\w+\\.?\\w*");
    smatch m;

    sregex_iterator beg{args.cbegin(), args.cend(), argR},
        end{};

    for (auto i = beg; i != end; i++) {
        auto gateName = i->str();
        auto gate = AddGate(gateName);
        res.push_back(gate);
    }

    return res;
}

gate *circuit::AddGate(string name) {
    list<gate *> emptyList;
    auto one = Find(gates, name);
    if (one == nullptr) {
        one = new gate{name, NONE, emptyList};
        gates.push_back(one);
    }
    return one;
}

gateType circuit::GetType(string t) {
    if (t == "AND")
        return AND;
    if (t == "OR")
        return OR;
    if (t == "NOT")
        return NOT;
    if (t == "NAND")
        return NAND;
    if (t == "NOR")
        return NOR;
    if (t == "XOR")
        return XOR;
    if (t == "NXOR")
        return NXOR;
    if (t == "DFF")
        return DFF;

    throw logic_error("Couldn't recognize operator");
}
