#include <vertex.h>

vertex::vertex() {}

vertex::vertex(variable *v) {
    var = v;
    mark = 0;
}

vertex::vertex(variable *v, u_int32_t i) {
    var = v;
    id = i;
    mark = 0;
}

vertex::~vertex() {}

bool vertex::operator==(vertex &two) {
    if (GetVariable() != two.GetVariable())
        return false;

    if (GetLow() != two.GetLow() or GetHigh() != two.GetHigh())
        return false;

    return true;
}

void vertex::SetVariable(variable *v) { var = v; }
variable *vertex::GetVariable() { return var; }

void vertex::SetMark(bool m) { mark = m; }
bool vertex::GetMark() { return mark; }
void vertex::SwitchMark() { mark = not mark; }

void vertex::SetId(u_int32_t i) { id = i; }
u_int32_t vertex::GetId() { return id; }

string vertex::InfoVertex() {
    return InfoVariable(*var) + " | " +
           "id: " + to_string(id) + " | " +
           "mark: " + to_string(mark);
}

ostream &operator<<(ostream &r, vertex &v) {
    r << v.Info();
    return r;
}