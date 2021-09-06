document.addEventListener("DOMContentLoaded", function() {
    let colors = ["blue", "red", "plum", "purple", "gold", "yellow", "aqua", "pink"];
    let inputs = document.getElementsByClassName("openinp");
    let inpbtn = document.querySelector(".inpbtn");
    let response = document.querySelector(".response");
    let inp2 = document.querySelector(".inp2");
    let inpbtn2 = document.querySelector(".inpbtn2");
    let intro = document.querySelector(".intro");

    function pageAlert()
    {
        alert("Please endeavour to fill the input fields below. Thank you!");
    }

    function greet()
    {
        if(inputs[0].value != "" && inputs[1].value != "") {
            intro.innerHTML = `<h3>Hello ${inputs[0].value}</h3>
            <p>Hi ${inputs[0].value}, nice to meet you! I'm glad to know this(<b>${inputs[1].value}</b>) about you. I'm sure you
            want to know more about me too, so feel free to explore this page.</p>`;

            intro.style.display = "block";
        }

        inputs[0].value = "";
        inputs[1].value = "";

    }

    setInterval(changeColor,1000);

    function changeColor()
    {
        if(window.getComputedStyle(intro).display === "block")
        {
            let randindex = Math.round(Math.random()*colors.length);
            intro.style.backgroundColor = colors[randindex];
        }
    }

    function game()
    {
        if(inp2.value === "july")
        {
            response.innerText = "Correct!";
            response.style.backgroundColor = "#5cb85c";
        }
        else if(inp2.value === "")
        {
            response.innerText = "Please type an answer!";
            response.style.backgroundColor = "#f0ad4e";
        }
        else
        {
            response.innerText = "Incorrect!";
            response.style.backgroundColor = "#d9534f";
        }

        response.style.display = "block";

        inp2.value = "";

        setTimeout(function() {
            response.style.display = "none";
        }, 1000)
    }

    pageAlert();

    inpbtn.addEventListener("click", greet);

    inpbtn2.addEventListener("click", game);

});








