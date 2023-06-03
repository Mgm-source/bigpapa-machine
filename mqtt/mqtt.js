// making the connect variables
const HOST = "localhost";
const PORT = 9001;

let mqtt = new Paho.MQTT.Client(HOST,PORT,"clientjs");

mqtt.onMessageArrived = recieveMessage;

function recieveMessage(message)
{
    console.log(message.payloadString);
}

function onConnect(){

    console.log("connected");
    message = new Paho.MQTT.Message("hello World");
    mqtt.subscribe("test");
    
    // topic sensor1
     message.destinationName = "test";
     // publish topic sensor1
     mqtt.send(message);

}

function onFailed(){
    console.log("offline");
}

function mqttConn(){
    // show connection details to the console
    console.log("connecting to "+HOST+":"+PORT);
    //Creating a client object 
    
    let options = {
        "onSuccess": onConnect,
        "onFailure": onFailed,
        "userName": "",
        "password": ""
    };
    // connects to the server
    mqtt.connect(options);
}

mqttConn();