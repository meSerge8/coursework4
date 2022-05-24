#include "bdd.h"

ostream &operator<<(ostream &os, bdd &b)
{
    os << "========== bdd ==========" << endl;
    for (auto root : b.roots)
    {
        auto verts = BuildVertexList(root);
        os << endl
          << "----- new root -----" << endl
          << "amount of vertices: " << to_string(verts.size()) << endl
          << endl;

        for (auto v : verts)
            os << *v << endl;

        os << "----- new root end -----" << endl;
    }
    os << endl
      << "========== bdd end ==========" << endl;

    return os;
}
