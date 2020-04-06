//Makes sure that the web page is fully loaded before it starts working/listening
document.addEventListener("DOMContentLoaded",startupWebPage);

function startupWebPage()
{ 
 // declaring the canvas 
 const cvs = document.getElementById("gameSpace");
 const ctx = cvs.getContext("2d");

 var userCoordinate = [];
 var userx = 0;
 var usery = 0;

 var thimbleplaceholder = " ";
 var thimblecheat = "T";

 var UserAnswer = "No response";

 var randtx = 0;
 var randty = 0;

 var gameroom = [];  

 gameroom = new grid(10,10);

 function grid(x, y){

   var grid = [];
  
   for(i=1; i<=y; i++){
      var row = [];
  
      for(j=1; j<=x; j++){
         row.push(j)
  
      }
      grid.push(row)
    }
      return grid;
  }

function getRand(max){

  return Math.floor(Math.random()*max+1);
}

function playPrompt(){

   UserAnswer = prompt("Do you want to play Find The Thimble? Y/N");

  if(UserAnswer.toLocaleUpperCase() === "Y")
  {
    return true;
  }
  else
  {
    return false;
  }
}

function userGuess(){

   userx = prompt("Enter the X-coordinate:");
   usery = prompt("Enter the Y-coordinate:");
   
   userCoordinate.push(userx);
   userCoordinate.push(usery);

   if(gameroom[userx][usery] != thimbleplaceholder) {
      gameroom[userx][usery]= "*";
   }
 
   return userCoordinate
}

function checkGuess(checkx,checky){

    if(gameroom[checkx][checky] == gameroom[randtx][randty]){

      alert("Congratulations you found the Thimble");
      if(playPrompt() == false)
      {
         alert("Quit of the tab then");
      }
      else{
         location.reload();
      }
   }
   else if((randty - checky) >= 7 || (randtx - checkx) >= 7){

      console.log("Freezing");
   }
   else if((randty - checky) >= 5 || (randtx - checkx) >= 5){

      console.log("Cold");
   }
   else if((randty - checky) >= 3 || (randtx - checkx) >= 5){

      console.log("Warm");
   }
   else if((randty - checky) >= 1 || (randtx - checkx) >= 5){

      console.log("Hot");
   }

   console.log(gameroom);
   console.log((randty - checky));
   console.log((randtx - checkx));

}

 function hideThimble()
 {

   for(var i = 0; i< gameroom.length;i++)
   {
      for (var j = 0; j < gameroom[0].length; j++)
      {
         gameroom[j][i] = "#";
         console.log(gameroom[j][i]);
      }
   }
   // pure laziness that what is. 
    var rnd = getRand(10);
    console.log(rnd);
    randtx = rnd;

    var rnd = getRand(10);
    console.log(rnd);
    randty = rnd;

   gameroom[randtx][randty] = thimbleplaceholder;

 }
 function startTimbleGame(){

   if(playPrompt() == true){

   do{

   hideThimble();
   userGuess();
   checkGuess(userCoordinate[0],userCoordinate[1]); 
  } while (playPrompt())
   
 }
}
startTimbleGame();
}