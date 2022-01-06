// making the connect variables
const HOST = "localhost";
const PORT = 80;

let reconnectTimeout=1000;
let mqtt = new Paho.MQTT.Client(HOST,PORT,"clientjs");

function onConnect(){
    
    console.log("connected");
    message = new Paho.MQTT.Message("hello World");
    
    // topic sensor1
     message.destinationName = "test";
     // publish topic sensor1
     mqtt.send(message);

}

function onFailed(){
    console.log("offline");
}

function MQTTconnect(){
    // show connection details to the console
    console.log("connecting to "+HOST+":"+PORT);
    //Creating a client object 
    
    let options = {
        onSuccess: onConnect,
        onFailure: onFailed,
        userName : "bob1",
        password : "yes"



    };
    // connects to the server
    mqtt.connect(options);
}

