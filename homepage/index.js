function ShowButton(buttons, start, stop){
    if(buttons === undefined){
        console.error("Button object undefined");
        return;
    }
    if(start === undefined){
        start = 0;
    }
    if(stop === undefined){
        stop = buttons.length;
    }

    for(let i = start; i < stop; i++){
        buttons[i].classList.add("btn-appear");
    }
    return;
}
function Collapse(element){
    element.classList.toggle("show");
}