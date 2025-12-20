import time
import board
import busio
import joblib
import pandas as pd
from adafruit_ads1x15.analog_in import AnalogIn
import adafruit_ads1x15.ads1115 as ADS
import firebase_admin
from firebase_admin import credentials, db

# ==== Firebase Setup ====
cred = credentials.Certificate("/home/jinmoyee/Desktop/Jinmoyee/8 sem/main/ustm-phd-a5c2e-firebase-adminsdk-fbsvc-f242297d19.jso")
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://ustm-phd-a5c2e-default-rtdb.firebaseio.com'
})

# ==== Load Model ====
model = joblib.load("chemical_dosage_model.pkl")

# ==== I2C & ADC Setup ====
i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)

# ==== Calibration Constants ====
# pH: Calibrated with lemon juice and tap water
PH_SLOPE = 12.863
PH_INTERCEPT = -17.026

# TDS: Standard calibration
TDS_CALIBRATION_FACTOR = 500  # ppm/V

# ==== Helper Functions ====

def get_average_voltage(channel, samples=50, delay=0.1):
    total = 0
    for _ in range(samples):
        total += channel.voltage
        time.sleep(delay)
    return total / samples

def get_pond_dimensions(pond_id="pona_a"):
    coord_ref = db.reference(f"/closed_polygon_coordinates/{pond_id}")
    data = coord_ref.get()
    if data:
        length = float(data["length"])
        width = float(data["width"])
        depth = float(data["depth"])
        return length, width, depth
    else:
        raise ValueError("Pond data not found in Firebase.")

def predict_dosage(pH, turbidity, temperature, tds, pond_volume):
    input_data = pd.DataFrame([[pH, turbidity, temperature, tds, pond_volume]],
                              columns=["pH", "Turbidity", "Temperature", "TDS", "Volume (Liters)"])
    prediction = model.predict(input_data)
    chemical_dosage = {
        "Alum (mL)": prediction[0][0],
        "Carbon (g)": prediction[0][1],
        "Baking Soda (g)": prediction[0][2],
        "Bleach (mL)": prediction[0][3]
    }
    return chemical_dosage

# ==== Main ====

try:
    # Get pond volume
    length, width, depth = get_pond_dimensions("pona_a")
    pond_volume = length * width * depth * 1000  # m³ to Liters
    print(f"Pond Volume: {pond_volume:.2f} Liters")

    # ==== Read pH Sensor for 5 seconds ====
    print("\nReading pH sensor for 5 seconds...")
    ph_channel = AnalogIn(ads, ADS.P0)
    ph_voltage = get_average_voltage(ph_channel, samples=50, delay=0.1)  # ~5s
    pH_value = PH_SLOPE * ph_voltage + PH_INTERCEPT

    # ==== Read TDS Sensor for 5 seconds ====
    print("Reading TDS sensor for 5 seconds...")
    tds_channel = AnalogIn(ads, ADS.P1)
    tds_voltage = get_average_voltage(tds_channel, samples=50, delay=0.1)  # ~5s
    tds_value = tds_voltage * TDS_CALIBRATION_FACTOR

    # Clamp TDS value
    tds_value = max(0, min(tds_value, 1000))

    # Optional: Replace with real sensors
    turbidity_value = 5       # Dummy value
    temperature_value = 25    # Dummy value

    print(f"\nVoltage (pH): {ph_voltage:.3f} V | Estimated pH: {pH_value:.2f}")
    print(f"Voltage (TDS): {tds_voltage:.3f} V | Estimated TDS: {tds_value:.2f} ppm")

    # ==== Predict and Show Chemical Dosage ====
    dosage_result = predict_dosage(pH_value, turbidity_value, temperature_value, tds_value, pond_volume)

    print("\n=== Recommended Chemical Dosages ===")
    for chemical, amount in dosage_result.items():
        print(f"{chemical}: {amount:.2f}")

except Exception as e:
    print(f"Error: {e}")

