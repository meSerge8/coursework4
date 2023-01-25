#include "Gate.h"

vector<Gate *> sortTopological(vector<Gate *> gates) {
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
            auto f = find(gates.begin(), gates.end(), sucGate);
            if (f == gates.end()) {
                continue;
            }

            int i = f - gates.begin();
            in_degrees[i]--;
            if (in_degrees[i] == 0) {
                q.push(gates[i]);
            }
        }
    }

    if (gates.size() != countVisited) {
        char buffer[300];
        sprintf(buffer, "Sorting failed: there is a cycle in graph: gates = %ld, visited = %d", gates.size(), countVisited);
        throw logic_error(string(buffer));
    }

    return result;
}