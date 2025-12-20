import joblib
import pandas as pd

# Load trained model
model = joblib.load("chemical_dosage_model.pkl")

# Function to predict chemical dosage
def predict_dosage(pH, turbidity, temperature, tds, pond_volume):
    # Prepare input data
    input_data = pd.DataFrame([[pH, turbidity, temperature, tds, pond_volume]], 
                              columns=["pH", "Turbidity", "Temperature", "TDS", "Volume (Liters)"])
    
    # Predict chemical dosage
    prediction = model.predict(input_data)

    # Convert to readable format
    chemical_dosage = {
        "Alum (mL)": prediction[0][0],
        "Carbon (g)": prediction[0][1],
        "Baking Soda (g)": prediction[0][2],
        "Bleach (mL)": prediction[0][3]
    }
    
    return chemical_dosage

# Example: User enters pond dimensions
length = float(input("Enter pond length in meters: "))
width = float(input("Enter pond width in meters: "))
avg_depth = float(input("Enter average depth in meters: "))

# Calculate pond volume
pond_volume = length * width * avg_depth * 1000
print(f"Estimated Pond Volume: {pond_volume} Liters")

# Example sensor readings (Replace with actual sensor values)
pH_value = 7.2
turbidity_value = 5
temperature_value = 22
tds_value = 250

# Get chemical dosage prediction
dosage_result = predict_dosage(pH_value, turbidity_value, temperature_value, tds_value, pond_volume)

# Display recommendations
print("Recommended Chemical Dosages:")
for chemical, amount in dosage_result.items():
    print(f"{chemical}: {amount:.2f}")
