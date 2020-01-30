function createArray(length) {
    var arr = new Array(length || 0),
        i = length;

    if (arguments.length > 1) {
        var args = Array.prototype.slice.call(arguments, 1);
        while(i--) arr[length-1 - i] = createArray.apply(this, args);
    }

    return arr;
}

var x, y, randomthimbleX, randomthimbleY = 0;

        var Guess = 1;

        const thimbleplaceholder = " "; //"thimble"

        const thimbleCheat = "#t";

        const gameroom = new createArray(10,10);

        var Yesno;


for (var i = 0; i < gameroom.length(0); i++) {
        
        for ( var j = 0; j < gameroom.length(1); j++){
                
                gameroom[i,j] = "#";
        }
}
