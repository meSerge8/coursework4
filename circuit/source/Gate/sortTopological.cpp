#include "Gate.h"

vector<Gate *> Gate::sortTopological(vector<Gate *> gates) {
    vector<int> in_degrees(gates.size(), 0);
    queue<Gate *> q;

    for (size_t i = 0; i < gates.size(); i++) {
        in_degrees[i] = gates[i]->CountPredecessors();
        if (in_degrees[i] == 0) {
            q.push(gates[i]);
        }
    }

    int countVisited = 0;
    vector<Gate *> result;

    while (!q.empty()) {
        countVisited++;
        Gate *frontGate = q.front();
        q.pop();
        result.push_back(frontGate);

        for (Gate *sucGate : frontGate->GetSuccessors()) {
            int i = find(gates.begin(), gates.end(), sucGate) - gates.begin();
            in_degrees[i]--;
            if (in_degrees[i] == 0)
                q.push(gates[i]);
        }
    }

    if (gates.size() != countVisited)
        throw logic_error("Sorting failed: there is a cycle in graph");

    return result;
}