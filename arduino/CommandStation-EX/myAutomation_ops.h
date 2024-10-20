AUTOSTART
POWERON
SETLOCO(LocoNum)

POM(CvMasterVolume, 10)

CALL(DisplayClear)
CALL(LedOff)
CALL(InitTurnouts)
FOLLOW(MainLoop)
DONE

SEQUENCE(MainLoop)

  // Loco in house, cars on two spurs in front of near sensors (2, 4, or 6)

  IF(SwRun)

    IF(Sensor3)
      SCREEN(0, 0, "ERROR")
      SCREEN(0, 2, "SENSOR 3")
      CALL(TootTootIf)
      DELAY(1000)
      FOLLOW(MainLoop)
    ENDIF

    IF(Sensor5)
      SCREEN(0, 0, "ERROR")
      SCREEN(0, 2, "SENSOR 5")
      CALL(TootTootIf)
      DELAY(1000)
      FOLLOW(MainLoop)
    ENDIF

    IF(Sensor7)
      SCREEN(0, 0, "ERROR")
      SCREEN(0, 2, "SENSOR 7")
      CALL(TootTootIf)
      DELAY(1000)
      FOLLOW(MainLoop)
    ENDIF

    SCREEN(0, 0, "RUNNING")
    SCREEN(0, 2, " ")

    CALL(LedWhite)

    FON(HeadLight)
    CALL(DitchLightsOn)
    CALL(SwitchModeOn)
    CALL(EngineSoundIf)
    DELAY(5000)

    // Comments:
    //   spur1+ means there is a car on spur1
    //   spur2- means there is not a car on spur2
    //   spur3? means we don't know if there's a car on spur3

    IF(Sensor2)
      // spur1+ spur2? spur3?
      IF(Sensor4)
        // spur1+ spur2+ spur3?
        IF(Sensor6)
          // spur1+ spur2+ spur3+
          // ERROR all spurs occupied
          SCREEN(0, 0, "ERROR")
          SCREEN(0, 2, "THREE CARS")
          PRINT("ERROR: THREE CARS")
          CALL(TootTootIf)
          DELAY(1000)
          FOLLOW(MainLoop)
        ELSE
          // spur1+ spur2+ spur3-
          // move spur1 to spur3
          SCREEN(0, 0, "SPUR 1 TO 3")
          PRINT("Spur 1 to Spur 3")
          CALL(FetchSpur1)
          CALL(Uncouple)
          CALL(SpotSpur3)
        ENDIF
      ELSE
        // spur1+ spur2- spur3?
        IF(Sensor6)
          // spur1+ spur2- spur3+
          // move spur3 to spur2
          SCREEN(0, 0, "SPUR 3 TO 2")
          PRINT("Spur 3 to Spur 2")
          CALL(FetchSpur3)
          CALL(Uncouple)
          CALL(SpotSpur2)
        ELSE
          // spur1+ spur2- spur3-
          // move spur1 to spur3
          SCREEN(0, 0, "SPUR 1 TO 3")
          PRINT("Spur 1 to Spur 3")
          CALL(FetchSpur1)
          CALL(Uncouple)
          CALL(SpotSpur3)
        ENDIF
      ENDIF
    ELSE
      // spur1- spur2? spur3?
      IF(Sensor4)
        // spur1- spur2+ spur3?
        IF(Sensor6)
          // spur1- spur2+ spur3+
          // move spur2 to spur1
          SCREEN(0, 0, "SPUR 2 TO 1")
          PRINT("Spur 2 to Spur 1")
          CALL(FetchSpur2)
          CALL(Uncouple)
          CALL(SpotSpur1)
        ELSE
          // spur1- spur2+ spur3-
          // move spur2 to spur1
          SCREEN(0, 0, "SPUR 2 TO 1")
          PRINT("Spur 2 to Spur 1")
          CALL(FetchSpur2)
          CALL(Uncouple)
          CALL(SpotSpur1)
        ENDIF
      ELSE
        // spur1- spur2- spur3?
        IF(Sensor6)
          // spur1- spur2- spur3+
          // move spur3 to spur2
          SCREEN(0, 0, "SPUR 3 TO 2")
          PRINT("Spur 3 to Spur 2")
          CALL(FetchSpur3)
          CALL(Uncouple)
          CALL(SpotSpur2)
        ELSE
          // spur1- spur2- spur3-
          // ERROR no cars
          SCREEN(0, 0, "ERROR")
          SCREEN(0, 2, "NO CARS")
          PRINT("ERROR: NO CARS")
          CALL(TootTootIf)
          DELAY(1000)
          FOLLOW(MainLoop)
        ENDIF
      ENDIF
    ENDIF

    CALL(GoHome)

  ELSE // IF(SwRun)

    SCREEN(0, 0, "WAITING FOR RUN")
    SCREEN(0, 2, " ")
    SCREEN(0, 4, " ")
    PRINT("Waiting for Run Sw")
    CALL(LedRed)

    DELAY(1000)

    FOFF(HeadLight)
    CALL(DitchLightsOff)
    CALL(SwitchModeOff)
    CALL(EngineSoundOff)

  ENDIF // IF(SwRun)

  FOLLOW(MainLoop)
