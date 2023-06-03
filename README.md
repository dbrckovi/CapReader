# CapReader
Arduino Nano based capacitance meter

# Brief description:
Can measure capacitors from 1nF upwards.

When button is pressed, continuously discharges and charges the capacitor through different resistors, measuring time it takes for a capacitor to charge up to 63.2%.
When the value is measured, discharges the capacitor and value is displayed on LCD.

Button must be held until measurement is finished.

# Problems:
 
 - Measuring capacitors of about 10uF takes longer than 100+F. Resistor values must be calibrated to avoid these jumps in measurement time
 - Measurements which took < 10ms are discarded. This value is probably too high.

# Ideas:
 - Try using micros instead of millis
 - Try replacing 10M resistor with 100M to see if pF capacitances can be measured.
 - Try adding 220 Ohm resistor to see if really big capacitors can be measured in reasonable time.

# Todo:
 - Add code comments
 - Add schematic
 - Write proper readme
 - Choose proper license