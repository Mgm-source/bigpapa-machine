document.addEventListener("DOMContentLoaded",event=>{
    const content = document.getElementById("content");
    const getcontent = fetch("http://localhost/bigpapa-machine/php/Gamehub/models/home.php?page=leaderboard",{ method : "get"});
    getcontent.then(function(response){
        if(response.ok){
            return response.json();
        }
        throw new Error(`request failed: ${response.status}`);
    }).then( (response)=>{

        console.log(response);

        if(response) {
            
            const frag = document.createDocumentFragment();
            const table = document.createElement("table");
            table.id = "tleaderboard";
    
            //const tfooter = document.createElement("tfoot");
            //const tcell = document.createElement("td");
    
            // should probs make a 2d loop to make the table creation cleaner/neater
            const tHead = document.createElement("thead");
            const trow = document.createElement("tr");
            Object.keys(response[0]).forEach(element => {
                
                const header = document.createElement("td");
                header.textContent = element.toUpperCase();
    
                trow.appendChild(header);
                
            });
    
            tHead.appendChild(trow);
            table.appendChild(tHead);
            
            const tbody= document.createElement("tbody");
            response.forEach(element => {
                const trow = document.createElement("tr");
    
                const name = document.createElement("td");
                name.textContent = element.name;
                const username = document.createElement("td");
                username.textContent = element.username;
                const dur = document.createElement("td");
                dur.textContent = element.duration;
                const score = document.createElement("td");
                score.textContent = element.score;
    
                trow.appendChild(name);
                trow.appendChild(username);
                trow.appendChild(dur);
                trow.appendChild(score);
                tbody.appendChild(trow);
                
            });
    
            table.appendChild(tbody);
            
            frag.appendChild(table);
    
            content.appendChild(frag);
    
            console.log(frag);
            
        }
        
    }).catch(erro=>{
        console.log(erro);
    })

})
