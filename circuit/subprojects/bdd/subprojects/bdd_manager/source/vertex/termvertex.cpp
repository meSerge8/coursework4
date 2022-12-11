#include <vertex.h>

term_vertex::term_vertex() {}
term_vertex::term_vertex(variable *v, u_int32_t i) : vertex::vertex(v, i) {}
term_vertex::term_vertex(variable *v) : vertex::vertex(v) {}
term_vertex::~term_vertex() {}

vertex *term_vertex::CreateCopy() {
    return new term_vertex(GetVariable(), GetId());
}

bool term_vertex::IsTerminal() { return true; }

vertex *term_vertex::GetLow() { return nullptr; }
vertex *term_vertex::GetHigh() { return nullptr; }

string term_vertex::Info() {
    return "Terminal vertex\n" +
           InfoVertex() + "\n";
}