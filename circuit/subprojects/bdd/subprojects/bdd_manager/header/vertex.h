#pragma once

#include <iostream>
#include <string>

#include "variable.h"

using namespace std;

// TODO

// struct variable
// {
//     string value;
//     u_int32_t index;
// };

class vertex
{
private:
    variable *var;
    u_int32_t id = 0;
    bool mark = 0;

public:
    //Constructors
    vertex();
    vertex(variable *);
    vertex(variable *, u_int32_t);
    virtual ~vertex();

    virtual vertex *CreateCopy() = 0;

    virtual bool IsTerminal() = 0;

    virtual vertex *GetLow() = 0;
    virtual vertex *GetHigh() = 0;

    virtual string Info() = 0;

    bool operator==(vertex &);

    void SetMark(bool);
    bool GetMark();
    void SwitchMark();

    void SetVariable(variable *);
    variable *GetVariable();

    void SetId(u_int32_t);
    u_int32_t GetId();

    string InfoVertex();

    friend ostream &operator<<(ostream &, vertex &);
};

//----------------------------------------------------------
// move to different h files
class term_vertex : public vertex
{
public:
    term_vertex();
    term_vertex(variable *);
    term_vertex(variable *, u_int32_t);
    ~term_vertex();

    vertex *CreateCopy() override;

    bool IsTerminal() override;

    vertex *GetLow() override;
    vertex *GetHigh() override;

    string Info() override;
};

//----------------------------------------------------------

class non_term_vertex : public vertex
{
private:
    vertex *low;
    vertex *high;

public:
    non_term_vertex(vertex *lowOne, vertex *highOne);
    non_term_vertex(variable *, u_int32_t, vertex *, vertex *);
    non_term_vertex(variable *, vertex *, vertex *);
    ~non_term_vertex();

    vertex *CreateCopy() override;

    bool IsTerminal() override;

    vertex *GetLow() override;
    vertex *GetHigh() override;

    string Info() override;
};