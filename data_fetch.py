import firebase_admin
from firebase_admin import credentials, firestore

# Step 1: Initialize Firebase Admin SDK with your service account key
cred = credentials.Certificate('cloud_data.json')  # Provide the path to your JSON file
firebase_admin.initialize_app(cred)


db = firestore.client()

# Step 3: Fetch data from the "detections" collection
def fetch_data():
    detections_ref = db.collection('detections')  # Replace 'detections' with your collection name
    docs = detections_ref.stream()

    # Check if any documents are returned
    if not docs:
        print("No documents found.")
    else:
        print(f"Found {len(list(docs))} documents.")  # Print the number of documents

    # Step 4: Loop through documents and print nested fields
    for doc in docs:
        print(f"Fetching data for doc ID: {doc.id}")  # Print the document ID for debugging

        data = doc.to_dict()
        
        # Debugging: Print the full document data
        print(f"Document Data: {data}")

        # Access the nested fields
        sensor_data = data.get('sensorData', {})
        values = sensor_data.get('values', {})

        # Debugging: Check if nested data exists
        print(f"sensor_data: {sensor_data}")
        print(f"values: {values}")

        # Access specific fields inside 'values' and 'sensorData'
        casualty_count = values.get('casualtyCount', 'N/A')
        distance = values.get('distance', 'N/A')
        is_alive = values.get('isAlive', 'N/A')
        is_dead = values.get('isDead', 'N/A')

        # Print the extracted data
        print(f"ID: {doc.id} | Casualty Count: {casualty_count} | Distance: {distance} | Is Alive: {is_alive} | Is Dead: {is_dead}")

# Step 5: Call fetch_data function
fetch_data()
