# Desktop Train

This project is a small HO-scale layout on my desk that runs switching
operations under my monitor to distract me.

## Operations

There's an engine house on the left, and three spurs on the right. When idle,
there is a locomotive in the engine house and two of the spurs are occupied
with one car each. Each cycle, the locomotive fetches one of the cars, spots
it to the empty spur, and returns to the engine house. Repeat forever.

The trains runs under control of [DCC-EX](https://dcc-ex.com), using some
[EX-RAIL](https://dcc-ex.com/ex-rail) scripts. The loco has to be DCC
(obviously), the turnouts are computer-controlled, and there are eight sensors
on the track to let the computer know where everything is.

## Track

I use [Kato Unitrack](https://katousa.com/ho-unitrack):
* [Just the track](Desktop Layout Track.jpg)
* [With engine house, monitor, laptop stand](Desktop Layout Stuff.jpg)
* [Fancy SCARM rendering](Desktop Layout 3D.jpg)

T0 and T1 are the turnouts, each with a Kato turnout machine. The computer can
close or throw the switches to route the train.

S0 through S7 are sensors. The computer can tell when something (loco or car)
is in front of one of the sensors.

S0 is used when the locomotive is going to the house, to see when it is fully
inside.

S1 is used for uncoupling; the track next to it is Kato's magnetic uncoupler.
The sensor is mounted so it can "see" between the loco and car to know when
the couplers are centered on the magnet. To uncouple, the loco pulls a car to
the left and stops when the couplers are over the magnet. A bit of jostling
gets them uncoupled, with the car's coupler still over the magnet, ready for a
shove.

S2, S4, and S6 are used when shoving a car to a spur. They are mounted about
100mm from the end of each spur.

S3, S5, and S7 are used when fetching a car from a spur. They are mounted
about 50mm from the end of each spur.

The distance between the sensors on each spur is such that:
* When shoving to the spur, the loco can shove until the first sensor (e.g.
S2) is triggered, and stop before the second sensor (e.g. S3) is triggered.
* When fetching from the spur, the loco can move right until the second sensor
(e.g. S3) is triggered, stop before the end of the track, and that point
assume it has coupled to the car.

For example, to move a car from spur1 to spur3:
* loco in house on left, a car on spur1 to the right blocking S2
* close T0 to line turnouts for spur1
* loco moves to the right, bumps car, and continues until S3 triggers
* loco with car coupled moves left until the couplers are over the magnet (S1
can see between the loco and car)
* loco jostles a little to uncouple (retrying if necessary)
* open T0 and close T1 to line turnouts for spur3
* loco moves right, pushing car to spur3 until S6 triggers
* loco leaves car blocking S6 but not S7
* loco returns to engine house

The middle spur is just about as short as it can be and still have coupling
work. When a car is spotted to the middle spur, it's "far" end will be between
S4 and S5, or about 75mm from the end of the spur. There has to be enough
straight track between the car and the last curve so the loco can line up
straight enough with the car to couple. If the spur is too short, the loco
will still be on the curve when the couplers meet and it might not work.

## Hardware

### Computer

The computer is the one recommended by the DCC-EX project: an
[Elegoo Mega 2560 R3](https://us.elegoo.com/collections/arduino-kits/products/elegoo-mega-2560-r3-board)
with an
[Arduino Motor Shield](https://store-usa.arduino.cc/products/arduino-motor-shield-rev3).
Other variations surely work just as well.

### Power

One objective was to have a single 12V power input, used to power the track,
the turnout machines, and the computer. The Arduino Mega 2560 says it can
take up to 20V input, but the Elegoo Mega 2560 only specifies up to 9V. It
would not be surprising if it used a cheaper regulator. In any case, the 12V
input is regulated down to ~8V to power the Elegoo, the 5V output from the
Elegoo's regulator is used to power the turnout machine logic (below), and
12V is fed to the motor shield (for the track) and the capacitive discharge
unit for the turnouts (below).

### Sensors

The sensors are
[Pololu Digital Distance Sensors](https://www.pololu.com/product/4050).
The module has a
[VL6180X](https://www.st.com/en/imaging-and-photonics-solutions/vl6180x.html)
controlled by a microcontroller on it, and asserts a signal if anything is
detected within 50mm. It has a three-wire interface: two for power and one for
the detect signal.

### Turnouts

The two turnouts are driven by a
[TI L293DNE](https://www.ti.com/product/L293D/part-details/L293DNE). It
requires two power supplies: one for the turnouts, and one for the logic
signals. The turnout power is the 12V input, but passed through a capacitive
discharge unit to avoid burning out a turnout due to bugs. The capacitor
value is chosen so it can reliably throw a turnout, and the resistor value so
the capacitor recharges enough in about half a second. Technically the
resistor can dissipate 1.44W instantaneously at power on, but normally it
charges the capacitor starting at a few volts, so maybe a bit over half a
watt for a few hundred milliseconds each throw. In any case a 1-Watt resistor
is easy to use and should be well capable of the power required.


12V >----/\/\/------+------> L293DNE VCC2
          100       |
          1 W      === 2200 uF
                    |
                   GND

Six GPIOs are needed, three for each turnout. There might be a way to do it
with two per turnout, but GPIOs are plentiful on the Mega 2560. Controlling
the turnouts basically follows
[this example](https://dcc-ex.com/ex-commandstation/accessories/turnouts/solenoid-turnouts.html#using-an-l293d-motor-driver-single-solenoid-coil-turnouts),
where "External Power" on their fritzing diagram is the capacitive discharge
unit.

### Wiring

Bussed power to the sensors
AWG30 is fine
Just lays along the track

### Display

There's an i2c 64 x 128 OLED in one of the upstairs windows, used to show what the
computer is trying to do to help diagnose trouble. The text is so tiny it's only
good for diagnostics, not very good for show.

### LED

There's an RGB LED in the engine house, driven directly by GPIOs. I could not
get DCC-EX to set each color with "analogWrite" or equivalent to PWM each
color, so each color is just off or on. Resistors were picked to keep the
current around 15 mA (I think each pin can do 20 mA), except green which seems
inherently brighter on the particular LED I used:

* Red - 220 ohms, 2.1 V drop, 13 mA
* Green - 270 ohms, 2.75 V drop, 8.5 mA
* Blue - 100 ohms, 3.2 V drop, 18 mA

## Other

There are lots of 3D-printed parts, some critical and some not. There were all
designed in [Autodesk Fusion](https://www.autodesk.com/products/fusion-360)
(free for noncommercial use) and printed in PLA on a
[Prusa i3 MK3S+](https://www.prusa3d.com/category/original-prusa-i3-mk3s/).

* Spur sensor holders. These hold the Pololu sensors vertically next to the
track with the sensor at the same height as the couplers. Having them at that
height makes it so when a car moves in front of a sensor, the sensor sees the
coupler first. (In other layouts it is important to see the entire train as
one rather than a sequence of cars, but that is less important here.)

* Uncoupler sensor holder. This is like the other sensor holders, but positions
the sensor a little higher so it does not see the couplers. The idea is it
needs to see the gap between cars to do the uncoupling.

* Track ends. These little brackets snap onto the ends of the track so trains
can't drive off the desk. The Kato track-end pieces look better but leave a
lot of wasted room at the end. These also have screw holes for the spur and
sensor spacers.

* Spur and sensor spacers. Since this setup sits on my desk where stuff is
constantly moving around, it gets jostled. Rather than have the track always
kinky, there are printed spacers that hold the spurs in place relative to each
other. The spacers also hold the sensors in the right places along the spurs
(50mm and 100mm from the ends) so sensor movement doesn't break things. All
of the spacers are drawn up in Fusion so it can get the geometry right.

* Engine house. This goes at the left end, and is long enough to comfortably
hold an SW1200 or GP30, with all the electronics in the ceiling. Putting the
electronics in the ceiling lets the whole house fit in the printer's volume.
There is one piece that is the floor and walls, another is the ceiling where
everything mounts, and a third is the roof that just sits on top.

## Software

The software is CommandStation-EX (an Arduino program) with a fairly simple
EX-Rail script to read sensors, control turnouts, and run the train. In this
repo, the directory arduino/CommandStation-EX has the original 5.0.7 release
changed as follows:
* config.h copied from config.example.h, then (1) WiFi disabled and (2)
display enabled. Disabling WiFi is not really required, and enabling the
display is (obviously) only if you have a display.
* CommandStation-EX.ino changed to not show free RAM on the display;
* myAutomation\*.h scripts added to run everything.

The CommandStation-EX automatically looks for myAutomation.h and enables
EX-Rail if it is there. This system uses a few #included files to organize
things:
* myAutomation\_layout.h has stuff about the layout (sensors, turnouts, etc.)
* myAutomation\_loco.h has stuff about the loco used (how to control lights
and sounds)
* myAutomation\_actions.h has a bunch of subroutines
* myAutomation\_ops.h has the top-level operations scripts
* myAutomation.h #includes all these

If a newer version of CommandStation-EX drops, it might basically work to just
copy the myAutomation\*.h files into it and build. Creating config.h and
editing CommandStation-EX.ino are just for the display.

The arduino build is done with the
[command line tools](https://github.com/arduino/arduino-cli/releases).
I have not used the IDE for quite a while, and never used the online tools,
although I'm sure either of those would work just as well. A few batch files
set up, initialize, build, and download to the board:
* ac-init.bat is run once at the beginning of time, and sets up the command
line tools
* brd-mega2560.bat is run once per terminal session, and sets an environment
variable for the building
* ac-build.bat <project> <port> will build and (if <port> is supplied)
download a project to the board, e.g. 'ac-build.bat CommandStation-EX' to
build, or 'ac-build-bat CommandStation-EX com3' to build and flash the board.
