//Makes sure that the web page is fully loaded before it starts working/listening
document.addEventListener("DOMContentLoaded",startupWebPage);


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

function startupWebPage()
{ 
 // declaring the canvas 
 const cvs = document.getElementById("gameSpace");
 const ctx = cvs.getContext("2d");

 var x,y,guess,randtx,randty,col,row;
 var thimbleplaceholder,thimblecheat,Yesno;

 var  gameroom = grid(10,10)
 
 function draw()
 {
   for(var i = 0; i< gameroom.length;i++)
   {
      for (var j = 0; j < gameroom[0].length; j++)
      {
         gameroom[j, i] = "#";
         console.log(gameroom[j, i]);
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
 draw();
}

