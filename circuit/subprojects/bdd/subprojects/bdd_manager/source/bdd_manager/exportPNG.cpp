#include "bdd_manager.h"

string begining = "digraph BDD {",
       nodeShape = "node [shape=circle];",
       ending = "}";

void bdd_manager::ExportPNG(vector<string> *outs, vector<vertex *> *vs, string filename) {
    ofstream dotGV(filename + ".gv");

    dotGV << begining << endl
          << nodeShape << endl
          << BindOuts(outs, vs) << endl;

    for (auto root : *vs) {
        ClearMark(root);
        DrawVertexsRecursive(root, &dotGV, 1);
        ClearMark(root);
    }

    dotGV << ending;
    dotGV.close();
}

void bdd_manager::DrawVertexsRecursive(vertex *v, ofstream *dotGV, bool m) {
    bool vMark = v->GetMark();
    if (vMark == m)
        return;
    v->SetMark(m);

    string name = to_string((long)v),
           vertVar = v->GetVariable()->value;

    if (v->IsTerminal()) {
        *dotGV << name + "[shape=box label=\"" + vertVar + "\"];" << endl;
        return;
    }

    vertex *low = v->GetLow(),
           *high = v->GetHigh();

    string nameLow = to_string((long)low),
           nameHigh = to_string((long)high);

    *dotGV << name + "[label=\"" + vertVar + "\"];" << endl
           << name + " -> " + nameLow + " [taillabel=\"0\" fontname=\"bold\"];" << endl
           << name + " -> " + nameHigh + " [taillabel=\"1\" fontname=\"bold\"];" << endl;

    DrawVertexsRecursive(low, dotGV, m);
    DrawVertexsRecursive(high, dotGV, m);
}

string bdd_manager::BindOuts(vector<string> *outs, vector<vertex *> *vs) {
    string res = "";
    auto itrOut = outs->begin();
    auto itrVs = vs->begin();

    for (int i = 0; i < outs->size(); i++) {
        auto outname = *itrOut;
        auto rootvtx = to_string((long)*itrVs);

        res += outname + " [shape = house];\n" +
               outname + " -> " + rootvtx + ";\n";

        itrOut++;
        itrVs++;
    }
    return res;
}