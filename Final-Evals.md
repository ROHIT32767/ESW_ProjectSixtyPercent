# Prana Air PM Sensor:

## General details:
- Power input - `5V`
- Data transfer through Rx and Tx - `3.3V`
- Particle size resolution - `0.3µm`
- Units - `µg/m3`
- Communication type - `UART`

## Configuration types:
- Baud rate - `9600`
- Data bits - `8`
- Stop bit - `1`
- No parity bit

## Pros of this sensor:
- Values of higher sizes include values of lower particle sizes also
- Mean time of failure `>= 30000 hours`
- Working temperature - `-20°C to 70°C`
- Operating humidity - `0 to 90% RH (non-condensing)`
- `PM2.5` readings are given to be strictly calibrated
- Draws less current of `70mA`

<hr>

# Prana Air NDIR CO2 Sensor:

## General details:
- `NDIR` - Non-Dispersive InfraRed
- Measurement range - `0 to 10000 ppm`
- Resolution - `1 ppm`
- Units - `ppm`
- Input voltage - `5V`

## Configuration types:
- Both `PWM` (Pulse Width Modulation - We used this) and `UART` modes of communication exist
- Our code is written such that the sensor is configured to sense between `0` and `2000` as we set cycle length of PWM mode to `1004ms = (2 + 1000 + 2 ms)` (High level cycle + Middle level cycle + Low level cycle lengths)

## Pros of this sensor:
- Sensor has self-calibration cycle every `4 days`
- Zero point of sensor is `400ppm`
- Working temperature - `0°C to 50°C`
- Operating humidity - `0 to 95% RH (non-condensing)`
- Draws less current of `20mA`

<hr>

# Adafruit SGP40 + SHT4x Sensor:

## Working mechanism:
- Uses heater that controls hotplate T-sensors and heater controllers (both analog)
- Uses MOx material that handles analog frontend (data reading)
- System controller (digital) uses data from on-chip memory (digital) and interacts with heater controllers along with the analog frontend to handle signal processing (digital) which interacts with the I2C interface
- Raw measurement is obtained from raw signal `SRAW` which is directly proportional to the logarithm of the resistance of the MOx material
- Takes `30ms` to take one measurement

## General details:
- Units of raw measurement - `µg/m3`
- VOC Index - `No units`
- SCL clock frequency - `400 kHz`
- Working temperature - `-20°C to 55°C`
- Operating humidity - `0 to 90% RH (non-condensing)`
- Input volatge - Both `5V` and `3.3V` are supported
- `3.3V` pin can support upto `100mA`
- I2C bus level voltage limits - `1.7-3.6V`

## Configuration types:
- Communication protocol - `I2C` with address `0x59`
- RAW measurement is provided as a `16-bit` word followed by one `CRC` (Cyclic Redundancy Check) bit
- SRAW is sent to the processing algorithm at a sampling rate of `1Hz`
- I2C supports standard and fast modes with maximum clock frequencies `100 kHz` and `400 kHz` respectively

## Pros of this sensor:
- The digital signal processing also handles humidity compensation
- Voltage regulator is added for the `5V` pin so that any voltage from `3-5V` is safely brought to the appropriate voltage levels
- Working temperature - `-10°C to 50°C`
- Operating humidity - `0 to 90% RH (non-condensing)` including humidity compensation
- Has a self-test for measured values 
- Does not contain materials that are harmful to the environment such as `Pb`, `Cd`, `Hg` and halogens

<hr>

# VOC:

- VOC Index is the state of the reading of the sensor relative to the previous values of the sensor
-  Hence, VOC Index value of `100` denotes average readings and typical gas composition over the past `24` hours. `< 100` shows air quality is better than average and `> 100` shows air quality is worse compared to average

- VOCs can also enter a building via polluted outdoor air.

- Common examples of VOCs include:
    - Benzine, emitted from petroleum
    - Formaldehyde, common in many fabrics, coatings and building materials
    - Acetone, found wallpaper
    - Ethanol, found in paints
    - Butanone, found in paints and other coatings, glues and cleaning products
    - Ethylene glycol, used in industrial solvents, paints and detergents
    - Methylene chloride, used for paint strippers, degreasing, cleaning and manufacturing