Description
===========

Example of state machine using State Design Pattern described by the Gang of Four.

There example consists of two important base classes:
Processor - the State Machine or the context for the state
ProcessorState - the state of the context

The ProcessorState and its subclasses hold the state transition logic. They do not hold any business logic.
The Processor and its subclasses hold all the business logic. They do not hold any state transition logic. The Processor takes care of the state creation base on the logic described by the states, so logic of building a state controls by the Processor.

When the Processor receives a request for an action, the control flow is passed to the current state as an event. Depending on the defined state transition logic and action for each state, the current state may delegate the work back to the Processor as an event to action upon or the current state may pass the next state to transit back to the Processor.

Build
=====
You can build using Visual Studio 2022 or later, using C++14.
Only the Release for x64 build configuration is setup. I have not tested with other configurations yet.
Therefore, ensure your build configuration is set to Release for x64 before attempting to build.

Test
=====
The TransactionServiceTest project uses Google Test to demonstrate some of the state transactions, including when timeout occurs.
You can read more about how to setup Google Test for your projects in my blog:
https://robertbui.com/how-to-test-driven-development-using-google-test-on-visual-studio-2022/

You will also learn how to run the tests as well.





