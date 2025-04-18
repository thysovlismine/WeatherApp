# Weather App

This is an Application that I had to make for college. The app uses the available [GIOS API](https://powietrze.gios.gov.pl/pjp/content/api) to fetch the data about stations in Poland and their sensors that measure some weird stuff. The app can list all of the stations, their sensors, and specific sensor data presented in a chart. All fetched data is stored in a local JSON database which supports the app with already saved data so that the user can still view data but offline.

### Requirements

Using [vcpkg](https://vcpkg.io/) install:

```
vcpkg install nlohmann-json
vcpkg install cpr
vcpkg install wxwidgets
vcpkg install wxcharts
```

### Compiling

*Tested on Windows and Ubuntu.*

**Replace `@@@VCPKPG_CMAKE_PATH_HERE@@@` with the path to the VCPKG cmake file which can be checked via `vcpkg integrate install`.**
```
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=@@@VCPKPG_CMAKE_PATH_HERE@@@ -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

The compiled app should be in `build/Release/app.exe`. On my Ubuntu, it's straight in `build/app`.

## Documentation

Run:

```
doxygen Doxyfile
```

Visit `html/index.html`.

## Unit Testing

### Requirements

Using [vcpkg](https://vcpkg.io/) install:

```
vcpkg install gtest
```

Running Tests:

### Compiling

*Tested on Windows.*

**Replace `@@@VCPKPG_CMAKE_PATH_HERE@@@` with the path to the VCPKG cmake file which can be checked via `vcpkg integrate install`.**
```
cd tests
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=@@@VCPKPG_CMAKE_PATH_HERE@@@
cmake "--build" "."
```

### Running

Just run built executables.
