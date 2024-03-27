//The sum of the both portions
let result = 0;
//The total player erros
let mistakes = 0;
//The total right answers
let score = 0;
//The timer object
let timerID;
//logs whether the game is running to prevent player exploitation
let is_game_happening = false;

//Sound effects
let right_answer_sound = new Audio("/sounds/RightAnswer.mp3");
let mistake_sound = new Audio("/sounds/Mistake.mp3");
let game_over_sound = new Audio("/sounds/GameOver.mp3");
let start_sound = new Audio ("/sounds/Start.mp3");



function start_game(){

    //Prevent the player clicking really fast and starting the game multiple times
    if (is_game_happening === true){
        return;
    }
    is_game_happening = true;

    //Hide the start button and show the game

    const elements = document.querySelectorAll(".transition");
    for (const element of elements){
        element.classList.add("active");
    }

    document.getElementById("start-game").classList.add("transition");

    //Show health or restarts it if needed
    const health = document.getElementsByClassName("health")[0].children;

    reset(health);
    //Star the timer
    set_timer()

    start_sound.play();


    //Enable the user answer the questions
    const input = document.getElementById("input-box");

    input.addEventListener("keydown", check_keys);
    input.removeAttribute("disabled", "");
    input.focus();

    //Get the result of the math calculation
    result = game();
}

//check the user answer if the user press one of this keys
function check_keys(event){
    let keys = ["Enter", "Return", " "];
    for (let key of keys){
        if(event.key === key){
            check_answer();
        }
    }
}

//Reset the score, mistakes, input box and the hearts when starting a new game
function reset(health){
    document.getElementById("score").innerHTML = 0;
    document.getElementById("input-box").value = "";
    score = 0;
    mistakes = 0;

    for (const heart of health){
        heart.classList.add("have-hp");
    }
}

//Start the timer
function set_timer(){
    const timer_element = document.getElementById("time");
    let minutes = 0;
    let seconds = 0;
    timerID = setInterval(function (){
        seconds++;
        if (seconds >= 60)
        {
            seconds = 0;
            minutes++;
        }
        timer_element.innerHTML = add_zero(minutes) + ":" + add_zero(seconds);
    }, 1000);

}

//Add a extra zero to the timer if the value is less them 10
function add_zero(num){
    if (num < 10){
        num = "0" + num;
    }
    return num;
}

//Get two random numbers less them 100 and return the sum of both
function game(){
    let portion_A_Num = Math.floor(Math.random() * 100);
    let portion_B_Num = Math.floor(Math.random() * 100);

    document.getElementById("portionA").innerHTML = add_zero(portion_A_Num);
    document.getElementById("portionB").innerHTML = add_zero(portion_B_Num);

    //returns the result of the operation
    return portion_B_Num + portion_A_Num;
}

//verify the user input
function check_answer(){
    //prevent player exploit
    if(is_game_happening === false){
        return;
    }

    const input = document.getElementById("input-box");
    let value = parseInt(input.value);

    //if the answer is right, update the score, clean the input box and generate a new question
    if(value === result){
        input.value = "";

        score++;
        document.getElementById("score").innerHTML = score;

        result = game();

        //plays a sound or restarts it if needed
        if (right_answer_sound.paused === false){
            right_answer_sound.currentTime = 0;
        }
        else{
            right_answer_sound.play();
        }

    }
    //else decrease the user health and check if the user still have hearts left
    else{
        const health = document.getElementsByClassName("health")[0].children;
        health[mistakes].classList.remove("have-hp");

        mistakes++;
        if (mistakes >= 3){
            is_game_happening = false
            game_over();
            return;
        }

        //plays a sound or restarts it if needed
        if (mistake_sound.paused === false){
            mistake_sound.currentTime = 0;
        }
        else{
            mistake_sound.play();
        }
    }
}

//Stop the game when the user has no health remaining
function game_over(){

    game_over_sound.play();
    //Hide the submit button and show the start button again
    const buttons = document.querySelectorAll("button.math-btn-style");

    buttons[0].classList.remove("active");
    buttons[1].classList.remove("transition");

    //Disables the user from answering the questions and shows the result that made him lose
    const input = document.getElementById("input-box");

    input.removeEventListener("keydown", check_keys);
    input.setAttribute("disabled", "");
    input.value = result;

    //Stop the timer
    clearInterval(timerID);
}