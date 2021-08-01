//Makes sure that the web page is fully loaded before it starts working/listening
document.addEventListener("DOMContentLoaded", startupWebPage);

function startupWebPage() {

         // declaring the canvas 
         const cvs = document.getElementById("gameSpace");
         const ctx = cvs.getContext('2d');
   
         // referencing element/s 
         const restartBtn = document.getElementById("restartBtn");

         var randtx = 0;
         var randty = 0;
      
         // how big the game is
         const gameroom = 10;

         
   function render() {

      // dimension **how big a square should be 
      const dim = 64;

      // storing user mouse coordinates
      let userx = 0;
      let usery = 0;

      // the canvas is as large as the screen
      cvs.width = dim * gameroom;
      cvs.height = dim * gameroom;

      cvs.addEventListener("click", event => {
         userx = Math.floor(event.offsetX / dim);
         usery = Math.floor(event.offsetY / dim);
         checkGuess(userx, usery);

         ctx.beginPath();
         // making the rectangle go to the center of the square
         ctx.strokeRect((userx * dim) + dim/4, (usery * dim) + dim/4, dim/2, dim/2);
         ctx.closePath();
         
      })

      // refreshes page when user click on new game button
      restartBtn.addEventListener("click",()=>{
         startTimbleGame();
      })

      return function drawBoard() {
         for (var i = 0; i < gameroom; i++) {
            for (let j = 0; j < gameroom; j++) {
               ctx.strokeStyle = 'rgba(0, 0, 0, 0.7)';
               ctx.beginPath();
               ctx.strokeRect(i * dim, j * dim, dim, dim);
               ctx.closePath();
            }
         }
         // where the timble is
         // ctx.beginPath();
         // ctx.strokeStyle = "green";
         // // making the rectangle go to the center of the square
         // ctx.strokeRect((thimblex * dim) + dim/4, (thimbley * dim) + dim/4, dim/2, dim/2);


      };

   }

   function getRand(max) {

      return Math.floor(Math.random() * max);
   }

   function checkGuess(checkx, checky) {

      switch (true) {
         case (Math.abs(randty - checky) + Math.abs(randtx - checkx) >= 7):
            console.log("Freezing");
            ctx.strokeStyle = "blue";
            break;
         case (Math.abs(randty - checky) + Math.abs(randtx - checkx) >= 5):
            console.log("Cold");
            ctx.strokeStyle = "aqua";
            break;
         case (Math.abs(randty - checky) + Math.abs(randtx - checkx) >= 3):
            console.log("Warm");
            ctx.strokeStyle = "orange";
            break;
         case (Math.abs(randty - checky) + Math.abs(randtx - checkx) == 0):
            ctx.strokeStyle = "green";
            alert("Congratulations you found the Thimble");
            break;
         default:
            console.log("Hot");
            ctx.strokeStyle = "red";
      }

      console.log((randty - checky));
      console.log((randtx - checkx));

   }

   function hideThimble() {

   // pure laziness thats what it is. 
      randtx = getRand(gameroom);
      randty = getRand(gameroom);

   }

   function startTimbleGame() {
      ctx.clearRect(0, 0, cvs.width, cvs.height);
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