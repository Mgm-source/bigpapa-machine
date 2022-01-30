document.addEventListener("DOMContentLoaded",event=>{

    const content = fetch("http://localhost/bigpapa-machine/php/Gamehub/models/home.php?page=leaderboard",{ method : "get"});
    content.then(function(response){
        if(response.ok){
            return response.json();
        }
        throw new Error(`request failed: ${response.status}`);
    }).then( (response)=>{
        console.log(response);
    })

})

