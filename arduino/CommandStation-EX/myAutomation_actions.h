ALIAS(CreepDcc, 8)
ALIAS(SlowDcc, 20)
ALIAS(FastDcc, 40)

ALIAS(MainLoop, 1)

ALIAS(Close0, 4)
ALIAS(Throw0, 5)
ALIAS(Close1, 6)
ALIAS(Throw1, 7)

ALIAS(LedOff, 10)
ALIAS(LedRed, 11)
ALIAS(LedGreen, 12)
ALIAS(LedBlue, 13)
ALIAS(LedYellow, 14)
ALIAS(LedMagenta, 15)
ALIAS(LedCyan, 16)
ALIAS(LedWhite, 17)

ALIAS(DisplayClear, 18)

ALIAS(Uncouple, 20)
ALIAS(UncoupleRetry, 21)

ALIAS(SpotPart1, 30)
ALIAS(SpotPart2, 31)
ALIAS(SpotSpur1, 32)
ALIAS(SpotSpur2, 33)
ALIAS(SpotSpur3, 34)

ALIAS(FetchPart1, 40)
ALIAS(FetchPart2, 41)
ALIAS(FetchSpur1, 42)
ALIAS(FetchSpur2, 43)
ALIAS(FetchSpur3, 44)

ALIAS(GoHome, 50)

// Turnout control

SEQUENCE(Close0)
  SET(T0Close)
  SET(T0Pulse)
  DELAY(TurnoutPulse_ms)
  RESET(T0Pulse)
  RESET(T0Close)
  DELAY(TurnoutRecharge_ms)
  RETURN

SEQUENCE(Throw0)
  SET(T0Throw)
  SET(T0Pulse)
  DELAY(TurnoutPulse_ms)
  RESET(T0Pulse)
  RESET(T0Throw)
  DELAY(TurnoutRecharge_ms)
  RETURN

SEQUENCE(Close1)
  SET(T1Close)
  SET(T1Pulse)
  DELAY(TurnoutPulse_ms)
  RESET(T1Pulse)
  RESET(T1Close)
  DELAY(TurnoutRecharge_ms)
  RETURN

SEQUENCE(Throw1)
  SET(T1Throw)
  SET(T1Pulse)
  DELAY(TurnoutPulse_ms)
  RESET(T1Pulse)
  RESET(T1Throw)
  DELAY(TurnoutRecharge_ms)
  RETURN

SEQUENCE(InitTurnouts)
  // all turnout pins output, low
  RESET(T0Pulse)
  RESET(T0Close)
  RESET(T0Throw)
  RESET(T1Pulse)
  RESET(T1Close)
  RESET(T1Throw)
  CALL(Close0)
  CALL(Close1)
  RETURN

// LED

SEQUENCE(LedOff)
  RESET(RedPin)
  RESET(GreenPin)
  RESET(BluePin)
  RETURN

SEQUENCE(LedRed)
  SET(RedPin)
  RESET(GreenPin)
  RESET(BluePin)
  RETURN

SEQUENCE(LedGreen)
  RESET(RedPin)
  SET(GreenPin)
  RESET(BluePin)
  RETURN

SEQUENCE(LedBlue)
  RESET(RedPin)
  RESET(GreenPin)
  SET(BluePin)
  RETURN

SEQUENCE(LedYellow)
  SET(RedPin)
  SET(GreenPin)
  RESET(BluePin)
  RETURN

SEQUENCE(LedMagenta)
  SET(RedPin)
  RESET(GreenPin)
  SET(BluePin)
  RETURN

SEQUENCE(LedCyan)
  RESET(RedPin)
  SET(GreenPin)
  SET(BluePin)
  RETURN

SEQUENCE(LedWhite)
  SET(RedPin)
  SET(GreenPin)
  SET(BluePin)
  RETURN

// Display

SEQUENCE(DisplayClear)
  SCREEN(0, 0, " ")
  SCREEN(0, 1, " ")
  SCREEN(0, 2, " ")
  SCREEN(0, 3, " ")
  SCREEN(0, 4, " ")
  SCREEN(0, 5, " ")
  SCREEN(0, 6, " ")
  SCREEN(0, 7, " ")
  RETURN

// Uncoupling seems more reliable for more cars if we start ahead of the
// magnet and push back into it. The failure mode when starting behind
// the magnet and pulling over it is sometimes both couplers get pulled
// to the same side.

// Uncouple
// On entry:
// - Loco+car moving forward towards uncoupler
// On return:
// - Loco ahead of uncoupler
// - Car on uncoupler ready to push

SEQUENCE(Uncouple)
  SCREEN(0, 2, "UNCOUPLE")
  SCREEN(0, 4, " ")
  PRINT("Uncouple")
  AT(Sensor1)
  DELAY(2000)
  POM(CvDeceleration, 10)
  FWD(CreepDcc)
  AT(-Sensor1)
  // can see between the cars
  DELAY(2500)
  STOP
  DELAY(2000)
  // "goto here" would work for the retry
  // couplers should be just past magnet
  // XXX If Sensor1 is not activated at this point, there's probably
  // not a car (fetching failed)
  REV(CreepDcc)
  AT(-Sensor1)
  // can see between the cars
  STOP
  DELAY(2000)
  FWD(CreepDcc)
  DELAY(2000)
  STOP
  DELAY(2000)
  // If Sensor1 is active, it's the car and uncoupling failed
  IF(Sensor1)
    CALL(UncoupleRetry)
  ENDIF
  RETURN

SEQUENCE(UncoupleRetry)
  SCREEN(0, 4, "UNCOUPLE RETRY")
  PRINT("Uncouple Retry")
  // couplers should be just past magnet
  REV(CreepDcc)
  AT(-Sensor1)
  // can see between the cars
  STOP
  DELAY(2000)
  FWD(CreepDcc)
  DELAY(2000)
  STOP
  DELAY(2000)
  // If Sensor1 is active, it's the car and uncoupling failed
  IF(Sensor1)
    FOLLOW(UncoupleRetry)
  ENDIF
  RETURN

// Spot car on spur
// - Loco should be ahead of Sensor1
// - Car should be just behind Sensor1, but still on magnet
// - Back up and push car to spur
// - Pull forward, leaving Loco just ahead of Sensor1
// On return:
// - Car on spur
// - Loco just ahead of Sensor1, moving SlowDcc

// Set turnouts
// Call SpotPart1
// Wait for spur-end sensor
// Call SpotPart2

SEQUENCE(SpotPart1)
  SCREEN(0, 4, "PART 1")
  CALL(BellIf)
  POM(CvAcceleration, 40)
  DELAY(1000)
  REV(SlowDcc)
  AFTER(Sensor1)
  RETURN

SEQUENCE(SpotPart2)
  SCREEN(0, 4, "PART 2")
  POM(CvDeceleration, 0)
  STOP
  DELAY(2000)
  CALL(BellOff)
  CALL(EngineSoundIf)
  CALL(UncoupleSound)
  // XXX check that we left the car behind
  FWD(FastDcc)
  AT(Sensor1)
  POM(CvDeceleration, 10)
  FWD(SlowDcc)
  RETURN

SEQUENCE(SpotSpur1)
  SCREEN(0, 2, "SPOT 1")
  PRINT("Spot to Spur 1")
  CALL(Close0)
  CALL(SpotPart1)
  AT(Sensor2)
  CALL(SpotPart2)
  RETURN

SEQUENCE(SpotSpur2)
  SCREEN(0, 2, "SPOT 2")
  PRINT("Spot to Spur 2")
  CALL(Throw0)
  CALL(Throw1)
  CALL(SpotPart1)
  AT(Sensor4)
  CALL(SpotPart2)
  RETURN

SEQUENCE(SpotSpur3)
  SCREEN(0, 2, "SPOT 3")
  PRINT("Spot to Spur 3")
  CALL(Throw0)
  CALL(Close1)
  CALL(SpotPart1)
  AT(Sensor6)
  CALL(SpotPart2)
  RETURN

// Fetch car from spur:
// - Loco should be ahead of Sensor1
// - Car should be on spur
// - Go couple to car
// On return:
// - Loco+Car still on spur

// reverse fast, delay after sensor1, reverse slow
SEQUENCE(FetchPart1)
  SCREEN(0, 4, "PART 1")
  DELAY(1000)
  POM(CvAcceleration, 10)
  REV(FastDcc)
  AFTER(Sensor1)
  DELAY(2000)
  POM(CvDeceleration, 10)
  REV(SlowDcc)
  CALL(EngineSoundIf)
  ENDIF
  RETURN

// stop, make sounds, forward slow
SEQUENCE(FetchPart2)
  SCREEN(0, 4, "PART 2")
  POM(CvDeceleration, 0)
  STOP
  DELAY(2000)
  CALL(CoupleSound)
  CALL(TootTootIf)
  CALL(EngineSoundIf)
  POM(CvAcceleration, 10)
  FWD(SlowDcc)
  RETURN

SEQUENCE(FetchSpur1)
  SCREEN(0, 2, "FETCH 1")
  PRINT("Fetch from Spur 1")
  CALL(Close0)
  CALL(FetchPart1)
  AT(Sensor3)
  CALL(FetchPart2)
  RETURN

SEQUENCE(FetchSpur2)
  SCREEN(0, 2, "FETCH 2")
  PRINT("Fetch from Spur 2")
  CALL(Throw0)
  CALL(Throw1)
  CALL(FetchPart1)
  AT(Sensor5)
  CALL(FetchPart2)
  RETURN

SEQUENCE(FetchSpur3)
  SCREEN(0, 2, "FETCH 3")
  PRINT("Fetch from Spur 3")
  CALL(Throw0)
  CALL(Close1)
  CALL(FetchPart1)
  AT(Sensor7)
  CALL(FetchPart2)
  RETURN

// Going into the house

// After SpotPart2; has just reached Sensor1 and been told
// to decelerate (10) to SlowDcc
SEQUENCE(GoHome)
  SCREEN(0, 0, "HOME")
  SCREEN(0, 2, " ")
  SCREEN(0, 4, " ")
  PRINT("Go Home")
  AFTER(Sensor1)
  DELAY(4000)
  FWD(CreepDcc)
  AT(Sensor0)
  POM(CvDeceleration, 10)
  DELAY(1000)
  STOP
  DELAY(2000)
  RETURN
