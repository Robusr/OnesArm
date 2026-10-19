# Firmware

## STM32 (STM32CubeIDE)

| Project | MCU | Intended function | Actual state |
|---|---|---|---|
| `stm32/demo_LED` | STM32F407ZGTx | LED / GPIO demo | CubeMX skeleton, empty user loop |
| `stm32/demo_LED1` | STM32F103C8Tx | LED demo | CubeMX skeleton |
| `stm32/demo_test` | STM32F407ZGTx | GPIO + RTC test | CubeMX skeleton |
| `stm32/Key` | STM32F103C8Tx | Key/LED input | `LED_KEY/keyled.c` has compile errors; `keyled.h` is empty |
| `stm32/KeyLED` | STM32F103C8Tx | Key + LED | Empty user code |
| `stm32/彩色液晶屏驱动...` | STM32F407 | 2.0 inch 240 × 320 LCD driver | Driver project; verify board wiring before use |

HAL CAN is commented out in every generated configuration. No PWM servo, stepper or CAN application code is present. The projects are useful as pin/clock references, **not** as a working arm controller. See `../docs/errata.md` E-11.

## MicroPython

`micropython/` contains:

- `V1.0/ssd1306.py` — SSD1306 OLED driver.
- `Position/l76x.py`, `Position/micropyGPS/` — GNSS parsing libraries and examples.

There is no `main.py`, no servo/CAN driver and no kinematics implementation. The report’s §4.3.1 claim of porting the kinematics to MicroPython is not supported by the archived code.

## Building

- STM32: open the `.ioc` in STM32CubeIDE, regenerate if needed, and build the matching project. Check the linker script and MCU variant.
- MicroPython: copy the relevant library to a Pico W running MicroPython; the GNSS examples expect a UART connection to an L76X module.

## Third-party code

`micropyGPS` ships with its own licence (see `micropython/Position/micropyGPS/LICENSE`). The SSD1306 and L76X files are vendor-style drivers without an explicit licence header; keep their provenance when redistributing.
