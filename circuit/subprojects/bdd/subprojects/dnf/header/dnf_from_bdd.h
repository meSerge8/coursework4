#pragma once

#include <exception>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

#define conjunction vector<var_dnf_from_bdd>

enum var_dnf_from_bdd {
    none,
    positive,
    negative
};

class dnf_from_bdd {
   private:
    u_int variableNumber;
    vector<conjunction> conjuctions;
    vector<string> names;

   public:
    // Constructors
    dnf_from_bdd(int varNum);
    ~dnf_from_bdd();

    // Add conjunction
    void AddConjunction(conjunction);

    // Import names
    void ImportNames(vector<string> names);

    // Print
    friend ostream &operator<<(ostream &, dnf_from_bdd &);

   private:
    // Print
    string PrintConjunction(conjunction);
};

// Print

ostream &operator<<(ostream &, list<dnf_from_bdd> &);