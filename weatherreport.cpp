#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

namespace WeatherSpace
{    
    class IWeatherSensor {
        public:
            virtual double TemperatureInC() const = 0;
            virtual int Precipitation() const = 0;
            virtual int Humidity() const = 0;
            virtual int WindSpeedKMPH() const = 0;
    };
    /// <summary>
    /// This is a stub for a weather sensor. For the sake of testing 
    /// we create a stub that generates weather data and allows us to
    /// test the other parts of this application in isolation
    /// without needing the actual Sensor during development
    /// </summary>
    class SensorStub : public IWeatherSensor {
        int Humidity() const override {
            return 72;
        }

        int Precipitation() const override {
            return 70;
        }

        double TemperatureInC() const override {
            return 26;
        }

        int WindSpeedKMPH() const override {
            return 52;
        }
    };
    class HighPrecipLowWindStub : public IWeatherSensor 
    {
        double TemperatureInC() const override { return 22; }  // mild temp
        int Precipitation() const override { return 80; }      // high precipitation
        int Humidity() const override { return 60; }
        int WindSpeedKMPH() const override { return 10; }      // calm wind
    };

    class HighTempLowPrecipStub : public IWeatherSensor 
    {
        double TemperatureInC() const override { return 30; }  // hot day
        int Precipitation() const override { return 10; }      // low precipitation
        int Humidity() const override { return 40; }
        int WindSpeedKMPH() const override { return 20; }      // normal wind
    };

    class HighWindLowPrecipStub : public IWeatherSensor
    {
        double TemperatureInC() const override { return 28; }  // warm
        int Precipitation() const override { return 15; }      // low precip
        int Humidity() const override { return 50; }
        int WindSpeedKMPH() const override { return 60; }      // strong winds
    };
    // string Report(const IWeatherSensor& sensor)
    // {
    //     int precipitation = sensor.Precipitation();
    //     // precipitation < 20 is a sunny day
    //     string report = "Sunny Day";

    //     if (sensor.TemperatureInC() > 25)
    //     {
    //         if (precipitation >= 20 && precipitation < 60)
    //             report = "Partly Cloudy";
    //         else if (sensor.WindSpeedKMPH() > 50)
    //             report = "Alert, Stormy with heavy rain";
    //     }
    //     return report;
    // }
    string Report(const IWeatherSensor& sensor)
    {
        int precipitation = sensor.Precipitation();
        string report = "Sunny Day";
    
        if (precipitation > 60 && sensor.WindSpeedKMPH() < 50) {
            report = "Rainy";
        }
        else if (sensor.TemperatureInC() > 25) {
            if (precipitation >= 20 && precipitation < 60)
                report = "Partly Cloudy";
            else if (sensor.WindSpeedKMPH() > 50)
                report = "Alert, Stormy with heavy rain";
        }
        return report;
    }
    
    void TestRainy()
    {
        HighPrecipLowWindStub sensor;
        string report = Report(sensor);
        cout << "Rainy test: " << report << endl;
        // Strengthened: must exactly say "Rainy"
        assert(report == "Rainy");  // <-- will FAIL with current implementation
    }

    void TestHighPrecipitation()
    {
        HighPrecipLowWindStub sensor;
        string report = Report(sensor);
        cout << "High precipitation test: " << report << endl;
        assert(report == "Rainy");  // <-- will FAIL
    }

    void TestSunnyDay()
    {
        HighTempLowPrecipStub sensor;
        string report = Report(sensor);
        cout << "Sunny test: " << report << endl;
        assert(report == "Sunny Day"); // <-- might FAIL depending on logic
    }

    void TestStormy()
    {
        HighWindLowPrecipStub sensor;
        string report = Report(sensor);
        cout << "Stormy test: " << report << endl;
        assert(report == "Alert, Stormy with heavy rain"); // <-- may PASS, but exposes the path
    }
}

void testWeatherReport() {
    cout << "\nWeather report test\n";
    WeatherSpace::TestRainy();
    WeatherSpace::TestHighPrecipitation();
    WeatherSpace::TestSunnyDay();
    WeatherSpace::TestStormy();
    cout << "All is well (maybe)\n";
}
