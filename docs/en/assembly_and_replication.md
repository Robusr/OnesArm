# Assembly and Replication

## 1. Choose a revision first

Do not mix v1 and v2 parts.

- **v1** — 15 kgf·cm PWM servos, Raspberry Pi Pico W, five module boards, 16P gold-finger interconnect. This is the configuration described in report Chapters 1–4 and the 2024 defence deck.
- **v2** — 42BYGH47 steppers, FLE-42-20 reducers, STM32F103C8T6 CAN modules, STM32F407ZGT6 controller, Controller/Monitor boards, 350 W supply. This is the configuration in report Chapter 5.

The CAD drive folder is named `FLE-42-20_42BYGH27`; the text says 42BYGH47. Confirm the motor before printing a joint housing.

## 2. Tools and materials

- Hex keys (M3/M5), screwdrivers, flush cutters, calipers.
- Soldering station, flux, multimeter, current-limited bench supply.
- 3D printer (SLA for 9400A resin; FDM may be used for fit checks only).
- Sheet-metal laser cutting/bending service; carbon-tube cutting and bonding jig.
- STM32CubeIDE for the STM32 projects; MicroPython for the Pico W libraries.
- MATLAB with Robotics Toolbox for the original kinematics scripts; Python 3 for the verification scripts.

## 3. Fabrication

### 3.1 3D printing

- Use the STEP files in `mechanical/output/3dp/`. The first batch has 17 part types; the reprint batch has 8. Print the joint housings in 9400A resin with the layer normal perpendicular to the T/N sliding face.
- Clean the sliding faces; a rough surface will make the N node bind.
- Check the M3 hole diameter after printing. The report specifies 3 mm diameter, 3 mm depth.

### 3.2 Sheet metal

- 5 mm 5052 aluminium for the long links, short links and base plates.
- Deburr every edge; the carbon tube is bonded into the link, so a burr can start a crack.
- Check that the M5 node holes align before bending. The build list is in `BOM/manufacturing/定做生产.md`.

### 3.3 Carbon tube

- 50 × 46 mm tube, cut to the lengths in `BOM/manufacturing/碳管定做/清单.md`.
- Bond with a structural epoxy; abrade and clean the aluminium and tube surfaces first.
- Keep the tube dry and vented during cure; trapped air can push the link out of alignment.

### 3.4 PCB

- Order from the Gerber archives in `electronics/output/gerber/`. Check the drill and outline layers before paying.
- The v1 boards are 2024-02/03; the v2 Controller/Monitor boards are 2024-07. Do not mix them.
- There is no EDA source; if you need a change, redraw the board from the Gerber/BOM and the photos.

## 4. Mechanical assembly

1. Install the bearings and the drive in the joint housing. Check free rotation before closing the cover.
2. Fit the PCB in its pocket; route the FPC away from the bearing.
3. Slide the N node into the T node, set the selected orientation, insert the M5 screw and tighten.
4. Build the chain from the base upward. Keep the joint axes parallel or perpendicular as required by the chosen assembly code (for example AyCxBy-D).
5. Fit the end effector on the last T/N interface.
6. Mount the base on the platform; fit the four suction cups or bolt the base to the test plate.
7. Check that every joint can reach its limit without pulling a cable.

## 5. Wiring

- v1: 16P gold-finger between modules; 12P FPC and XH 3P inside a module; 3 PWM + 5 LED + selector per joint board.
- v2: CAN daisy chain with TJA1050 transceivers; 350 W supply through XT60; 5 V logic from LM2596.
- Mark pin 1 on every connector. The gold-finger connector is not reverse-polarity protected.
- Add strain relief at the joint; the harness must not carry the joint load.

## 6. Firmware and software

- STM32: open the `.ioc` in STM32CubeIDE, regenerate if needed, and build. The user code is a skeleton; add the PWM/CAN application for your revision.
- Pico W: copy the SSD1306/GNSS libraries from `firmware/micropython/`; write a `main.py` for your own test. No arm-control `main.py` is supplied.
- MATLAB: add `software/matlab/kinematics` to the path and run `AyCxBy_D`. Expect the known issues in `software/README.md`.
- Python verification: `python scripts/verify_theory/report_checks.py` and `python -m unittest discover -s scripts/verify_theory -v`.

## 7. Test procedure

1. **Bench check** — one joint, no load, low speed. Verify direction, limit and current.
2. **Single-module check** — joint + link, no end effector. Check the T/N screw and cable clearance.
3. **Chain check** — assemble the 4-DOF AyCxBy-D configuration. Move slowly through the joint limits.
4. **End-effector check** — gripper open/close, ultrasonic distance, gas-sensor output, pen contact.
5. **Trajectory check** — command a short joint-space trajectory; record the actual joint angles if feedback is available.
6. **Payload check** — only after the actuator margin is resolved; state the load location and reach.

There are no acceptance numbers in the archive. Do not copy a “passed” result from the report; record your own measurements.

## 8. Known issues before you build

- Eq. (3.7) is singular; use standard DH and the verification script, not the printed matrix.
- Joint limits 3/4 differ between the table and MATLAB.
- The “energy” index is a kinematic proxy; `Optimization.m` is unrelated.
- 10 N at 0.45 m is about 4.5 N·m, above one servo’s 1.47 N·m stall torque.
- No EDA source, no arm firmware and no measured data are present.

See [errata](../errata.md) and [verification](../verification.md).
