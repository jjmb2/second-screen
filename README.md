# second-screen

Arduino code and a Python script to display cpu data on an SSD1306 screen. Still in development - expect lots of changes.

## Requirements

- an Arduino wired up to an SSD130 screen
- Arduino IDE
- `Adafruit SSD1306` and `Adafruit GFX Library` installed in the IDE
- Python 3 and pip
- Linux (for now)

## Installing and Running

We run the script with pyserial installed in a venv, but you can also skip steps 3-5 and install the package globally if you prefer.

1. Compile and upload the Arduino sketch to your board.
2. Open `cpuinfo.py` and change the port to whatever your board is on.
3. Run `python3 -m venv .venv`.
4. Run `source .venv/bin/activate`.
5. Run `pip3 install -r requirements.txt`.
6. Run `python3 cpuinfo.py`.

If everything has gone right, you should see your CPU temperature displayed on the screen.

## Contributing

The script has only been tested on Linux, so any contributions to get it working on other OSes are appreciated.
