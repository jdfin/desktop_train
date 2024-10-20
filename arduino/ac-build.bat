
arduino-cli compile %1 ^
    --clean ^
    --config-file ./config.yaml ^
    --fqbn %FQBN%

::  --verbose
::  --build-path "%CD%/build"

if "%2" == "" goto :eof

arduino-cli upload %1 -p %2 ^
    --verbose ^
    --config-file ./config.yaml ^
    --fqbn %FQBN%

::  --build-path "%CD%/build"
