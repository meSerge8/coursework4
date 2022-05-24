#include "bdd_manager.h"

vertex *bdd_manager::Reduce(vertex *rootVert)
{
    auto vertsMap = BuildVertexMap(rootVert);
    map<uint, vertex *> idMap{{0, CreateZero()},
                              {1, CreateOne()}};

    for (auto itrVar = vars.rbegin(); itrVar != vars.rend(); itrVar++)
    {
        auto curList = vertsMap.at(*itrVar);
        EraseRedundant(curList);
        AssignId(curList, &idMap);
    }
    DeleteVertexMap(&vertsMap);
    auto res = GetRightRoot(rootVert, &idMap);
    return res;
}

map<variable *, list<vertex *> *> bdd_manager::BuildVertexMap(vertex *rootVert)
{
    map<variable *, list<vertex *> *> res;

    for (auto itr : GetVariables())
        res.emplace(itr, new list<vertex *>);

    for (auto itr : BuildVertexList(rootVert))
    {
        auto vrb = itr->GetVariable();
        res.at(vrb)->push_back(itr);
    }
    return res;
}

void bdd_manager::EraseRedundant(list<vertex *> *lv)
{
    vertex *vtx;
    uint lowId, highId;

    auto itr = lv->begin();
    while (itr != lv->end())
    {
        vtx = *itr;
        lowId = vtx->GetLow()->GetId();
        highId = vtx->GetHigh()->GetId();
        if (lowId == highId)
        {
            vtx->SetId(lowId);
            itr = lv->erase(itr);
        }
        else
        {
            itr++;
        }
    }
}

void bdd_manager::AssignId(list<vertex *> *lv, map<uint, vertex *> *idMap)
{
    for (auto itr = lv->begin(); itr != lv->end(); itr++)
    {
        AddVertex(*itr, idMap);
        EraseDuplicates(itr, lv);
    }
}

void bdd_manager::AddVertex(vertex *vtx, map<uint, vertex *> *idMap)
{
    auto newId = idMap->size();
    vtx->SetId(newId);
    auto rightVertex = BuildRightVertex(vtx, idMap);
    idMap->emplace(newId, rightVertex);
}

vertex *bdd_manager::BuildRightVertex(vertex *ref, map<uint, vertex *> *idMap)
{
    vertex *rightLow = idMap->at(ref->GetLow()->GetId()),
           *rightHigh = idMap->at(ref->GetHigh()->GetId());

    return new non_term_vertex(ref->GetVariable(), ref->GetId(),
                               rightLow, rightHigh);
}

void bdd_manager::EraseDuplicates(list<vertex *>::iterator itr,
                                  list<vertex *> *lv)
{

    vertex *itrVtx, *vtx = *itr;

    uint lowId = vtx->GetLow()->GetId(),
         highId = vtx->GetHigh()->GetId(),
         itrLowId, itrHighId;

    for (itr++; itr != lv->end();)
    {
        itrVtx = *itr;
        itrLowId = itrVtx->GetLow()->GetId();
        itrHighId = itrVtx->GetHigh()->GetId();

        if (lowId == itrLowId and highId == itrHighId)
        {
            itrVtx->SetId(vtx->GetId());
            itr = lv->erase(itr);
        }
        else
        {
            itr++;
        }
    }
}

vertex *bdd_manager::GetRightRoot(vertex *root,
                                  map<uint, vertex *> *idMap)
{
    auto id = root->GetId();
    return idMap->at(id);
}

void bdd_manager::DeleteVertexMap(map<variable *, list<vertex *> *> *map)
{
    for (auto itr = map->begin(); itr != map->end(); itr++)
        delete (*itr).second;
}