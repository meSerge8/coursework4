#include "PermissibleSetBuilder.h"

bool containsVec(vector<vector<bool>> *vs, vector<bool> v) {
    return find(vs->begin(), vs->end(), v) != vs->end();
}
