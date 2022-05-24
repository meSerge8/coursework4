#include "bdd.h"

string begining = "digraph BDD {",
       nodeShape = "node [shape=circle];",
       zeroEdge = " [taillabel=\"0\" fontname=\"bold\"];",
       oneEdge = " [taillabel=\"1\" fontname=\"bold\"];",
       ending = "}";

void bdd::ExportGV(string filename)
{
    ofstream dotGV(filename + ".gv");

    dotGV << begining << endl
          << nodeShape << endl
          << BindOuts() << endl;

    for (auto root : roots)
    {
        ClearMark(root);
        DrawVertexsRecursive(root, dotGV, 1);
        ClearMark(root);
    }

    dotGV << ending;
    dotGV.close();
}

string bdd::BindOuts()
{
    string res;
    auto itrOut = rootNames.begin();
    auto itrVs = roots.begin();

    for (int i = 0; i < rootNames.size(); i++)
    {
        string outname = *itrOut,
               rootvtx = to_string((long)*itrVs);

        res += outname + " [shape = house];\n" +
               outname + " -> " + rootvtx + ";\n";

        itrOut++;
        itrVs++;
    }
    return res;
}

void bdd::DrawVertexsRecursive(vertex *v, ofstream &dotGV, bool m)
{
    bool vMark = v->GetMark();
    if (vMark == m)
        return;
    v->SetMark(m);

    string name = to_string((long)v),
           vertVar = v->GetVariable()->value;

    if (v->IsTerminal())
    {
        dotGV << name + "[shape=box label=\"" + vertVar + "\"];" << endl;
        return;
    }

    vertex *low = v->GetLow(),
           *high = v->GetHigh();

    string nameLow = to_string((long)low),
           nameHigh = to_string((long)high);

    dotGV << name + "[label=\"" + vertVar + "\"];" << endl
          << name + " -> " + nameLow + zeroEdge << endl
          << name + " -> " + nameHigh + oneEdge << endl;

    DrawVertexsRecursive(low, dotGV, m);
    DrawVertexsRecursive(high, dotGV, m);
}
