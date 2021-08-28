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

class OnEnterState(State):

    def register_handlers(self):
        self.handlers = {
            'enter': self.on_enter
        }



class PiOff(OnEnterState):
    def on_enter(self, state, event):
        print("make sure power to pis is off")
    
class Sleep(OnEnterState):
    def on_enter(self, state, event):
        print("go into deep sleep")

class PiOn(OnEnterState):
    def on_enter(self, state, event):
        print("power it up!")
    

class Hold(OnEnterState):
    def on_enter(self):
        print("ignition off, waiting on decision to shutdown")

class StartShutdown(OnEnterState):
    def on_enter(self):
        print("send signal to PIs for shutdown")

class WaitForShutdown(OnEnterState):
    def on_enter(self):
        print("waiting for PIs to shutdown")

class ShutdownConfirmed(OnEnterState):
    def on_enter(self):
        print("PIs no longer consuming power")

