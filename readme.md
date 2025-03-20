
# Requirements

```
vcpkg install nlohmann-json
vcpkg install cpr
vcpkg install wxwidgets
vcpkg install wxcharts
```

# Compiling

Replace `@@@VCPKPG_CMAKE_PATH_HERE@@@` with the path to the VCPKG cmake file which can be checked via `vcpkg integrate install`.
```
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=@@@VCPKPG_CMAKE_PATH_HERE@@@
cmake --build .
```

# Plan Kodu

- `WindowMain` - Wybór stacji Pomiarowej.
- `?` - Odczyt parametru danej stacji pomiarowej.

# Noticed Errors:

- There is a problem when you make a fetch to a wrongly written url
- LineChart seem to also allow to see values in the points that are between values or weirdly around... leading to a unreadable chart when mouse hovers on it.
- JSON values should be parsed via a try/catch method cause reading an int for example from a null value will cause an error (thus may stop a part of a code or a whole).
- App crashes when there is no internet

# Strategy / Approach

- `HttpRequest` should be called by a `Panel` and not by the DBMS. To be clear, DBMS could acctually handle every async thing, but then would come a question of when to update things. So let a `Panel` be the initiator which recieves the response from the server, and gives it to the DBMS to parse it and include in its DB. 


# Plan DB

```
DB structure:

----DB
    |
    |---index.json                  //Info o stacjach
    |
    |---station_$stationId$.json    //Info o sensorach danej stacji
    |
    |---sensor_$stationId$.json     //Dane dotyczące danego sensora, danej konkretnej stacji (stationId is unikatowy)
```
