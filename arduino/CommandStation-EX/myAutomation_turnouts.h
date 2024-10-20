// Exercise the turnouts

AUTOSTART
FOLLOW(MainLoop)
DONE

SEQUENCE(MainLoop)

  IF(SwRun)
    CALL(Throw0)
    CALL(Throw1)
    CALL(Close0)
    CALL(Close1)
  ENDIF

  FOLLOW(MainLoop)
