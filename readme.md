
# Plan Kodu

- `WindowMain` - Wybór stacji Pomiarowej.
- `?` - Odczyt parametru danej stacji pomiarowej.

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

# Plan Działania

1. Użytkownik wskazuje {stationId}. (wybrane z listy)
2. Prezentacja wszystkich {paramName} dla tego {stationId}, aby pokazać co stacja potrafi mierzyć
    ```
    [{
        "id": 92,                   //unikalny {sensorId}
        "stationId": 14,            //Taki jak {stationId}
        "param": {
            "paramName": "pył zawieszony PM10",
            "paramFormula": "PM10",
            "paramCode": "PM10",
            "idParam": 3
        }
    }]
    ```
3. Użytkownik wskazuje {sensorId} i ma okno z danymi dotyczącymi pomiaru o takim {sensorId}
    - obliczyć wartości najmniejsze i największe
    - wskazać, kiedy te wartości miały miejsce (data, godzina)
    - obliczyć wartość średnią
    - obliczyć trend (czy dane mają tendencję do wzrostu, czy maleją)
    - Dane pomiarowe należy przedstawić w formie wykresu.
        - Użytkownik powinien mieć możliwość wyboru z jakiego okresu dane mają się pojawić na wykresie.
    ```
    {
        "key": "PM10",
        "values": [
        {
            "date": "2017-03-28 11:00:00",
            "value": 30.3018
        },
        {
            "date": "2017-03-28 12:00:00",
            "value": 27.5946
        }]
    }
    ```

---
## Api info

API: [https://powietrze.gios.gov.pl/pjp/content/api](https://powietrze.gios.gov.pl/pjp/content/api)

Stacje pomiarowe - Usługa sieciowa udostępniająca listę stacji pomiarowych.
```
curl https://api.gios.gov.pl/pjp-api/rest/station/findAll
```

Stanowiska pomiarowe - usługa sieciowa udostępniająca listę stanowisk pomiarowych dostępnych na wybranej stacji pomiarowej.
```
curl https://api.gios.gov.pl/pjp-api/rest/station/sensors/{stationId}
curl https://api.gios.gov.pl/pjp-api/rest/station/sensors/515
```

Dane pomiarowe - usługa sieciowa udostępniająca dane pomiarowe na podstawie podanego identyfikatora stanowiska pomiarowego.
```
curl https://api.gios.gov.pl/pjp-api/rest/data/getData/{sensorId}
curl https://api.gios.gov.pl/pjp-api/rest/data/getData/3497
```


Indeks jakości powietrza - usługa sieciowa udostępniająca indeks jakości powietrza na podstawie podanego identyfikatora stacji pomiarowej.

```
curl https://api.gios.gov.pl/pjp-api/rest/aqindex/getIndex/{stationId}
curl https://api.gios.gov.pl/pjp-api/rest/aqindex/getIndex/52
```