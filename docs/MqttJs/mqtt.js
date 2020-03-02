// making the connect variables
var mqtt;
var reconnectTimeout=1000;
var host="localhost";
var port=1883;

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
    console.log("connecting to "+host+":"+port);
    //Creating a client object 
    mqtt = new Paho.MQTT.Client(host,port,"clientjs");
    var options = {
        timeout: 3,
        onSuccess: onConnect,
    };
    // connects to the server
    mqtt.connect(options);
}

