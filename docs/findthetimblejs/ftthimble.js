//Makes sure that the web page is fully loaded before it starts working/listening
document.addEventListener("DOMContentLoaded", startupWebPage);

function startupWebPage() {

   // declaring the canvas 
   const cvs = document.getElementById("gameSpace");
   const ctx = cvs.getContext('2d');

   // canvas click event listener
   cvs.addEventListener("click", checkGuess);

   // referencing element/s 
   const restartBtn = document.getElementById("restartBtn");
      // refreshes page when user click on new game button
      restartBtn.addEventListener("click", reset)

   const promptP = document.getElementById("prompt");
   const modelBox = document.getElementsByClassName("container")[0];

   // how big the game is
   const gameroom = 10;

   // storing the location of thimble
   let randtx = 0;
   let randty = 0;

   // counter 
   let guess = 0;

   // dimension **how big a square should be 
   const dim = 62;

   function render() {

      // clear canvas before drawing on it 
      ctx.clearRect(0, 0, cvs.width, cvs.height);

      // The canvas is proportional to the dimension set
      cvs.width = dim * gameroom;
      cvs.height = dim * gameroom;

      return function drawBoard() {

         for (var i = 0; i < gameroom; i++) {
            for (let j = 0; j < gameroom; j++) {
               ctx.strokeStyle = 'rgba(0, 0, 0, 0.7)';
               ctx.beginPath();
               ctx.strokeRect(i * dim, j * dim, dim, dim);
               ctx.closePath();
            }
         }

      };

   }

   function reset() {
      // hides model box, zeros the guess counter and restarts the game
      modelBox.style.visibility = "hidden";
      guess = 0;
      startTimbleGame();
   }

   function getRand(max) {
      return Math.floor(Math.random() * max);
   }

   function checkGuess(event) {

      // storing user mouse coordinates
      let userx = Math.floor(event.offsetX / dim);
      let usery = Math.floor(event.offsetY / dim);

      switch (true) {
         case (Math.abs(randty - usery) + Math.abs(randtx - userx) >= 7):
            //console.log("Freezing");
            ctx.strokeStyle = "blue";
            break;
         case (Math.abs(randty - usery) + Math.abs(randtx - userx) >= 5):
            //console.log("Cold");
            ctx.strokeStyle = "aqua";
            break;
         case (Math.abs(randty - usery) + Math.abs(randtx - userx) >= 3):
            //console.log("Warm");
            ctx.strokeStyle = "orange";
            break;
         case (Math.abs(randty - usery) + Math.abs(randtx - userx) == 0):
            ctx.strokeStyle = "green";
            modelBox.style.visibility = "visible";
            promptP.textContent = `Congratulations, you found the thimble! Failed attempts: ${guess} `;
            break;
         default:
            //console.log("Hot");
            ctx.strokeStyle = "red";
      }
      // making the rectangle go to the center of the square
      ctx.beginPath();
      ctx.strokeRect((userx * dim) + dim / 4, (usery * dim) + dim / 4, dim / 2, dim / 2);
      ctx.closePath();

      guess++;
   }

   function hideThimble() {

      // pure laziness thats what it is. pefection.
      randtx = getRand(gameroom);
      randty = getRand(gameroom);
   }

   function startTimbleGame() {
      hideThimble();
      render()();
   }

   startTimbleGame();
}
      // // console game *** old stuff
      // var gameroom = [];
      // gameroom = new grid(gameroomx, gameroomy);

      // function grid(x, y) {

      //    var grid = [];

      //    for (i = 1; i <= y; i++) {
      //       var row = [];

      //       for (j = 1; j <= x; j++) {
      //          row.push(j)

      //       }
      //       grid.push(row)
      //    }
      //    return grid;
      // }

      // var thimbleplaceholder = " ";

      // for (var i = 0; i < gameroom.length; i++) {
      //    for (var j = 0; j < gameroom[0].length; j++) {
      //       gameroom[j][i] = "#";
      //       console.log(gameroom[j][i]);
      //    }
      // }
      // console.log(randtx, randty);
      // gameroom[randtx][randty] = thimbleplaceholder;

      // where the timble is "cheat"
      // ctx.beginPath();
      // ctx.strokeStyle = "green";
      // making the rectangle go to the center of the square
      // ctx.strokeRect((thimblex * dim) + dim/4, (thimbley * dim) + dim/4, dim/2, dim/2);