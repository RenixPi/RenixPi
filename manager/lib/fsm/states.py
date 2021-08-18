from pysm import StateMachine, State, Event

# class StandBy(State):
#     def on_enter(self, state, event):
#         print("enter standby")

#     def on_exit(self, state, event):
#         print("exit standby")

#     def on_event1(self, state, event):
#         print("handling event1")

#     def on_event2(self, state, event):
#         print("handling event2")

#     def register_handlers(self):
#         self.handlers = {
#             'enter': self.on_enter,
#             'exit': self.on_exit,
#             'event1': self.on_event1,
#             'event2': self.on_event2
#         }

class InitialPowerUp(State):
    def on_enter(self, state, event):
        print("make sure power to pis is off")



