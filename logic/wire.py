"""
实现wire
"""

class Wire(object):
    """ wire """
    def __init__(self, value):
        self.value = value
        self.actions = []

    def get_signal(self):
        return self.value

    def set_signal(self, value):
        if self.value != value:
            self.value = value
            self.call_each_actions()

    def return_set_signal(self, value):
        def set_signal():
            self.set_signal(value)
        return set_signal

    def call_each_actions(self):
        for action in self.actions:
            action()

    def add_action(self, action):
        self.actions.append(action)
        action()

    def __repr__(self):
        return "<WIRE value: %s>" % self.value

