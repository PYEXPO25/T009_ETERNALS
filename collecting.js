const db = firebase.firestore();
const usersRef = db.collection("users"); // Change "users" to your Firestore collection

usersRef.get().then((querySnapshot) => {
    querySnapshot.forEach((doc) => {
        console.log(doc.id, "=>", doc.data()); // Display data in console
        document.getElementById("output").innerHTML += <p>${JSON.stringify(doc.data())}</p>;
    });
}).catch((error) => {
    console.error("Error fetching data:", error);
});