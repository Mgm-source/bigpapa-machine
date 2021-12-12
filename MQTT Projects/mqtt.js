// making the connect variables
let reconnectTimeout=1000;
let mqtt = new Paho.MQTT.Client(HOST,PORT,"clientjs");
const HOST = "localhost";
const PORT = 1883;

function onConnect(){
    // If there's a connection subscribe to the mqtt and send a message
    console.log("connected");
    //mqtt.subscribe("senor1");
    message = new Paho.MQTT.Message("hello World");

     // topic sensor1
   message.destinationName = "sensor1";
  // publish topic sensor1
   mqtt.send(message);

}

function MQTTconnect(){
    // show connection details to the console
    console.log("connecting to "+HOST+":"+PORT);
    //Creating a client object 
    
    let options = {
        timeout: 3,
        onSuccess: onConnect,
    };
    // connects to the server
    mqtt.connect(options);
}

