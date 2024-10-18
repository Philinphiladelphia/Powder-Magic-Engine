## Compliation requirements:

python3 -m pip install meson
python3 -m pip install ninja

```
sudo apt install libluajit-5.1-dev libcurl4-openssl-dev libssl-dev libfftw3-dev zlib1g-dev libsdl2-dev libbz2-dev libjsoncpp-dev libpng-dev
```

Make build dir:
`python3 ~/gunpowder_plot/meson-1.5.1/meson setup builddir`

Build and compile:
```
meson.py setup build-debug
cd build-debug
meson.py compile
```

Run:
`./powder`

Install libs:
cd ..
python3 install_libs.py /home/phil/iceoryx_ws/src/powdertoy_ros_wrapper