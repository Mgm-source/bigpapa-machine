
"use scrict";

document.addEventListener("DOMContentLoaded", function () {

    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");
    ctx.font = '24px Arial';
    ctx.fillStyle = "orange";
    ctx.fillText("Strafe to START", canvas.width / 2 - 72, canvas.height / 2);

    const dStack = ["d", "a", "mouseClick"];
    const aStack = ["a", "d", "mouseClick"];
    const wStack = ["w", "s", "mouseClick"];
    const sStack = ["s", "w", "mouseClick"];

    let averageTime = null;

    let currentStack = [];
    let timedHits = [];

    let startKey = null;

    let hits = 0;
    let counter = 0;
    let errorCounter = 0;

    function captureEvent(event, name) {

        let correctKey = false;

        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.font = '10px Arial';
        ctx.fillStyle = "blue";

        if (name) {

            if (counter === 0) {
                if (name !== "mouseClick") startKey = name;
            }

            if (startKey) {

                currentStack.push({ "key": name, "timeStamp": event.timeStamp });

                switch (startKey) {
                    case "w": correctKey = currentStack[counter].key === wStack[counter];
                        break;
                    case "a": correctKey = currentStack[counter].key === aStack[counter];
                        break;
                    case "s": correctKey = currentStack[counter].key === sStack[counter];
                        break;
                    case "d": correctKey = currentStack[counter].key === dStack[counter];
                        break;
                }

            }

            if (correctKey) {

                if (currentStack.length > 1) {
                    ctx.fillText("Time in Milliseconds : " + (currentStack[counter].timeStamp - currentStack[counter - 1].timeStamp).toFixed(2), 0, 50);
                }

                if (currentStack.length === 3) {

                    ctx.fillText("Total Time in Milliseconds : " + ((currentStack[1].timeStamp - currentStack[0].timeStamp) + (currentStack[2].timeStamp - currentStack[1].timeStamp)).toFixed(2), 0, 60);

                    timedHits.push(((currentStack[1].timeStamp - currentStack[0].timeStamp) + (currentStack[2].timeStamp - currentStack[1].timeStamp)).toFixed(2));

                    averageTime = (timedHits.reduce((prev, curr) => Number(prev) + Number(curr)) / timedHits.length).toFixed(2);
                }

            }

            counter++;
            hits++;

        }

        if (!correctKey) {
            errorCounter++;
            counter = 3;
        }


        if (counter > 2) {
            counter = 0;
            startKey = null;
            currentStack = [];

        }

        if (timedHits.length != 0) ctx.fillText("Average Time in Milliseconds : " + averageTime, 0, 70);
        ctx.fillText("Number of errors: " + errorCounter, 0, 80);
        ctx.fillText("Number of tries: " + hits, 0, 90);
        ctx.fillText("Error rate: " + (errorCounter / hits).toFixed(2), 0, 100);

        ctx.font = '25px Arial';
        correctKey ? ctx.fillStyle = "green" : ctx.fillStyle = "red";
        ctx.fillText(name || "Wrong Input: WASD", canvas.width / 2, canvas.height / 2);
    }

    document.addEventListener("mousedown", (event) => {
        console.log(event);
        captureEvent(event, "mouseClick");
        
    });

    document.addEventListener("keydown", (event) => {
        const key = event.key.toLowerCase();
        const validkey = (key === "w" || key === "a" || key === "s" || key === "d") ? key : false;
        console.log(event);
        captureEvent(event, validkey);
    });

});