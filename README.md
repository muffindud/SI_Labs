# Laboratory Work No. 1.1

## Required tools:

* platformio

```bash
sudo pacman -S platformio-core
```

## Run commands:

```bash
sudo platformio run --target upload --upload-port /dev/ttyACM0 && 
sudo pio device monitor --port /dev/ttyACM0 
```