//#define LOCO_NUM 1130
#define LOCO_NUM 852

ALIAS(LocoNum, 3)

// Function numbers that are not loco-specific)

ALIAS(HeadLight, 0)
ALIAS(Horn, 2)

// CV numbers (some are decoder-specific)

ALIAS(CvAcceleration, 3)
ALIAS(CvDeceleration, 4)
ALIAS(CvMasterVolume, 63)

// Sequences

ALIAS(BellIf,          100)
ALIAS(BellOff,         101)
ALIAS(TootTootIf,      102)
ALIAS(EngineSoundIf,   104)
ALIAS(EngineSoundOff,  105)
ALIAS(CoupleSound,     106)
ALIAS(UncoupleSound,   107)

ALIAS(DitchLightsOn,   110)
ALIAS(DitchLightsOff,  111)
ALIAS(SwitchModeOn,    112)
ALIAS(SwitchModeOff,   113)

SEQUENCE(BellIf)
  IF(SwSound)
    FON(1)
  ELSE
    FOFF(1)
  ENDIF
  RETURN

SEQUENCE(BellOff)
  FOFF(1)
  RETURN

SEQUENCE(TootTootIf)
  IF(SwSound)
    FON(2)
    DELAY(200)
    FOFF(2)
    DELAY(200)
    FON(2)
    DELAY(500)
  ENDIF
  FOFF(2)
  RETURN

SEQUENCE(EngineSoundIf)
  IF(SwSound)
    FON(8)
  ELSE
    FOFF(8)
  ENDIF
  RETURN

SEQUENCE(EngineSoundOff)
  FOFF(8)
  RETURN

SEQUENCE(CoupleSound)
#if LOCO_NUM == 852 
  IF(SwSound)
    DELAY(3000)
    FON(3)
    DELAY(2000)
  ENDIF
#elif LOCO_NUM == 1130
  // no sound
#elif LOCO_NUM == 2265
  IF(SwSound)
    DELAY(3000)
    FON(3)
    DELAY(2000)
  ENDIF
#endif
  RETURN

SEQUENCE(UncoupleSound)
#if LOCO_NUM == 852
  IF(SwSound)
    DELAY(3000)
    FOFF(3)
    DELAY(2000)
  ENDIF
#elif LOCO_NUM == 1130
  // no sound
#elif LOCO_NUM == 2265
  IF(SwSound)
    DELAY(3000)
    FOFF(3)
    DELAY(2000)
  ENDIF
#endif
  RETURN

SEQUENCE(DitchLightsOn)
#if LOCO_NUM == 852
  FON(6)
#elif LOCO_NUM == 1130
  FON(6)
#elif LOCO_NUM == 2265
  FON(5)
#endif
  RETURN

SEQUENCE(DitchLightsOff)
#if LOCO_NUM == 852
  FOFF(6)
#elif LOCO_NUM == 1130
  FOFF(6)
#elif LOCO_NUM == 2265
  FOFF(5)
#endif
  RETURN

SEQUENCE(SwitchModeOn)
#if LOCO_NUM == 1130
  FON(12)
#elif LOCO_NUM == 2265
  FON(6)
#endif
  RETURN

SEQUENCE(SwitchModeOff)
#if LOCO_NUM == 1130
  FOFF(12)
#elif LOCO_NUM == 2265
  FOFF(6)
#endif
  RETURN
