
// CamelCase avoids collisions with language keywords (e.g. main).
// DCC-EX uses CamelCase too but looks well-scoped.

//                     -----S6--S7--|
//                    /
//                   T1-----S4--S5--|
//                  /
// ----S0----S1----T0-------S2--S3--|

// Mega 2560 end connector pinout:
//
//             +5V +5V
//              22 23
//     Sensor0  24 25
//              26 27  Sensor1
//     Sensor2  28 29  Sensor3
//     Sensor4  30 31  Sensor5
//     Sensor6  32 33  Sensor7
//              34 35
//              36 37
//              38 39
//      RedPin  40 41  GreenPin
//     BluePin  42 43
//   DON'T USE ~44 45~
//       SwRun ~46 47  SwSound
//     T0Pulse  48 49  T1Pulse
//     T0Close  50 51  T1Close
//     T0Throw  52 53  T1Throw
//             GND GND
//
// Power connector:
//   Sensors (GND, +5V)
//   Switches (GND, +5V)
//   TopLight (GND, maybe +5V)

// Automation, Route, and Sequence IDs (1..32767)
ALIAS(InitTurnouts, 1000)

// Turnout IDs

ALIAS(Turnout0, 1)
ALIAS(Turnout1, 2)

// Pin IDs

              /*22*/               /*23*/
ALIAS(Sensor0,  24)                /*25*/
              /*26*/ ALIAS(Sensor1,  27)
ALIAS(Sensor2,  28)  ALIAS(Sensor3,  29)
ALIAS(Sensor4,  30)  ALIAS(Sensor5,  31)
ALIAS(Sensor6,  32)  ALIAS(Sensor7,  33)
              /*34*/               /*35*/
              /*36*/               /*37*/
              /*38*/               /*39*/
ALIAS(RedPin,   40)  ALIAS(GreenPin, 41)
ALIAS(BluePin,  42)                /*43*/
              /*44*/               /*45*/
ALIAS(SwRun,    46)  ALIAS(SwSound,  47)
ALIAS(T0Pulse,  48)  ALIAS(T1Pulse,  49)
ALIAS(T0Close,  50)  ALIAS(T1Close,  51)
ALIAS(T0Throw,  52)  ALIAS(T1Throw,  53)

// error flag (gpio number-space)
ALIAS(ErrorFlag, 100)

// Other

// With a 500 msec recharge:
// 6 msec is not enough
// 7 msec seems to be barely enough
ALIAS(TurnoutPulse_ms, 50)

// With a 50 msec pulse:
// 300 msec is not enough
// 350 msec seems to be enough
ALIAS(TurnoutRecharge_ms, 500)
