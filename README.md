# Heislab---TilDat

Bug 1:
If you press the button that is in the same store as the elevator. The lights light up and does not turn off until the elevator returns to the same store. 
Fixet: The condition on light is now outside the switch, with conditions: State = Wait and State = Open_door.

Bug 2:
up button doues not work in the 3 store.
Fixed.

Bug 3:
When in state = Wait_stop, the elevator reads input orderes store as higher than current position and goes up (until it gets stuck).
When in Wait_Stop and ordered_store > current_pos -> Goes up to ordered_store without issues.
When in Wait_Stop and ordered_store < current_pos -> Goes up to , and unless a store with higher number is pressed before it reaches the top, it will go up until it stops by itself.

Bug 4: 
Timer in State = Wait is irregular, and the elevator waits between 0.5 seconds and 10 seconds depending on state, direction, number of orders...

