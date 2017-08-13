from gate import inverter
from wire import Wire
from agenda import Agenda, THE_AGENDA

def monitor(name, wire):

    def show():
        nonlocal wire
        global THE_AGENDA
        print("{[name: %s]" % name, end="")
        print("[current_time: %s]" % THE_AGENDA.current_time, end="")
        print("[new_value: : %s]}" % wire.get_signal(), end="\n\n")

    wire.add_action(show)


i = Wire(0)
monitor("input", i)
o = Wire(0)
monitor("output", o)

print("-------------------inverter(i,o)----------------------")
inverter(i, o)
THE_AGENDA.run_all_actions()

print("------------------------------------------------------")
i.set_signal(1)
THE_AGENDA.run_all_actions()

print("------------------------------------------------------")
i.set_signal(0)
THE_AGENDA.run_all_actions()

print("------------------------------------------------------")
i.set_signal(1)
THE_AGENDA.run_all_actions()

print("------------------------------------------------------")
i.set_signal(0)
THE_AGENDA.run_all_actions()

print("------------------------------------------------------")
i.set_signal(1)
THE_AGENDA.run_all_actions()

print("------------------------------------------------------")
i.set_signal(0)
THE_AGENDA.run_all_actions()

