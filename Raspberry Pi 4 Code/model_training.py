import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
import joblib

# Example Dataset (Replace with actual data for better accuracy)
data = {
    "pH": [6.5, 7.0, 7.5, 8.0, 6.8, 7.3, 7.8, 7.1, 7.4, 6.9],
    "Turbidity": [2, 4, 6, 8, 5, 7, 9, 3, 5, 4],
    "Temperature": [20, 22, 24, 26, 21, 23, 25, 22, 24, 21],
    "TDS": [100, 200, 300, 400, 250, 350, 450, 150, 275, 225],
    "Volume (Liters)": [5000, 10000, 15000, 20000, 12000, 18000, 22000, 8000, 14000, 10000],  # User-provided volume

    # Output: Chemical Dosages (scaled per 10,000 liters)
    "Alum (mL)": [50, 100, 150, 200, 120, 180, 220, 80, 140, 100],
    "Carbon (g)": [3, 5, 7, 9, 6, 8, 10, 4, 7, 5],
    "Baking Soda (g)": [2, 4, 6, 8, 5, 7, 9, 3, 6, 4],
    "Bleach (mL)": [10, 20, 30, 40, 25, 35, 45, 15, 30, 20]
}

# Convert to DataFrame
df = pd.DataFrame(data)

# Define inputs (X) and outputs (Y)
X = df[["pH", "Turbidity", "Temperature", "TDS", "Volume (Liters)"]]
Y = df[["Alum (mL)", "Carbon (g)", "Baking Soda (g)", "Bleach (mL)"]]

# Split dataset into training & testing (80% train, 20% test)
X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2, random_state=42)

# Train the model using Random Forest Regressor
model = RandomForestRegressor(n_estimators=100, random_state=42)
model.fit(X_train, Y_train)

# Save the trained model
joblib.dump(model, "chemical_dosage_model.pkl")

print("Model trained and saved successfully!")
