const content = document.getElementsByClassName("container");
document.addEventListener("DOMContentLoaded",event=>{

    const getcontent = fetch("http://localhost/bigpapa-machine/php/Gamehub/models/home.php?page=leaderboard",{ method : "get"});
    getcontent.then(function(response){
        if(response.ok){
            return response.json();
        }
        throw new Error(`request failed: ${response.status}`);
    }).then( (response)=>{
        console.log(response);
    })

})
