class Agenda(object):
    """Agenda维持模拟器需要执行的action
    {
        <time1>:[action1, action2, action3, ...],
        <time2>:[action1, action2, action3, ...],
        <time3>:[action1, action2, action3, ...],
        ...
    }
    """
    def __init__(self):
        self.current_time = 0
        self.time_actions = {}

    def add_action(self, time, action):
        """增加action"""
        if time in self.time_actions:
            self.time_actions[time].append(action)
        else:
            self.time_actions[time] = [action]

    def run_all_actions(self):
        """运行agenda中所有的action"""
        time_actions = dict(self.time_actions.items())
        for time, actions in time_actions.items():
            if actions == []:
                del self.time_actions[time]
            else:
                self.current_time = time
                for action in actions:
                    action()
                actions.clear()

    def __repr__(self):
        return "<AGENDA current_time: %s>" % self.current_time


# 全局变量，保存一切需要执行的操作
THE_AGENDA = Agenda()

def after_delay(delay_time, action):
    """在适当的时间所对应的队列增加action"""
    THE_AGENDA.add_action(delay_time + THE_AGENDA.current_time,
                          action)
