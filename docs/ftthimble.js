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

function startupWebPage()
{ 
 // declaring the canvas 
 const cvs = document.getElementById("canvas");
 const ctx = cvs.getContext("2d");

 cvs = document.getElementById("scale");

 var x,y,guess,randtx,randty,col,row;
 var thimbleplaceholder,thimblecheat,Yesno;
 
 var  gameroom = grid(10,10)
 
 function draw()
 {
   
 }
}
