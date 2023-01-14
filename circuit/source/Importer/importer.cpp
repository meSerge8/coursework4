#include "Importer.h"

const regex INPUT_R("INPUT\\((\\w+\\.?\\w*)\\)"),
    OUTPUT_R("OUTPUT\\((\\w+\\.?\\w*)\\)"),
    COMMENT_R("#.*"),
    EMPTY_R("\\s*"),
    GATE_R("(\\w+\\.?\\w*)=(\\w+\\.?\\w*)\\((.*)\\)"),
    DFF_R("(\\w+\\.?\\w*)=DFF\\((.*)\\)");

Circuit Importer::Import(string fileName) {
    ifstream bench(fileName);
    if (not bench)
        throw invalid_argument("File doesn't exist");

    string line;
    while (getline(bench, line)) {
        string noSpaces = regex_replace(line, regex("\\s"), "");
        processLine(noSpaces);
    }
    bench.close();

    return {
        Gate::sortTopological(this->gates),
        this->inGates,
        this->outGates};
}

void Importer::processLine(string line) {
    smatch m;

    if (regex_match(line, m, INPUT_R)) {
        addInput(m[1]);
    }

    else if (regex_match(line, m, OUTPUT_R)) {
        addOutput(m[1]);
    }

    else if (regex_match(line, m, DFF_R)) {
        addDFF(m[1], m[2]);
    }

    else if (regex_match(line, m, GATE_R)) {
        addGate(m);
    }

    else if (regex_match(line, m, COMMENT_R)) {
        return;
    }

    else if (regex_match(line, m, EMPTY_R)) {
        return;
    }

    else
        throw invalid_argument("Unknown command");
}

void Importer::addInput(string gateName) {
    Gate *g = FindByName(this->gates, gateName);
    if (g != nullptr) {
        throw logic_error("input gate redeclaration");
    }

    g = new Gate(gateName, INPUT);
    this->gates.push_back(g);
    this->inGates.push_back(g);
}

void Importer::addOutput(string gateName) {
    Gate *g = FindByName(this->gates, gateName);
    if (g != nullptr) {
        throw logic_error("output gate redeclaration");
    }

    g = new Gate(gateName, INPUT);
    this->gates.push_back(g);
    this->outGates.push_back(g);
}

void Importer::addGate(smatch m) {
    string gateName = m[1];
    Gate *g = FindByName(this->gates, gateName);
    auto gateType = getType(m[2]);

    if (g != nullptr) {
        g->SetType(gateType);
    } else {
        g = new Gate(gateName, gateType);
        this->gates.push_back(g);
    }

    addSubGates(g, m[3]);
}

void Importer::addSubGates(Gate *g, string subGates) {
    regex regxArgs("\\w+\\.?\\w*");
    sregex_iterator
        beg{
            subGates.cbegin(),
            subGates.cend(),
            regxArgs,
        },
        end{};

    for (auto i = beg; i != end; i++) {
        string gateName = i->str();

        auto subGate = FindByName(this->gates, gateName);

        if (subGate == nullptr) {
            subGate = new Gate(gateName, INPUT);
            this->gates.push_back(subGate);
        }
        g->AddPredecessor(subGate);

        subGate->AddSuccessors(g);
    }
}

void Importer::addDFF(string inputGateName, string outputGateName) {
    addInput(inputGateName);
    addOutput(outputGateName);
}

GateType Importer::getType(string t) {
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

    throw logic_error("Couldn't recognize operator " + t);
}