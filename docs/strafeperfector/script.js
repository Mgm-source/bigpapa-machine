document.addEventListener("DOMContentLoaded", function () {
    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");
    let averageTime = null;

    let currentStack = [];
    let startKey = null;
    let counter = 0;
    let errorCounter = 0;
    let timedHits = [];

    const dStack = ["d", "a", "click"];
    const aStack = ["a", "d", "click"];
    const wStack = ["w", "s", "click"];
    const sStack = ["s", "w", "click"];

    function captureEvent(event, valid) {
        let correctKey = false;
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.font = '10px Arial';
        if (valid) {

            if (counter === 0) {
                if (event.type == "keydown") startKey = event.key;
            }

            if (startKey) {

                switch (event.key) {
                    case "w": currentStack.push({ "key": event.key, "timeStamp": event.timeStamp });
                        break;
                    case "a": currentStack.push({ "key": event.key, "timeStamp": event.timeStamp });
                        break;
                    case "s": currentStack.push({ "key": event.key, "timeStamp": event.timeStamp });
                        break;
                    case "d": currentStack.push({ "key": event.key, "timeStamp": event.timeStamp });
                        break;
                    default: if (event.type === "click") currentStack.push({ "key": event.type, "timeStamp": event.timeStamp });
                        break;
                }

                switch (startKey) {
                    case "w": correctKey = currentStack[counter].key == wStack[counter];
                        break;
                    case "a": correctKey = currentStack[counter].key == aStack[counter];
                        break;
                    case "s": correctKey = currentStack[counter].key == sStack[counter];
                        break;
                    case "d": correctKey = currentStack[counter].key == dStack[counter];
                        break;
                    default: counter = 3;
                }


            }

            if (currentStack.length > 1) {
                ctx.fillText("Time in Milliseconds : " + (currentStack[counter].timeStamp - currentStack[counter - 1].timeStamp).toFixed(2), 0, 50);
            }

            if (currentStack.length == 3) {

                ctx.fillText("Time in Milliseconds : " + ((currentStack[1].timeStamp - currentStack[0].timeStamp) + (currentStack[2].timeStamp - currentStack[1].timeStamp)).toFixed(2), 0, 60);

                if (correctKey) {
                    timedHits.push(((currentStack[1].timeStamp - currentStack[0].timeStamp) + (currentStack[2].timeStamp - currentStack[1].timeStamp)).toFixed(2));

                    averageTime = timedHits.reduce(function (prev, curr) {
                        return (Number(prev) + Number(curr));
                    }) / timedHits.length;
                }


            }

            if (!correctKey) errorCounter++;

            counter++;

            if (counter > 2 || !correctKey) {
                counter = 0;
                startKey = null;
                currentStack = [];


            }

        }
        if (timedHits.length != 0) ctx.fillText("Average Time in Milliseconds : " + averageTime.toFixed(2), 0, 70);
        ctx.fillText("Number of errors: " + errorCounter, 0, 80);
        ctx.font = '50px Arial';
        correctKey ? ctx.fillStyle = "green" : ctx.fillStyle = "red";
        ctx.fillText((event.type === "click") ? "click" : event.key, canvas.width / 2, canvas.height / 2);
    }

    document.addEventListener("keydown", (event) => {
        const key = event.key.toLowerCase();
        const validkey = (key === "w" || key === "a" || key === "s" || key === "d") ? true : false;
        captureEvent(event, validkey);
    })

    document.addEventListener("click", (event) => {
        captureEvent(event, true);
    })

})

