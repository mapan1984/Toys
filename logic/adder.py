from wire import Wire
from gate import add_gate, or_gate, interver

def half_adder(a, b, s, c):
    d = Wire(0)
    e = Wire(0)
    or_gate(a, b, d)
    and_gate(a, b, c)
    interver(c, e)
    and_gate(d, e, s)
