#include <vertex.h>

non_term_vertex::non_term_vertex(vertex *lowOne,
                                 vertex *highOne) : vertex::vertex() {
    low = lowOne;
    high = highOne;
}
non_term_vertex::non_term_vertex(variable *v,
                                 vertex *lowOne,
                                 vertex *highOne) : vertex::vertex(v) {
    low = lowOne;
    high = highOne;
}
non_term_vertex::non_term_vertex(variable *v,
                                 u_int32_t i,
                                 vertex *lowOne,
                                 vertex *highOne) : vertex::vertex(v, i) {
    low = lowOne;
    high = highOne;
}
non_term_vertex::~non_term_vertex() {}

vertex *non_term_vertex::CreateCopy() {
    return new non_term_vertex(GetVariable(), GetId(), low, high);
}

bool non_term_vertex::IsTerminal() { return false; }

vertex *non_term_vertex::GetLow() { return low; }
vertex *non_term_vertex::GetHigh() { return high; }

string non_term_vertex::Info() {
    return "Non Terminal vertex\n" +
           InfoVertex() + "\n" +
           "  Low  -> " + low->InfoVertex() + "\n" +
           "  High -> " + high->InfoVertex() + "\n";
}