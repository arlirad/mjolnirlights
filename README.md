# mjolnirlights

Arduino code that I used to make the lights on my ***Halo*** *Mjolnir Powered Assault Armor/Mark V[B]* cosplay work. Utilizes **Adafruit_NeoPixel** to drive those addressable RGB LED strips and features a software debouncing implementation to avoid using a capacitor.

# Technical description

In the lore, each one of those glowy things is a [*shield emitter*](https://www.halopedia.org/Energy_shielding). I assume the same convention for my lights.

Each *emitter* is represented by a `class emitter` which contains:
- `Adafruit_NeoPixel` instance reference,
- Offset on the LED strip,
- Count of LEDs,
- Parameter to reverse the LED order

Such a structure allows having multiple *emitters* on the same pin whilst keeping the code clean. I have segmented LED strips with connectors in order to allow me to actually put on the armor. Whilst physically such strips are not a single strip anymore, electrically and logically they behave as one, thus I will refer to those as single strips.

The emitters are as such:
- `EM_TORSO_FL` - left front torso
- `EM_TORSO_FM` - middle front torso
- `EM_TORSO_FR` - right front torso
- `EM_TORSO_BL` - left back torso
- `EM_TORSO_BM` - middle back torso
- `EM_TORSO_BR` - right back torso
- `EM_TORSO_AL` - left arm
- `EM_TORSO_AR` - right arm
- `EM_TORSO_TL` - left thigh
- `EM_TORSO_TR` - right thigh

Where:
- `EM_TORSO_FL`, `EM_TORSO_FM` and `EM_TORSO_AL` are on strip 0, and there is a connector between `EM_TORSO_FM` and `EM_TORSO_AL`,
- `EM_TORSO_FR`, `EM_TORSO_BL`, `EM_TORSO_BM` and `EM_TORSO_BR` are on strip 1, and there is a connector between `EM_TORSO_FR` and `EM_TORSO_BL`,
- `EM_TORSO_AR` is on strip 2
- `EM_TORSO_TL` is on strip 3, with a connector between it and the Arduino
- `EM_TORSO_TR` is on strip 4, with a connector between it and the Arduino

The Arduino is turned on and off using a simple switch. Furthermore, there is a pin for a button to switch light patterns, code of which utilises software debouncing. Yes, there is a RGB rainbow mode.

# Why the repo?

Why not? Maybe someone finds this code useful.

# Lawyer stuff

*Halo* is a registered trademark of Microsoft or one of its many subsidiaries. This README contains zero Master Chiefs, zero Cortanas, and exactly one bad joke.