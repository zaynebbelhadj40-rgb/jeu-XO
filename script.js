function display() {
    document.getElementById("footer").style.height="300px";
    document.getElementById("vote").hidden = false;
}
function alpha(ch){
    i=0
    let ch1=ch.toLowerCase();
    while(i<ch1.length && (ch1[i]>="a" && ch1[i]<="z" || ch1[i]==" " )){
        i++;
    }
    if(i==ch1.length)
        return true;
    else
        return false;
}
function verifier(){
    
    let nom=document.getElementById("nom").value.trim();
    if(nom.length==0 || (!(alpha(nom)))){
        document.getElementById("erreurNom").innerHTML="saisir le nom s'il vous plaît(Le nom ne contient que des lettres de l'alphabet)<br>"
         return false;}
    document.getElementById("erreurNom").innerHTML="";
    let eng1=document.getElementById("1");
    let eng2=document.getElementById("2");
    let eng3=document.getElementById("3");
    let eng4=document.getElementById("4");
    if(!(eng1.checked || eng2.checked || eng3.checked || eng4.checked)){
        document.getElementById("erreurEnergie").innerHTML="le choix d'une energie est obligatoire <br>";
        return false;
    }
    document.getElementById("erreurEnergie").innerHTML="";
    let acc=document.getElementById("accept");
    if(!(acc.checked)){
        document.getElementById("erreurAccept").innerHTML="Cochez *J'accepte de voter* <br>";
        return false;
    }
    document.getElementById("erreurAccept").innerHTML="";
       
    alert("Vote terminé avec succès")     
    return true;
}
function verif(){
    
    let nom=document.getElementById("nom").value.trim();
    if(nom.length==0 || (!(alpha(nom)))){
        document.getElementById("erreurNom").innerHTML="saisir le nom s'il vous plaît<br>(Le nom ne contient que des lettres de l'alphabet)<br>"
         return false;}
    document.getElementById("erreurNom").innerHTML="";
    let mail=document.getElementById('mail').value;
    if(mail.indexOf("@")==-1 || !(mail.endsWith(".com"))){
       document.getElementById("erreurmail").innerHTML="le Email est de la forme xxxx@yyyy.com<br>"; 
       return false;
    }
    let suj=document.getElementById('sujet').value;
    if(suj.length==0){
        document.getElementById("erreursujet").innerHTML="écrivez de préférence le sujet<br>";
        return false;
    }
    let msg=document.getElementById('message').value;
    if(msg.length==0){
        document.getElementById("erreurmes").innerHTML="écrivez votre message<br>";
        return false;
    }
    return true;
}
function rechercher() {
    let mot = document.getElementById("searchInput").value;
    mot = mot.toLowerCase();
    if (mot === "solaire") {
        window.location.href = "solar.html";
    } 
    else if (mot === "eolien") {
        window.location.href = "wind.html";
    }
    else if (mot === "hydraulique") {
        window.location.href = "water.html";
    }
    else if (mot === "biomasse") {
        window.location.href = "biomasse.html";
    }
    else if(mot === "histoire"){
        window.location.href = "histoire.html";
    }
    else {
        alert("Page non trouvée. Essayez : solaire, éolien, hydraulique, biomasse,histoire");
    }
}