document.addEventListener("DOMContentLoaded", function () {
    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");

    let currentStack = [];
    let startKey = null;
    let counter = 0;

    const dStack = ["d", "a", "click"];
    const aStack = ["a", "d", "click"];
    const wStack = ["w", "s", "click"];
    const sStack = ["s", "w", "click"];

    function captureEvent(event, valid) {
        let correctKey = false;

        if (valid) {

            if (counter === 0) {
                if (event.type == "keydown") startKey = event.key;
            }

            if (startKey) {

                switch (event.key) {
                    case "w": currentStack.push(event.key);
                        break;
                    case "a": currentStack.push(event.key);
                        break;
                    case "s": currentStack.push(event.key);
                        break;
                    case "d": currentStack.push(event.key);
                        break;
                    default: if (event.type === "click") currentStack.push(event.type);
                        break;
                }

                switch (startKey) {
                    case "w": correctKey = currentStack[counter] == wStack[counter];
                        break;
                    case "a": correctKey = currentStack[counter] == aStack[counter];
                        break;
                    case "s": correctKey = currentStack[counter] == sStack[counter];
                        break;
                    case "d": correctKey = currentStack[counter] == dStack[counter];
                        break;
                }

            }

            counter++;

            if (counter > 2 || !correctKey) {
                counter = 0;
                startKey = null;
                currentStack = [];

            }

        }

        ctx.clearRect(0, 0, canvas.width, canvas.height);
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

