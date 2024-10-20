// Move left and right along spur1 between sensors

AUTOSTART
POWERON
SETLOCO(LocoNum)
CALL(LedOff)
CALL(InitTurnouts)
POM(CvAcceleration, 0)
POM(CvDeceleration, 0)
FOLLOW(MainLoop)
DONE

SEQUENCE(MainLoop)

  // Move left
  CALL(LedRed)
  FWD(SlowDcc)
  AT(Sensor0)
  STOP
  DELAY(2000)

  // Move right
  CALL(LedGreen)
  REV(SlowDcc)
  AT(Sensor2)
  STOP
  DELAY(2000)

  FOLLOW(MainLoop)
