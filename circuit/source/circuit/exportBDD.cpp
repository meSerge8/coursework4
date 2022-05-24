#include "circuit.h"

bdd circuit::ExportBDD()
{
    auto gateVertexs = MakeBasicMap();

    bdd bdd_res;
    auto mng = bdd_res.GetManager();

    for (auto outGate : outputs)
    {
        auto root = MakeVertex(outGate, &gateVertexs, mng);
        string name = outGate->name;
        bdd_res.AddRoot(root, name);
    }

    return bdd_res;
}

// Замечание: если не вычленять заранее входные точки то
// общее bdd выходит короче по количеству вершин
map<string, vertex *> circuit::MakeBasicMap()
{
    map<string, vertex *> gateVertMap;
    // AddInputs(&gateVertMap); // Создаёт мапу и добавляет все входы чтобы бдд была по порядку
    return gateVertMap;
}

vertex *circuit::MakeVertex(gate *gate, map<string, vertex *> *gvMap, bdd_manager *mng)
{
    auto it = gvMap->find(gate->name);
    if (it != gvMap->end())
    {
        return it->second;
    }

    list<vertex *> subVs;
    for (auto subGate : gate->subGates)
    {
        auto sv = MakeVertex(subGate, gvMap, mng);
        subVs.push_back(sv);
    }

    auto newVertex = PerformOperation(gate, subVs, mng);
    gvMap->insert(make_pair(gate->name, newVertex));

    return newVertex;
}

//  Можно выделить Гейт в отдельный класс тогда операцию по
// превращению в вершину можно реализовать проще
vertex *circuit::PerformOperation(gate *gate, list<vertex *> subgs, bdd_manager *mng)
{

    switch (gate->type)
    {
    case NOT:
        if (subgs.size() != 1)
            throw logic_error("expected only one arg");
        return mng->Negate(subgs.front());

    case INPUT:
        return mng->CreateVertex(gate->name);

    case DFF:
        return mng->CreateVertex(gate->name);

    case AND:
        return mng->AND(subgs);

    case OR:
        return mng->OR(subgs);

    case NAND:
        return mng->NAND(subgs);

    case NOR:
        return mng->NOR(subgs);

    case XOR:
        return mng->XOR(subgs);

    case NXOR:
        return mng->NXOR(subgs);

    default:
        throw logic_error("Can't deduce what to do");
    }
}

// void circuit::AddInputs(map<string, vertex *> *map)
// {
//     for (auto gate : gates)
//     {
//         if (gate->type == INPUT or gate->type == DFF)
//         {
//             auto newVert = mng->CreateVertex(gate->name);
//             map->insert(make_pair(gate->name, newVert));
//         }
//     }
// }
