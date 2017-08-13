"""
实现逻辑门
"""

from wire import Wire
from agenda import after_delay


AND_GATE_DELAY = 1
OR_GATE_DELAY = 3
INVERTER_DELAY = 2


def logic_and(a1, a2):
    """return logical a1 and a2"""
    if a1 == 0 or a2 == 0:
        return 0
    elif a1 == 1 and a2 == 1:
        return 1
    else:
        print("LOGICAL AND: Invalid signal a1:%d a2:%d" % (a1, a2))

def logic_or(o1, o2):
    """return logical o1 or o2"""
    if o1 == 1 or o2 == 1:
        return 1
    elif o1 == 0 and o2 == 0:
        return 0
    else:
        print("LOGICAL OR: Invalid signal o1:%d o2:%d" % (o1, o2))

def logical_not(value):
    """return logical not value"""
    if value == 1:
        return 0
    elif value == 0:
        return 1
    else:
        print("LOGICAL NOT: Invalid signal %d" % value)

def inverter(i, o):
    """关联i与o，使i与o的关系与逻辑非的输入输出相符"""
    def invert_input():
        """它被当作wire的action使用，将time-action加入agenda"""
        new_value = logical_not(i.get_signal())
        after_delay(INVERTER_DELAY, o.return_set_signal(new_value))

    i.add_action(invert_input)

def and_gate(a1, a2, o):
    def and_inupt():
        new_value = logical_and(a1, a2)
        after_delay(AND_GATE_DELAY, o.return_set_signal(new_value))
    a1.add_action(and_inupt)
    a2.add_action(and_inupt)

def or_gate(o1, o2, o):
    def or_inupt():
        new_value = logical_or(a1, a2)
        after_delay(OR_GATE_DELAY, o.return_set_signal(new_value))
    o1.add_action(or_inupt)
    o1.add_action(or_inupt)
