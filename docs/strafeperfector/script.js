"use scrict";

document.addEventListener("DOMContentLoaded", function () {

    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");
    ctx.font = '24px Arial';
    ctx.fillStyle = "orange";
    ctx.fillText("Strafe to START", canvas.width / 2 - 72, canvas.height / 2);

    const strafeKeys = {
        "d": ["d", "a", "mousedown"],
        "a": ["a", "d", "mousedown"],
        "w": ["w", "s", "mousedown"],
        "s": ["s", "w", "mousedown"]
    }

    let currentStack = [];
    let timedHits = [];

    let currentKey = null;

    let hits = 0;
    let counter = 0;
    let errorCounter = 0;

    function captureEvent(captureObj) {
        let correctKey = false;

        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.font = '10px Arial';
        ctx.fillStyle = "blue";

        if (counter === 0 || !currentKey) {
            currentStack = [];
            if (strafeKeys[captureObj["key"]]) currentKey = strafeKeys[captureObj["key"]];
        }

        if (currentKey) correctKey = currentKey[counter] === captureObj.key;

        if (correctKey) {
            currentStack.push(captureObj.timeStamp);
            if (currentStack.length > 1) ctx.fillText("Time in Milliseconds : " + (currentStack[counter] - currentStack[counter - 1]).toFixed(2), 0, 50);
            counter++;
        } else {
            counter = 0;
            currentKey = null;
        }

        if (currentStack.length === 3) timedHits.push(((currentStack[1] - currentStack[0]) + (currentStack[2] - currentStack[1])));


        if (timedHits.length !== 0) {
            ctx.fillText("Total Time in Milliseconds : " + timedHits[timedHits.length - 1], 0, 60);
            ctx.fillText("Average Time in Milliseconds : " + (timedHits.reduce((prev, curr) => prev + curr) / timedHits.length).toFixed(2), 0, 70);

        }

        hits++;

        ctx.fillText("Number of errors: " + errorCounter, 0, 80);
        ctx.fillText("Error rate: " + (errorCounter / hits).toFixed(2), 0, 100);

        ctx.font = '25px Arial';
        correctKey ? ctx.fillStyle = "green" : ctx.fillStyle = "red";
        ctx.fillText(captureObj.key || "Wrong Input: WASD", canvas.width / 2, canvas.height / 2);

        if (counter > 2) counter = 0;
        
    }

    document.addEventListener("mousedown", (event) => {
        captureEvent({ "key": event.type, "timeStamp": event.timeStamp });

    });

    document.addEventListener("keydown", (event) => {
        captureEvent({ "key": event.key.toLowerCase(), "timeStamp": event.timeStamp });
    });

});