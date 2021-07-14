//Makes sure that the web page is fully loaded before it starts working/listening
document.addEventListener("DOMContentLoaded", startupWebPage);

// dimension
const dim = 64;

var userx = 0;
var usery = 0;
var userCoordinate = [];

function startupWebPage() {
   function render() {
      // declaring the canvas 
      const cvs = document.getElementById("gameSpace");
      const ctx = cvs.getContext('2d');
      // the canvas is as large as the screen
      cvs.width = dim * gameroomx
      cvs.height = dim * gameroomy;
      cvs.addEventListener("click", event => {
         userx = Math.floor(event.x / dim);
         usery = Math.floor(event.y / dim);
         checkGuess(userx, usery);
      })

      return function drawBoard(thimblex, thimbley) {
         for (var i = 0; i < gameroomx; i++) {
            for (let j = 0; j < gameroomy; j++) {
               ctx.strokeStyle = 'rgba(0, 0, 0, 0.7)';
               ctx.beginPath();
               ctx.strokeRect(i * dim, j * dim, dim, dim);
               ctx.closePath();
            }
         }
         ctx.beginPath();
         ctx.strokeStyle = "green";
         ctx.strokeRect(thimblex * dim, thimbley * dim, dim / 2, dim / 2);


      };

   }

   var thimbleplaceholder = " ";

   var randtx = 0;
   var randty = 0;

   var gameroom = [];
   var gameroomx = 10;
   var gameroomy = 10;

   gameroom = new grid(gameroomx, gameroomy);

   function grid(x, y) {

      var grid = [];

      for (i = 1; i <= y; i++) {
         var row = [];

         for (j = 1; j <= x; j++) {
            row.push(j)

         }
         grid.push(row)
      }
      return grid;
   }

   function getRand(max) {

      return Math.floor(Math.random() * max);
   }

   function checkGuess(checkx, checky) {

      if (gameroom[checkx][checky] == gameroom[randtx][randty]) {

         alert("Congratulations you found the Thimble");
         location.reload();
      }

      switch (true) {
         case (Math.abs(randty - checky) + Math.abs(randtx - checkx) >= 7):
            console.log("Freezing");
            break;
         case (Math.abs(randty - checky) + Math.abs(randtx - checkx) >= 5):
            console.log("Cold");
            break;
         case (Math.abs(randty - checky) + Math.abs(randtx - checkx) >= 3):
            console.log("Warm");
            break;
         default:
            console.log("Hot");
      }

      console.log(gameroom);
      console.log((randty - checky));
      console.log((randtx - checkx));

   }

   function hideThimble() {

      for (var i = 0; i < gameroom.length; i++) {
         for (var j = 0; j < gameroom[0].length; j++) {
            gameroom[j][i] = "#";
            console.log(gameroom[j][i]);
         }
      }

      // pure laziness thats what it is. 
      randtx = getRand(gameroomx);
      randty = getRand(gameroomy);

      console.log(randtx, randty);
      gameroom[randtx][randty] = thimbleplaceholder;

   }

   function startTimbleGame() {
      hideThimble();
      render()(randtx, randty);
   }
   startTimbleGame();
}